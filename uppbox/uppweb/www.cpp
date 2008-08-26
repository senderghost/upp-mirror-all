#include "www.h"
#define IMAGECLASS WWW
#define IMAGEFILE  <uppweb/www.iml>
#include <Draw/iml.h>
#include <plugin/ftp/ftp.h>

#define LLOG(x)  // LOG(x)

#ifdef PLATFORM_WIN32
//String rootdir = "e:\\src\\";
String rootdir = "u:\\";
String uppbox =    rootdir + "uppbox";
String uppsrc =    rootdir + "uppsrc";
String reference = rootdir + "reference";
String examples =  rootdir + "examples";
String targetdir = rootdir + "uppwww";
String diffdir   = rootdir + "wwwupp";
#else
String rootdir;
String uppbox;
String uppsrc;
String reference;
String examples;
String targetdir;
String diffdir;
#endif

bool ContainsAt(const String &source, const String &pattern, int pos)
{
	return    pos >= 0
	       && pos + pattern.GetLength() <= source.GetLength()
	       && 0 == memcmp(source.Begin() + pos, pattern.Begin(), pattern.GetLength());
}

bool StartsWith(const String &source, const String &pattern)
{
	return ContainsAt(source, pattern, 0);
}

bool EndsWith(const String &source, const String &pattern)
{
	return ContainsAt(source, pattern, source.GetLength() - pattern.GetLength());
}

String ImgName(int q)
{
	return Sprintf("%di.png", q);
}

typedef Image (*ImageFn)();

namespace Upp {
template<>
unsigned GetHashValue(const ::ImageFn& fn) { return (unsigned)(uintptr_t) fn; }
};

String GetImageSrc(ImageFn img)
{
	static Index<ImageFn> il;
	int q = il.Find(img);
	if(il.Find(img) < 0) {
		q = il.GetCount();
		il.Add(img);
		PNGEncoder png;
		png.SaveFile(AppendFileName(targetdir, ImgName(q)),(*img)());
	}
	return ImgName(q);
}

Htmls Wimg(ImageFn img)
{
	return HtmlImg(GetImageSrc(img)).Border(0);
}

Htmls RoundFrame(Htmls data, String border, Color bg)
{
	return HtmlPackedTable().BgColor(bg).Width(-100)
	          .Attr("style", "border-style: solid; border-width: 1px; border-color: #" + border + ";")
	       / HtmlLine() / data;
}

HtmlTag BoxWidth(int width)
{
	return HtmlPackedTable().Width(width) / HtmlLine();
}

Htmls BarSection(const char *txt)
{
	Htmls bar;
	bar.Br();
	bar << HtmlPackedTable().BgColor(WhiteGray).Width(-100) /
			(HtmlRow() / (
				HtmlCell().Width(10) / "&nbsp;" +
				HtmlCell() / HtmlArial(8) / HtmlBold() / txt +
				HtmlCell().Width(10) / "&nbsp;"
			));
	return bar;
}

Htmls BarCaption(const char *text)
{
	return HtmlLine()
	         .Width(-100)
	         .VCenter()
	         .Style("background-image: url('" + GetImageSrc(WWW::Caption) + "'); "
			        "border: 0px solid black;"
	                "padding-left:12px; padding-right:0px; "
	                "padding-top:1px; padding-bottom:1px;"
	                "color:#FFFFFF;")
	         / HtmlBold() / HtmlArial(8) / text;
}

Htmls BarItem(Htmls content, const char *style)
{
	String bgStyle = "background-image: url('" + GetImageSrc(WWW::Button) + "'); ";
	return HtmlLine().Width(-100).VCenter().Style(bgStyle + style)
	         / content;
}

Htmls BarLink(const char *link, const char *text, bool nxt = true)
{
	String style = "border: 0px solid black; "
	               "padding-left:12px; padding-right:0px; "
	               "padding-top:6px; padding-bottom:6px;";
	if(nxt)
	  style += " border-top: 1px solid #6E89AE;";

	return BarItem( HtmlLink(link).Class("l1") / text, style );
}

