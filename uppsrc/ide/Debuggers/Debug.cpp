#include "Debuggers.h"

#ifdef COMPILER_MSC

#define STATUS_WX86_CONTINUE             0x4000001D
#define STATUS_WX86_SINGLE_STEP          0x4000001E
#define STATUS_WX86_BREAKPOINT           0x4000001F
#define STATUS_WX86_EXCEPTION_CONTINUE   0x40000020
#define STATUS_WX86_EXCEPTION_LASTCHANCE 0x40000021
#define STATUS_WX86_EXCEPTION_CHAIN      0x40000022

#define LLOG(x)    DLOG(x)

String Pdb::Hex(adr_t a)
{
#ifdef CPU_64
	return Format64Hex(a);
#else
	return FormatIntHex(a);
#endif
}

void Pdb::Error()
{
	LLOG("ERROR: " << DeQtf(GetLastErrorMessage()));
	Exclamation("Error!&" + DeQtf(GetLastErrorMessage()));
	running = false;
	Stop();
}

void Pdb::UnloadModuleSymbols()
{
	for(int i = 0; i < module.GetCount(); i++) {
		ModuleInfo& f = module[i];
		if(f.symbols) {
			SymUnloadModule64(hProcess, f.base);
			LLOG("Unloaded symbols for " << f.path << ' ' << Hex(module[i].base) << '/' << hProcess);
		}
	}
}

int  Pdb::FindModuleIndex(adr_t base)
{
	for(int i = 0; i < module.GetCount(); i++)
		if(module[i].base == base)
			return i;
	return -1;
}

static Vector<String> test;

BOOL CALLBACK Pdb::EnumGlobals(PSYMBOL_INFO pSym, ULONG SymbolSize, PVOID UserContext)
{
//	LocalsCtx& c = *(GlobalsCtx *)UserContext;
	if(pSym->Tag == SymTagData)
		test.Add(pSym->Name);
	return TRUE;
}

void Pdb::LoadModuleInfo()
{
	ModuleInfo f;
	dword cb = 1;
	HMODULE  h;
	if(!EnumProcessModules(hProcess, &h, sizeof(HMODULE), &cb)) {
		Error();
		return;
	}
	int n = cb / sizeof(HMODULE);
	Buffer<HMODULE> m(n);
	if(!EnumProcessModules(hProcess, m, cb, &cb)) {
		Error();
		return;
	}
	Vector<ModuleInfo> nm;
	for (int i = 0; i < n; i++) {
		MODULEINFO mi;
		if(GetModuleInformation(hProcess, m[i], &mi, sizeof(mi))) {
			ModuleInfo& f = nm.Add();
			f.base = (adr_t)mi.lpBaseOfDll;
			f.size = mi.SizeOfImage;
			int q = FindModuleIndex(f.base);
			if(q >= 0) {
				ModuleInfo& of = module[q];
				f.path = of.path;
				f.symbols = of.symbols;
				of.symbols = false;
				LLOG("Stable " << Hex(f.base) << " (" << Hex(f.size) << "): " << f.path);
			}
			else {
				char name[MAX_PATH];
				if(GetModuleFileNameEx(hProcess, m[i], name, MAX_PATH)) {
					f.path = name;
					if(FileExists(ForceExt(f.path, ".pdb"))) {
						adr_t w = (adr_t)SymLoadModule64(hProcess, NULL, name, 0, f.base, f.size);
						if(w) {
							LLOG("Loading symbols " << Hex(f.base) << '/' << hProcess << " returned base " << Hex(w));
							f.symbols = true;
						#if 0
							TimeStop t;
						    SymEnumSymbols(hProcess, w, 0, &EnumGlobals, 0);
						#endif
						}
					}
				}
				LLOG(Hex(f.base) << " (" << Hex(f.size) << "): " << f.path);
			}
		}
	}
	UnloadModuleSymbols();
	module = nm;
	refreshmodules = false;
}

