#include "OleDB.h"

#define LLOG(x)

#if defined(PLATFORM_WIN32) && defined(COMPILER_MSC)

NAMESPACE_UPP

// #define BYREF // This was not success, maybe later?

#define LTIMING(x) // RTIMING(x)

typedef ULONG DBLENGTH;
typedef LONG  DBROWCOUNT;

typedef Value (*OutBindProc)(const DBBINDING& binding, const byte *data);
typedef void (*InBindProc)(const DBBINDING& binding, byte *data, const Value& value);

static WString GetErrorText(IRef<IErrorInfo> err)
{
	OleBstr bstr;
	WString errtext;
	if(SUCCEEDED(err->GetDescription(bstr.Set())))
		errtext = bstr;
	if(SUCCEEDED(err->GetSource(bstr.Set())))
		errtext << " (" << WString(bstr) << ")";
	return errtext;
}

WString OleDBErrorInfo(HRESULT hr)
{
	IRef<IErrorInfo> err;
	WString errtext;
	if(GetErrorInfo(0, err.Set()) == S_OK && !!err) {
		IRef<IErrorRecords> recerr;
		if(SUCCEEDED(QueryInterface(err, recerr)) && !!recerr) {
			ULONG nrec = 0;
			if(SUCCEEDED(recerr->GetRecordCount(&nrec)))
				for(int i = nrec; --i >= 0;) {
					IRef<IErrorInfo> suberr;
					if(SUCCEEDED(recerr->GetErrorInfo(i, GetUserDefaultLCID(), suberr.Set())) && !!suberr) {
						if(!IsNull(errtext))
							errtext << '\n';
						IRef<ISQLErrorInfo> sqlerr;
						if(SUCCEEDED(recerr->GetCustomErrorObject(i, IID_ISQLErrorInfo, sqlerr.SetUnk())) && !!sqlerr) {
							OleBstr state;
							long error;
							if(SUCCEEDED(sqlerr->GetSQLInfo(state.Set(), &error)))
								errtext << NFormat("%s(%d): ", String(state), error).ToWString();
						}
						errtext << GetErrorText(suberr);
					}
				}
		}
		else
			errtext = GetErrorText(err);
	}
	else
		errtext = NFormat("OleDB(%08x): nezn�m� chyba", hr).ToWString();
	return errtext;
}

void OleDBVerify(HRESULT hr)
{
	if(SUCCEEDED(hr))
		return;
	throw Exc(OleDBErrorInfo(hr).ToString());
}

const char *OleDBParseString(const char *s)
{
	ASSERT(*s == '\'');
	s++;
	while(*s)
		if(*s++ == '\'' && *s++ != '\'')
			return s - 1;
	return NULL;
}

String OleDBParseStringError(const char *s)
{
	String err = "Parse error: unterminated string ";
	int l = strlen(s);
	enum { SAMPLE = 10 };
	if(l <= SAMPLE)
		err.Cat(s, l);
	else {
		err.Cat(s, SAMPLE);
		err.Cat("...");
	}
	return err;
}

/*
String OleDBParseRefError(const char *s)
{
	return NFormat("Parse error: invalid ?%% type specifier '%c'", *s);
}
*/

int OleDBParse(const char *statement, String& out, OleDBConnection *conn, OleDBSession *session)
{
	String cmd;
	int args = 0;
	const char *s = statement;
	while(*s) {
		if(*s == '\'') {
			const char *b = s;
			s = OleDBParseString(b);
			if(!s) {
				if(session)
					session->SetError(OleDBParseStringError(b), statement);
				return -1;
			}
			cmd.Cat(b, s - b);
		}
		else if(*s == '?') {
			++s;
			++args;
			cmd.Cat('?');
/*
			if(*s == '%') {
				OracleRef oraref;
				const char *p = s + 1;
				s = oraref.Parse(p);
				if(!s) {
					if(session)
						session->SetError(String() << "Parse error: invalid ?% type specifier '"
						<< *p << "'", statement);
					return -1;
				}
				conn->SetParam(args - 1, oraref);
			}
*/
		}
		else
			cmd.Cat(*s++);
	}
	out = cmd;
	return args;
}

static void DBInEmpty(const DBBINDING& binding, byte *data, const Value& v)
{
}

static void DBInInt(const DBBINDING& binding, byte *data, const Value& v)
{
	*(int *)(data + binding.obValue) = v;
}

static void DBInDouble(const DBBINDING& binding, byte *data, const Value& v)
{
	*(double *)(data + binding.obValue) = v;
}

static void DBInString(const DBBINDING& binding, byte *data, const Value& v)
{
	String s(v);
	int l = s.GetLength();
	ASSERT(binding.cbMaxLen >= l + 1u);
	memcpy(data + binding.obValue, s, l + 1);
	*(DBLENGTH *)(data + binding.obLength) = l;
}

static void DBInWString(const DBBINDING& binding, byte *data, const Value& v)
{
	WString s(v);
	int l = s.GetLength();
	ASSERT(binding.cbMaxLen >= sizeof(wchar) * (l + 1));
	memcpy(data + binding.obValue, s, sizeof(wchar) * (l + 1));
	*(DBLENGTH *)(data + binding.obLength) = 2 * l;
}

static void DBInTime(const DBBINDING& binding, byte *data, const Value& v)
{
	*(DATE *)(data + binding.obValue) = ToDATE(Time(v));
}

static Value DBOutInt(const DBBINDING& binding, const byte *data)
{
	return *(const int *)(data + binding.obValue);
}

static Value DBOutBool(const DBBINDING& binding, const byte *data)
{
	return *(const byte *)(data + binding.obValue) & 1;
}

static Value DBOutI8(const DBBINDING& binding, const byte *data)
{
	return (double)*(const longlong_t *)(data + binding.obValue);
}

static Value DBOutDouble(const DBBINDING& binding, const byte *data)
{
	return *(const double *)(data + binding.obValue);
}

#ifdef BYREF
static Value DBOutString(const DBBINDING& binding, const byte *data)
{
	return String(*(char **)(data + binding.obValue), *(const DBLENGTH *)(data + binding.obLength));
}

static Value DBOutWString(const DBBINDING& binding, const byte *data)
{
	return WString(*(const wchar **)(data + binding.obValue), *(const DBLENGTH *)(data + binding.obLength) >> 1);
}
#else
static Value DBOutString(const DBBINDING& binding, const byte *data)
{
	return String(data + binding.obValue, *(const DBLENGTH *)(data + binding.obLength));
}

