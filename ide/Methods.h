#ifndef _ide_Methods_h_
#define _ide_Methods_h_

#include "ide.h"

class TextSwitch : public Switch {
public:
	virtual void   SetData(const Value& data);
	virtual Value  GetData() const;
};

class DirTable : public ArrayCtrl {
public:
	virtual void   SetData(const Value& data);
	virtual Value  GetData() const;

protected:
	void Modify()  { Update(); }

	EditString      edit;
	SelectDirButton edit_dir;

	void Init(const char *name = NULL);

public:
	DirTable();
	DirTable(const char *name);
};

class DirMap : public ArrayCtrl {
public:
	virtual void   SetData(const Value& data);
	virtual Value  GetData() const;

protected:
	void Modify()  { Update(); }

	EditString      localpath, remotepath;
	SelectDirButton edit_dir;

public:
	DirMap();
};

class BuilderSetup;

class BuilderSetupInterface : public ParentCtrl {
public:
	virtual ~BuilderSetupInterface() {}

	virtual void New(const String& builder) = 0;
	virtual void OnLoad() = 0;
	virtual void InitSetupCtrlsMap(VectorMap<Id, Ctrl*>& map) = 0;
	
	virtual void InitBuilderSetup(BuilderSetup& bs);
};

class AndroidBuilderSetup : public WithBuildMethodsAndroidBuilderSetupLayout<BuilderSetupInterface> {
public:
	FrameRight<Button> ndkBrowse;
	FrameRight<Button> jdkBrowse;
	
public:
	AndroidBuilderSetup();
	
	virtual void New(const String& builder);
	virtual void OnLoad();
	
	virtual void InitSetupCtrlsMap(VectorMap<Id, Ctrl*>& map);

private:
	void LoadPlatforms(const AndroidSDK& sdk);
	void LoadBuildTools(const AndroidSDK& sdk);
	void LoadDropList(DropList& dropList, Vector<String> values, const String& defaultKey = "");
};

class BuilderSetup {
public:
	BuilderSetupInterface* setupCtrl;
	VectorMap<Id, Ctrl*> setupCtrlsMap;
};

class DefaultBuilderSetup : public WithBuildMethodsDefaultBuilderSetupLayout<BuilderSetupInterface> {
public:
	TextOption debug_blitz;
	TextSwitch debug_linkmode;
	TextOption release_blitz;
	TextSwitch release_linkmode;
	TextOption allow_pch;
	DirTable   path;
	DirTable   include;
	DirTable   lib;
	
public:
	DefaultBuilderSetup();
	
	virtual void New(const String& builder);
	virtual void OnLoad();
	
	virtual void InitSetupCtrlsMap(VectorMap<Id, Ctrl*>& map);
};

class BuildMethods : public WithBuildMethodsLayout<TopWindow> {
public:
	OpenFileButton open_script;
	TextOption linkmode_lock;
	
	EditStringNotNull name;
	Index<String>     origfile;
	String            default_method;
	
	ArrayMap<String, BuilderSetup> setups;
	
	AndroidBuilderSetup androidSetup;
	DefaultBuilderSetup defaultSetup;
	
	void Load();
	bool Save();

	void NewBuilder();
	void ShowDefault();
	void SetDefault();
	void ChangeMethod();
	void Import();

	void MethodMenu(Bar& bar);
	
	String GetSetupPrefix(const String& setupKey) const;
	void   InitSetups();
	void   SwitchSetupView();
	VectorMap<String, String> SieveBuilderVars(const VectorMap<String, String>& map);
	VectorMap<String, String> MapBuilderVars(const VectorMap<String, String>& map);
	
	typedef BuildMethods CLASSNAME;

	BuildMethods();
	
private:
	void          SieveBuilders(Index<String>& sievedBuilders, const Index<String>& builders) const;
	String        BuildersToString(const Index<String>& builders) const;
	Index<String> StringToBuilders(const String& str) const;
	Index<String> GetBuilders() const;
};

#endif