Htmls SearchBar(const char *domain)
{
	Htmls form =
	  HtmlForm("http://www.google.com/search", false, "GET")
	    .Style("margin:0px;padding:0px;") /
	    ( HtmlHidden("ie", "UTF-8") +
	      HtmlHidden("oe", "UTF-8") +
	      HtmlEdit("q", 15) +
	      HtmlHidden("domains", domain) +
	      HtmlHidden("sitesearch", domain)
	    );

	Htmls content;
	content << HtmlPackedTable().Width(-100)
	           / HtmlRow() / (
	               HtmlCell() / Wimg(WWW::google) +
	               HtmlCell() / form
	            );

	String style = "border: 0px solid black; "
	               "padding-left:6px; padding-right:0px; "
	               "padding-top:4px; padding-bottom:4px;";
	               "border-top: 1px solid #6E89AE;";
	return BarItem(content, style);
}

HtmlTag HtmlPadding(int p)
{
	return HtmlPackedTable().Width(-100) /
		   HtmlLine();
}

VectorMap<String, String> escape;

String QtfAsHtml(const char *qtf, Index<String>& css,
                 const VectorMap<String, String>& links,
                 const VectorMap<String, String>& labels,
                 const String& outdir, const String& fn = Null)
{
	return EncodeHtml(ParseQTF(qtf), css, links, labels, outdir, fn, Zoom(8, 40), escape, 40);
}

#define TOPICFILE <uppweb/www.tpp/all.i>
#include <Core/topic_group.h>

#define TOPICFILE <uppweb/www_news.tpp/all.i>
#include <Core/topic_group.h>

#define TOPICFILE <ide/app.tpp/all.i>
#include <Core/topic_group.h>

String GetText(const char *s)
{
	return GetTopic(s).text;
}

VectorMap<String, Topic> tt;

String Www(const char *topic)
{
	return GatherTopics(tt, String().Cat() << "topic://uppweb/www/" << topic << "$en-us");
}

String FolderLinks(String package, String group)
{
	String qtf;
	FindFile ff(AppendFileName(AppendFileName(AppendFileName(uppsrc, package), group + ".tpp"), "*.tpp"));
	while(ff) {
		if(ff.IsFile()) {
			String title;
			String tl = "topic://" + package + '/' + group + '/' + GetFileTitle(ff.GetName());
			GatherTopics(tt, tl, title);
			qtf << "________[^" << tl << "^ " << DeQtf(Nvl(title, tl)) << "]&";
		}
		ff.Next();
	}
	return qtf;
}

void AddFiles(String& qtf, const String& dir, const char* ext, bool& b)
{
	FindFile ff(AppendFileName(dir, "*." + String(ext)));
	while(ff) {
		qtf << "[A4* " << DeQtf(ff.GetName()) << "]&&"
		    << CppAsQtf(LoadFile(AppendFileName(dir, ff.GetName())))
		    << "&&&";
		ff.Next();
		b = true;
	}
}

struct Isort {
	bool operator()(const String& a, const String& b) const
	{
		return ToUpper(a) < ToUpper(b);
	}
};

