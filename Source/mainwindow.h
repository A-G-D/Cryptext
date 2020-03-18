/*
*	<mainwindow.h>
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

#ifndef _MAINWINDOW_H_
#define _MAINWINDOW_H_

#include "namespaces.h"
#include "winformstemplate.h"
#include "textfileswindow.h"
#include "aboutwindow.h"
#include "translatorwindow.h"

/*
*	MainWindow Class
*/
ref class MainWindow : public WinFormsTemplate::AppPage
{
private:

	Button
		^btnTextFiles,
		^btnTranslationFiles,
		^btnTranslator;

	LinkLabel ^lnklabelAbout;

protected:

	!MainWindow();
	~MainWindow();

	virtual void InitializeComponent() override;

public:

	MainWindow();

	void ClickTextFilesButton();
	void ClickTranslationFilesButton();
};
#endif

#pragma endregion