bool Pdb::AddBp(adr_t address)
{
	LLOG("AddBp: " << Hex(address));
	LLOG("AddBp: " << Hex((adr_t)(LPVOID) address));
	if(bp_set.Find(address) >= 0)
		return true;
	byte prev;
	if(!ReadProcessMemory(hProcess, (LPCVOID) address, &prev, 1, NULL))
		return false;
	LLOG("ReadProcessMemory OK");
	byte int3 = 0xcc;
	if(!WriteProcessMemory(hProcess, (LPVOID) address, &int3, 1, NULL))
		return false;
	LLOG("WriteProcessMemory OK");
//	FlushInstructionCache (hProcess, (LPCVOID)address, 1);
	bp_set.Put(address, prev);
	return true;
}

bool Pdb::RemoveBp(adr_t address)
{
	int pos = bp_set.Find(address);
	if(pos < 0)
		return true;
	if(!WriteProcessMemory(hProcess, (LPVOID)address, &bp_set[pos], 1, NULL))
		return false;
	FlushInstructionCache(hProcess, (LPCVOID)address, 1);
	bp_set.Unlink(pos);
	return true;
}

bool Pdb::RemoveBp()
{
	for(int i = bp_set.GetCount(); --i >= 0;)
		if(!bp_set.IsUnlinked(i)) {
			adr_t address = bp_set.GetKey(i);
			if(!WriteProcessMemory(hProcess, (LPVOID)address, &bp_set[i], 1, NULL))
				return false;
			FlushInstructionCache(hProcess, (LPCVOID)address, 1);
			bp_set.Unlink(i);
		}
	bp_set.Clear();
	return true;
}

void Pdb::Lock()
{
	if(lock == 0) {
		IdeHidePtr();
		IdeDebugLock();
		watches.Disable();
		locals.Disable();
		framelist.Disable();
		dlock.Show();
		IdeSetBar();
	}
	lock++;
}

void Pdb::Unlock()
{
	lock--;
	if(lock == 0) {
		IdeDebugUnLock();
		watches.Enable();
		locals.Enable();
		framelist.Enable();
		dlock.Hide();
		IdeSetBar();
	}
}

Pdb::Context Pdb::ReadContext(HANDLE hThread)
{
	Context r;
#ifdef CPU_64
	if(win64) {
		CONTEXT ctx;
		ctx.ContextFlags = CONTEXT_FULL;
		if(!GetThreadContext(hThread, &ctx))
			DLOG("GetThreadContext failed: " << GetLastErrorMessage());
		memcpy(&r.context64, &ctx, sizeof(CONTEXT));
	}
	else {
		WOW64_CONTEXT ctx;
		ctx.ContextFlags = WOW64_CONTEXT_FULL;
		Wow64GetThreadContext(hThread, &ctx);
		memcpy(&r.context32, &ctx, sizeof(WOW64_CONTEXT));
	}
#else
	CONTEXT ctx;
	ctx.ContextFlags = CONTEXT_FULL;
	GetThreadContext(hThread, &ctx);
	memcpy(&r.context32, &ctx, sizeof(CONTEXT));
#endif
	return r;
}

void Pdb::WriteContext(HANDLE hThread, Context& context)
{
#ifdef CPU_64
	if(win64) {
		CONTEXT ctx;
		memcpy(&ctx, &context.context64, sizeof(CONTEXT));
		ctx.ContextFlags = CONTEXT_FULL;
		if(!SetThreadContext(hThread, &ctx))
			DLOG("SetThreadContext failed: " << GetLastErrorMessage());
		_DBG_	if(GetThreadContext(hThread, &ctx)) DDUMP(Hex(ctx.Rip));
	}
	else {
		WOW64_CONTEXT ctx;
		memcpy(&ctx, &context.context32, sizeof(WOW64_CONTEXT));
		ctx.ContextFlags = CONTEXT_FULL;
		Wow64SetThreadContext(hThread, &ctx);
	}
#else
	CONTEXT ctx;
	memcpy(&ctx, &context.context32, sizeof(WOW64_CONTEXT));
	ctx.ContextFlags = CONTEXT_FULL;
	SetThreadContext(hThread, &ctx);
#endif
}

