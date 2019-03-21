/*
*	<appform.cpp>
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
#include "appform.h"
#include "namespaces.h"
#include "mainwindow.h"
#include "userdefinitions.h"
#include "macros.h"
#include "stringtable.h"
#include <gcroot.h>

extern gcroot<stringtable^> strtable;

AppForm::AppForm()
{
	Instance = this;
	Name = APPLICATION_NAME;
	Text = APPLICATION_NAME;
	SetStyle(ControlStyles::SupportsTransparentBackColor, true);
	MinimizeBox = true;
	MaximizeBox = true;
	ShowInTaskbar = true;
	StartPosition = FormStartPosition::CenterScreen;
	FormBorderStyle = System::Windows::Forms::FormBorderStyle::Sizable;
	AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
	MinimumSize = System::Drawing::Size(350, 400);
	Size = System::Drawing::Size(350, 400);
	ControlBox = true;

	UserDefined::GetProperties(this);

	ResumeLayout(false);
	mainWindow = gcnew MainWindow;
	mainWindow->Show();

	Window::tooltip->AutoPopDelay = 5000;
	Window::tooltip->InitialDelay = 1000;
	Window::tooltip->ReshowDelay = 500;
	Window::tooltip->ShowAlways = false;
}
void AppForm::OnShown(EventArgs ^e)
{
	Form::OnShown(e);
	if (defaultLoadFile != String::Empty)
	{
		String
			^fileName(defaultLoadFile->Substring(defaultLoadFile->LastIndexOf((wchar_t)'\\') + 1)),
			^fileContent(File::ReadAllText(defaultLoadFile)),
			^s(String::Empty);

		for (int i(0); i < fileContent->Length; ++i)
			(fileContent[i] == (wchar_t)'\n') ? s += L"\r\n" : s += fileContent[i];

		mainWindow->ClickTextFilesButton();
		mainWindow->textFilesWindow->InitDefaultLoadFile(fileName, s);
	}
}