/*
*	<aboutwindow.h>
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

#ifndef _ABOUTWINDOW_H_
#define _ABOUTWINDOW_H_

#include "namespaces.h"
#include "window.h"

/*
*	AboutWindow Class
*/
ref class AboutWindow : public Window
{
private:
	Window ^prevForm;
	Panel ^panelAbout;
	TextBox ^textboxLicense;
	LinkLabel
		^lnklabelBack,
		^lnklabelAboutInfo;

	void InitializeComponent();
	void OnLnkLabelBackClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e);
	void OnLnkLabelAboutClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e);

protected:

	!AboutWindow()
	{
	}

	~AboutWindow()
	{
		this->!AboutWindow();
	}

public:

	AboutWindow(Window ^form);

	virtual void Show() override;
	virtual void Hide() override;
};
#endif

#pragma endregion