String MakeExamples(const char *dir, const char *www)
{
	String ttxt;
	FindFile ff(AppendFileName(dir, "*.*"));
	ttxt << "{{1:3 ";
	bool next = false;
	Vector<String> ls;
	while(ff) {
		if(ff.IsFolder())
			ls.Add(ff.GetName());
		ff.Next();
	}
	Sort(ls, Isort());
	for(int i = 0; i < ls.GetCount(); i++) {
		String name = ls[i];
		String link = String().Cat() << www << '$' << name << ".html";
		Topic& topic = tt.Add(link);
		topic.title = name;
		String fn = AppendFileName(
						AppendFileName(
							AppendFileName(uppbox, "uppweb"),
							String(www) + ".tpp"
						),
						topic.title + "$en-us.tpp"
					);
		String h = ReadTopic(LoadFile(fn)).text;
		Package p;
		p.Load(AppendFileName(AppendFileName(dir, name), name + ".upp"));
		topic.text << "[R6* " << name << "]&&" << DeQtf(p.description) << "&";
		if(h.GetCount())
			topic.text << h;
		topic.text << "[A2<l0r0 &&";
		String d = AppendFileName(dir, name);
		bool b = false;
		AddFiles(topic.text, d, "h", b);
		AddFiles(topic.text, d, "hpp", b);
		AddFiles(topic.text, d, "cpp", b);
		AddFiles(topic.text, d, "usc", b);
		AddFiles(topic.text, d, "lay", b);
		AddFiles(topic.text, d, "key", b);
		AddFiles(topic.text, d, "brc", b);
		AddFiles(topic.text, d, "sch", b);
		AddFiles(topic.text, d, "xml", b);
		if(b) {
			if(next)
				ttxt << "\n::^ ";
			ttxt << "[^" << link << "^ " << DeQtf(topic.title) << "]::^ "
			     << DeQtf(p.description);
			next = true;
		}
	}
	ttxt << "}}&&";
	return ttxt;
}

void SrcDocs(String& qtf, const char *folder)
{
	static Index<String> x;
	if(x.Find(folder) >= 0)
		return;
	x.Add(folder);
	String srcdoc = FolderLinks(folder, "srcdoc");
	String src = FolderLinks(folder, "src");
	Package p;
	p.Load(AppendFileName(uppsrc, AppendFileName(folder, GetFileName(folder) + ".upp")));
	if(srcdoc.GetLength() || src.GetLength()) {
		qtf << "&&&[*4@b " << folder << "]&";
		if(!IsNull(p.description))
			qtf << "[2 " << p.description << "]&";
		if(srcdoc.GetCount()) {
			qtf << "&[3/* Using " << folder << "]&";
			qtf << srcdoc;
		}
		if(src.GetCount()) {
			qtf << "&[3/* " << folder << " reference]&";
			qtf << src;
		}
	}
}

int CharFilterLbl(int c)
{
	return IsAlNum(c) ? c : '.';
}

VectorMap<String, String> links;
VectorMap<String, String> labels;
Htmls header, bar, lastUpdate;