static Value DBOutWString(const DBBINDING& binding, const byte *data)
{
	return WString((const wchar *)(data + binding.obValue), *(const DBLENGTH *)(data + binding.obLength) >> 1);
}
#endif

static Value DBOutTime(const DBBINDING& binding, const byte *data)
{
	return FromDATE(*(const DATE *)(data + binding.obValue));
}

static Value DBOutBytes(const DBBINDING& binding, const byte *data)
{
	String r;
	HRESULT hr;
	BYTE pbBuff[3000];
	ULONG cbRead;
	ISequentialStream* pISequentialStream;
	IUnknown* pIUnknown = *((IUnknown**)(data + binding.obValue));
	pIUnknown->QueryInterface(IID_ISequentialStream, (void**)&pISequentialStream);
	ULONG cbNeeded = 3000;
	do {
	   hr = pISequentialStream->Read(pbBuff, cbNeeded, &cbRead);
	   r.Cat(pbBuff, 3000);
	}
	while (SUCCEEDED(hr) && hr != S_FALSE && cbRead == cbNeeded);
	pISequentialStream->Release();
	pIUnknown->Release();
	return r;
}

/*
static Value DBOutGuid(const DBBINDING& binding, const byte *data)
{
	return *(const Guid *)(data + binding.obValue);
}
*/

static Buffer<DBBINDING> GetRowDataBindings(const DBCOLUMNINFO *col, int count,
                                            Buffer<OutBindProc>& bindproc, int& rowbytes, Array<DBOBJECT>& object)
{
	rowbytes = 0;
	Buffer<DBBINDING> dbbind(count);
	object.Clear();
	bindproc.Alloc(count);
	OutBindProc *ob = bindproc;
	DBBINDING *db = dbbind;
	memset(db, 0, count * sizeof(DBBINDING));
	for(; --count >= 0; col++, db++, ob++) {
		db->iOrdinal = col->iOrdinal;
		db->dwPart = DBPART_STATUS | DBPART_VALUE;
		db->dwMemOwner = DBMEMOWNER_CLIENTOWNED;
		db->eParamIO = DBPARAMIO_NOTPARAM;
		db->obStatus = rowbytes;
		rowbytes += sizeof(DBSTATUS);
		switch(col->wType) {
		case DBTYPE_I1:
		case DBTYPE_I2:
		case DBTYPE_I4:
		case DBTYPE_UI1:
		case DBTYPE_UI2:
			db->wType = DBTYPE_I4;
			db->obValue = rowbytes;
			*ob = &DBOutInt;
			rowbytes += 4;
			break;

		case DBTYPE_BOOL:
			db->wType = DBTYPE_I1;
			db->obValue = rowbytes;
			*ob = &DBOutBool;
			rowbytes += 4;
			break;

		case DBTYPE_UI4:
			db->wType = DBTYPE_UI4;
			db->obValue = rowbytes;
			*ob = &DBOutInt;
			rowbytes += 4;
			break;

		case DBTYPE_UI8:
		case DBTYPE_I8:
			rowbytes = (rowbytes + 7) & -8;
			db->wType = col->wType;
			db->obValue = rowbytes;
			*ob = &DBOutI8;
			rowbytes += 8;
			break;

		case DBTYPE_R4:
		case DBTYPE_R8:
		case DBTYPE_CY:
		case DBTYPE_DECIMAL:
		case DBTYPE_NUMERIC:
		case DBTYPE_VARNUMERIC:
			rowbytes = (rowbytes + 7) & -8;
			db->wType = DBTYPE_R8;
			db->obValue = rowbytes;
			*ob = &DBOutDouble;
			rowbytes += 8;
			break;

		case DBTYPE_DATE:
		case DBTYPE_FILETIME:
		case DBTYPE_DBDATE:
		case DBTYPE_DBTIME:
		case DBTYPE_DBTIMESTAMP:
			rowbytes = (rowbytes + sizeof(DATE) - 1) & -(int)sizeof(DATE);
			db->wType = DBTYPE_DATE;
			db->obValue = rowbytes;
			*ob = &DBOutTime;
			rowbytes += sizeof(DATE);
			break;

#ifdef BYREF
		case DBTYPE_GUID:
		case DBTYPE_STR:
			db->wType = DBTYPE_BYREF|DBTYPE_STR;
			*ob = &DBOutString;
			db->cbMaxLen = col->ulColumnSize + 1;
		byref:
			db->obValue = rowbytes;
			db->dwMemOwner = DBMEMOWNER_PROVIDEROWNED;
			rowbytes += sizeof(void *);
			db->obLength = rowbytes;
			db->dwPart = DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
			rowbytes += sizeof(DBLENGTH);
			db->cbMaxLen = sizeof(void *);
			break;

		case DBTYPE_BYTES:
			if(col->dwFlags & DBCOLUMNFLAGS_ISLONG) {
				db->wType = DBTYPE_IUNKNOWN;
				db->cbMaxLen = sizeof(ISequentialStream*);
				db->pObject = &object.Add();
				db->pObject->iid = IID_ISequentialStream;
				db->pObject->dwFlags = STGM_READ;
				db->obValue = rowbytes;
				rowbytes += sizeof(ISequentialStream*);
				*ob = &DBOutBytes;
		    }
		    else {
				db->wType = DBTYPE_BYREF|DBTYPE_BYTES;
				*ob = &DBOutString;
				db->cbMaxLen = sizeof(void *);
				goto byref;
		    }
		    break;

		case DBTYPE_BSTR:
		case DBTYPE_WSTR:
			db->wType = DBTYPE_BYREF|DBTYPE_WSTR;
			*ob = &DBOutWString;
			db->cbMaxLen = sizeof(OLECHAR) * (col->ulColumnSize + 1);
			goto byref;

#else
		case DBTYPE_BYTES:
			if(col->dwFlags & DBCOLUMNFLAGS_ISLONG) {
				db->wType = DBTYPE_IUNKNOWN;
				db->cbMaxLen = sizeof(ISequentialStream*);
				db->pObject = &object.Add();
				db->pObject->iid = IID_ISequentialStream;
				db->pObject->dwFlags = STGM_READ;
				db->obValue = rowbytes;
				rowbytes += sizeof(ISequentialStream*);
				*ob = &DBOutBytes;
		    }
		    else {
				db->wType = DBTYPE_BYTES;
				db->obValue = rowbytes;
				*ob = &DBOutString;
				db->cbMaxLen = min<int>(col->ulColumnSize, 10000000);
				rowbytes += (db->cbMaxLen + 1 + 3) & -4;
				db->obLength = rowbytes;
				db->dwPart = DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
				rowbytes += sizeof(DBLENGTH);
		    }
			break;

		case DBTYPE_STR:
		case DBTYPE_GUID:
			db->wType = DBTYPE_STR;
			db->obValue = rowbytes;
			*ob = &DBOutString;
			db->cbMaxLen = min<unsigned>(col->ulColumnSize, 1000000) + 1;
			rowbytes += (db->cbMaxLen + 1 + 3) & -4;
			db->obLength = rowbytes;
			db->dwPart = DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
			rowbytes += sizeof(DBLENGTH);
			break;

		case DBTYPE_BSTR:
		case DBTYPE_WSTR:
			db->wType = DBTYPE_WSTR;
			db->obValue = rowbytes;
			db->cbMaxLen = sizeof(OLECHAR) * (min<unsigned>(col->ulColumnSize, 1000000) + 1);
			*ob = &DBOutWString;
			rowbytes += (db->cbMaxLen + 3) & -4;
			db->obLength = rowbytes;
			db->dwPart = DBPART_VALUE | DBPART_LENGTH | DBPART_STATUS;
			rowbytes += sizeof(DBLENGTH);
			break;
#endif
/*
		case DBTYPE_GUID:
			rowbytes = (rowbytes + 7) & -8;
			db->wType = DBTYPE_GUID;
			db->obValue = rowbytes;
			*ob = &DBOutGuid;
			rowbytes += sizeof(GUID);
			break;
*/
		default:
			throw Exc(NFormat("column[%d] has invalid type %d", (int)col->iOrdinal, (int)col->wType));
		}
	}

	rowbytes = (rowbytes + 7) & -8;
	return dbbind;
}

