/*
*	<utils.h>
*
*
*	Copyright (C) 2020 Aloever Dulay
*
*	This program is free software: you can redistribute it and/or modify it under the terms
*	of the GNU General Public License as published by the Free Software Foundation, version 3.
*
*	This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
*	without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*	See the GNU General Public License for more details.
*
*	You should have received a copy of the GNU General Public License along with this program.
*	If not, see <https://www.gnu.org/licenses/>.
*
*/
#pragma once

#ifndef _UTILS_H_
#define _UTILS_H_

#include "namespaces.h"
#include <string>


#define MIN(a, b) ((a < b) ? a : b)
#define CharArrayToString(pwc) static_cast<String^>(gcnew String((pwc).data()))

enum AnchorType
{
	TOP 			= AnchorStyles::Top,
	BOTTOM 			= AnchorStyles::Bottom,
	LEFT 			= AnchorStyles::Left,
	RIGHT 			= AnchorStyles::Right,
	TOP_LEFT 		= TOP | LEFT,
	TOP_RIGHT 		= TOP | RIGHT,
	BOTTOM_LEFT 	= BOTTOM | LEFT,
	BOTTOM_RIGHT 	= BOTTOM | RIGHT,
	CENTER_TOP 		= TOP | LEFT | RIGHT,
	CENTER_BOTTOM 	= BOTTOM | LEFT | RIGHT,
	CENTER 			= TOP | BOTTOM | LEFT | RIGHT
};

void CreateTextBox(TextBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, bool multiline);
void CreateLabel(Label ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor);
void CreateLinkLabel(LinkLabel ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor, LinkLabelLinkClickedEventHandler ^onClickHandler);
void CreateButton(Button ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onClickHandler);
void CreateComboBox(ComboBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onLostFocus);
void CreateCheckBox(CheckBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, Appearance look, bool autoCheck, EventHandler ^onCheckStateChanged);
void CreatePanel(Panel ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, bool autoScroll);
bool IsWhitespace(wchar_t c);
bool GetTextFiles(Collections::IList ^%list);
bool GetTranslations(Collections::IList ^%list);
String ^ReadTranslationFile(String ^entryName);
String ^GetEqualTranslation(String ^string);
std::wstring StringToCharArray(String ^str);

#endif

#pragma endregion