// This file is part of LuaScript.
// 
// Original work Copyright (C)2010, 2011, 2014 Dave Brotherstone
// Derived work Copyright (C)2016 Justin Dailey <dail8859@yahoo.com>
// 
// LuaScript is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public License
// as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#pragma once

#include "DockingDlgInterface.h"
#include "ConsoleInterface.h"
#include "Scintilla.h"
#include "GUI.h"

#include <vector>

struct SCNotification;
struct NppData;
struct LineDetails;
typedef std::basic_string<TCHAR> tstring;

class ConsoleDialog : public DockingDlgInterface
{
public:
	ConsoleDialog();
	ConsoleDialog(const ConsoleDialog& other);
	~ConsoleDialog();

	void initDialog(HINSTANCE hInst, NppData& nppData, ConsoleInterface *console);

	void doDialog();
	void hide();

	void writeText(size_t length, const char *text);
	void writeError(size_t length, const char *text);
	void clearText();
	void setPrompt(const char *prompt);
	HWND getScintillaHwnd() { return (HWND)m_sciOutput.GetID(); }

	void giveInputFocus() { SetFocus((HWND)m_sciInput.GetID()); }

protected:
	BOOL CALLBACK run_dlgProc(UINT Message, WPARAM wParam, LPARAM lParam);

private:
	ConsoleDialog& operator = (const ConsoleDialog&); // assignment operator disabled

	void createOutputWindow(HWND hParentWindow);
	void createInputWindow(HWND hParentWindow);
	void setStyles(GUI::ScintillaWindow &sw);
	void runStatement();

	static LRESULT CALLBACK inputWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);
	static LRESULT CALLBACK scintillaWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, UINT_PTR uIdSubclass, DWORD_PTR dwRefData);

	void showAutoCompletion();

	void historyNext();
	void historyPrevious();
	void historyAdd(const TCHAR *line);
	void historyEnd();

	tTbData m_data;
	GUI::ScintillaWindow  m_sciOutput;
	GUI::ScintillaWindow  m_sciInput;

	ConsoleInterface *m_console;
	std::string m_prompt;
	HICON m_hTabIcon;

	std::vector<tstring> m_history;
	tstring m_curLine;
	size_t m_currentHistory;

	HMENU m_hContext;
};

