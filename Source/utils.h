/*
*	<utils.h>
*
*
*	Copyright (C) 2019 Aloever Dulay
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
void CreateButton(Button ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onClickHandler);
void CreateComboBox(ComboBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onLostFocus);
bool IsWhitespace(wchar_t c);
bool GetTextFiles(Collections::IList ^%list);
bool GetTranslations(Collections::IList ^%list);

#endif

#pragma endregion