void Pdb::AddThread(dword dwThreadId, HANDLE hThread)
{
	if(threads.Find(dwThreadId) >= 0)
		return;
	Thread& f = threads.GetAdd(dwThreadId);
	// Retrive "base-level" stack-pointer, to have limit for stackwalks:
	Context c = ReadContext(hThread);
#ifdef CPU_64
	f.sp = win64 ? c.context64.Rsp : c.context32.Esp;
#else
	f.sp = c.context32.Esp;
#endif
	f.hThread = hThread;
	LLOG("Adding thread " << dwThreadId << ", Thread SP: " << Hex(f.sp) << ", handle: " << FormatIntHex((dword)(hThread)));
}

void Pdb::RemoveThread(dword dwThreadId)
{
	int q = threads.Find(dwThreadId);
	if(q >= 0) {
		Thread& f = threads[q];
		LLOG("Closing thread " << dwThreadId << ", handle: " << FormatIntHex((dword)(f.hThread)));
		CloseHandle(f.hThread);
		threads.Remove(q);
	}
}

#define EXID(id)       { id, #id },

struct {
	adr_t code;
	const char *text;
}
ex_desc[] = {
	EXID(EXCEPTION_ACCESS_VIOLATION)
	EXID(EXCEPTION_ARRAY_BOUNDS_EXCEEDED)
	EXID(EXCEPTION_DATATYPE_MISALIGNMENT)
	EXID(EXCEPTION_FLT_DENORMAL_OPERAND)
	EXID(EXCEPTION_FLT_DIVIDE_BY_ZERO)
	EXID(EXCEPTION_FLT_INEXACT_RESULT)
	EXID(EXCEPTION_FLT_INVALID_OPERATION)
	EXID(EXCEPTION_FLT_OVERFLOW)
	EXID(EXCEPTION_FLT_STACK_CHECK)
	EXID(EXCEPTION_FLT_UNDERFLOW)
	EXID(EXCEPTION_ILLEGAL_INSTRUCTION)
	EXID(EXCEPTION_IN_PAGE_ERROR)
	EXID(EXCEPTION_INT_DIVIDE_BY_ZERO)
	EXID(EXCEPTION_INT_OVERFLOW)
	EXID(EXCEPTION_INVALID_DISPOSITION)
	EXID(EXCEPTION_NONCONTINUABLE_EXCEPTION)
	EXID(EXCEPTION_PRIV_INSTRUCTION)
	EXID(EXCEPTION_STACK_OVERFLOW )
};

void Pdb::RestoreForeground()
{
	if(hWnd) {
		SetForegroundWindow(hWnd);
		LLOG("Restored foreground window: " << FormatIntHex((dword)hWnd));
	}
	hWnd = NULL;
}

void Pdb::SaveForeground()
{
	HWND hwnd = GetForegroundWindow();
	if(hwnd) {
		DWORD pid;
		GetWindowThreadProcessId(hwnd, &pid);
		if(pid == processid) {
			hWnd = hwnd;
			LLOG("Saved foreground window: " << Hex((adr_t)hWnd));
		}
	}
}

