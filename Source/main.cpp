/*
*	<main.cpp>
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
#include "macros.h"
#include "namespaces.h"
#include "winformstemplate.h"
#include "stringtable.h"
#include "mainwindow.h"
#include "textfileswindow.h"
#include "texteditingwindow.h"
#include "translationeditingwindow.h"
#include "translatorwindow.h"
#include "aboutwindow.h"
#include "stickynote.h"
#include "userdefinitions.h"
#include <gcroot.h>

using namespace System;
using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace WinFormsTemplate;

void OnFormInit();
void OnFormClosed(Object ^sender, FormClosedEventArgs ^e);
void OnKeyDown(Object ^sender, KeyEventArgs ^e);
void WriteToStickyNote(String ^filePath);

gcroot<StringTable^> strtable(gcnew StringTable(AppDomain::CurrentDomain->BaseDirectory + RESOURCES_FOLDER_NAME + L"\\" + STRING_TABLE_FILE_NAME));
gcroot<String^> initFilePath(String::Empty);
gcroot<ToolTip^> toolTip(gcnew ToolTip);
gcroot<MainWindow^> mainWindow(gcnew MainWindow);
gcroot<TextFilesWindow^> textFilesWindow(gcnew TextFilesWindow);
gcroot<TextEditingWindow^> textEditingWindow(gcnew TextEditingWindow);
gcroot<TranslationEditingWindow^> translationEditingWindow(gcnew TranslationEditingWindow);
gcroot<TranslatorWindow^> translatorWindow(gcnew TranslatorWindow);
gcroot<AboutWindow^> aboutWindow(gcnew AboutWindow);
gcroot<LicenseWindow^> licenseWindow(gcnew LicenseWindow);
gcroot<StickyNote^> stickyNote(gcnew StickyNote);
gcroot<AppForm^> appForm;
gcroot<AppPage^> currentPage;

bool ADVANCED_FLAG(false);


[STAThread]
void Main(array<String^> ^args)
{
	if ((gcnew Mutex(false, APPLICATION_NAME + L".exe"))->WaitOne(0, false))
	{
		bool styled(true);

		for (int i(0); i < args->Length; ++i)
		{
			if (args[i] == L"-basicstyle")
				styled = false;

			else if (args[i] == L"-load" && i < args->Length - 1)
			{
				if (File::Exists(args[++i]))
					initFilePath = args[i];
			}
			else if (File::Exists(args[i]))
				initFilePath = args[i];

			else if (args[i] == L"-advanced")
			{
				// To Be Continued =======>
			}
		}
		if (styled)
		{
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);
		}
		appForm = gcnew AppForm;
		OnFormInit();
		Application::Run(appForm);
	}
	else
		MessageBox::Show(L"Instance Already Running!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Hand);
}

void OnFormInit()
{
	appForm->Name					= APPLICATION_NAME;
	appForm->Text					= APPLICATION_NAME;
	appForm->MinimizeBox			= true;
	appForm->MaximizeBox			= true;
	appForm->ShowInTaskbar			= true;
	appForm->ControlBox				= true;
	appForm->KeyPreview				= true;
	appForm->StartPosition			= FormStartPosition::CenterScreen;
	appForm->FormBorderStyle		= FormBorderStyle::Sizable;
	appForm->AutoScaleDimensions	= SizeF(6, 13);
	appForm->AutoScaleMode			= AutoScaleMode::None;
	appForm->MinimumSize			= Size(350, 400);
	appForm->Size					= Size(350, 400);
	appForm->FormClosed				+= gcnew FormClosedEventHandler(&OnFormClosed);
	appForm->KeyDown				+= gcnew KeyEventHandler(&OnKeyDown);

	appForm->SuspendLayout();

	appForm->Add(
		mainWindow,
		textFilesWindow,
		textEditingWindow,
		translationEditingWindow,
		translatorWindow,
		aboutWindow,
		licenseWindow,
		stickyNote
	);

	appForm->ResumeLayout();

	UserDefined::GetProperties(appForm);

	mainWindow->Display();

	toolTip->AutoPopDelay		= 5000;
	toolTip->InitialDelay		= 1000;
	toolTip->ReshowDelay		= 500;
	toolTip->ShowAlways			= false;
	
	if (initFilePath != String::Empty)
	{
		String ^extension(Path::GetExtension(initFilePath));

		if (extension == TRANSLATION_FILE_EXTENSION)
		{
			mainWindow->ClickTranslationFilesButton();
			textFilesWindow->LoadTranslationOnInit(initFilePath);
		}
		else if (extension == TEXT_FILE_EXTENSION)
		{
			String ^keyPath(Path::GetDirectoryName(initFilePath) + L"\\" + Path::GetFileNameWithoutExtension(initFilePath) + KEY_FILE_EXTENSION);

			if (File::Exists(keyPath) && textEditingWindow->Load(initFilePath, false))
			{
				mainWindow->ClickTextFilesButton();
				textEditingWindow->Display();
			}
			else
				WriteToStickyNote(initFilePath);
		}
		else if (extension == KEY_FILE_EXTENSION)
		{
			String ^textPath(Path::GetDirectoryName(initFilePath) + L"\\" + Path::GetFileNameWithoutExtension(initFilePath) + TEXT_FILE_EXTENSION);

			if (File::Exists(textPath) && textEditingWindow->Load(textPath, false))
			{
				mainWindow->ClickTextFilesButton();
				textEditingWindow->Display();
			}
			else
				WriteToStickyNote(textPath);
		}
		else
			WriteToStickyNote(initFilePath);
	}
}
void OnFormClosed(Object ^sender, FormClosedEventArgs ^e)
{
	String
		^directoryPath(AppDomain::CurrentDomain->BaseDirectory + RESOURCES_FOLDER_NAME),
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
void OnKeyDown(Object ^sender, KeyEventArgs ^e)
{
	if (((StickyNote^)((AppPage^)currentPage)) != stickyNote && e->KeyCode == Keys::N && ((Control::ModifierKeys & Keys::Alt) == Keys::Alt))
		stickyNote->Display();
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

	stickyNote->WriteText(output);
	stickyNote->Display();
}