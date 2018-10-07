#import <Cocoa/Cocoa.h>

int main()
{
    [NSAutoreleasePool new];
  //  [NSThread detachNewThreadSelector:@selector(enableCocoaThreads:) toTarget:[[CocoaThreadEnabler alloc] init] withObject:nil];
    [NSApplication sharedApplication];
    [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];
    id menubar = [[NSMenu new] autorelease];

	{
	    id appMenuItem = [[NSMenuItem new] autorelease];
	    [menubar addItem:appMenuItem];
	    id appMenu = [[NSMenu new] autorelease];
	    id appName = [[NSProcessInfo processInfo] processName];
	    id quitTitle = [@"Quit this: " stringByAppendingString:appName];
	    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:quitTitle
	        action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
	    [appMenu addItem:quitMenuItem];
	    [appMenuItem setSubmenu:appMenu];
	}
	{
	    id appMenuItem = [[NSMenuItem new] autorelease];
	    [menubar addItem:appMenuItem];
	    NSMenu *appMenu = [[NSMenu new] autorelease];
	    id quitMenuItem = [[[NSMenuItem alloc] initWithTitle:@"something"
	        action:@selector(terminate:) keyEquivalent:@"q"] autorelease];
	    [appMenu addItem:quitMenuItem];
	    appMenu.title = @"Test";
	    [appMenuItem setSubmenu:appMenu];
	}

    id window = [[[NSWindow alloc] initWithContentRect:NSMakeRect(10, 10, 200, 200)
        styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO]
            autorelease];
    [window setTitle:@"test window"];
    [window makeKeyAndOrderFront:nil];
    [NSApp setDelegate: NSApp];
    [NSApp activateIgnoringOtherApps:YES];

    [NSApp setMainMenu:menubar];
    
    [NSApp finishLaunching];
    
    [NSApp run];
    return 0;
}
