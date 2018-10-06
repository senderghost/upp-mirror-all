#include <CtrlLib/CtrlLib.h>
#include <CtrlCore/CocoMM.h>

namespace Upp {

struct CocoMenuBar;

};

@interface CocoMenu : NSMenu<NSMenuDelegate>
{
@public
	Upp::Ptr<Upp::CocoMenuBar> ptr;
	Upp::Event<Upp::Bar&>      proc;
}
-(void)cocoMenuAction:(id)sender;
@end

namespace Upp {

struct CocoMenuBar : public Bar {
	CocoMenu *cocomenu;

	struct Item : Bar::Item {
		NSMenuItem      *nsitem;
		Event<>          cb;
		One<CocoMenuBar> submenu;

		virtual Item& Text(const char *text);
		virtual Item& Key(dword key);
		virtual Item& Image(const class Image& img);
		virtual Item& Check(bool check);
		virtual Item& Radio(bool check);
		virtual Item& Enable(bool _enable = true);
		virtual Item& Bold(bool bold = true);

		Item&   Label(const char *text);
		Item&   RightLabel(const char *text);

		Item& Key(KeyInfo& (*key)());

		Item()  { nsitem = [NSMenuItem new]; }
		~Item() { [nsitem release]; }
	};
	
	Array<Item> item;
	
	Item& AddItem() {
		Item& m = item.Add();
		[cocomenu addItem:m.nsitem];
		return m;
	}

	virtual bool IsMenuBar() const                  { return true; }

	virtual Item& AddItem(Event<> cb) {
		Item& m = AddItem();
		m.cb = cb;
		m.nsitem.target = cocomenu;
		m.nsitem.action = @selector(cocoMenuAction:);
		return m;
	}
	
	virtual Item&  AddSubMenu(Event<Bar&> proc) {
		Item& m = AddItem();
		m.submenu.Create();
		m.submenu->cocomenu->proc = proc;
		m.nsitem.action = @selector(cocoMenuAction:);
		m.nsitem.submenu = m.submenu->cocomenu;
		return m;
	}

	virtual void   AddCtrl(Ctrl *ctrl, int gapsize) { NEVER(); }
	virtual void   AddCtrl(Ctrl *ctrl, Size sz) { NEVER(); }

	virtual bool   IsEmpty() const;
	virtual void   Separator();
	
	void MenuAction(id item);
	
	CocoMenuBar() {
		cocomenu = [CocoMenu new];
		cocomenu.autoenablesItems = NO;
		cocomenu->ptr = this;
		cocomenu.delegate = cocomenu;
	}
	~CocoMenuBar() {
		[cocomenu release];
	}
};

void CocoMenuBar::MenuAction(id sender)
{
	DLOG("MenuAction " << sender);
	for(const Item& m : item)
		if(m.nsitem == sender) {
			m.cb();
			break;
		}
}

void CocoMenuBar::Separator()
{
	[cocomenu addItem:[NSMenuItem separatorItem]];
}

CocoMenuBar::Item& CocoMenuBar::Item::Text(const char *text)
{
	NSString *s = [NSString stringWithUTF8String:text];
	nsitem.title = s;
	if(submenu)
		submenu->cocomenu.title = s;
	return *this;
}

CocoMenuBar::Item& CocoMenuBar::Item::Key(dword key)
{
	static Tuple2<int, int> code[] = {
		#include "NSMenuKeys.i"
	};
	auto *v = FindTuple(code, __countof(code), key & ~(K_CTRL|K_SHIFT|K_ALT|K_OPTION));
	if(v) {
		unichar chr = v->b;
		nsitem.keyEquivalent = [NSString stringWithCharacters:&chr length:1];
		nsitem.keyEquivalentModifierMask = (key & K_CTRL ? NSEventModifierFlagCommand : 0) |
		                                   (key & K_SHIFT ? NSEventModifierFlagShift : 0) |
		                                   (key & K_ALT ? NSEventModifierFlagControl : 0) |
		                                   (key & K_OPTION ? NSEventModifierFlagOption : 0);
	}
	return *this;
}

CocoMenuBar::Item& CocoMenuBar::Item::Image(const class Image& img)
{
	nsitem.image = GetNSImage(img);
	return *this;
}

CocoMenuBar::Item& CocoMenuBar::Item::Check(bool check)
{
	nsitem.state = check ? NSControlStateValueOn : NSControlStateValueOff;
	return *this;
}

CocoMenuBar::Item& CocoMenuBar::Item::Radio(bool check)
{
	return Check(check);
}

CocoMenuBar::Item& CocoMenuBar::Item::Enable(bool enable)
{
	DDUMP(enable);
	nsitem.enabled = enable;
	return *this;
}

CocoMenuBar::Item& CocoMenuBar::Item::Bold(bool bold)
{
	return *this;
}

bool CocoMenuBar::IsEmpty() const
{
	return item.GetCount() == 0;
}

void TestMenu(Ctrl *ctrl, Point p)
{
	static CocoMenuBar bar;
	
//	bar.Add("Test 1", [] { PromptOK("1"); });
//	bar.Separator();
	bar.Sub("test", [](Bar &bar) {
		bar.Add("test submenu", [] { Exclamation("Submenuitem!"); });
		bar.Add(AsString(Random()), CtrlImg::exclamation(), [] { Exclamation("Submenuitem!"); });
	});
	bar.Sub("Submenu", [](Bar &bar) {
		bar.Add("Submenu 2", [] { Exclamation("Submenuitem!"); });
		bar.Add(AsString(Random()), [] { Exclamation("Submenuitem!"); });
		bar.Add("Test 2", [] { PromptOK("2"); }).Key(K_ALT_A);
		bar.Add(false, "Test 2 disabled", [] { PromptOK("2"); }).Key(K_ALT|K_PERIOD);
		bar.Add("Check", [] {}).Check(false)
		   .Key(K_ESCAPE);
	});
//	static bool chk;
//	bar.Add("Check", [&] { chk = !chk; }).Check(chk);
	
	[NSApp setMainMenu:bar.cocomenu];
	return;
	
	ctrl = ctrl->GetTopCtrl();
	
	p -= ctrl->GetScreenRect().TopLeft();
	
	NSPoint np;
	np.x = p.x;
	np.y = p.y;
	
	[bar.cocomenu popUpMenuPositioningItem:bar.item[0].nsitem
                              atLocation:np
                                  inView:(NSView *)ctrl->GetNSView()];

}

}

@implementation CocoMenu

-(void)cocoMenuAction:(id)sender {
	DLOG("cocoMenuAction");
	if(ptr)
		ptr->MenuAction(sender);
}

- (void)menuWillOpen:(NSMenu *)menu {
	DLOG("menuWillOpen");
	CocoMenu *m = (CocoMenu *)menu;
	if(m && m->ptr && proc) {
		[m removeAllItems];
		proc(*m->ptr);
	}
}

-(void)submenuAction:(id)sender {
	DDUMP("submenuAction");
	if(ptr)
		proc(*ptr);
	[super submenuAction:sender];
}

@end
