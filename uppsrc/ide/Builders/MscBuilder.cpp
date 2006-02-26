#include "Builders.h"
#pragma hdrstop

#include <coff/binobj/binobj.h>

static bool HasTail(String s, const char *tail)
{
	int tl = strlen(tail);
	int sl = s.GetLength();
	if(sl < tl)
		return false;
	for(const char *p = s.GetIter(sl - tl); *p; p++, tail++)
		if(*tail != '*' && *tail != *p)
			return false;
	return *tail == 0;
}

static void AddObjectExports(const char *path, Index<String>& out)
{
#ifdef PLATFORM_WIN32
	FileMapping mapping;
	if(!mapping.Open(path))
		return;
	const byte *begin = mapping.Begin();
	const COFF_IMAGE_FILE_HEADER *hdr = (const COFF_IMAGE_FILE_HEADER *)begin;
	if(hdr->Machine != COFF_IMAGE_FILE_MACHINE_I386)
		return;
	const COFF_IMAGE_SECTION_HEADER *sechdr = (const COFF_IMAGE_SECTION_HEADER *)(begin
		+ sizeof(COFF_IMAGE_FILE_HEADER) + hdr->SizeOfOptionalHeader);
	Index<int> code_sections;
	for(int i = 0; i < hdr->NumberOfSections; i++)
		if(sechdr[i].Characteristics & COFF_IMAGE_SCN_CNT_CODE)
			code_sections.Add(i + 1);
	const COFF_IMAGE_SYMBOL *symtbl = (const COFF_IMAGE_SYMBOL *)(begin + hdr->PointerToSymbolTable);
	const char *strtbl = (const char *)(symtbl + hdr->NumberOfSymbols);
	for(int i = 0; i < (int)hdr->NumberOfSymbols; i++)
	{
		const COFF_IMAGE_SYMBOL& sym = symtbl[i];
		if(sym.StorageClass == COFF_IMAGE_SYM_CLASS_EXTERNAL && code_sections.Find(sym.SectionNumber) >= 0)
		{
			String name = COFFSymbolName(sym, strtbl);
			if(!HasTail(name, "AEPAXI@Z"))
			{
				if(*name == '_' && name.Find('@') < 0)
					name.Remove(0, 1);
				out.FindAdd(name);
			}
		}
		i += sym.NumberOfAuxSymbols;
	}
#endif
}

void   MscBuilder::AddFlags(Index<String>& cfg)
{
	cfg.FindAdd("MSC");
}

String MscBuilder::CmdLine()
{
	String cc;
	if(HasFlag("ARM"))
		cc = "clarm";
	else
	if(HasFlag("MIPS"))
		cc = "clmips";
	else
	if(HasFlag("SH3"))
		cc = "shcl /Qsh3";
	else
	if(HasFlag("SH4"))
		cc = "shcl /Qsh4";
	else
		cc = HasFlag("INTEL") ? "icl" : "cl";
	cc << " -c -nologo -W3 -GR";
	cc << IncludesDefinesTargetTime();
	return cc;
}

String MscBuilder::MachineName() const
{
	if(HasFlag("ARM"))  return "ARM";
	if(HasFlag("MIPS")) return "MIPS";
	if(HasFlag("SH3"))  return "SH3";
	if(HasFlag("SH4"))  return "SH4";
	if(HasFlag("WIN32")) return "I386";
	return "IX86";
}

String MscBuilder::LinkerName() const
{
	if(HasFlag("ULD")) return "uld";
	return "link";
}

static bool sContainsPchOptions(const String& x)
{
	Index<String> a = Split(x, ' ');
	return  a.Find("-Gl") >= 0 || a.Find("/Gl") >= 0 || a.Find("-Y-") >= 0 || a.Find("/Y-") >= 0
	     || a.Find("-Yc") >= 0 || a.Find("/Yc") >= 0 || a.Find("-Yd") >= 0 || a.Find("/Yd") >= 0
	     || a.Find("-Yl") >= 0 || a.Find("/Yl") >= 0 || a.Find("-Yu") >= 0 || a.Find("/Yu") >= 0
	     || a.Find("-YX") >= 0 || a.Find("/YX") >= 0;
}

bool MscBuilder::HasAnyDebug() const
{
	return HasFlag("DEBUG") || HasFlag("DEBUG_MINIMAL") || HasFlag("DEBUG_FULL");
}