Vector<Value> GetRowData(const byte *buffer, const DBBINDING *dbbind, const OutBindProc *bindprocs, int count)
{
	Vector<Value> out;
	out.SetCount(count);
	for(Value *op = out.Begin(); --count >= 0; op++, dbbind++, bindprocs++)
		switch(*(const dword *)(buffer + dbbind->obStatus)) {
		case DBSTATUS_S_ISNULL:
			break;
		case DBSTATUS_S_OK: {
//				LTIMING("GetRowData/bindproc");
				*op = (*bindprocs)(*dbbind, buffer);
			}
			break;
		default:
			*op = ErrorValue(NFormat("column[%d]: %d", (int)dbbind->iOrdinal,
				(int)*(const dword *)(buffer + dbbind->obStatus)));
			break;
		}
	return out;
}

class OleDBConnection : public Link<OleDBConnection>, public SqlConnection
{
public:
	OleDBConnection(OleDBSession *session);
	virtual ~OleDBConnection();

	void                    Clear();

	virtual void            SetParam(int i, const Value& r);
	virtual bool            Execute();
	virtual int             GetRowsProcessed() const;
	virtual bool            Fetch();
	virtual void            GetColumn(int i, Ref r) const;
	virtual void            Cancel();
	virtual SqlSession&     GetSession() const { ASSERT(session); return *session; }
	virtual String          GetUser() const    { ASSERT(session); return session->user; }
	virtual String          ToString() const;
	virtual Value           GetInsertedId() const;

	void                    Execute(IRef<IRowset> rowset);

private:
	bool                    TryExecute();
	void                    TryPrefetch();
	void                    ClearArgs();
	void                    SyncArgs();

private:
	OleDBSession           *session;

	struct Param {
		Param() : vtype(VOID_V), alloc(0), bindproc(&DBInEmpty) {}

		int        vtype;
		int        alloc;
		Value      value;
		InBindProc bindproc;
	};

	IRef<ICommand>          cmd;
	IRef<ICommandText>      cmd_text;
	IRef<ICommandPrepare>   cmd_prepare;
	IRef<IAccessor>         cmd_accessor;
	HACCESSOR               cmd_haccessor;
	Array<Param>            cmd_param;
	Buffer<DBBINDING>       cmd_bindings;
	Buffer<byte>            cmd_argbuffer;

	IRef<IRowset>           fetch_rowset;
	IRef<IAccessor>         fetch_accessor;
	HACCESSOR               fetch_haccessor;
	Buffer<OutBindProc>     fetch_bindprocs;
	Buffer<DBBINDING>       fetch_bindings;
	Buffer<byte>            fetch_rowbuffer;
	Buffer<HROW>            fetch_hrows;
	int                     fetch_rowbytes;
	int                     fetch_chunk;
	Vector< Vector<Value> > prefetch;
	Vector<Value>           current_row;
	DBROWCOUNT              fetch_rowcount;
	bool                    fetch_eof;
	String                  last_insert_table;
	Array<DBOBJECT>         object;

	enum {
		MAX_FETCH_ROWS = 100,
		MAX_FETCH_BYTES = 100000,
	};
};

OleDBConnection::OleDBConnection(OleDBSession *session_)
: session(session_)
{
	if(session)
		LinkAfter(&session->clink);
	fetch_haccessor = 0;
	cmd_haccessor = 0;
}

OleDBConnection::~OleDBConnection()
{
	if(session)
		Unlink();
}

Value OleDBConnection::GetInsertedId() const
{
	Sql sql(GetSession());
	return last_insert_table.GetCount() ? sql.Select("IDENT_CURRENT('" + last_insert_table + "')")
	                                    : sql.Select("@@IDENTITY");
}

void OleDBConnection::Clear()
{
	Cancel();
	cmd_param.Clear();
	cmd.Clear();
	cmd_text.Clear();
	cmd_prepare.Clear();
	cmd_accessor.Clear();
//	ClearArgs();
//	cmd_param.Clear();
//	fetch_rowset.Clear();
//	cmd.Clear();
//	cmd_text.Clear();
//	cmd_prepare.Clear();
//	cmd_accessor.Clear();
	session = NULL;
}

