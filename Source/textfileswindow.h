/*
*	<textfileswindow.h>
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

#ifndef _TEXTFILESWINDOW_H_
#define _TEXTFILESWINDOW_H_

#include "namespaces.h"
#include "window.h"
#include "texteditingwindow.h"
#include "translationeditingwindow.h"

/*
*	TextFilesWindow Class
*/
ref class TextFilesWindow : public Window
{
public:

	TextEditingWindow ^textEditingWindow;
	TranslationEditingWindow ^translationEditingWindow;

private:

	Window ^prevForm;
	Button
		^btnBack,
		^btnCreateText,
		^btnEditText,
		^btnDeleteText;
	ListBox ^listboxTextFiles;

	void InitializeComponent();
	void OnBtnBackClick(Object ^sender, EventArgs ^e);
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

public:

	bool flag;

	TextFilesWindow(Window ^form);

	void UpdateList();

	void LoadTranslationOnInit(String ^filePath);

	virtual void Show() override;
	virtual void Hide() override;
};
#endif

#pragma endregion