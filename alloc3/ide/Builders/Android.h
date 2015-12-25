#ifndef _ide_Builders_Android_h_
#define _ide_Builders_Android_h_

#include <Core/Core.h>

NAMESPACE_UPP

class AndroidProject {
public:
	AndroidProject();
	AndroidProject(const String& dir);
	virtual ~AndroidProject();
	
	String GetDir() const;
	String GetJavaDir() const;
	String GetJavaDir(const String& package) const;
	String GetJniDir() const;
	String GetJniDir(const String& package) const;
	String GetLibsDir() const;
	String GetResDir() const;
	String GetBuildDir() const;
	String GetClassesDir() const;
	String GetBinDir() const;
	String GetObjDir() const;
	String GetObjLocalDir() const;
	
	String GetManifestPath() const;
	String GetJniMakeFilePath() const;
	String GetJniApplicationMakeFilePath() const;
	
	void SetDir(const String& dir);
	
	bool HasDir() const;
	
private:
	String dir;
};

class AndroidApplicationMakeFile {
public:
	AndroidApplicationMakeFile();
	virtual ~AndroidApplicationMakeFile();
	
	String ToString() const;
	
public:
	void SetPlatform(const String& platform);
	void SetArchitectures(const Vector<String>& architectures);
	void AddArchitecture(const String& architecture);
	void SetCppRuntime(const String& cppRuntime);
	void SetCppFlags(const String& cppFlags);
	void SetCFlags(const String& cFlags);
	void SetOptim(const String& optim);
	void SetToolchain(const String& toolchain);
	
protected:
	void AppendPlatform(String& makeFile) const;
	void AppendArchitectures(String& makeFile) const;
	void AppendCppRuntime(String& makeFile) const;
	void AppendCppFlags(String& makeFile) const;
	void AppendCFlags(String& makeFile) const;
	void AppendOptim(String& makeFile) const;
	void AppendToolchain(String& makeFile) const;
	
private:
	String         platform;
	Vector<String> architectures;
	String         cppRuntime;
	String         cppFlags;
	String         cFlags;
	String         toolchain;
	String         optim;
};

class AndroidModuleMakeFile : public Moveable<AndroidModuleMakeFile> {
public:
	AndroidModuleMakeFile();
	AndroidModuleMakeFile(const String& name);
	virtual ~AndroidModuleMakeFile();

	void Clear();
	String ToString() const;

public:
	void AddSourceFile(const String& path);
	void AddCppFlag(const String& name, const String& value = "");
	void AddLdLibrary(const String& ldLibrary);
	void AddStaticLibrary(const String& staticLibrary);
	void AddStaticModuleLibrary(const String& staticModuleLibrary);
	void AddSharedLibrary(const String& sharedLibrary);
	
	String GetName() const { return this->name; }
	void   SetName(const String& name) { this->name = name; }
	
protected:
	void AppendName(String& makeFile) const;
	void AppendSourceFiles(String& makeFile) const;
	void AppendCppFlags(String& makeFile) const;
	void AppendLdLibraries(String& makeFile) const;
	void AppendStaticLibraries(String& makeFile) const;
	void AppendSharedLibraries(String& makeFile) const;
	void AppendModules(String& makeFile) const;
	
private:
	String name;
	Vector<String> sourceFiles;
	VectorMap<String, String> cppFlags;
	Vector<String> ldLibraries;
	Vector<String> staticLibraries;
	Vector<String> staticModuleLibraries;
	Vector<String> sharedLibraries;
};

class AndroidMakeFile {
public:
	static void AppendString(String& makeFile,
	                         const String& variable,
	                         const String& variableName);
	static void AppendStringVector(String& makeFile,
	                               const Vector<String>& vec,
	                               const String& variableName,
	                               const String& variablePrefix = "",
	                               const String& variableSuffix = "");
	
public:
	AndroidMakeFile();
	virtual ~AndroidMakeFile();
	
public:
	bool IsEmpty() const;
	void Clear();
	
	bool HasFooter();
	
	void AddHeader();
	void AddInclusion(const String& inclusion);
	void AddModuleImport(const String& moduleName);
	
	String ToString() const;
	
protected:
	void AppendHeader(String& makeFile) const;
	void AppendInclusions(String& makeFile) const;
	void AppendImportedModules(String& makeFile) const;
	
private:
	bool hasHeader;
	Vector<String> inclusions;
	Vector<String> importedModules;
};

END_UPP_NAMESPACE

#endif
