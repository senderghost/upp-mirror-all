#ifndef _PostgreSQL_PostgeSQL_h_
#define _PostgreSQL_PostgeSQL_h_

#ifndef flagNOPOSTGRESQL

#include <Sql/Sql.h>
#ifdef PLATFORM_WIN32
#include <libpq-fe.h>
#elif defined(PLATFORM_POSIX)
#include <postgresql/libpq-fe.h>
#endif

NAMESPACE_UPP

const char *PostgreSQLReadString(const char *s, String& stmt);

bool PostgreSQLPerformScript(const String& text,
#ifdef NOAPPSQL
	StatementExecutor& se,
#else
	StatementExecutor& se = SQLStatementExecutor(),
#endif
	Gate2<int, int> progress_canceled = false
);


String PostgreSQLTextType(int n);

class PostgreSQLSession : public SqlSession {
public:
	virtual bool                  IsOpen() const                   { return conn; }
	virtual RunScript             GetRunScript() const             { return &PostgreSQLPerformScript; }

	virtual Vector<String>        EnumUsers();
	virtual Vector<String>        EnumDatabases();
	virtual Vector<String>        EnumTables(String database);
	virtual Vector<String>        EnumViews(String database);
	virtual Vector<String>        EnumSequences(String database);
	virtual Vector<SqlColumnInfo> EnumColumns(String database, String table);
	virtual Vector<String>        EnumPrimaryKey(String database, String table);
	virtual String                EnumRowID(String database, String table);
	virtual Vector<String>        EnumReservedWords();

protected:
	virtual SqlConnection *CreateConnection();

private:
	PGconn               *conn;

	void                  ExecTrans(const char * statement);
	Vector<String>        EnumData(char type, const char *schema = NULL);
	String                ErrorMessage();

public:
	bool                  Open(const char *connect);
	void                  Close();

	String                GetUser()   { return PQuser(conn); }
	operator PGconn *     ()   { return conn; }

	virtual void          Begin();
	virtual void          Commit();
	virtual void          Rollback();

	PostgreSQLSession()       { conn = NULL; Dialect(PGSQL); }
	~PostgreSQLSession()      { Close(); }
};

class PgSequence : public ValueGen {
	SqlId       ssq;
	SqlId&      seq;
	SqlSession *session;

public:
	virtual Value  Get();

	Value operator++()                                                  { return Get(); }

	void Set(SqlId id, SqlSession& s)                                   { ssq = id; session = &s; }

#ifndef NOAPPSQL
	void Set(SqlId id)                                                  { ssq = id; session = NULL; }
	PgSequence(const char *name) : ssq(name), seq(ssq)                  { session = NULL; }
	PgSequence(SqlId& seq) : seq(seq)                                   { session = NULL; }
#endif
	PgSequence(const char *name, SqlSession& s) : ssq(name), seq(ssq)   { session = &s; }
	PgSequence(SqlId& seq, SqlSession& s) : seq(seq)                    { session = &s; }
	PgSequence() : seq(ssq)                                             { session = NULL; }
};

END_UPP_NAMESPACE

#endif

#endif