bool Pdb::RunToException()
{
	LLOG("RUN TO EXCEPTION");
	TimeStop ts;
	bool disasfocus = disas.HasFocus();
	bool locked = false;
	bool frestored = false;
	invalidpage.Clear();
	mempage.Clear();
	int opn = 0;
	for(;;) {
		if(terminated) {
			if(locked)
				Unlock();
			return false;
		}
		opn++;
		if(WaitForDebugEvent(&event, 0)) {
			opn = 0;
			running = false;
			switch(event.dwDebugEventCode) {
			case EXCEPTION_DEBUG_EVENT: {
				LLOG("EXCEPTION_DEBUG_EVENT");
				LLOG("Exception: " << FormatIntHex(event.u.Exception.ExceptionRecord.ExceptionCode) <<
				     " at: " << FormatIntHex(event.u.Exception.ExceptionRecord.ExceptionAddress) <<
				     " first: " << event.u.Exception.dwFirstChance);
				SaveForeground();
				const EXCEPTION_RECORD& x = event.u.Exception.ExceptionRecord;
				DDUMP(Hex(x.ExceptionCode));
				DDUMP(findarg(x.ExceptionCode, EXCEPTION_BREAKPOINT, EXCEPTION_SINGLE_STEP,
				              STATUS_WX86_BREAKPOINT, STATUS_WX86_SINGLE_STEP));
				if(findarg(x.ExceptionCode, EXCEPTION_BREAKPOINT, EXCEPTION_SINGLE_STEP,
				                            STATUS_WX86_BREAKPOINT, STATUS_WX86_SINGLE_STEP) < 0)
				{
					DLOG("EXCEPTION");
					if(event.u.Exception.dwFirstChance) {
						LLOG("First chance " << FormatIntHex(x.ExceptionCode));
						Context c = ReadContext(threads[0].hThread);
						DDUMP(Hex(c.context64.Rip)); _DBG_
						break;
					}
					String desc = Format("Exception: [* %lX] at [* %08llX]&",
					                     (int64)x.ExceptionCode, (int64)x.ExceptionAddress);
					for(int i = 0; i < __countof(ex_desc); i++)
						if(ex_desc[i].code == x.ExceptionCode)
							desc << "[* " << DeQtf(ex_desc[i].text) << "]&";
					if(x.ExceptionCode == EXCEPTION_ACCESS_VIOLATION) {
						desc << (x.ExceptionInformation[0] ? "[*@3 writing]" : "[*@4 reading]");
						desc << Format(" at [* %08llX]", (int64)x.ExceptionInformation[1]);
					}
					PromptOK(desc);// better owner!!!
				}
				TopWindow *w = GetTopWindow();
				if(w && !w->IsForeground()) {
					LLOG("Setting theide as foreground");
					GetTopWindow()->SetForeground();
				}
				if(disasfocus)
					disas.SetFocus();
				if(locked)
					Unlock();
				if(refreshmodules)
					LoadModuleInfo();
				LLOG("event.dwThreadId = " << event.dwThreadId);
				for(int i = 0; i < threads.GetCount(); i++) {
					Thread& t = threads[i];
					(Context&)t = ReadContext(threads[i].hThread);
					if(event.dwThreadId == threads.GetKey(i)) {
						LLOG("Setting current context");
						if(findarg(event.u.Exception.ExceptionRecord.ExceptionCode, EXCEPTION_BREAKPOINT, STATUS_WX86_BREAKPOINT) >= 0
						   && bp_set.Find((win64 ? t.context64.Rip : t.context32.Eip) - 1) >= 0)
						   // We have stopped at breakpoint, need to move address back for retry
					#ifdef CPU_64
							if(win64)
								t.context64.Rip--;
							else
					#endif
								t.context32.Eip--;
						context = t;
					}
				}
				DDUMP(Hex(context.context64.Rip));
				RemoveBp();
				return true;
			}
			case CREATE_THREAD_DEBUG_EVENT:
				LLOG("Create thread: " << event.dwThreadId);
				AddThread(event.dwThreadId, event.u.CreateThread.hThread);
				break;
			case EXIT_THREAD_DEBUG_EVENT:
				LLOG("Exit thread: " << event.dwThreadId);
				RemoveThread(event.dwThreadId);
				break;
			case CREATE_PROCESS_DEBUG_EVENT:
				LLOG("Create process: " << event.dwProcessId);
				processid = event.dwProcessId;
				AddThread(event.dwThreadId, event.u.CreateProcessInfo.hThread);
				CloseHandle(event.u.CreateProcessInfo.hFile);
				CloseHandle(event.u.CreateProcessInfo.hProcess);
				break;
			case EXIT_PROCESS_DEBUG_EVENT:
				LLOG("Exit process: " << event.dwProcessId);
				if(locked)
					Unlock();
				terminated = true;
				return false;
				CleanupOnExit();
				if(ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE))
					LLOG("ContinueDebugEvent(EXIT_PROCESS_DEBUG_EVENT) -> OK");
				else
					LLOG("ContinueDebugEvent -> " << GetErrorMessage(GetLastError()));
				return false;
			case LOAD_DLL_DEBUG_EVENT: {
				LLOG("Load dll: " << event.u.LoadDll.lpBaseOfDll);
				CloseHandle(event.u.LoadDll.hFile);
				refreshmodules = true;
				break;
			}
			case UNLOAD_DLL_DEBUG_EVENT:
				LLOG("UnLoad dll: " << event.u.UnloadDll.lpBaseOfDll);
				refreshmodules = true;
				break;
			case RIP_EVENT:
				LLOG("RIP!");
				Exclamation("Process being debugged died unexpectedly!");
				terminated = true;
				if(locked)
					Unlock();
				return false;
			}
			ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_EXCEPTION_NOT_HANDLED);
			running = true;
		}
		if(ts.Elapsed() > 200) {
			if(!lock) {
				Lock();
				locked = true;
			}
			if(!frestored) {
				RestoreForeground();
				frestored = true;
			}
		}
		if(lock) {
			GuiSleep(opn < 1000 ? 0 : 100);
			Ctrl::ProcessEvents();
		}
		else
			Sleep(opn < 1000 ? 0 : 100);
	}
}

