/*
*	<window.h>
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

#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "namespaces.h"
#include <gcroot.h>

/*
*	Parent Window Class
*/
ref class Window
{
protected:

	!Window()
	{
	}
	virtual ~Window()
	{
		this->!Window();
	}

public:

	Form ^form;

	static ToolTip ^tooltip = gcnew ToolTip;

	static void Add(Control ^control);
	static void Remove(Control ^control);
	static void PauseLayout();
	static void ResumeLayout();
	static void PerformLayout();

	virtual void Show();
	virtual void Hide();

	void Display(Window ^form);
};
#endif

#pragma endregion