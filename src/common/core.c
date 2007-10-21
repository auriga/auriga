// $Id: core.c,v 1.1.1.1 2004/06/24 19:29:20 running_pinata Exp $
// original : core.c 2003/02/26 18:03:12 Rev 1.7

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#	include <windows.h>
#else
#	include <unistd.h>
#	include <signal.h>
#endif

#include "core.h"
#include "socket.h"
#include "timer.h"
#include "malloc.h"
#include "utils.h"
#include "lock.h"

// for VC.NET 2005
#if _MSC_VER >= 1400
#pragma comment(lib, "user32.lib")
#endif

int packet_parse_time = 0;

/*======================================
 *	CORE : Signal Sub Function
 *--------------------------------------
 */

static volatile int auriga_is_running = 1;

#ifdef _WIN32
static BOOL WINAPI core_CtrlHandlerRoutine( DWORD dwCtrlType )
{
	auriga_is_running = 0;
	return TRUE;
}
#else
static void sig_proc(int sn)
{
	switch(sn){
	case SIGINT:
	case SIGTERM:
		auriga_is_running = 0;
		break;
	}
}
#endif

/*======================================
 *	CORE : MAINROUTINE
 *--------------------------------------
 */

static char pid_file[256];

static void pid_delete(void)
{
	remove(pid_file);
}

static void pid_create(const char* file)
{
	FILE *fp;
	int len, lock;

	strncpy(pid_file, file, sizeof(pid_file) - 1);
	pid_file[sizeof(pid_file)-1] = '\0';

	len = (int)strlen(pid_file);
	if(len > 4 && pid_file[len - 4] == '.') {
		pid_file[len - 4] = 0;
	}
	strcat(pid_file,".pid");
	fp = lock_fopen(pid_file, &lock);
	if(fp) {
#ifdef _WIN32
		fprintf(fp,"%lu",(unsigned long)GetCurrentProcessId());
#else
		fprintf(fp,"%d",getpid());
#endif
		lock_fclose(fp, pid_file, &lock);
		atexit(pid_delete);
	}
}

double uptime(void)
{
	static time_t boot = 0;
	time_t now;

	if(boot == 0) {
		time(&boot);
	}
	time(&now);

	return (now - boot) / 86400.0;
}

#ifdef _WIN32

#include <imagehlp.h>
#pragma comment(lib, "imagehlp.lib")