void ExportPage(int i)
{
		Index<String> css;
		String path = links.GetKey(i);
		RLOG("Exporting " << path);
		Htmls html;
		String text = GetText(path);
		int h;
		h = ParseQTF(tt[i].text).GetHeight(1000);
		String page = QtfAsHtml(tt[i], css, links, labels, targetdir, links[i]);
		Color paper = SWhite;
		if(path == "topic://uppweb/www/download$en-us")
			page << LoadFile(GetDataFile("adsense3.txt"));
/*		if(path == "topic://uppweb/www/index$en-us") {
			for(int q = 0; q < news.GetCount(); q++) {
				String n = GetText("uppweb/www_news/" + news[q]);
				String h = news[q];
				int i = h.Find('$');
				if(i >= 0)
					h = h.Mid(0, i);
				if(h.GetLength() == 8)
					h = h.Mid(0, 4) + '-' + h.Mid(4, 2) + '-' + h.Mid(6, 2);
				page << "<br>";
				page << "<div style='font-family:sans-serif; font-weight: bold; "
				        "font-height: 12px; color: White; background: #2020d0'>&nbsp;&nbsp;"
				     << h << "</div><br>";
				page << QtfAsHtml(n, css, links, targetdir, FormatIntAlpha(q) + "_n");
				page << "<br>";
			}
		}*/
		Color bg = Color(210, 217, 210);
		html <<
			HtmlPackedTable().Width(-100) /
			   	HtmlLine().ColSpan(3) / header +
			HtmlPackedTable().Width(-100) / (
				HtmlLine().ColSpan(3).BgColor(bg).Height(6) / "" +
				HtmlRow() / (
					HtmlTCell().Center() / BoxWidth(160).Center() / (
						bar +
						"<br>" +
//						"<p align=\"center\">" +
						LoadFile(GetDataFile("adsense2.txt")) +
						"<br><br>" +
						LoadFile(GetDataFile("adlinks.txt")) +
						(h > 25000 ? "<br><br>" + LoadFile(GetDataFile("adsense2.txt"))
						                                : "") +
				       	"<br><br><br>" +
//						LoadFile(GetDataFile("referral.txt")) +
//						LoadFile(GetDataFile("referral2.txt")) +
//						LoadFile(GetDataFile("donations.txt")) +
//						"<br><br>" +
//						amazon[i % amazon.GetCount()] +
				       	"<br><br><br>" +
						HtmlLink("http://sourceforge.net/projects/upp/") /
						  HtmlImg("http://sourceforge.net/sflogo.php?group_id=93970&type=2",
						          "SourceForge.net Logo").Border(0).Width(125).Height(37) +
				       	"<br><br>" +
				       	HtmlLink("http://www.sdjournal.org/en/") /
							HtmlImg(GetImageSrc(WWW::Sdj)).Border(0) +
				       	"<br><br>" +
				       	(links[i] == "index.html" ? lastUpdate : Htmls()) +
				       	HtmlImg("http://www.vol.cz/cgi-bin/wc/upp").Width(1).Height(1)
					) +
					HtmlTCell().BgColor(bg) / BoxWidth(6) / "" +
					HtmlTCell().Width(-100).BgColor(bg) /
						RoundFrame(HtmlPadding(8) / page, "6E89AE;padding: 10px;", White)
				)
			);

		String topicTitle = tt.GetKey(i);
		String pageTitle = "Ultimate++";
		if(StartsWith(topicTitle, "examples$"))
		{
			String referenceName = topicTitle.Mid( 9, topicTitle.GetLength()-14 );
			pageTitle += " / Demos / " + referenceName;
		}
		else if(StartsWith(topicTitle, "reference$"))
		{
			String referenceName = topicTitle.Mid( 10, topicTitle.GetLength()-15 );
			pageTitle += " / Examples / " + referenceName;
		}

		Htmls content =
		    "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n" +
			HtmlHeader(pageTitle, AsCss(css) +
				"a.l1         { text-decoration:none; font-size: 8pt; font-family: sans-serif; "
				              "font-weight: normal; }\n"
				"a.l1:link    { color:#000000; }\n"
				"a.l1:visited { color:#000080; }\n"
				"a.l1:hover   { color:#9933CC; }\n"
				"a.l1:active  { color:#000000; }\n"
				"a.l2         { text-decoration:none; font-size: 12pt; font-family: sans-serif; "
				              "font-variant: small-caps; }\n"
				"a.l2:link    { color:#0066FF; }\n"
				"a.l2:visited { color:#FF6600; }\n"
				"a.l2:hover   { color:#BC0624; }\n"
				"a.l2:active  { color:#BC0024; }\n",
				"<META NAME=\"keywords\" "
				"CONTENT=\""
				"framework, toolkit, widget, c++, visual, studio, dev-cpp, builder, ide, class, component,"
				"wxwidgets, qt, rapid, application, development, rad, mfc, linux, gui, sdl, directx, desktop"
				"\">"
				"<meta name=\"robots\" content=\"index,follow\">"
//				"<link rel=\"shortcut icon\" href=\"/favicon.ico\" />"
			)


		    .BgColor(bg)
		    .Alink(Red).Link(Black).Vlink(Blue)
		    / html;
		SaveFile(AppendFileName(targetdir, links[i]), content);
}

