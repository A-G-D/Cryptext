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
#include "stickynote.h"
#include "mainwindow.h"
#include "namespaces.h"
#include "userdefinitions.h"
#include "macros.h"
#include "stringtable.h"
#include <gcroot.h>

extern gcroot<stringtable^> strtable;
extern gcroot<Window^> currentPage;

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
	FormBorderStyle = ::FormBorderStyle::Sizable;
	AutoScaleDimensions = SizeF(6, 13);
	AutoScaleMode = ::AutoScaleMode::None;
	MinimumSize = ::Size(350, 400);
	Size = ::Size(350, 400);
	ControlBox = true;
	KeyPreview = true;

	UserDefined::GetProperties(this);

	ResumeLayout(false);

	stickyNote = gcnew StickyNote;
	mainWindow = gcnew MainWindow;
	mainWindow->Show();
	currentPage = mainWindow;

	Window::tooltip->AutoPopDelay = 5000;
	Window::tooltip->InitialDelay = 1000;
	Window::tooltip->ReshowDelay = 500;
	Window::tooltip->ShowAlways = false;
}

void WriteToStickyNote(String ^filePath)
{
	String
		^output(String::Empty),
		^fileContent(File::ReadAllText(filePath));

	for (int i(0); i < fileContent->Length; ++i)
		if (fileContent[i] == (wchar_t)'\n' && (i  && fileContent[i - 1] != (wchar_t)'\r'))
			output += L"\r\n";
		else
			output += fileContent[i];

	AppForm::Instance->stickyNote->WriteText(output);
	AppForm::Instance->mainWindow->Display(AppForm::Instance->stickyNote);
}
void AppForm::OnShown(EventArgs ^e)
{
	if (defaultLoadFile != String::Empty)
	{
		String ^extension(Path::GetExtension(defaultLoadFile));

		if (extension == TRANSLATION_FILE_EXTENSION)
		{
			mainWindow->ClickTranslationFilesButton();
			mainWindow->textFilesWindow->LoadTranslationOnInit(defaultLoadFile);
		}
		else if (extension == TEXT_FILE_EXTENSION)
		{
			String ^keyPath(Path::GetDirectoryName(defaultLoadFile) + L"\\" + Path::GetFileNameWithoutExtension(defaultLoadFile) + KEY_FILE_EXTENSION);

			if (File::Exists(keyPath) && mainWindow->textFilesWindow->textEditingWindow->Load(defaultLoadFile, false))
			{
				mainWindow->ClickTextFilesButton();
				mainWindow->textFilesWindow->Display(mainWindow->textFilesWindow->textEditingWindow);
			}
			else
				WriteToStickyNote(defaultLoadFile);
		}
		else if (extension == KEY_FILE_EXTENSION)
		{
			String ^textPath(Path::GetDirectoryName(defaultLoadFile) + L"\\" + Path::GetFileNameWithoutExtension(defaultLoadFile) + TEXT_FILE_EXTENSION);

			if (File::Exists(textPath) && mainWindow->textFilesWindow->textEditingWindow->Load(textPath, false))
			{
				mainWindow->ClickTextFilesButton();
				mainWindow->textFilesWindow->Display(mainWindow->textFilesWindow->textEditingWindow);
			}
			else
				WriteToStickyNote(textPath);
		}
		else
			WriteToStickyNote(defaultLoadFile);
	}
	Form::OnShown(e);
}
void AppForm::OnFormClosed(FormClosedEventArgs ^e)
{
	String
		^directoryPath(AppDomain::CurrentDomain->BaseDirectory + L"\\" + RESOURCES_FOLDER_NAME),
		^filePath(directoryPath + L"\\" + STICKY_NOTE_FILE_NAME);

	if (Directory::Exists(directoryPath))
	{
		if (!File::Exists(filePath))
			File::Create(filePath)->Close();

		File::SetAttributes(filePath, FileAttributes::Normal);
		File::WriteAllText(filePath, stickyNote->GetText());
		File::SetAttributes(filePath, FileAttributes::Hidden | FileAttributes::System);
	}
}
void AppForm::OnKeyDown(KeyEventArgs ^e)
{
	if (((Window^)currentPage) != stickyNote && e->KeyCode == Keys::N && ((Control::ModifierKeys & Keys::Alt) == Keys::Alt))
		((Window^)currentPage)->Display((Window^)stickyNote);
	Form::OnKeyDown(e);
}