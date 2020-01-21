/*
*	<textfileswindow.h>
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

#ifndef _TEXTFILESWINDOW_H_
#define _TEXTFILESWINDOW_H_

#include "namespaces.h"
#include "winformstemplate.h"
#include "texteditingwindow.h"
#include "translationeditingwindow.h"

/*
*	TextFilesWindow Class
*/
ref class TextFilesWindow : public WinFormsTemplate::AppPage
{
private:

	Button
		^btnBack,
		^btnCreateText,
		^btnEditText,
		^btnDeleteText;
	ListBox ^listboxTextFiles;

	void OnBtnEditTextClick(Object ^sender, EventArgs ^e);
	void OnBtnDeleteTextClick(Object ^sender, EventArgs ^e);
	void OnBtnCreateTextClick(Object ^sender, EventArgs ^e);

protected:

	!TextFilesWindow()
	{
	}
	~TextFilesWindow()
	{
		this->!TextFilesWindow();
	}

	virtual void InitializeComponent() override;

	virtual void OnShow() override;

public:

	bool flag;

	TextFilesWindow();

	void UpdateList();

	void LoadTranslationOnInit(String ^filePath);
};
#endif

#pragma endregion