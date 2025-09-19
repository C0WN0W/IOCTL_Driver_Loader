#pragma once
#include "Utils/GlobalVars.hpp"

// these shitty structs were copied from a decompiled shit project
struct Struct10317 {
	DWORD Member1031A;
	DWORD Member1031B;
	DWORD Member1031C;
	DWORD Member1031D;
};

struct Struct10318 {	// _SERVICE_STATUS
	DWORD Member1031E;	// dwServiceType
	DWORD Member1031F;	// dwCurrentState
	DWORD Member10320;	// dwControlsAccepted
	DWORD Member10321;	// dwWin32ExitCode
	DWORD Member10322;	// dwServiceSpecificExitCode
	DWORD Member10323;	// dwCheckPoint
	DWORD Member10324;	// dwWaitHint
};						// SERVICE_STATUS, *LPSERVICE_STATUS

struct Struct10319 {
	DWORD Member10325;
	DWORD Member10326;
	DWORD Member10327;
	DWORD Member10328;
	DWORD Member10329;
	DWORD Member1032A;
	DWORD Member1032B;
};