void OleDBConnection::SetParam(int i, const Value& r)
{
	if(i >= cmd_param.GetCount())
		ClearArgs();
	Param& par = cmd_param.At(i);
	par.value = r;
	if(IsNull(r)) {
		if(cmd_haccessor)
			*(dword *)(cmd_argbuffer + cmd_bindings[i].obStatus) = DBSTATUS_S_ISNULL;
	}
	else {
		int l;
		switch(r.GetType()) {
		case BOOL_V:
		case INT_V:
			if(par.vtype != INT_V && par.vtype != DOUBLE_V) {
				ClearArgs();
				par.vtype = INT_V;
				par.bindproc = &DBInInt;
			}
			break;

		case DOUBLE_V:
			if(par.vtype != DOUBLE_V) {
				ClearArgs();
				par.vtype = DOUBLE_V;
				par.bindproc = &DBInDouble;
			}
			break;
		
		case SQLRAW_V:
			l = String(SqlRaw(r)).GetLength();
			if(par.vtype != SQLRAW_V || par.alloc < l) {
				ClearArgs();
				par.vtype = SQLRAW_V;
				par.alloc = max(2 * l, 32);
				par.bindproc = &DBInString;
			}
			break;

		case STRING_V:
			l = String(r).GetLength();
			if(par.vtype != STRING_V && par.vtype != WSTRING_V || par.alloc < l) {
				ClearArgs();
				par.vtype = STRING_V;
				par.alloc = max(2 * l, 32);
				par.bindproc = &DBInString;
			}
			break;

		case WSTRING_V:
			l = WString(r).GetLength();
			if(par.vtype != WSTRING_V || par.alloc < l) {
				ClearArgs();
				par.vtype = WSTRING_V;
				par.alloc = max(2 * l, 32);
				par.bindproc = &DBInWString;
			}
			break;
		
		case DATE_V:
		case TIME_V:
			if(par.vtype != TIME_V) {
				ClearArgs();
				par.vtype = TIME_V;
				par.bindproc = &DBInTime;
			}
			break;

		default:
			NEVER();
			break;
		}
		if(cmd_haccessor) {
			const DBBINDING& binding = cmd_bindings[i];
			*(dword *)(cmd_argbuffer + binding.obStatus) = DBSTATUS_S_OK;
			par.bindproc(binding, cmd_argbuffer, r);
		}
	}
}

bool OleDBConnection::Execute()
{
	try {
		// There seems to be a problem in MSSQL with "select @@IDENTITY" nested in another select
		// "select IDENTITIY_CURRENT('tablename') works, thus this ugly workaround
		last_insert_table.Clear();
		CParser p(statement);
		if((p.Id("insert") || p.Id("INSERT")) && (p.Id("into") || p.Id("INTO")) && p.IsId())
			last_insert_table = p.ReadId();
		return TryExecute();
	}
	catch(Exc e) {
		if(session)
			session->SetError("Execute(OleDB): " + e, statement);
		Cancel();
		cmd.Clear();
		return false;
	}
}

bool OleDBConnection::TryExecute()
{
//	session->PreExec();
//	if(t)
//		*t << statement << "\n";
	int args = 0;
	if(!session) {
		LLOG("OleDB Execute: invalid cursor (zombie state)");
		return false; // zombie state or closed session
	}
	if(!session->dbsession)
		throw Exc("session is closed");
	if(parse)
		Cancel();
	if(!cmd) {
		OleDBVerify(session->dbsession->CreateCommand(NULL, cmd.GetIID(), cmd.SetUnk()));
		OleDBVerify(QueryInterface(cmd, cmd_text));
		OleDBVerify(QueryInterface(cmd, cmd_accessor));
		QueryInterface(cmd, cmd_prepare);
		parse = true;
	}
	if(parse) {
		String rawcmd;
		args = OleDBParse(statement, rawcmd, this, session);
		OleDBVerify(cmd_text->SetCommandText(session->dialect, ~OleBstr(rawcmd)));
		if(!!cmd_prepare)
			OleDBVerify(cmd_prepare->Prepare(0));
		if(cmd_param.GetCount() != args) {
			ClearArgs();
			cmd_param.SetCount(args);
		}
	}
	int time = msecs();
	DBPARAMS params;
	params.pData = 0;
	params.cParamSets = 0;
	params.hAccessor = 0;
	if(!cmd_param.IsEmpty()) {
		if(!cmd_haccessor)
			SyncArgs();
		params.pData = cmd_argbuffer;
		params.cParamSets = 1;
		params.hAccessor = cmd_haccessor;
	}
	IRef<IRowset> frowset;
	OleDBVerify(cmd->Execute(NULL, frowset.GetIID(), &params, &fetch_rowcount, frowset.SetUnk()));
	Stream *t = session->GetTrace();
	if(t && session->IsTraceTime())
		*t << NFormat("----- %s exec %d ms:\n", ToString(), msecs(time));

//	if(!dynamic_param.IsEmpty()) {
//		dynamic_pos = -1;
//		for(int i = 0; i < dynamic_param.GetCount(); i++)
//			param[dynamic_param[i]].DynaFlush();
//		dynamic_rows = param[dynamic_param[0]].dynamic.GetCount();
//	}

	if(parse && !!frowset)
		Execute(frowset);
	else {
		fetch_rowset = frowset;
		fetch_rowcount = 0;
	}
	fetch_eof = info.IsEmpty();
//	session->PostExec();
	return true;
}

