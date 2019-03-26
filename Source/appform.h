/*
*	<appform.h>
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

#ifndef _APPFORM_H_
#define _APPFORM_H_

#include "namespaces.h"
#include "mainwindow.h"

/*
*	Form Class
*/
ref class AppForm : public Form
{
private:
	MainWindow ^mainWindow;

	!AppForm()
	{
		delete mainWindow;
	}
	~AppForm()
	{
		this->!AppForm();
	}

public:

	static String ^defaultLoadFile = String::Empty;

	AppForm();

	virtual void OnShown(EventArgs ^e) override;

	static AppForm ^Instance;

};
#endif

#pragma endregion