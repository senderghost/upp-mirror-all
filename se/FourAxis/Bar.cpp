#include "Hot4d.h"

void FourAxisDlg::SetBar()
{
	menu.Set([=](Bar& bar) {
		bar.Sub("File",
			[=](Bar& bar) {
				bar.Add("Open..", [=] { Open(); });
				bar.Add("Save", [=] { Save(); });
				bar.Add("Save as..", [=] { SaveAs(); });
				if(lrufile.GetCount())
					lrufile(bar, THISFN(OpenFile));
				bar.Separator();
				bar.Add("Exit", [=] { Exit(); });
		});
	});
}