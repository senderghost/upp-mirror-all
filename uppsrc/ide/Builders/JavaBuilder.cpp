#include "Builders.h"

String AdjustLines(const String& file)
{
	String out;
	const char *p = file;
	while(*p)
	{
		const char *b = p;
		while(*p && (byte)*p <= ' ' && *p != '\r' && *p != '\n')
			p++;
		if(*p == '#')
		{
			out.Cat("//");
			b = p;
			while(*p && *p != '\n' && *p != '\"')
				p++;
			out.Cat(b, p - b);
			b = p;
			if(*p == '\"')
			{
				out.Cat('\"');
				b = ++p;
				while(*p && *p++ != '\n')
					;
				const char *e = p;
				while(e > b && (byte)e[-1] <= ' ')
					e--;
				if(e[-1] == '\"')
					e--;
				out.Cat(UnixPath(String(b, e)));
				out.Cat("\"\r\n");
				b = p;
				continue;
			}
		}
		out.Cat(b, p - b);
		while(*p && *p != '\n')
		{
			b = p;
			while(*p && *p != '\n' && *p != '\r')
				p++;
			out.Cat(b, p - b);
			while(*p == '\r')
				p++;
		}
		if(*p == '\n')
		{
			p++;
			out.Cat("\r\n");
		}
	}
	return out;
}

String JavaBuilder::JavaLine()
{
	return "javac";
}

String JavaBuilder::JarLine()
{
	return "jar";
}

enum { MAINCLASS, MAINDIR, MANIFEST, ITEMCOUNT };

bool JavaBuilder::BuildPackage(const String& package, Vector<String>& linkfile, String& linkoptions,
	const Vector<String>& all_uses, const Vector<String>& all_libraries, int)
{
	int time = msecs();
	int i;
	int manifest = -1;
	String packagepath = PackagePath(package);
	Package pkg;
	pkg.Load(packagepath);
	String packagedir = GetFileFolder(packagepath);
	ChDir(packagedir);
	PutVerbose("cd " + packagedir);
	Vector<String> pkgsfile;
	Vector<String> sfile;
	Vector<String> sobjfile;
	Vector<String> soptions;
	bool           error = false;
	bool main = HasFlag("MAIN");

	for(i = 0; i < pkg.GetCount(); i++) {
		if(!IdeIsBuilding())
			return false;
		if(!pkg[i].separator) {
			String gop = Gather(pkg[i].option, config.GetKeys());
			Vector<String> srcfile = CustomStep(SourcePath(package, pkg[i]));
			if(srcfile.GetCount() == 0)
				error = true;
			for(int j = 0; j < srcfile.GetCount(); j++)
			{
				String fn = srcfile[j];
				String ext = ToLower(GetFileExt(fn));
				bool ismf = false;
				if(ext == ".java" || main && ext == ".mf")
				{
					if(ext == ".mf")
					{
						ismf = true;
						if(manifest >= 0)
						{
							PutConsole(NFormat("%s(1): duplicate manifest file", GetHostPath(fn)));
							PutConsole(NFormat("%s(1): (previous manifest file)", GetHostPath(sfile[manifest])));
						}
						manifest = sfile.GetCount();
					}
					String pkgfile = AppendFileName(package, pkg[i]);
					pkgsfile.Add(pkgfile);
					sfile.Add(fn);
					soptions.Add(gop);
					String objfile = NativePath(CatAnyPath(outdir, ismf ? String("manifest.mf") : pkgfile));
					sobjfile.Add(objfile);
				}
			}
		}
	}

	Vector<Host::FileInfo> sobjinfo = host->GetFileInfo(sobjfile);
	int ccount = 0;
	for(i = 0; i < sfile.GetCount(); i++) {
		if(!IdeIsBuilding())
			return false;
		if(HdependFileTime(sfile[i]) > sobjinfo[i]) {
			ccount++;
			if(!PreprocessJava(sfile[i], sobjfile[i], soptions[i]))
				error = true;
		}
	}
	linkfile.Add(outdir);
	if(ccount > 0)
		PutConsole(String().Cat() << ccount << " file(s) preprocessed in " << GetPrintTime(time) <<
		           " " << int(GetTickCount() - time) / ccount << " msec/file");
	linkoptions << ' ' << Gather(pkg.link, config.GetKeys());

	if(!error && HasFlag("MAIN") && !sfile.IsEmpty())
	{
		String mainfile = sfile.Top();
		String mainobj = sobjfile.Top();
		String maincls = ForceExt(mainobj, ".class");
		String libs;
		int i;
		for(i = 0; i < libpath.GetCount(); i++)
			libs << (i ? ";" : " -classpath ") << '\"' << libpath[i] << '\"';
		String linkcmd;
		linkcmd << "javac";
		linkcmd << (HasFlag("DEBUG") ? " -g" : " -g:none");
		if(!HasFlag("DEBUG"))
			if(!IsNull(release_options))
				linkcmd << ' ' << release_options;
			else
				linkcmd << " -O";
		linkcmd << " -deprecation" << linkoptions << " -sourcepath ";
		bool win32 = HasFlag("WIN32");
		for(i = 0; i < linkfile.GetCount(); i++) {
			linkcmd << (i ? (win32 ? ";" : ":") : "");
			if(linkfile[i].Find(' ') >= 0)
				linkcmd << '\"' << linkfile[i] << '\"';
			else
				linkcmd << linkfile[i];
		}
		linkfile.InsertN(0, ITEMCOUNT);
		linkfile[MAINCLASS] = maincls;
		linkfile[MAINDIR] = outdir;
		linkfile[MANIFEST] = (manifest >= 0 ? sobjfile[manifest] : String());
		linkcmd << ' ' << mainobj;
		linkoptions = linkcmd;
	}
	return !error;
}