void OleDBConnection::Execute(IRef<IRowset> rowset)
{
	fetch_rowset = rowset;
	fetch_eof = false;
	fetch_rowcount = 0;

	OleBuffer<DBCOLUMNINFO> columns;
	OleBuffer<OLECHAR> names;
	ULONG fetchcols;
	IRef<IColumnsInfo> cinfo(~fetch_rowset);
	OleDBVerify(cinfo->GetColumnInfo(&fetchcols, columns.Set(), names.Set()));
	info.SetCount(fetchcols);
	for(int i = 0; i < (int)fetchcols; i++) {
		SqlColumnInfo& colinfo = info[i];
		const DBCOLUMNINFO& dbci = columns[i];
		colinfo.name = WString((const wchar *)dbci.pwszName).ToString();
		colinfo.precision = (dbci.bPrecision == (byte)~0 ? int(Null) : dbci.bPrecision);
		colinfo.scale = (dbci.bScale == (byte)~0 ? int(Null) : dbci.bScale);
		colinfo.width = dbci.ulColumnSize;
		switch(dbci.wType) {
		case DBTYPE_I1: case DBTYPE_I2: case DBTYPE_I4:
		case DBTYPE_UI1: case DBTYPE_UI2: case DBTYPE_UI4:
		case DBTYPE_BOOL:
			colinfo.type = INT_V;
			break;

		case DBTYPE_UI8: case DBTYPE_I8:
		case DBTYPE_R4: case DBTYPE_R8:
		case DBTYPE_CY:
		case DBTYPE_DECIMAL:
		case DBTYPE_NUMERIC:
		case DBTYPE_VARNUMERIC:
			colinfo.type = DOUBLE_V;
			break;

		case DBTYPE_DATE: case DBTYPE_FILETIME:
		case DBTYPE_DBDATE: case DBTYPE_DBTIME:
		case DBTYPE_DBTIMESTAMP:
			colinfo.type = TIME_V;
			break;

		case DBTYPE_BYTES:
		case DBTYPE_STR:
		case DBTYPE_BSTR:
		case DBTYPE_WSTR:
		case DBTYPE_GUID:
			colinfo.type = STRING_V;
			break;

		default:
			colinfo.type = UNKNOWN_V;
			break;
		}
	}
	fetch_bindings = GetRowDataBindings(columns, fetchcols, fetch_bindprocs, fetch_rowbytes, object);
	fetch_chunk = minmax<int>(MAX_FETCH_BYTES / (fetch_rowbytes + 1), 1, MAX_FETCH_ROWS);
	fetch_rowbuffer.Alloc(fetch_rowbytes);
	fetch_hrows.Alloc(fetch_chunk);
	OleDBVerify(QueryInterface(fetch_rowset, fetch_accessor));
	OleDBVerify(fetch_accessor->CreateAccessor(DBACCESSOR_ROWDATA, fetchcols,
		fetch_bindings, fetch_rowbytes, &fetch_haccessor, NULL));
}

int OleDBConnection::GetRowsProcessed() const
{
	return fetch_rowcount;
}

bool OleDBConnection::Fetch()
{
	LTIMING("OleDBConnection::Fetch");
	if(fetch_eof)
		return false;
	ASSERT(!!fetch_rowset);
	current_row.Clear();
	if(prefetch.IsEmpty())
		try {
			TryPrefetch();
			if(prefetch.IsEmpty()) {
				fetch_eof = true;
				return false;
			}
		}
		catch(Exc e) {
			session->SetError("Fetch(OleDB): " + e, statement);
			fetch_eof = true;
			return false;
		}
	LTIMING("OleDBConnection::Fetch->scroll");
	current_row = prefetch[0];
	prefetch.Remove(0);
	fetch_rowcount++;
	return true;
}

void OleDBConnection::TryPrefetch()
{
	LTIMING("OleDBConnection::TryPrefetch");
	
	ULONG countrows;
	HROW *prows = fetch_hrows;

	{
		LTIMING("OleDBConnection::TryPrefetch->GetNextRows");
		HRESULT hr;
		if(!fetch_rowset) {
			session->SetError("Fetch(OleDB): execute failed (null rowset)", statement);
			return;
		}
		if(FAILED(hr = fetch_rowset->GetNextRows(DB_NULL_HCHAPTER, 0, fetch_chunk, &countrows, &prows))) {
			session->SetError(("Fetch(OleDB): " + OleDBErrorInfo(hr)).ToString(), statement);
			return;
		}
	}
	if(countrows <= 0)
		return;
	for(unsigned i = 0; i < countrows; i++) {
		{
			LTIMING("OleDBConnection::TryPrefetch->GetData");
			OleDBVerify(fetch_rowset->GetData(fetch_hrows[i], fetch_haccessor, fetch_rowbuffer));
		}
		LTIMING("OleDBConnection::TryPrefetch->GetRowData");
		prefetch.Add() = GetRowData(fetch_rowbuffer, fetch_bindings, fetch_bindprocs, info.GetCount());
	}
	LTIMING("OleDBConnection::TryPrefetch->ReleaseRows");
	OleDBVerify(fetch_rowset->ReleaseRows(countrows, prows, NULL, NULL, NULL));
}

void OleDBConnection::GetColumn(int i, Ref r) const
{
	r.SetValue(current_row[i]);
}

void OleDBConnection::SyncArgs()
{
	ClearArgs();
	int nparam = cmd_param.GetCount();
	if(nparam == 0)
		return;
	cmd_bindings.Alloc(nparam);
	DBBINDING *cb = cmd_bindings;
	memset(cb, 0, sizeof(DBBINDING) * nparam);
	int rowbytes = 0;
	int i;
	for(i = 0; i < nparam; i++, cb++) {
		const Param& par = cmd_param[i];
		cb->iOrdinal = i + 1;
		cb->obStatus = rowbytes;
		cb->dwPart = DBPART_STATUS | DBPART_VALUE;
		cb->dwMemOwner = DBMEMOWNER_CLIENTOWNED;
		cb->eParamIO = DBPARAMIO_INPUT;
		rowbytes += sizeof(dword);
		switch(par.vtype) {
		default:
			NEVER();
		case VOID_V:
			cb->wType = DBTYPE_WSTR;
			cb->dwPart = DBPART_STATUS;
			break;

		case INT_V:
			cb->wType = DBTYPE_I4;
			cb->obValue = rowbytes;
			rowbytes += sizeof(int);
			break;

		case DOUBLE_V:
			cb->wType = DBTYPE_R8;
			rowbytes = (rowbytes + 7) & -8;
			cb->obValue = rowbytes;
			rowbytes += 8;
			break;

		case SQLRAW_V:
			cb->wType = DBTYPE_BYTES;
			cb->dwPart = DBPART_STATUS | DBPART_VALUE | DBPART_LENGTH;
			cb->cbMaxLen = par.alloc + 1;
			cb->obValue = rowbytes;
			rowbytes = (rowbytes + par.alloc + 1 + 3) & -4;
			cb->obLength = rowbytes;
			rowbytes += sizeof(DBLENGTH);
			break;

		case STRING_V:
			cb->wType = DBTYPE_STR;
			cb->dwPart = DBPART_STATUS | DBPART_VALUE | DBPART_LENGTH;
			cb->cbMaxLen = par.alloc + 1;
			cb->obValue = rowbytes;
			rowbytes = (rowbytes + par.alloc + 1 + 3) & -4;
			cb->obLength = rowbytes;
			rowbytes += sizeof(DBLENGTH);
			break;

		case WSTRING_V:
			cb->wType = DBTYPE_WSTR;
			cb->dwPart = DBPART_STATUS | DBPART_VALUE | DBPART_LENGTH;
			cb->cbMaxLen = sizeof(wchar) * (par.alloc + 1);
			cb->obValue = rowbytes;
			rowbytes = (rowbytes + sizeof(wchar) * par.alloc + sizeof(wchar) + 3) & -4;
			cb->obLength = rowbytes;
			rowbytes += sizeof(DBLENGTH);
			break;

		case TIME_V:
			cb->wType = DBTYPE_DATE;
			rowbytes = (rowbytes + 7) & -8;
			cb->obValue = rowbytes;
			rowbytes += sizeof(DATE);
			break;
		}
	}
	cmd_argbuffer.Alloc(rowbytes);
	OleDBVerify(cmd_accessor->CreateAccessor(DBACCESSOR_PARAMETERDATA,
		nparam, cmd_bindings, rowbytes, &cmd_haccessor, NULL));
	cb = cmd_bindings;
	for(i = 0; i < nparam; i++, cb++) {
		const Param& par = cmd_param[i];
		if((*(dword *)(cmd_argbuffer + cb->obStatus)
		= IsNull(par.value) ? DBSTATUS_S_ISNULL : DBSTATUS_S_OK) == DBSTATUS_S_OK)
			par.bindproc(*cb, cmd_argbuffer, par.value);
	}
}