bool MscBuilder::BuildPackage(const String& package, Vector<String>& linkfile, String& linkoptions,
	const Vector<String>& all_uses, const Vector<String>& all_libraries, int opt)
{
	int i;
	String packagepath = PackagePath(package);
	Package pkg;
	pkg.Load(packagepath);
	String packagedir = GetFileFolder(packagepath);
	ChDir(packagedir);
	PutVerbose("cd " + packagedir);
	Vector<String> obj;

	bool is_shared = HasFlag("SO");

	String cc = CmdLine();
	if(HasFlag("EVC"))
	{
		if(!HasFlag("SH3") && !HasFlag("SH4"))
			cc << " -Gs8192"; // disable stack checking
		cc << " -GF" // read-only string pooling
		      " -GX-"; // turn off exception handling
	}
	else
	if(HasFlag("MSC8"))
		cc << " -EHsc";
	else
		cc << " -GX";
	String pdb = GetHostPathQ(CatAnyPath(outdir, GetAnyFileName(package) + ".pdb"));
	String pch;
	if(!HasFlag("MSC8")) // MSC8 does not support automatic precompiled headers...
		pch << " -YX -Fp" << GetHostPathQ(CatAnyPath(outdir, GetAnyFileName(package) + ".pch")) << ' ';
	cc << " -Gy -Fd" << pdb;
	if(HasFlag("DEBUG_MINIMAL"))
		cc << " -Zd";
	if(HasFlag("DEBUG_FULL"))
		cc << " -Zi";
	cc << ' ' << Gather(pkg.option, config.GetKeys());
	cc << (HasFlag("SHARED") || is_shared ? " -MD" : (HasFlag("MT") || HasFlag("MSC8")) ? " -MT" : " -ML");

	String cc_size = cc;
	String cc_speed = cc;
	bool   release = false;

	if(HasFlag("DEBUG"))
		cc << "d " << debug_options;
	else {
		release = true;
		cc << ' ' << release_size_options;
		cc_speed << ' ' << release_options;
		if(opt == R_SPEED || pkg.optimize_speed)
			cc = cc_speed;
	}

	Vector<String> sfile, isfile;
	Vector<String> soptions, isoptions;
	Vector<bool>   optimize, ioptimize;
	Vector<String> sobjfile;
	bool           error = false;

	for(i = 0; i < pkg.GetCount(); i++) {
		if(!IdeIsBuilding())
			return false;
		if(!pkg[i].separator) {
			String gop = Gather(pkg[i].option, config.GetKeys());
			Vector<String> srcfile = CustomStep(SourcePath(package, pkg[i]));
			if(srcfile.GetCount() == 0)
				error = true;
			for(int j = 0; j < srcfile.GetCount(); j++) {
				String fn = srcfile[j];
				String ext = ToLower(GetFileExt(fn));
				if(ext == ".c" || ext == ".cpp" || ext == ".cc" || ext == ".cxx" || ext == ".rc" || ext == ".brc") {
					sfile.Add(fn);
					soptions.Add(gop);
					optimize.Add(release && pkg[i].optimize_speed && opt == R_OPTIMAL);
				}
				else
				if(ext == ".icpp") {
					isfile.Add(fn);
					isoptions.Add(gop);
					ioptimize.Add(release && pkg[i].optimize_speed && opt == R_OPTIMAL);
				}
				else
				if(ext == ".obj")
					obj.Add(fn);
				else
				if(ext == ".lib")
					linkfile.Add(fn);
			}
		}
	}

	if(HasFlag("BLITZ")) {
		Blitz b = BlitzStep(sfile, soptions, obj, ".obj", optimize);
		if(b.build) {
			PutConsole("BLITZ:" + b.info);
			int time = GetTickCount();
			if(Execute(cc + " -Tp " + GetHostPathQ(b.path) + " -Fo" + GetHostPathQ(b.object)) == 0)
				PutCompileTime(time, b.count);
			else
				error = true;
		}
	}

	int first_ifile = sfile.GetCount();
	sfile.AppendPick(isfile);
	soptions.AppendPick(isoptions);
	optimize.AppendPick(ioptimize);

	int time = GetTickCount();
	int ccount = 0;

	if(sContainsPchOptions(cc))
		pch = Null;

	for(i = 0; i < sfile.GetCount(); i++) {
		if(!IdeIsBuilding())
			return false;
		String fn = sfile[i];
		String ext = ToLower(GetFileExt(fn));
		bool rc = (ext == ".rc");
		bool brc = (ext == ".brc");
		bool init = (i >= first_ifile);
		String objfile = CatAnyPath(outdir, GetFileTitle(fn) + (rc ? "$rc.obj" : brc ? "$brc.obj" : ".obj"));
		if(HdependFileTime(fn) > GetFileTime(objfile)) {
			int time = GetTickCount();
			bool execerr = false;
			if(rc) {
				PutConsole(GetFileNamePos(fn));
				execerr = Execute("rc /fo" + GetHostPathQ(objfile)
				                + Includes(" /i") + ' ' + GetHostPathQ(fn));
			}
			else if(brc) {
				PutConsole(GetFileNamePos(fn));
				try {
					String hfn = GetHostPath(fn);
					String brcdata = LoadFile(hfn);
					if(brcdata.IsVoid())
						throw Exc(NFormat("error reading file '%s'", hfn));
					CParser parser(brcdata, hfn);
					BinaryToObject(GetHostPath(objfile), parser, GetFileDirectory(hfn), THISBACK(BinObjConsole));
				}
				catch(Exc e) {
					PutConsole(e);
					execerr = true;
				}
			}
			else {
				String c = cc;
				if(optimize[i])
					c = cc_speed;
				execerr = Execute(c + (sContainsPchOptions(soptions[i]) ? String() : pch)
				                  + soptions[i] + (ext == ".c" ? " -Tc " : " -Tp ")
				                  + GetHostPathQ(fn) + " -Fo" + GetHostPathQ(objfile));
			}
			if(execerr)
				DeleteFile(objfile);
			error |= execerr;
			PutVerbose("compiled in " + GetPrintTime(time));
			ccount++;
		}
		if(init)
			linkfile.Add(objfile);
		else
			obj.Add(objfile);
	}
	if(ccount)
		PutConsole(String().Cat() << ccount << " file(s) compiled in " << GetPrintTime(time) <<
		           " " << int(GetTickCount() - time) / ccount << " msec/file");

	if(error)
		return false;

	Vector<String> pkglibs = Split(Gather(pkg.library, config.GetKeys()), ' ');
	for(int i = 0; i < pkglibs.GetCount(); i++) {
		String libfile = AppendExt(pkglibs[i], ".lib");
		if(!IsFullPath(libfile)) {
			for(int p = 0; p < libpath.GetCount(); p++) {
				String nf = NormalizePath(libfile, libpath[p]);
				if(FileExists(nf)) {
					libfile = nf;
					break;
				}
			}
		}
		linkfile.Add(libfile);
	}
	linkoptions << ' ' << Gather(pkg.link, config.GetKeys());

	time = GetTickCount();
	if(!HasFlag("MAIN")) {
		if(HasFlag("BLITZ") || HasFlag("NOLIB")) {
			linkfile.Append(obj);
			return true;
		}
		String product;
		if(is_shared)
			product = GetSharedLibPath(package);
		else
			product = CatAnyPath(outdir, GetAnyFileName(package) + ".lib");
		Time producttime = GetFileTime(product);
		linkfile.Add(ForceExt(product, ".lib"));
		Vector<Host::FileInfo> objinfo = host->GetFileInfo(obj);
		for(int i = 0; i < obj.GetCount(); i++)
			if(objinfo[i] > producttime) {
				String lib;
				if(is_shared) {
					lib << LinkerName() << " -dll -nologo -machine:" << MachineName()
						<< " -pdb:" << GetHostPathQ(ForceExt(product, ".pdb"))
						<< " -out:" << GetHostPathQ(product)
						<< " -incremental:no";
					if(HasAnyDebug())
						lib << " -debug -OPT:NOREF";
					else
						lib << " -OPT:REF";
					if(HasFlag("GUI"))
						lib << (HasFlag("WIN32") ? " -subsystem:windows" : " -subsystem:windowsce");
					else
						lib << " -subsystem:console";
					Index<String> exports;
					for(int o = 0; o < obj.GetCount(); o++)
						AddObjectExports(obj[o], exports);
					String def;
					def << "LIBRARY " << AsCString(GetFileName(product)) << "\n\n"
						"EXPORTS\n";
					for(int o = 0; o < exports.GetCount(); o++)
						def << '\t' << exports[o] << "\n"; //" @" << (o + 1) << "\n";
					String deffile = ForceExt(product, ".def");
					if(!SaveChangedFile(deffile, def))
					{
						PutConsole(NFormat("%s: error saving file", deffile));
						return false;
					}
					lib << " -def:" << GetHostPathQ(deffile);
					for(int i = 0; i < libpath.GetCount(); i++)
						lib << " -LIBPATH:" << GetHostPathQ(libpath[i]);
					lib << ' ' << Gather(pkg.link, config.GetKeys());
					for(int i = 0; i < all_uses.GetCount(); i++)
						lib << ' ' << GetHostPathQ(ForceExt(GetSharedLibPath(all_uses[i]), ".lib"));
					for(int i = 0; i < all_libraries.GetCount(); i++) {
						String libfile = AppendExt(all_libraries[i], ".lib");
						if(!IsFullPath(libfile)) {
							for(int p = 0; p < libpath.GetCount(); p++) {
								String nf = NormalizePath(libfile, libpath[p]);
								if(FileExists(nf)) {
									libfile = nf;
									break;
								}
							}
						}
						lib << ' ' << GetHostPathQ(libfile);
					}
				}
				else
					lib << "link /lib -nologo -out:" << GetHostPathQ(product)
						<< ' ' << Gather(pkg.link, config.GetKeys());
				for(int i = 0; i < obj.GetCount(); i++)
					lib << ' ' << GetHostPathQ(obj[i]);
				PutConsole("Creating library...");
				DeleteFile(product);
				if(Execute(lib)) {
					DeleteFile(product);
					return false;
				}
				PutConsole(String().Cat() << product << " (" << GetFileInfo(product).length
				           << " B) created in " << GetPrintTime(time));
				break;
			}
		return true;
	}

	obj.Append(linkfile);
	linkfile = obj;
	return true;
}

