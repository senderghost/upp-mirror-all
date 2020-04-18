#include <RichEdit/RichEdit.h>

using namespace Upp;

String FileName() {
	return GetDataFile("test.txt");
}

GUI_APP_MAIN
{
	StdLogSetup(LOG_FILE|LOG_COUT);
	SetLanguage(LNGC_('C', 'S', 'C', 'Z', CHARSET_UTF8));
	
	Ctrl::SetUHDEnabled();

	RichEditWithToolBar e;
	e.Pick(ParseQTF(LoadFile(FileName())));
//	e.SetPage(Size(4000, 1600));
	TopWindow w;
	w.SetRect(0, 0, DPI(700), DPI(500));
	w.Sizeable().Zoomable();
	StaticRect r;
	w.Add(e.SizePos());

	w.Run();
	String x = e.GetQTF();
	SaveFile(FileName(), x);
	
	LOG("Exit");
}

#if 0
----------------------------------
Thread: 1

cairo_scale () from /usr/lib/x86_64-linux-gnu/libcairo.so.2
Upp::TopFrameDraw::TopFrameDraw (this=0x7ffffffeb458, ctrl=<optimized out>, r=...) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkWnd.cpp:542
Upp::ViewDraw::ViewDraw (this=0x7ffffffeb458, ctrl=0x7ffffffecfe0, r=...) at /home/cxl/upp.src/uppsrc/CtrlCore/Ctrl.cpp:1087
Upp::ViewDraw::ViewDraw (this=0x6c85d8 <vtable for Upp::TopFrameDraw+16>, ctrl=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlCore.h:1674
Upp::DrawDragRect (q=..., f=...) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkUtil.cpp:47
Upp::Ctrl::GtkDraw (widget=<optimized out>, cr=<optimized out>, user_data=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:111
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
g_closure_invoke () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit_valist () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
gtk_main_do_event () from /usr/lib/x86_64-linux-gnu/libgtk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
g_closure_invoke () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit_valist () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_dispatch () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_iteration () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
Upp::Ctrl::FetchEvents (may_block=true) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:312
Upp::Ctrl::EventLoop (ctrl=0x7ffffffec6d0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:680
Upp::LocalLoop::Run (this=0x7ffffffec6d0) at /home/cxl/upp.src/uppsrc/CtrlCore/LocalLoop.cpp:15
Upp::RectTracker::Track (this=0x7ffffffec6d0, r=..., _tx=<optimized out>, _ty=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/LocalLoop.cpp:93
Upp::RichEdit::LeftDown (this=0x7ffffffed1f0, p=..., flags=<optimized out>) at /home/cxl/upp.src/uppsrc/RichEdit/Mouse.cpp:116
Upp::Ctrl::MouseEvent (this=<optimized out>, event=<optimized out>, p=..., zdelta=0, keyflags=4075264192) at /home/cxl/upp.src/uppsrc/Core/Gtypes.h:177
Upp::Ctrl::MouseEvent0 (this=0x7ffffffed1f0, event=129, p=..., zdelta=0, keyflags=8388608) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:92
Upp::Ctrl::MouseEventH (this=0x7ffffffed1f0, event=129, p=..., zdelta=0, keyflags=8388608) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:110
Upp::Ctrl::MEvent0 (this=0x7ffffffed1f0, e=129, p=..., zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:337
Upp::Ctrl::DispatchMouseEvent (this=<optimized out>, e=129, p=..., zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:612
Upp::Ctrl::DispatchMouseEvent (this=<optimized out>, e=129, p=..., zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:612
Upp::Ctrl::DispatchMouse (this=0x7ffffffecfe0, e=129, p=..., zd=0) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:586
Upp::Ctrl::GtkMouseEvent (this=<optimized out>, action=128, act=<optimized out>, zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:372
Upp::Ctrl::GtkButtonEvent (this=<optimized out>, action=128) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:381
Upp::Ctrl::Proc (this=0x7ffffffecfe0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:415
Upp::Ctrl::ProcessEvent0 (quit=<optimized out>, fetch=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:607
Upp::Ctrl::ProcessEvents0 (quit=0x0, fetch=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:633
Upp::Ctrl::ProcessEvents (quit=0x0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:650
Upp::Ctrl::EventLoop (ctrl=0x7ffffffecfe0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:681
Upp::TopWindow::Run (this=<optimized out>, appmodal=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/TopWindow.cpp:324
GuiMainFn_ () at /home/cxl/sandbox/uppdev/RichEditTest/main.cpp:25
Upp::AppExecute__ (app=0x0) at /home/cxl/upp.src/uppsrc/Core/App.cpp:442
main (argc=1, argv=0x7fffffffe438, envptr=0x7fffffffe448) at /home/cxl/sandbox/uppdev/RichEditTest/main.cpp:9

----------------------------------
Thread: 2

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_iteration () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/gio/modules/libdconfsettings.so
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffea793700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 3

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_iteration () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffe9f92700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 4

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_loop_run () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgio-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffe9791700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 5

syscall () at ../sysdeps/unix/sysv/linux/x86_64/syscall.S:38
g_cond_wait_until () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_async_queue_timeout_pop () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffe8b1f700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 6

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989460) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989460) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd959b700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 7

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9894c0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9894c0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd8d9a700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 8

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989520) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989520) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd3fff700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 9

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989580) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989580) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd37fe700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 10

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9895c0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9895c0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd2ffd700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 11

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989620) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989620) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd27fc700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 12

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989680) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989680) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd1ffb700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 13

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9896e0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9896e0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd17fa700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 14

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989740) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989740) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd0ff9700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 15

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf1120 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9897a0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9897a0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd07f8700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 16

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libpulse.so.0
pa_mainloop_poll () from /usr/lib/x86_64-linux-gnu/libpulse.so.0
pa_mainloop_iterate () from /usr/lib/x86_64-linux-gnu/libpulse.so.0
pa_mainloop_run () from /usr/lib/x86_64-linux-gnu/libpulse.so.0
/usr/lib/x86_64-linux-gnu/libpulse.so.0
/usr/lib/x86_64-linux-gnu/pulseaudio/libpulsecommon-11.1.so
start_thread (arg=0x7fffcad66700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95



----------------------------------
Thread: 1

cairo_scale () from /usr/lib/x86_64-linux-gnu/libcairo.so.2
Upp::TopFrameDraw::TopFrameDraw (this=0x7ffffffeb468, ctrl=<optimized out>, r=...) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkWnd.cpp:536
Upp::ViewDraw::ViewDraw (this=0x7ffffffeb468, ctrl=0x7ffffffecfe0, r=...) at /home/cxl/upp.src/uppsrc/CtrlCore/Ctrl.cpp:1087
Upp::ViewDraw::ViewDraw (this=0x6c8db0 <vtable for Upp::TopFrameDraw+16>, ctrl=0x7ffffffecfe0) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlCore.h:1674
Upp::DrawDragRect (q=..., f=...) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkUtil.cpp:46
Upp::Ctrl::GtkDraw (widget=<optimized out>, cr=<optimized out>, user_data=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:111
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
g_closure_invoke () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit_valist () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
/usr/lib/x86_64-linux-gnu/libgtk-3.so.0
gtk_main_do_event () from /usr/lib/x86_64-linux-gnu/libgtk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
g_closure_invoke () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit_valist () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
g_signal_emit () from /usr/lib/x86_64-linux-gnu/libgobject-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libgdk-3.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_dispatch () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_iteration () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
Upp::Ctrl::FetchEvents (may_block=true) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:312
Upp::Ctrl::EventLoop (ctrl=0x7ffffffec6d0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:680
Upp::LocalLoop::Run (this=0x7ffffffec6d0) at /home/cxl/upp.src/uppsrc/CtrlCore/LocalLoop.cpp:15
Upp::RectTracker::Track (this=0x7ffffffec6d0, r=..., _tx=<optimized out>, _ty=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/LocalLoop.cpp:93
Upp::RichEdit::LeftDown (this=0x7ffffffed1f0, p=..., flags=<optimized out>) at /home/cxl/upp.src/uppsrc/RichEdit/Mouse.cpp:116
Upp::Ctrl::MouseEvent (this=<optimized out>, event=<optimized out>, p=..., zdelta=0, keyflags=4075264192) at /home/cxl/upp.src/uppsrc/Core/Gtypes.h:177
Upp::Ctrl::MouseEvent0 (this=0x7ffffffed1f0, event=129, p=..., zdelta=0, keyflags=8388608) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:92
Upp::Ctrl::MouseEventH (this=0x7ffffffed1f0, event=129, p=..., zdelta=0, keyflags=8388608) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:110
Upp::Ctrl::MEvent0 (this=0x7ffffffed1f0, e=129, p=..., zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:337
Upp::Ctrl::DispatchMouseEvent (this=<optimized out>, e=129, p=..., zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:612
Upp::Ctrl::DispatchMouseEvent (this=<optimized out>, e=129, p=..., zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:612
Upp::Ctrl::DispatchMouse (this=0x7ffffffecfe0, e=129, p=..., zd=0) at /home/cxl/upp.src/uppsrc/CtrlCore/CtrlMouse.cpp:586
Upp::Ctrl::GtkMouseEvent (this=<optimized out>, action=128, act=<optimized out>, zd=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:372
Upp::Ctrl::GtkButtonEvent (this=<optimized out>, action=128) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:381
Upp::Ctrl::Proc (this=0x7ffffffecfe0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:415
Upp::Ctrl::ProcessEvent0 (quit=<optimized out>, fetch=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:607
Upp::Ctrl::ProcessEvents0 (quit=0x0, fetch=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:633
Upp::Ctrl::ProcessEvents (quit=0x0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:650
Upp::Ctrl::EventLoop (ctrl=0x7ffffffecfe0) at /home/cxl/upp.src/uppsrc/CtrlCore/GtkEvent.cpp:681
Upp::TopWindow::Run (this=<optimized out>, appmodal=<optimized out>) at /home/cxl/upp.src/uppsrc/CtrlCore/TopWindow.cpp:324
GuiMainFn_ () at /home/cxl/sandbox/uppdev/RichEditTest/main.cpp:25
Upp::AppExecute__ (app=0x0) at /home/cxl/upp.src/uppsrc/Core/App.cpp:442
main (argc=1, argv=0x7fffffffe438, envptr=0x7fffffffe448) at /home/cxl/sandbox/uppdev/RichEditTest/main.cpp:9

----------------------------------
Thread: 2

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_iteration () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/gio/modules/libdconfsettings.so
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffea793700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 3

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_context_iteration () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffe9f92700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 4

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_main_loop_run () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libgio-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffe9791700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 5

syscall () at ../sysdeps/unix/sysv/linux/x86_64/syscall.S:38
g_cond_wait_until () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
g_async_queue_timeout_pop () from /usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
/usr/lib/x86_64-linux-gnu/libglib-2.0.so.0
start_thread (arg=0x7fffe8b1f700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 6

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989460) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989460) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd959b700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 7

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9894c0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9894c0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd8d9a700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 8

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989520) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989520) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd3fff700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 9

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989580) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989580) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd37fe700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 10

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9895c0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9895c0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd2ffd700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 11

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989620) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989620) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd27fc700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 12

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989680) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989680) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd1ffb700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 13

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9896e0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9896e0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd17fa700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 14

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec989740) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec989740) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd0ff9700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 15

futex_wait_cancelable (private=<optimized out>, expected=0, futex_word=0xaf2110 <Upp::CoWork::GetPool()::pool+114848>) at ../sysdeps/unix/sysv/linux/futex-internal.h:88
pthread_cond_wait.c:502
pthread_cond_wait.c:655
Upp::ConditionVariable::Wait (timeout_ms=-1, this=<optimized out>, m=...) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:624
Upp::CoWork::Pool::ThreadRun (tno=<optimized out>) at /home/cxl/upp.src/uppsrc/Core/CoWork.cpp:161
Upp::Function<void ()>::operator()() const (this=0x7fffec9897a0) at /home/cxl/upp.src/uppsrc/Core/Function.h:76
Upp::sThreadRoutine (arg=0x7fffec9897a0) at /home/cxl/upp.src/uppsrc/Core/Mt.cpp:91
start_thread (arg=0x7fffd07f8700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

----------------------------------
Thread: 16

../sysdeps/unix/sysv/linux/poll.c:29
/usr/lib/x86_64-linux-gnu/libpulse.so.0
pa_mainloop_poll () from /usr/lib/x86_64-linux-gnu/libpulse.so.0
pa_mainloop_iterate () from /usr/lib/x86_64-linux-gnu/libpulse.so.0
pa_mainloop_run () from /usr/lib/x86_64-linux-gnu/libpulse.so.0
/usr/lib/x86_64-linux-gnu/libpulse.so.0
/usr/lib/x86_64-linux-gnu/pulseaudio/libpulsecommon-11.1.so
start_thread (arg=0x7fffcad66700) at pthread_create.c:463
clone () at ../sysdeps/unix/sysv/linux/x86_64/clone.S:95

#endif