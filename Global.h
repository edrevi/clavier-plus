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

#include "Resource.h"

#include "MyString.h"


const size_t bufString = 128;
const size_t bufHotKey = 128;
const size_t bufCode = 32;
const size_t bufWindowTitle = 256;

const int bufClipboardString = MAX_PATH * 10;

// Name of the environment variable set by clipboardToEnvironment().
const LPCTSTR clipboard_env_variable = _T("CLIPBOARD");


const LPCTSTR pszApp = _T("Clavier+");


extern HANDLE e_hHeap;
extern HINSTANCE e_hInst;
extern HWND e_hwndInvisible;  // Invisible background window
extern HWND e_hdlgModal;
extern bool e_bIconVisible;


inline WNDPROC subclassWindow(HWND hwnd, WNDPROC new_window_proc) {
	return reinterpret_cast<WNDPROC>(SetWindowLongPtr(hwnd, GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(new_window_proc)));
}


// Display a message box. The message is read from string resources.
int messageBox(HWND hwnd, UINT idString, UINT uType = MB_ICONERROR, LPCTSTR pszArg = NULL);

// Centers a window relatively to its parent.
void centerParent(HWND hwnd);

// Reads the text of a dialog box control.
void getDlgItemText(HWND hdlg, UINT id, String& str);

// Setups a label control for displaying an URL.
//
// Args:
//   hdlg: The handle of the dialog box containing the control to setup.
//   control_id: The ID of the label control in the dialog box.
//   link: The URL to give to the control. It must be static buffer: the string will not
//     be copied to a buffer.
void initializeWebLink(HWND hdlg, UINT control_id, LPCTSTR link);

// Wrapper for CreateThread()
void startThread(LPTHREAD_START_ROUTINE pfn, void* params);

// Writes a NULL-terminated string to a file.
void writeFile(HANDLE hf, LPCTSTR strbuf);

// Retrieves the basename of the process that created a window.
//
// Args:
//   hwnd: The window to get the process name of.
//   process_name: The buffer where to put the basename of the process that created the window,
//     in lowercase. Should have a size of MAX_PATH.
//
// Returns:
//   True on success (process_name contains a valid name), false on failure.
bool getWindowProcessName(HWND hwnd, LPTSTR process_name);

// Sleeps in idle priority.
//
// Args:
//   dwDurationMS: The time to sleep, in milliseconds.
void sleepBackground(DWORD dwDurationMS);

// Wrapper for SHGetFileInfo() that does not call the function if the file belongs
// to a slow device. If the call to SHGetFileInfo() fails and SHGFI_USEFILEATTRIBUTES was not
// specified in flags, the flag is added and SHGetFileInfo() is called again.
//
// Args:
//   path: The path of the file or directory to call SHGetFileInfo() on.
//   file_attributes: Given as argument to SHGetFileInfo().
//   shfi: Where to save the result of SHGetFileInfo().
//   flags: Given as argument to SHGetFileInfo(). If path is on a slow device,
//     according pathIsSlow(), SHGFI_USEFILEATTRIBUTES is added to flags before it is given
//     to SHGetFileInfo().
//
// Returns:
//   True on success, false on failure.
bool getFileInfo(LPCTSTR path, DWORD file_attributes, SHFILEINFO& shfi, UINT flags);

// Puts the text contents of the clipboard to the environment variable named clipboard_env_variable.
void clipboardToEnvironment();

// Returns a visible child of a window matching the given window class name, if any.
//
// Args:
//   hwnd_parent: The parent to consider the child window of.
//   wnd_class: The window class the returned window should match.
//   allow_same_prefix: If false, the returned window will have exactly wnd_class as class name.
//     If true, it will have wnd_class only as prefix; full equality is not enforced.
//
// Returns:
//   The handle of a matching window, with no particular priority if several windows match,
//   or NULL if no matching window is found.
HWND findVisibleChildWindow(HWND hwnd_parent, LPCTSTR wnd_class, bool allow_same_prefix);

// Determines whether a window has a window class, or a prefix of it.
//
// Args:
//   hwnd: The window to check the class of.
//   wnd_class: The class the window should have.
//   allow_same_prefix: If false, the window should have exactly wnd_class as class name to match.
//     If true, it should only have wnd_class only as prefix; full equality is not enforced.
//
// Returns:
//   True if the class of hwnd matches wnd_class.
bool checkWindowClass(HWND hwnd, LPCTSTR wnd_class, bool allow_same_prefix);

// Finds a top-level window whose title matches a regexp.
//
// Args:
//   title_regexp: The regular expression the title of the returned window will match.
//     The regular expression is evaluated by matchWildcards().
//
// Returns:
//   The handle of a window matching the title regexp, with no particular priority if several
//   windows match.
HWND findWindowByName(LPCTSTR title_regexp);