/*
const CONTEXT& Pdb::CurrentContext()
{
	return threads.Get((int)~threadlist).context;
}
*/

void Pdb::WriteContext(dword cf)
{
	DLOG("WriteContext");
	WriteContext(threads.Get(event.dwThreadId).hThread, context);
}

bool Pdb::SingleStep()
{
	LLOG("SINGLE STEP 0");
#if CPU_64
	if(win64)
		context.context64.EFlags |= 0x100;
	else
#endif
		context.context32.EFlags |= 0x100;
	WriteContext();
	running = true;
	ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE);
	if(!RunToException())
		return false;
#if CPU_64
	if(win64)
		context.context64.EFlags &= ~0x100;
	else
#endif
		context.context32.EFlags &= ~0x100;
	WriteContext();
	return true;
}

bool Pdb::Continue()
{
	LLOG("** Continue");
	running = true;
	ContinueDebugEvent(event.dwProcessId, event.dwThreadId, DBG_CONTINUE);
	return RunToException();
}

void Pdb::SetBreakpoints()
{
	RemoveBp();
	for(int i = 0; i < breakpoint.GetCount(); i++)
		AddBp(breakpoint[i]);
}

void Pdb::BreakRunning() //TODO: Fix in wow64?
{
	stop = true;
	if(running) {
		BOOL (WINAPI *debugbreak)(HANDLE Process);
		debugbreak = (BOOL (WINAPI *)(HANDLE))
		             GetProcAddress(GetModuleHandle("kernel32.dll"), "DebugBreakProcess");
		if(debugbreak)
			(*debugbreak)(hProcess);
		else
			for(int i = 0; i < threads.GetCount(); i++) {
				HANDLE hThread = threads[i].hThread;
				SuspendThread(hThread);
				CONTEXT ctx;
				ctx.ContextFlags = CONTEXT_CONTROL;
				GetThreadContext(hThread, &ctx);
				ctx.EFlags |= 0x100;
				SetThreadContext(hThread, &ctx);
				GetThreadContext(hThread, &ctx);
				ResumeThread(hThread);
			}
	}
}

void Pdb::Stop()
{
	terminated = true;
}

bool Pdb::IsFinished()
{
	return terminated;
}

#endif