GUI_APP_MAIN
{
	StdLogSetup(LOG_COUT);

	RLOG("--- uppweb started at " << GetSysTime());

	rootdir = GetHomeDirFile("upp.src");
	uppbox =    AppendFileName(rootdir, "uppbox");
	uppsrc =    AppendFileName(rootdir, "uppsrc");
	reference = AppendFileName(rootdir, "reference");
	examples =  AppendFileName(rootdir, "examples");
	targetdir = GetHomeDirFile("uppwww");
	diffdir   = GetHomeDirFile("wwwupp");

	DeleteFolderDeep(targetdir);
	DirectoryCreate(targetdir);

	DUMP(uppsrc);
	GatherRefLinks(uppsrc);

	SaveFile(AppendFileName(targetdir, "sdj.gif"), LoadFile(GetDataFile("sdj.gif")));

	escape.Add("PAYPAL", LoadFile(GetDataFile("donations.txt")));

	header = HtmlPackedTable()
	       .Width(-100)
	       .BgColor(White)
	       .Attr("style", "border: 1px solid #6E89AE;"
	                      "padding-left: 10px;padding-right: 0px;padding-top: 0px;padding-bottom: 0px;")
	       /
			HtmlRow() / (
			    HtmlCell() / HtmlLink("index.html") / Wimg(WWW::Logo6) +
			    HtmlCell().Right().Bottom()
			              .Style("padding-bottom: 5px; "
			                     "background-image: url('" + GetImageSrc(WWW::HB) + "')")
			    / HtmlArial(14) / (LoadFile(GetDataFile("adsense.txt")) + "&nbsp;&nbsp;"/* + "<br>..harnessing the real power of C++&nbsp;&nbsp;"*/)
			);

	GatherTopics(tt, "topic://uppweb/www/index$en-us");
	
	Htmls bi, bex, bdoc, bcom, bcon, bsearch;

//	bi << BarLink("index.html", "Home", false);
	bi << BarLink(Www("overview"), "Overview", false);
	bi << BarLink(Www("examples"), "Examples");
	int di = tt.GetCount() - 1;
	tt[di].text << MakeExamples(examples, "examples");
	tt[di].text << GetTopic("topic://uppweb/www/reference$en-us").text;
	tt[di].text << MakeExamples(reference, "reference");
	bi << BarLink(Www("ss"), "Screenshots");
	bi << BarLink(Www("comparison"), "Comparisons");
	bi << BarLink(Www("apps"), "Applications");
	bi << BarLink(Www("download"), "Download");

	di = tt.GetCount();
	bi << BarLink(Www("documentation"), "Manual");
	bi << BarLink(Www("Roadmap"), "Status & Roadmap");

	String qtf;
	FindFile ff(AppendFileName(uppsrc, "*.*"));
	SrcDocs(qtf, "Core");
	SrcDocs(qtf, "Draw");
	SrcDocs(qtf, "CtrlCore");
	SrcDocs(qtf, "CtrlLib");
	SrcDocs(qtf, "RichText");
	SrcDocs(qtf, "RichEdit");
	while(ff) {
		if(ff.IsFolder())
			SrcDocs(qtf, ff.GetName());
		ff.Next();
	}

	tt[di].text << qtf;

	bi << BarLink(Www("FAQ"), "FAQ");
	bi << BarLink(GatherTopics(tt, "topic://ide/app/About$en-us"), "Authors & License");

	bi << BarLink("http://www.ultimatepp.org/forum", "Forums");
//	bcom << BarLink(Www("mailing"), "Mailing lists");
	bi << BarLink("http://www.ultimatepp.org/wiki/index.php", "Wiki");
	bi << BarLink(Www("Funding"), "Funding Ultimate++");
//	bcom << BarLink(Www("helpus"), "Getting involved");
//	bcom << BarLink("mailto: upp@ntllib.org", "Contact developers");

	bsearch << BarCaption("Search on this site");
	bsearch << SearchBar("www.ultimatepp.org");

	HtmlTag bf = HtmlPackedTable()
	       .Width(-100)
	       .BgColor(White)
	       .Attr("style", "border-style: solid; border-width: 1px; border-color: #6E89AE;"
	                      "padding: 0px");
	String div = HtmlTable().Border(0).Width(-100) / HtmlLine();
	bar = bf / bi + div +
//	      bf / bex + div +
//	      bf / bdoc + div +
//	      bf / bcom + div +
//	      bf / bcon + div +
	      bf / bsearch;

	for(int i = 0; i < tt.GetCount(); i++) {
		String topic = tt.GetKey(i);
		links.Add(topic, topic == "topic://uppweb/www/index$en-us" ? "index.html" :
		                 memcmp(topic, "topic://", 8) ? topic : TopicFileNameHtml(topic));
	}

	DUMPC(reflink.GetKeys());

	for(int i = 0; i < reflink.GetCount(); i++) {
		String l = reflink.GetKey(i);
		String lbl = Filter(l, CharFilterLbl);
		String f = links.Get(reflink[i], Null) + '#' + lbl;
		links.Add(l, f);
		static const char *x[] = { "::struct", "::class", "::union" };
		for(int i = 0; i < 3; i++) {
			String e = x[i];
			if(EndsWith(l, e)) {
				links.Add(l.Mid(0, l.GetLength() - e.GetLength()), f);
			}
		}
		labels.Add(l, lbl);
	}

	Date d = GetSysDate();
	lastUpdate = HtmlItalic() / HtmlArial(8) / HtmlFontColor(Gray()) /
	                   (String().Cat() << "Last update " << GetSysDate());

//	Vector<String> amazon = Split(LoadFile(GetDataFile("amazon.txt")), '\n');//440

	for(int i = 0; i < tt.GetCount(); i++)
		ExportPage(i);

//	SaveFile(AppendFileName(targetdir, "favicon.ico"), LoadFile(AppendFileName(uppsrc, "ide/ide.ico")));
	SaveFile(AppendFileName(targetdir, "stats.html"),
	         HtmlImg("http://www.vol.cz/cgi-bin/wc/upp") + "<br>" +
	         HtmlLink("http://www.mygooglepagerank.com", "_blank") /
		         "<img src=\"http://www.mygooglepagerank.com/PRimage.php?url=http://upp.sf.net\" "
		         "border=\"0\" width=\"66\" height=\"13\" "
		         "alt=\"Google PageRank&trade; - Post your PR with MyGooglePageRank.com\">" +
	         "<noscript>" +
	         HtmlLink("http://www.mygooglepagerank.com").Title("My Google Page Rank") /
	           "My Google Page Rank" +
	         "</noscript>" +
	         HtmlLink("http://www.mygooglepagerank.com", "_blank") /
		         "<img src=\"http://www.mygooglepagerank.com/PRimage.php?url=http://www.ultimatepp.org\" "
		         "border=\"0\" width=\"66\" height=\"13\" "
		         "alt=\"Google PageRank&trade; - Post your PR with MyGooglePageRank.com\">" +
	         "<noscript>" +
	         HtmlLink("http://www.mygooglepagerank.com").Title("My Google Page Rank") /
	           "My Google Page Rank" +
	         "</noscript>"
	);
	BeepInformation();

	Vector<String> upload;
	{
		FindFile ff(AppendFileName(targetdir, "*.*"));
		while(ff) {
			if(ff.IsFile()) {
				String s = LoadFile(AppendFileName(targetdir, ff.GetName()));
				String f = AppendFileName(diffdir, ff.GetName());
				if(LoadFile(f) != s) {
					upload.Add(ff.GetName());
				}
			}
			ff.Next();
		}
	}
	DirectoryCreate(diffdir);
	if(upload.GetCount()) {
		FtpClient ftp;
		RLOG("Connecting ftp...");
		if(!ftp.Connect(getenv("UPPFTP"), getenv("UPPFTPUSR"), getenv("UPPFTPPWD"), true)) {
			RLOG("Unable to connect!" + ftp.GetError());
			SetExitCode(1);
			return;
		}
		if(!ftp.Cd("www")) {
			RLOG("Unable to 'cd www'");
			SetExitCode(1);
			return;
		}
		for(int i = 0; i < upload.GetCount(); i++) {
			RLOG("Uploading " << upload[i]);
			String s = LoadFile(AppendFileName(targetdir, upload[i]));
			if(!ftp.Save(upload[i], s)) {
				RLOG("FTP error (file upload): " + ftp.GetError());
				SetExitCode(1);
				return;
			}
			SaveFile(AppendFileName(diffdir, upload[i]), s);
		}
	}
	BeepInformation();
}