void OleDBConnection::ClearArgs()
{
	if(cmd_haccessor) {
		if(!!cmd_accessor)
			cmd_accessor->ReleaseAccessor(cmd_haccessor, NULL);
		cmd_haccessor = NULL;
		cmd_bindings.Clear();
		cmd_argbuffer.Clear();
	}
}

void OleDBConnection::Cancel()
{
	current_row.Clear();
	prefetch.Clear();
	if(!!cmd)
		cmd->Cancel();

	fetch_rowbuffer.Clear();
	fetch_bindings.Clear();
	fetch_bindprocs.Clear();
	fetch_hrows.Clear();
	if(!!fetch_accessor && !!fetch_haccessor)
		fetch_accessor->ReleaseAccessor(fetch_haccessor, NULL);
	fetch_haccessor = NULL;
	fetch_accessor.Clear();
	fetch_rowset.Clear();
	info.Clear();

	ClearArgs();
}

String OleDBConnection::ToString() const
{
	if(!session)
		return "OleDB zombie connection";
	return NFormat("OleDB[user=%s]", session->user);
}

OleDBSession::OleDBSession()
{
	level = -1;
	Dialect(MSSQL);
}

OleDBSession::~OleDBSession()
{
	Close();
}

Array<OleDBSession::Provider> OleDBSession::EnumProviders()
{
	OleInit();
	Array<OleDBSession::Provider> out;
	try {
		IRef<ISourcesRowset> src(CLSID_OLEDB_ENUMERATOR);
		IRef<IRowset> rowset;
		src->GetSourcesRowset(NULL, IID_IRowset, 0, NULL, rowset.SetUnk());
/*
		IRef<IColumnsInfo> cinfo;
		OleDBVerify(QueryInterface(rowset, cinfo));
		ULONG count;
		OleBuffer<DBCOLUMNINFO> columns;
		OleBuffer<OLECHAR> names;
		OleDBVerify(cinfo->GetColumnInfo(&count, columns.Set(), names.Set()));
		enum { ENAME, EDESC, EGUID, ECOUNT };
		DBCOLUMNINFO fetch_cols[ECOUNT];
		ZeroArray(fetch_cols);
		int i;
		for(i = 0; i < (int)count; i++) {
			WString colname = columns[i].pwszName;
			if(colname == L"SOURCES_NAME")        fetch_cols[ENAME] = columns[i];
			else if(colname == L"SOURCES_DESCRIPTION") fetch_cols[EDESC] = columns[i];
			else if(colname == L"SOURCES_CLSID")       fetch_cols[EGUID] = columns[i];
		}
		for(i = 0; i < ECOUNT; i++)
			if(!fetch_cols[i].pwszName)
				throw Exc("invalid provider enumerator");

		int rowbytes;
		Buffer<OutBindProc> bindprocs;
		Buffer<DBBINDING> bindings = GetRowDataBindings(fetch_cols, ECOUNT, bindprocs, rowbytes);
		Buffer<byte> rowbuffer(rowbytes);

		IRef<IAccessor> accessor;
		OleDBVerify(QueryInterface(rowset, accessor));
		HACCESSOR haccessor;
		OleDBVerify(accessor->CreateAccessor(DBACCESSOR_ROWDATA, ECOUNT, bindings, rowbytes, &haccessor, NULL));

		HROW hrow;
		HROW *prow = &hrow;
		ULONG countrows;
		while(SUCCEEDED(rowset->GetNextRows(DB_NULL_HCHAPTER, 0, 1, &countrows, &prow)) && countrows > 0) {
			OleDBVerify(rowset->GetData(hrow, haccessor, rowbuffer));
			Vector<Value> data = GetRowData(rowbuffer, bindings, bindprocs, ECOUNT);
			OleDBVerify(rowset->ReleaseRows(countrows, prow, NULL, NULL, NULL));
			Provider& provider = out.Add();
			provider.name = data[0];
			provider.description = data[1];
			provider.guid = data[2];
		}

		OleDBVerify(accessor->ReleaseAccessor(haccessor, NULL));
*/
		OleDBSession dummy;
		One<OleDBConnection> conn = new OleDBConnection(&dummy);
		conn->Execute(rowset);
		Sql cursor(-conn);
		int cname = -1, cdesc = -1, cguid = -1;
		for(int i = 0; i < cursor.GetColumns(); i++) {
			String ci = cursor.GetColumnInfo(i).name;
			if(ci == "SOURCES_NAME") cname = i;
			else if(ci == "SOURCES_DESCRIPTION") cdesc = i;
			else if(ci == "SOURCES_CLSID") cguid = i;
		}
		if(cname < 0) throw Exc("SOURCES_NAME column not found");
		if(cdesc < 0) throw Exc("SOURCES_DESCRIPTION column not found");
		if(cguid < 0) throw Exc("SOURCES_CLSID column not found");

		while(cursor.Fetch()) {
			Provider& provider = out.Add();
			provider.name = cursor[cname];
			provider.description = cursor[cdesc];
			provider.guid = cursor[cguid];
		}
	}
	catch(Exc e) {
		LLOG("OleDB::GetProviders->" << e);
	}
	return out;
}