bool MscBuilder::Link(const Vector<String>& linkfile, const String& linkoptions, bool createmap)
{
	int time = GetTickCount();
	for(int i = 0; i < linkfile.GetCount(); i++)
		if(GetFileTime(linkfile[i]) >= targettime) {
			String link;
			link << LinkerName() << " -nologo -machine:" << MachineName()
			<< " -pdb:" << GetHostPathQ(ForceExt(target, ".pdb"))
			<< " -out:" << GetHostPathQ(target);
			if(HasAnyDebug())
				link << " -incremental:yes -debug -OPT:NOREF";
			else
				link << " -incremental:no -OPT:REF";
			if(HasFlag("GUI"))
				link << (HasFlag("WIN32") ? " -subsystem:windows" : " -subsystem:windowsce");
			else
				link << " -subsystem:console";
			if(createmap)
				link << " -MAP";
			if(HasFlag("DLL"))
				link << " -DLL";
			for(i = 0; i < libpath.GetCount(); i++)
				link << " -LIBPATH:\"" << libpath[i] << '\"';
			link << ' ' << linkoptions << ' ';
			for(i = 0; i < linkfile.GetCount(); i++)
				link << ' ' << GetHostPathQ(AppendExt(linkfile[i], ".lib"));
			PutConsole("Linking...");
			CustomStep(".pre-link");
			if(Execute(link) == 0) {
				CustomStep(".post-link");
				PutConsole(String().Cat() << GetHostPath(target) << " (" << GetFileInfo(target).length
				           << " B) linked in " << GetPrintTime(time));
				return true;
			}
			else {
				DeleteFile(target);
				return false;
			}
		}
	PutConsole(String().Cat() << GetHostPath(target) << " (" << GetFileInfo(target).length
	           << " B) is up to date.");
	return true;
}

bool MscBuilder::Preprocess(const String& package, const String& file, const String& target)
{
	FileOut out(target);
	return Execute(CmdLine() + " -E " + file, out);
}

Builder *CreateMscBuilder()
{
	return new MscBuilder;
}

void RegisterMscBuilder()
{
	RegisterBuilder("MSC71", CreateMscBuilder);
	RegisterBuilder("MSC8", CreateMscBuilder);
	RegisterBuilder("EVC_ARM", CreateMscBuilder);
	RegisterBuilder("EVC_MIPS", CreateMscBuilder);
	RegisterBuilder("EVC_SH3", CreateMscBuilder);
	RegisterBuilder("EVC_SH4", CreateMscBuilder);
	RegisterBuilder("INTEL", CreateMscBuilder);
}