// Determines if a string matches a wildcards pattern, by ignoring case.
//
// Args:
//   pattern: The pattern to use for testing matching. Supports '*' and '?'.
//     This string must be given in lower case.
//   subject: The string to test against the pattern. The case does not matter.
//   pattern_end: If not null, points to the successor of the last character of the pattern; if
//     equals pattern, the pattern will be considered empty.
//
// Returns:
//   True if the subject matches the pattern, false otherwise.
bool matchWildcards(LPCTSTR pattern, LPCTSTR subject, LPCTSTR pattern_end = NULL);

// Copies text into the clipboard.
void setClipboardText(LPCTSTR text);


//------------------------------------------------------------------------
// SHBrowseForFolder wrapper:
// - use custom title
// - set initial directory
// - return directory path instead of LPITEMIDLIST
//------------------------------------------------------------------------

bool browseForFolder(HWND hwnd_parent, LPCTSTR title, LPTSTR directory);


//------------------------------------------------------------------------
// Changes the current directory in the given dialog box.
// Supported dialog boxes:
// - Standard Windows File/Open and similar: GetOpenFileName, GetSaveFileName
// - MS Office File/Open and similar
// - Standard Windows folder selection: SHBrowseForFolder
//
// Args:
//   hwnd: The window handle of the dialog box or one of its controls.
//   directory: The directory to set in the dialog box.
//
// Returns:
//   True if the dialog box is supported and the current directory has been changed.
//------------------------------------------------------------------------

bool setDialogBoxDirectory(HWND hwnd, LPCTSTR directory);


//------------------------------------------------------------------------
// Shell API tools
//------------------------------------------------------------------------

bool getSpecialFolderPath(int index, LPTSTR path);
bool getShellLinkTarget(LPCTSTR link_file, LPTSTR target_path);


//------------------------------------------------------------------------
// Application-specific helpers
//------------------------------------------------------------------------

// Returns the translation of a token in the current language.
LPCTSTR getToken(int tok);

// Returns the name of a language in this language.
LPCTSTR getLanguageName(int lang);

// Returns the index of a token from its name. The name of the token can be in any language.
//
// Returns:
//   A tok* enum value, or tokNotFound if the token does not match any token.
int findToken(LPCTSTR token);

// Increments a string pointer until the end of the string or a comma is encountered, then skips
// spaces. The comma is replaced by a null character, so that the initial pointer (before being
// incremented) will point to the string before the comma.
//
// Args:
//   chr_ptr: A reference to the pointer to increment. The string initially pointed will be
//     unescaped if unescape is true.
//   unescape: If true, unescapes the string according to backslashes. The string is unescaped in
//     place, which is possible because the unescaping process can only reduce the string length.
void skipUntilComma(TCHAR*& chr_ptr, bool unescape = false);

// Isolates the next ';'-separated token with a '\0'.
// Returns token_start, then modifies token_start to point to the start of the next token.
LPCTSTR getSemiColonToken(LPTSTR& token_start);


//------------------------------------------------------------------------
// Strings translation
//------------------------------------------------------------------------

#include "I18n.h"

// A string translated in all available languages.
class TranslatedString {
public:
	
	// Loads the translation of the string for the current language.
	void load(UINT id) {
		m_translations[i18n::getLanguage()].loadString(id);
	}
	
	// Sets the translation of the string for the current language.
	void set(LPCTSTR strbuf) {
		m_translations[i18n::getLanguage()] = strbuf;
	}
	
	// Returns the translation of the string for a given language,
	// an empty string when the translation should use the default.
	LPCTSTR get(int lang) const {
		return m_translations[lang];
	}
	
	// Returns the translation of the string for the current language.
	// Falls back to the default default if the translation is empty.
	LPCTSTR get() const {
		LPCTSTR translation = get(i18n::getLanguage());
		return *translation ? translation : get(i18n::langDefault);
	}
	
private:
	
	// Translations of the string, indexed by language.
	String m_translations[i18n::langCount];
};


//------------------------------------------------------------------------
// Command line parsing and executing
//------------------------------------------------------------------------

void findFullPath(LPTSTR path, LPTSTR full_path);

void shellExecuteCmdLine(LPCTSTR command, LPCTSTR directory, int show_mode);


class ShellExecuteThread {
public:
	
	ShellExecuteThread(const String& command, const String& directory, int show_mode)
		: m_command(command), m_directory(directory), m_show_mode(show_mode) {}
	
	static DWORD WINAPI thread(void* params);
	
private:
	
	String m_command;
	String m_directory;
	int m_show_mode;
};


//------------------------------------------------------------------------
// Settings loading and saving
//------------------------------------------------------------------------

enum {
	colContents,
	colKeystroke,
	colCond,
	colUsageCount,
	colDescription,
	colCount
};

const int nbColSize = colCount - 1;

extern int e_acxCol[colCount];

extern SIZE e_sizeMainDialog;
extern bool e_bMaximizeMainDialog;

extern TCHAR e_pszIniFile[MAX_PATH];


//------------------------------------------------------------------------
// Autostart setting
//------------------------------------------------------------------------

bool isAutoStartEnabled();
void setAutoStartEnabled(bool enabled);