bool OleDBSession::Open(String connect)
{
	const char *b = connect, *p = b;
	while(*p && *p != '/' && *p != '@')
		p++;
	String user(b, p);
	String password;
	if(*p == '/') {
		b = ++p;
		while(*p && *p != '@')
			p++;
		password = String(b, p);
	}
	String provider, datasource;
	if(*p == '@') {
		b = ++p;
		while(*p && *p != '/')
			p++;
		provider = String(b, p);
		if(*p++)
			datasource = p;
	}
	return Open(user, password, datasource, provider);
}

bool OleDBSession::Open(String user, String password, String datasource, String provider)
{
	return OpenProp(NFormat("Provider=%s;Data Source=%s;User ID=%s;Password=%s",
		provider, datasource, user, password));
}

bool OleDBSession::OpenProp(String propset)
{
	Close();
	try {
		OleInit();
		IRef<IDataInitialize> init(CLSID_MSDAINITIALIZE);
		OleDBVerify(init->GetDataSource(NULL, CLSCTX_INPROC_SERVER, ~OleBstr(propset),
			dbinit.GetIID(), dbinit.SetUnk()));
		HRESULT hres = dbinit->Initialize();
		if(FAILED(hres))
			throw Exc(OleDBErrorInfo(hres).ToString());
		IRef<IDBCreateSession> dbcs(~dbinit);
		if(FAILED(hres = dbcs->CreateSession(NULL, dbsession.GetIID(), dbsession.SetUnk())))
			throw Exc(OleDBErrorInfo(hres).ToString());
		QueryInterface(dbsession, transaction);
		QueryInterface(dbsession, transaction_object);
		IRef<IDBProperties> dbprop(~dbinit);
		DBPROPID propid[] = { DBPROP_AUTH_USERID };
		DBPROPIDSET propidset = { propid, 1 };
		propidset.guidPropertySet = DBPROPSET_DBINIT;
		DBPROPSET *propset = NULL;
		ULONG outcount;
		OleDBVerify(dbprop->GetProperties(1, &propidset, &outcount, &propset));
		if(outcount == 1 && propset->cProperties && propset->rgProperties)
			user = ToUpper(String(AsValue(propset->rgProperties->vValue)));
		for(int i = 0; i < (int)outcount; i++) {
			for(int p = 0; p < (int)propset[i].cProperties; p++)
				VariantClear(&propset[i].rgProperties[p].vValue);
			CoTaskMemFree(propset[i].rgProperties);
		}
		CoTaskMemFree(propset);
		dialect = DBGUID_DEFAULT; // todo
		level = 0;
		return true;
	}
	catch(Exc e) {
		SetError(e, "connect");
		dbinit.Clear();
		return false;
	}
}

void OleDBSession::Close()
{
	if(!!dbsession && level > 0) {
		LLOG("OleDBSession::Close->transaction level = " << level);
	}
	while(!clink.IsEmpty()) {
		clink.GetNext()->Clear();
		clink.GetNext()->Unlink();
	}
	user = Null;
	transaction.Clear();
	dbsession.Clear();
	if(!!dbinit && FAILED(dbinit->Uninitialize())) {
		LLOG("OleDBSession::Close error, watch out for leaks!");
	}
	dbinit.Clear();
	level = -1;
}

void OleDBSession::Begin()
{
	level++;
	ULONG tran_level;
	HRESULT hr;
	if(!transaction)
		SetError("Transactions not supported by data source", "StartTransaction(OleDB)");
	else if(!transaction_object && level >= 2)
		SetError("Nested transactions not supported by data source", "StartTransaction(OleDB)");
	else if(FAILED(hr = transaction->StartTransaction(ISOLATIONLEVEL_READCOMMITTED, 0, NULL, &tran_level)))
		SetError(OleDBErrorInfo(hr).ToString(), "StartTransaction(OleDB)");
}

void OleDBSession::Commit()
{
	level--;
	ASSERT(level >= 0);
	try {
		if(!transaction)
			throw Exc("Transactions not supported by data source");
		if(level == 0)
			OleDBVerify(transaction->Commit(false, XACTTC_SYNC, 0));
		else if(!transaction_object)
			throw Exc("Nested transactions not supported by data source");
		else {
			IRef<ITransaction> nested_tran;
			OleDBVerify(transaction_object->GetTransactionObject(1 + level, nested_tran.Set()));
			OleDBVerify(nested_tran->Commit(false, XACTTC_SYNC, 0));
		}
	}
	catch(Exc e) {
		SetError(e, "Commit(OleDB)");
	}
}

void OleDBSession::Rollback()
{
	level--;
	ASSERT(level >= 0);
	try {
		if(!transaction)
			throw Exc("Transactions not supported by data source");
		if(level == 0)
			OleDBVerify(transaction->Abort(NULL, false, false));
		else if(!transaction_object)
			throw Exc("Nested transactions not supported by data source");
		else {
			IRef<ITransaction> nested_tran;
			OleDBVerify(transaction_object->GetTransactionObject(1 + level, nested_tran.Set()));
			OleDBVerify(nested_tran->Abort(NULL, false, false));
		}
	}
	catch(Exc e) {
		SetError(e, "Rollback(OleDB)");
	}
}

String OleDBSession::Savepoint()
{
	SetError("Savepoints not supported in OleDB", "Savepoint");
	return Null;
}

void OleDBSession::RollbackTo(const String& savepoint)
{
	SetError("Savepoints not supported in OleDB", "Rollback to Savepoint");
}

bool OleDBSession::IsOpen() const
{
	return !!dbinit;
}

SqlConnection *OleDBSession::CreateConnection()
{
	return new OleDBConnection(this);
}

Vector<String> OleDBSession::EnumUsers()
{
	Vector<String> out;
	return out;
}

Vector<String> OleDBSession::EnumDatabases()
{
	Vector<String> out;
	IRef<IDBSchemaRowset> srowset;
	if(SUCCEEDED(QueryInterface(dbsession, srowset)) && !!srowset) {
		IRef<IRowset> trowset;
		OleVerify(srowset->GetRowset(NULL, DBSCHEMA_CATALOGS, 0, NULL, trowset.GetIID(), 0, NULL, trowset.SetUnk()));
		One<OleDBConnection> conn = new OleDBConnection(this);
		conn->Execute(trowset);
		Sql cursor(-conn);
		int ccat = -1;
		for(int i = 0; i < cursor.GetColumns(); i++) {
			String n = cursor.GetColumnInfo(i).name;
			if(n == "CATALOG_NAME") ccat = i;
		}
		if(ccat >= 0)
			while(cursor.Fetch())
				out.Add(cursor[ccat]);
	}
	return out;
}

