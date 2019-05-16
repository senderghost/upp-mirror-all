struct PackageMode : Moveable<PackageMode> {
	int debug;
	int blitz;

	void Serialize(Stream& s) { s / debug / blitz / blitz; }

	PackageMode() { debug = blitz = Null; }
};

struct TargetMode {
	bool        target_override;
	String      target;
	int         linkmode;
	bool        createmap;
	String      version;
	PackageMode def;
	VectorMap<String, PackageMode> package;

	void        Serialize(Stream& s);

	TargetMode() { def.debug = def.blitz = 0; target_override = false; linkmode = 0; createmap = false; }
};

String NoCr(const char *s);
int CharFilterSlash(int c);

String GetDefaultMethod();
VectorMap<String, String> GetMethodVars(const String& method);

struct MakeBuild {
	virtual void ConsoleShow() = 0; //		ShowConsole();	console.Sync();
	virtual void ConsoleSync() = 0; // console.Sync()
	virtual void ConsoleClear() = 0;
	virtual void SetupDefaultMethod() = 0;
	virtual Vector<String> PickErrors() = 0; //console.PickErrors()
	virtual void BeginBuilding(bool sync_files, bool clear_console) = 0;
	virtual void EndBuilding(bool ok) = 0;
	virtual void ClearErrorEditor() = 0;
	virtual void DoProcessEvents() = 0;
	virtual void ReQualifyCodeBase() = 0;
	virtual void SetErrorEditor() = 0;
	virtual String GetMain() = 0;

	struct TransferFileInfo
	{
		String sourcepath;
		int    filetime;
		int    filesize;
	};

	ArrayMap<String, TransferFileInfo> transferfilecache;
	String       method;
	int          targetmode;
	TargetMode   debug;
	TargetMode   release;
	String       cmdout;
	String       target;
	String       onefile;
	bool         stoponerrors;
	bool         use_target;
	String       mainconfigparam;

	const TargetMode& GetTargetMode();
	Index<String> PackageConfig(const Workspace& wspc, int package, const VectorMap<String, String>& bm,
	                            String mainparam, Host& host, Builder& b, String *target = NULL);
	bool SyncHostFiles(RemoteHost& host);
	One<Host> CreateHost(bool sync_files);
	One<Builder> CreateBuilder(Host *host);
	String OutDir(const Index<String>& cfg, const String& package,
	              const VectorMap<String, String>& bm, bool use_target = false);
	bool BuildPackage(const Workspace& wspc, int pkindex, int pknumber, int pkcount,
	                  String mainparam, String outfile, Vector<String>& linkfile, String& linkopt,
	                  bool link = false);
	void SetHdependDirs();
	Vector<String> GetAllUses(const Workspace& wspc, int f);
	Vector<String> GetAllLibraries(const Workspace& wspc, int index,
	                               const VectorMap<String, String>& bm, String mainparam,
	                               Host& host, Builder& builder);
	bool Build(const Workspace& wspc, String mainparam, String outfile, bool clear_console = true);
	bool Build();
	void CleanPackage(const Workspace& wspc, int package);
	void RebuildAll();
	void Clean();
	void SaveMakeFile(const String& fn, bool exporting);
	
	MakeBuild();
};

extern bool output_per_assembly;
