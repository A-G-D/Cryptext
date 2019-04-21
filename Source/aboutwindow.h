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
#include "winformstemplate.h"

/*
*	AboutWindow Class
*/
ref class AboutWindow : public WinFormsTemplate::AppPage
{
private:

	Panel ^panelAbout;
	LinkLabel
		^lnklabelBack,
		^lnklabelAboutInfo;

	void OnLnkLabelAboutClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e);

protected:

	!AboutWindow()
	{
	}
	~AboutWindow()
	{
		this->!AboutWindow();
	}

	virtual void InitializeComponent() override;

public:

	AboutWindow();
};

/*
*	LicenseWindow Class
*/
ref class LicenseWindow : public WinFormsTemplate::AppPage
{
private:

	LinkLabel ^lnklabelBack;
	TextBox ^textboxLicense;
	
	void OnLnkLabelBackClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e);

protected:

	!LicenseWindow()
	{
	}
	~LicenseWindow()
	{
		this->!LicenseWindow();
	}

	virtual void InitializeComponent() override;

	virtual void OnShow() override;
	virtual void OnHide() override;

public:

	LicenseWindow();
};
#endif

#pragma endregion