static LONG WINAPI core_ExceptionRoutine(struct _EXCEPTION_POINTERS *e)
{
	HANDLE hProcess, hThread, hFile;
	SYSTEMTIME t;
	DWORD len, temp;
#ifdef _WIN64
	DWORD64            offset;
	STACKFRAME64       stack;
	IMAGEHLP_LINE64    lineinfo;
	IMAGEHLP_SYMBOL64 *symbol;
#else
	DWORD            offset;
	STACKFRAME       stack;
	IMAGEHLP_LINE    lineinfo;
	IMAGEHLP_SYMBOL *symbol;
#endif
	char  buf[256];
	const char* ErrType = "UNKNOWN";

	switch( e->ExceptionRecord->ExceptionCode ) {
		case EXCEPTION_ACCESS_VIOLATION:
			ErrType = "ACCESS_VIOLATION";
			break;
		case EXCEPTION_ARRAY_BOUNDS_EXCEEDED:
			ErrType = "ARRAY_BOUNDS_EXCEEDED";
			break;
		case EXCEPTION_DATATYPE_MISALIGNMENT:
			ErrType = "DATATYPE_MISALIGNMENT";
			break;
		case EXCEPTION_FLT_DIVIDE_BY_ZERO:
			ErrType = "FLT_DIVIDE_BY_ZERO";
			break;
		case EXCEPTION_ILLEGAL_INSTRUCTION:
			ErrType = "ILLEGAL_INSTRUCTION";
			break;
		case EXCEPTION_IN_PAGE_ERROR:
			ErrType = "IN_PAGE_ERROR";
			break;
		case EXCEPTION_INT_DIVIDE_BY_ZERO:
			ErrType = "INT_DIVIDE_BY_ZERO";
			break;
		case EXCEPTION_PRIV_INSTRUCTION:
			ErrType = "PRIV_INSTRUCTION";
			break;
		case EXCEPTION_STACK_OVERFLOW:
			ErrType = "STACK_OVERFLOW";
			break;
		case EXCEPTION_NONCONTINUABLE_EXCEPTION:
			ErrType = "NONCONTINUABLE_EXCEPTION";
			break;
		case EXCEPTION_INVALID_DISPOSITION:
		default:
			// 例外ハンドラのミス or 何もしない例外
			return EXCEPTION_CONTINUE_SEARCH;
	}

	hThread  = GetCurrentThread();
	hProcess = GetCurrentProcess();
	hFile = CreateFile(
		"crashdump.log", GENERIC_WRITE, FILE_SHARE_READ, NULL,
		OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL
	);

	// ログが取れなかったので何もしない。
	if( hFile == INVALID_HANDLE_VALUE )
		return EXCEPTION_CONTINUE_SEARCH;

	SetFilePointer( hFile, 0, NULL, FILE_END );
	GetLocalTime( &t );
	len = wsprintf(
		buf, "%04u/%02u/%02u %02u:%02u:%02u crashed by %s.\r\n",
		t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, ErrType
	);
	WriteFile( hFile, buf, len, &temp, NULL );

	len = wsprintf(buf, "\t%s\r\n", GetCommandLine());
	WriteFile( hFile, buf, len, &temp, NULL );

#ifdef _WIN64
	len = wsprintf(
		buf, "\tRIP: %08x%08x RSP: %08x%08x RBP: %08x%08x\r\n\r\n",
		(int)(e->ContextRecord->Rip >> 32), (int)(e->ContextRecord->Rip & 0xFFFFFFFF),
		(int)(e->ContextRecord->Rsp >> 32), (int)(e->ContextRecord->Rsp & 0xFFFFFFFF),
		(int)(e->ContextRecord->Rbp >> 32), (int)(e->ContextRecord->Rbp & 0xFFFFFFFF)
	);
	WriteFile( hFile, buf, len, &temp, NULL );
#else
	len = wsprintf(
		buf, "\tEIP: %08x ESP: %08x EBP: %08x\r\n\r\n",
		e->ContextRecord->Eip, e->ContextRecord->Esp, e->ContextRecord->Ebp
	);
	WriteFile( hFile, buf, len, &temp, NULL );
#endif

	symbol = (IMAGEHLP_SYMBOL *)GlobalAlloc( GMEM_FIXED, sizeof(symbol) + 512 );
	ZeroMemory( symbol, sizeof(symbol) + 512 );
	symbol->SizeOfStruct  = sizeof(symbol);
	symbol->MaxNameLength = 512;

	ZeroMemory( &stack,    sizeof(stack)    );
	ZeroMemory( &lineinfo, sizeof(lineinfo) );

	lineinfo.SizeOfStruct = sizeof(lineinfo);

#ifdef _WIN64
	stack.AddrPC.Offset    = e->ContextRecord->Rip;
	stack.AddrStack.Offset = e->ContextRecord->Rsp;
	stack.AddrFrame.Offset = e->ContextRecord->Rbp;
#else
	stack.AddrPC.Offset    = e->ContextRecord->Eip;
	stack.AddrStack.Offset = e->ContextRecord->Esp;
	stack.AddrFrame.Offset = e->ContextRecord->Ebp;
#endif
	stack.AddrPC.Mode      = AddrModeFlat;
	stack.AddrStack.Mode   = AddrModeFlat;
	stack.AddrFrame.Mode   = AddrModeFlat;

	SymSetOptions(SymGetOptions() | SYMOPT_LOAD_LINES);
	SymInitialize(hProcess, NULL, TRUE);

#ifdef _WIN64
	while(StackWalk64(
		IMAGE_FILE_MACHINE_AMD64, hProcess, hThread, &stack,
		e->ContextRecord, NULL, SymFunctionTableAccess64, SymGetModuleBase64, NULL)
#else
	while(StackWalk(
		IMAGE_FILE_MACHINE_I386, hProcess, hThread, &stack,
		e->ContextRecord, NULL, SymFunctionTableAccess, SymGetModuleBase, NULL)
#endif
	) {
#ifdef __BORLANDC__
		// BCC の場合はシンボル名が分からないのでアドレスは引かない。
		// シンボル名の出力はcrashdump.plで行う。
		len = wsprintf(buf, "\t0x%08x : unknown\r\n", stack.AddrPC.Offset);
#elif defined(_WIN64)
		// SymGetSymFromAddr64 は使用するべきじゃないらしい…。
		if(SymGetSymFromAddr(hProcess, stack.AddrPC.Offset, &offset, symbol)) {
			len = wsprintf(
				buf, "\t0x%08x%08x : %s + 0x%x",
				(int)(stack.AddrPC.Offset >> 32),
				(int)(stack.AddrPC.Offset & 0xFFFFFFFF), symbol->Name, (int)offset
			);
			if( SymGetLineFromAddr64( hProcess, stack.AddrPC.Offset, &temp, &lineinfo ) ) {
				len += wsprintf(
					buf+len, " (%s line %d)",
					lineinfo.FileName, lineinfo.LineNumber
				);
			}
			len += wsprintf(buf+len, "\r\n");
		} else {
			len = wsprintf(
				buf, "\t0x%08x%08x : unknown\r\n",
				(int)(stack.AddrPC.Offset >> 32),
				(int)(stack.AddrPC.Offset & 0xFFFFFFFF)
			);
		}
#else
		if(SymGetSymFromAddr(hProcess, stack.AddrPC.Offset, &offset, symbol)) {
			len = wsprintf(
				buf, "\t0x%08x : %s + 0x%x",
				stack.AddrPC.Offset, symbol->Name, offset
			);
			if( SymGetLineFromAddr( hProcess, stack.AddrPC.Offset, &temp, &lineinfo ) ) {
				len += wsprintf(
					buf+len, " (%s line %d)",
					lineinfo.FileName, lineinfo.LineNumber
				);
			}
			len += wsprintf(buf+len, "\r\n");
		} else {
			len = wsprintf(buf, "\t0x%08x : unknown\r\n", stack.AddrPC.Offset);
		}
#endif
		WriteFile( hFile, buf, len, &temp, NULL );
	}

	SymCleanup( hProcess );
	GlobalFree( symbol );

	len = wsprintf(buf, "\r\n\r\n----------------------------------------\r\n");
	WriteFile( hFile, buf, len, &temp, NULL );
	CloseHandle( hFile );
#ifndef _MSC_VER
	ExitProcess(0);
#endif
	return EXCEPTION_CONTINUE_SEARCH;
}

#endif

int main(int argc,char **argv)
{
	int next;

	pid_create(argv[0]);
	do_init_memmgr(argv[0]); // 一番最初に実行する必要がある
	do_socket();

#ifdef _WIN32
	SetConsoleCtrlHandler( core_CtrlHandlerRoutine, TRUE );
	SetUnhandledExceptionFilter( core_ExceptionRoutine );

	srand(gettick() ^ (GetCurrentProcessId() << 8));
	atn_srand(gettick() ^ (GetCurrentProcessId() << 8));
#else
	signal(SIGTERM,sig_proc);
	signal(SIGINT,sig_proc);

	srand(gettick() ^ (getpid() << 8));
	atn_srand(gettick() ^ (getpid() << 8));
#ifdef SIGPIPE
	signal(SIGPIPE,SIG_IGN);
#endif
#endif

	atexit(do_final);
	do_init(argc,argv);
	if (packet_parse_time > 0) {
		add_timer_func_list(parsepacket_timer,"parsepacket_timer");
		add_timer_interval(gettick()+packet_parse_time,parsepacket_timer,0,0,packet_parse_time);

		while(auriga_is_running) {
			next = do_timer(gettick_nocache());
			do_sendrecv(next);
		}
	} else {
		while(auriga_is_running) {
			next = do_timer(gettick_nocache());
			do_sendrecv(next);
			do_parsepacket();
		}
	}
	do_pre_final();

	exit(0);
	return 0;
}