Vector<String> OleDBSession::EnumTables(String database)
{
	Vector<String> out;
	IRef<IDBSchemaRowset> srowset;
	if(SUCCEEDED(QueryInterface(dbsession, srowset)) && !!srowset) {
		OleVariant restrictions[1];
		restrictions[0].vt = VT_BSTR;
		restrictions[0].bstrVal = StringToBSTR(database);
		IRef<IRowset> trowset;
		OleVerify(srowset->GetRowset(NULL, DBSCHEMA_TABLES, 1, restrictions, trowset.GetIID(), 0, NULL, trowset.SetUnk()));
		One<OleDBConnection> conn = new OleDBConnection(this);
		conn->Execute(trowset);
		Sql cursor(-conn);
		int cname = -1;
		int cschema = -1;
		int ctype = -1;
		for(int i = 0; i < cursor.GetColumns(); i++) {
			String n = cursor.GetColumnInfo(i).name;
			if(n == "TABLE_NAME") cname = i;
			else if(n == "TABLE_SCHEMA") cschema = i;
			else if(n == "TABLE_TYPE") ctype = i;
		}
		if(cname >= 0)
			while(cursor.Fetch()) {
				if(ctype >= 0) {
					String t = cursor[ctype];
					if(t == "VIEW" || t == "SYSTEM VIEW")
						continue;
				}
				String t;
				if(cschema >= 0) {
					String s = cursor[cschema];
					if(!IsNull(s) && s != GetUser())
						t << s << '.';
				}
				t << (String)cursor[cname];
				out.Add(t);
			}
	}
	return out;
}

Vector<String> OleDBSession::EnumViews(String database)
{
	Vector<String> out;
	IRef<IDBSchemaRowset> srowset;
	if(SUCCEEDED(QueryInterface(dbsession, srowset)) && !!srowset) {
		OleVariant restrictions[1];
		restrictions[0].vt = VT_BSTR;
		restrictions[0].bstrVal = StringToBSTR(database);
		IRef<IRowset> trowset;
		OleVerify(srowset->GetRowset(NULL, DBSCHEMA_TABLES, 1, restrictions, trowset.GetIID(), 0, NULL, trowset.SetUnk()));
		One<OleDBConnection> conn = new OleDBConnection(this);
		conn->Execute(trowset);
		Sql cursor(-conn);
		int cname = -1;
		int cschema = -1;
		int ctype = -1;
		for(int i = 0; i < cursor.GetColumns(); i++) {
			String n = cursor.GetColumnInfo(i).name;
			if(n == "TABLE_NAME") cname = i;
			else if(n == "TABLE_SCHEMA") cschema = i;
			else if(n == "TABLE_TYPE") ctype = i;
		}
		if(cname >= 0)
			while(cursor.Fetch()) {
				if(ctype >= 0) {
					String t = cursor[ctype];
					if(t != "VIEW" && t != "SYSTEM VIEW")
						continue;
				}
				String t;
				if(cschema >= 0) {
					String s = cursor[cschema];
					if(!IsNull(s) && s != GetUser())
						t << s << '.';
				}
				t << (String)cursor[cname];
				out.Add(t);
			}
	}
	return out;
}

Vector<String> OleDBSession::EnumSequences(String database)
{
	Vector<String> out;
	return out;
}

Vector<String> OleDBSession::EnumPrimaryKeys(String database, String table)
{
	Vector<String> out;
	IRef<IDBSchemaRowset> srowset;
	if(SUCCEEDED(QueryInterface(dbsession, srowset)) && !!srowset) {
		OleVariant restrictions[3];
		restrictions[0].vt = VT_BSTR;
		restrictions[0].bstrVal = StringToBSTR(database);
		restrictions[1].vt = VT_BSTR;
		restrictions[1].bstrVal = StringToBSTR(database);
		restrictions[2].vt = VT_BSTR;
		restrictions[2].bstrVal = StringToBSTR(table);
		IRef<IRowset> trowset;
		OleVerify(srowset->GetRowset(NULL, DBSCHEMA_PRIMARY_KEYS, __countof(restrictions), restrictions,
			trowset.GetIID(), 0, NULL, trowset.SetUnk()));
		One<OleDBConnection> conn = new OleDBConnection(this);
		conn->Execute(trowset);
		Sql cursor(-conn);
		int cname = -1;
		int cord = -1;
		Vector<int> ordinal;
		for(int i = 0; i < cursor.GetColumns(); i++) {
			String n = cursor.GetColumnInfo(i).name;
			if(n == "COLUMN_NAME")
				cname = i;
			else if(n == "ORDINAL")
				cord = i;
		}
		if(cname >= 0)
			while(cursor.Fetch()) {
				out.Add(cursor[cname]);
				if(cord >= 0)
					ordinal.Add(cursor[cord]);
			}
		if(cord >= 0)
			IndexSort(ordinal, out);
	}
	return out;
	return out;
}

String OleDBSession::EnumRowID(String database, String table)
{
	Sql cursor(*this);
	String full_name = database;
	if(!IsNull(full_name)) full_name.Cat('.');
	full_name.Cat(table);
	if(cursor * Select(SqlCol("ROWID")).From(SqlCol(full_name)).Where(SqlBool::False()))
		return "ROWID";
	if(cursor * Select(SqlCol("IDENTITYCOL")).From(SqlCol(full_name)).Where(SqlBool::False())
	&& cursor.GetColumns() >= 1)
		return cursor.GetColumnInfo(0).name;
	return Null;
}

bool OleDBPerformScript(const String& text, StatementExecutor& executor, Gate2<int, int> progress_canceled)
{
	const char *p = text;
	while(*p) {
		String cmd;
		while(*p && *p != ';')
			if(*p == '\'') {
				const char *s = p;
				while(*++p && (*p != '\'' || *++p == '\''))
					;
				cmd.Cat(s, p - s);
			}
			else {
				if(*p > ' ')
					cmd.Cat(*p);
				else if(!cmd.IsEmpty() && *cmd.Last() != ' ')
					cmd.Cat(' ');
				p++;
			}
		if(progress_canceled(p - text.Begin(), text.GetLength()))
			return false;
		if(!IsNull(cmd) && !executor.Execute(cmd))
			return false;
		if(*p == ';')
			p++;
	}
	return true;
}

String OleDBTextType(int width)
{
	if(width <= 4000)
		return NFormat("varchar(%d)", width);
	return "text";
}

END_UPP_NAMESPACE

#endif
