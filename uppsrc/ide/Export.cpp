#include "ide.h"

bool IsDoc(String s)
{
	s = ToLower(s);
	return s.Find("readme") >= 0 || s.Find("copying") >= 0 || s.Find("license") >= 0 ||
	       s.Find("authors") >= 0;
}

void CopyFolder(const char *_dst, const char *_src, Index<String>& used, bool all)
{
	String dst = NativePath(_dst);
	String src = NativePath(_src);
	if(dst == src)
		return;
	FindFile ff(AppendFileName(src, "*"));
	bool realize = true;
	while(ff) {
		String s = AppendFileName(src, ff.GetName());
		String d = AppendFileName(dst, ff.GetName());
		if(ff.IsFolder())
			CopyFolder(d, s, used, all);
		else
		if(ff.IsFile() && (all || IsDoc(s) || used.Find(s) >= 0)) {
			if(realize) {
				RealizeDirectory(dst);
				realize = false;
			}
			SaveFile(d, LoadFile(s));
			SetFileTime(d, ff.GetLastWriteTime());
		}
		ff.Next();
	}
}

void Ide::ExportProject() {
	WithExportLayout<TopWindow> dlg;
	CtrlLayoutOKCancel(dlg, "Export project");
	FrameRight<Button> dsb;
	DirSel(dlg.outdir, dsb);
	CtrlRetriever r;
	if(IsNull(export_name))
		export_name = main;
	r(dlg.outdir, export_outdir);
	r(dlg.name, export_name);
	r(dlg.usedonly, export_usedonly);
	if(dlg.Execute() != IDOK)
		return;
	r.Retrieve();
	SaveFile(false);
	::Workspace wspc;
	wspc.Scan(main);
	Index<String> used;
	HdependClearDependencies();
	for(int i = 0; i < wspc.GetCount(); i++) {
		const Package& p = wspc.GetPackage(i);
		String pn = wspc[i];
		for(int j = 0; j < p.GetCount(); j++) {
			const Package::File& f = p[j];
			if(!f.separator) {
				String p = SourcePath(pn, f);
				used.FindAdd(p);
				Vector<String> d = HdependGetDependencies(p);
				for(int q = 0; q < d.GetCount(); q++)
					used.FindAdd(d[q]);
				for(int q = 0; q < f.depends.GetCount(); q++)
					used.FindAdd(SourcePath(pn, f.depends[q].text));
			}
		}
		used.FindAdd(SourcePath(pn, "init"));
	}
	String ep = AppendFileName(export_outdir, export_name);
	if(FileExists(ep)) {
		if(!PromptYesNo("There is a [* " + DeQtf(export_name) + "] file in the output directory.&"
		                "Do you want to delete it?")) return;
		FileDelete(ep);
	}
	if(DirectoryExists(ep)) {
		if(!PromptYesNo("Do you want to replace existing [* " + DeQtf(export_name) + "] export?"))
			return;
		DeleteFolderDeep(ep);
	}
	
	Progress pi("Exporting project");
	pi.SetTotal(wspc.GetCount());
	for(int i = 0; i < wspc.GetCount(); i++) {
		if(pi.StepCanceled())
			return;
		CopyFolder(AppendFileName(ep, wspc[i]), PackageDirectory(wspc[i]), used, !export_usedonly);
	}
	SaveMakeFile(AppendFileName(ep, "Makefile"), true);
}
