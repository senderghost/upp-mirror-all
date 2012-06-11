#include "Skylark.h"

#define LLOG(x)   DLOG(x)
#define LDUMPC(x) DDUMPC(x)
#define LDUMPM(x) DDUMPM(x)

SessionConfig::SessionConfig()
{
	cookie = "__skylark_session_cookie__";
	dir = ConfigFile("session");
	format = SESSION_FORMAT_BINARY;
	id_column = "ID";
	data_column = "DATA";
	lastwrite_column = "LASTWRITE";
}

String Http::SessionFile(const String& sid)
{
	ONCELOCK
		RealizeDirectory(app.session.dir);
	return AppendFileName(app.session.dir, sid);
}

void Http::LoadSession()
{
	const SessionConfig& cfg = app.session;
	session_var.Clear();
	session_id = (*this)[cfg.cookie];
	if(IsNull(session_id))
		return;
	String data;
	if(cfg.table.IsNull()) {
		data = LoadFile(SessionFile(session_id));
	}
	else {
		String data = SQLR % Select(cfg.data_column).From(cfg.table)
		                     .Where(cfg.id_column == session_id);
	}
	LOGHEX(data);
	switch(cfg.format) {
	case SESSION_FORMAT_JSON:
		LoadFromJson(session_var, data);
		break;
	case SESSION_FORMAT_XML:
		LoadFromXML(session_var, data);
		break;
	case SESSION_FORMAT_BINARY:
		LoadFromString(session_var, data);
		break;
	}
	LLOG("Loaded session: " << session_id);
	LDUMPM(session_var);
	for(int i = 0; i < session_var.GetCount(); i++)
		var.Add(session_var.GetKey(i), session_var[i]);
}

void Http::SaveSession()
{
	DDUMPM(session_var);
	const SessionConfig& cfg = app.session;
	SetCookie(cfg.cookie, session_id);
	if(IsNull(session_id))
		return;
	String data;
	switch(cfg.format) {
	case SESSION_FORMAT_JSON:
		data = StoreAsJson(session_var);
		break;
	case SESSION_FORMAT_XML:
		data = StoreAsXML(session_var, "session");
		break;
	case SESSION_FORMAT_BINARY:
		data = StoreAsString(session_var);
		break;
	}
	if(cfg.table.IsNull())
		SaveFile(SessionFile(session_id), data);
	else {
		SqlVal d = SqlBinary(data);
		Time tm = GetSysTime();
		SQL * Update(cfg.table)
				(cfg.data_column, d)
				(cfg.lastwrite_column, tm)
		      .Where(cfg.id_column == session_id);
		if(SQL.GetRowsProcessed() == 0)
			SQL * Insert(cfg.table)
			        (cfg.id_column, session_id)
					(cfg.data_column, d)
					(cfg.lastwrite_column, tm);
	}
	LLOG("Stored session: " << session_id);
	LDUMPM(session_var);
}

// ToDo: Limit number of session - remove oldest ones

Http& Http::ClearSession()
{
	session_var.Clear();
	session_id.Clear();
	return *this;
}

Http& Http::SessionSet(const char *id, const Value& value)
{
	if(IsNull(session_id))
		session_id = AsString(Uuid::Create());
	session_var.GetAdd(id) = value;
	var.GetAdd(id) = value;
	return *this;
}
