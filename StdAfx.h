// Clavier+
// Keyboard shortcuts manager
//
// Copyright (C) 2000-2008 Guillaume Ryder
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.


#pragma once

#pragma warning (disable: 4710 4711)

// Require compatibility with Windows 2000 or later.
#define NTDDI_VERSION NTDDI_WIN2K
#define _WIN32_IE       _WIN32_IE_IE60
#define _WIN32_WINNT    _WIN32_WINNT_WIN2K
#define STRICT  1
#include <sdkddkver.h>

// Disable some Microsoft standard library extensions.
#define __STDC_WANT_SECURE_LIB__  0
#define _CRT_DISABLE_PERFCRIT_LOCKS
#define _STRALIGN_USE_SECURE_CRT  0

// Do not include some Windows APIs we don't need.
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#define NOGDICAPMASKS
#define NOSYSCOMMANDS
#define NORASTEROPS
#define OEMRESOURCE
#define NOATOM
#define NOMEMMGR
#define NOMETAFILE
#define NOMINMAX
#define NOOPENFILE
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOPROFILER
#define NOMCX


#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <commctrl.h>
#include <commdlg.h>

#include <tchar.h>


// Memory leaks detection
#ifdef _DEBUG
#include <stdlib.h>
#include <crtdbg.h>
#define DEBUG_NEW  new(_NORMAL_BLOCK, __FILE__, __LINE__)
#else
#define DEBUG_NEW  new
#endif

#define new DEBUG_NEW


#ifndef UNICODE
#error Non-Unicode is no longer supported
#endif


#define toBool(value)  ((value) != 0)
#define arrayLength(static_array)  (sizeof(static_array) / sizeof(static_array[0]))
#define MY_UNUSED(ignored)

#define VERIFP(f, value)  { if (!(f))  return (value); }
#define VERIF(f)  VERIFP(f,false)
#define VERIFV(f)  { if (!(f))  return; }

#define min(a, b)  (((a) < (b)) ? (a) : (b))
#define max(a, b)  (((b) < (a)) ? (a) : (b))
