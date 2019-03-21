/*
*	<mainwindow.h>
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

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "namespaces.h"
#include "window.h"
#include "textfileswindow.h"

/*
*	MainWindow Class
*/
ref class MainWindow : public Window
{
public:
	TextFilesWindow ^textFilesWindow;

private:
	Button
		^btnTextFiles,
		^btnTranslationFiles;

	void InitializeComponent();
	void OnBtnTextFilesClick(Object ^sender, EventArgs ^e);
	void OnBtnTranslationFilesClick(Object ^sender, EventArgs ^e);

protected:

	!MainWindow()
	{
		delete textFilesWindow;
	}

	~MainWindow()
	{
		this->!MainWindow();
	}

public:

	MainWindow();

	virtual void Show() override;
	virtual void Hide() override;

	void ClickTextFilesButton();
};
#endif

#pragma endregion