bool JavaBuilder::Preprocess(const String& package, const String& file, const String& target)
{
	return Preprocess(file, target, Null);
}

bool JavaBuilder::PreprocessJava(String file, String target, String options)
{
	String mscpp = GetVar("MSCPP_JDK");
	String cc;
	if(!IsNull(mscpp))
		cc = mscpp + " /C /TP /P /nologo ";
	else
		cc = "cpp -C ";
	cc << IncludesDefinesTargetTime();
	int time = GetTickCount();
	RealizePath(target);
	String execpath;
	execpath << cc << ' ' << options << ' ';
	String prepfile;
	bool error = false;
	if(!IsNull(mscpp))
	{
		prepfile = ForceExt(file, ".i");
		host->ChDir(GetFileFolder(prepfile));
		execpath << GetHostPath(file);
	}
	else
	{
		PutConsole(file);
		execpath << GetHostPath(file) << " " << GetHostPath(target);
		prepfile = target;
	}
	if(Execute(execpath) != 0)
	{
		DeleteFile(target);
		error = true;
	}
	String prep = LoadFile(prepfile);
	if(prep.IsEmpty())
	{
		PutConsole(NFormat("Error loading preprocessed file %s", prepfile));
		error = true;
	}
	DeleteFile(prepfile);
	if(!prep.IsEmpty() && !::SaveFile(target, AdjustLines(prep)))
	{
		DeleteFile(target);
		error = true;
		PutConsole(NFormat("%s: error saving file.", target));
	}
	PutVerbose("preprocessed in " + GetPrintTime(time));
	return !error;
}

Time JavaBuilder::AddClassDeep(String& link, String dir, String reldir)
{
	Time time = Time::Low();
	Vector<String> folders;
	for(FindFile ff(AppendFileName(dir, AppendFileName(reldir, "*"))); ff; ff.Next())
	{
		if(ff.IsFolder())
			folders.Add(ff.GetName());
		else if(!stricmp(GetFileExtPos(ff.GetName()), ".class"))
		{
			link << " -C \"" << dir << "\" \"" << CatAnyPath(reldir, ff.GetName()) << '\"';
			time = max(time, Time(ff.GetLastWriteTime()));
		}
	}
	for(int f = 0; f < folders.GetCount(); f++)
		time = max(time, AddClassDeep(link, dir, AppendFileName(reldir, folders[f])));
	return time;
}

bool JavaBuilder::Link(const Vector<String>& linkfile, const String& linkoptions, bool)
{
	if(linkfile.GetCount() < ITEMCOUNT)
		return false;
	int time = GetTickCount();
	String mainclass = linkfile[MAINCLASS];
	String maindir = linkfile[MAINDIR];
	String manifest = linkfile[MANIFEST];
	PutConsole("Compiling...");
	if(Execute(linkoptions) != 0)
	{
		DeleteFile(mainclass);
		return false;
	}
	PutVerbose("compiled in " + GetPrintTime(time));
	host->ChDir(maindir);

	PutConsole("Archiving...");
	String link;
	link << "jar cf";
	if(!manifest.IsEmpty())
		link << 'm';
	link << ' ' << GetHostPath(target);
	if(!manifest.IsEmpty())
		link << ' ' << GetHostPath(manifest);
	Time tm = Time::Low();
	for(int i = ITEMCOUNT; i < linkfile.GetCount(); i++)
		tm = max(tm, AddClassDeep(link, linkfile[i], Null));
	if(tm > targettime)
	{
		CustomStep(".pre-link");
		if(Execute(link) != 0)
		{
			DeleteFile(target);
			return false;
		}
		CustomStep(".post-link");
		PutConsole(String().Cat() << target << " (" << GetFileInfo(target).length
		           << " B) archived in " << GetPrintTime(time));
	}
	else
		PutConsole(String().Cat() << GetHostPath(target) << " (" << GetFileInfo(target).length
		           << " B) is up to date.");
	return true;
}

static Builder *CreateJavaBuilder()
{
	return new JavaBuilder;
}

void RegisterJavaBuilder()
{
	RegisterBuilder("JDK", &CreateJavaBuilder);
}
