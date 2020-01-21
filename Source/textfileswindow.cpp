/*
*	<textfileswindow.cpp>
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
#include "textfileswindow.h"
#include "namespaces.h"
#include "winformstemplate.h"
#include "mainwindow.h"
#include "texteditingwindow.h"
#include "translationeditingwindow.h"
#include "utils.h"
#include "userdefinitions.h"
#include "macros.h"
#include "stringtable.h"
#include <gcroot.h>

using namespace WinFormsTemplate;

extern gcroot<StringTable^> strtable;
extern gcroot<MainWindow^> mainWindow;
extern gcroot<TextEditingWindow^> textEditingWindow;
extern gcroot<TranslationEditingWindow^> translationEditingWindow;

void OnBtnBackClick(Object ^sender, EventArgs ^e);

/*
*	TextFilesWindow Class Definitions
*/
void TextFilesWindow::InitializeComponent()
{
	CreateButton(btnBack, L"btnBack", L"Back", 12, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 4, AnchorType::BOTTOM_LEFT, gcnew EventHandler(&OnBtnBackClick));
	CreateButton(btnCreateText, L"btnCreateText", L"Create", 93, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 0, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TextFilesWindow::OnBtnCreateTextClick));
	CreateButton(btnEditText, L"btnEditText", L"Edit", 170, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 1, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TextFilesWindow::OnBtnEditTextClick));
	CreateButton(btnDeleteText, L"btnDeleteText", L"Delete", 247, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 2, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TextFilesWindow::OnBtnDeleteTextClick));

	listboxTextFiles = gcnew ListBox;
	listboxTextFiles->Sorted = true;
	listboxTextFiles->FormattingEnabled = true;
	listboxTextFiles->Location = Point(12, 17);
	listboxTextFiles->Name = L"listboxTextFiles";
	listboxTextFiles->Size = Size(310, 303);
	listboxTextFiles->Anchor = (AnchorStyles)AnchorType::CENTER;
	listboxTextFiles->TabIndex = 3;

	PauseLayout();

	AddControl(
		btnBack,
		btnCreateText,
		btnEditText,
		btnDeleteText,
		listboxTextFiles
	);
	OnHide();

	UserDefined::GetProperties(L"TextFilesPage.txt", btnBack, btnCreateText, btnEditText, btnDeleteText, listboxTextFiles);

	ResumeLayout();
}
void OnBtnBackClick(Object ^sender, EventArgs ^e)
{
	mainWindow->Display(true);
}
void TextFilesWindow::OnBtnEditTextClick(Object ^sender, EventArgs ^e)
{
	if (listboxTextFiles->SelectedItem != nullptr)
	{
		String ^itemName(listboxTextFiles->SelectedItem->ToString());
		if (flag)
		{
			if (File::Exists(AppDomain::CurrentDomain->BaseDirectory + TEXT_FILES_FOLDER_NAME + L"\\" + itemName + L"\\" + itemName + TEXT_FILE_EXTENSION))
			{
				if (textEditingWindow->Load(AppDomain::CurrentDomain->BaseDirectory + TEXT_FILES_FOLDER_NAME + L"\\" + itemName + L"\\" + itemName + TEXT_FILE_EXTENSION, true))
					textEditingWindow->Display(true);
			}
			else
				UpdateList();
		}
		else
		{
			ZipArchive ^archive(ZipFile::Open(AppDomain::CurrentDomain->BaseDirectory + TRANSLATION_ARCHIVE_NAME + TRANSLATION_ARCHIVE_EXTENSION, ZipArchiveMode::Read));
			ZipArchiveEntry ^entry(archive->GetEntry(itemName + TRANSLATION_FILE_EXTENSION));
			String ^text;

			bool exists(entry != nullptr);
			if (exists)
			{
				StreamReader ^sReader(gcnew StreamReader(entry->Open()));
				text = sReader->ReadToEnd();
				sReader->Close();
			}

			archive->~ZipArchive();
			if (exists)
			{
				if (translationEditingWindow->Load(itemName, text))
					translationEditingWindow->Display(true);
			}
			else
				UpdateList();
		}
	}
}
void TextFilesWindow::OnBtnDeleteTextClick(Object ^sender, EventArgs ^e)
{
	if (listboxTextFiles->SelectedItem != nullptr && MessageBox::Show((MESSAGE_FILE_DELETE_CONFIRM)->Replace(L"<FILE_NAME>", listboxTextFiles->SelectedItem->ToString()), CAPTION_FILE_DELETE_CONFIRM, MessageBoxButtons::YesNo, MessageBoxIcon::Question) == DialogResult::Yes)
	{
		if (flag)
			Directory::Delete(AppDomain::CurrentDomain->BaseDirectory + TEXT_FILES_FOLDER_NAME + L"\\" + listboxTextFiles->SelectedItem->ToString(), true);
		else
		{
			ZipArchive ^archive(ZipFile::Open(AppDomain::CurrentDomain->BaseDirectory + TRANSLATION_ARCHIVE_NAME + TRANSLATION_ARCHIVE_EXTENSION, ZipArchiveMode::Update));
			ZipArchiveEntry ^entry(archive->GetEntry(listboxTextFiles->SelectedItem->ToString() + TRANSLATION_FILE_EXTENSION));
			if (entry != nullptr)
				entry->Delete();
			archive->~ZipArchive();
		}
		UpdateList();
	}
}
void TextFilesWindow::OnBtnCreateTextClick(Object ^sender, EventArgs ^e)
{
	(flag ? (AppPage^)textEditingWindow : (AppPage^)translationEditingWindow)->Display(true);
}
TextFilesWindow::TextFilesWindow()
	: flag(false)
{
}
void TextFilesWindow::UpdateList()
{
	listboxTextFiles->Items->Clear();

	if (flag)
	{
		if (!GetTextFiles(listboxTextFiles->Items))
			Directory::CreateDirectory(AppDomain::CurrentDomain->BaseDirectory + TEXT_FILES_FOLDER_NAME);
	}
	else
		GetTranslations(listboxTextFiles->Items);
}
void TextFilesWindow::LoadTranslationOnInit(String ^filePath)
{
	translationEditingWindow->Load(Path::GetFileNameWithoutExtension(filePath), File::ReadAllText(filePath));
	translationEditingWindow->Display(true);
}
void TextFilesWindow::OnShow()
{
	PauseLayout();

	UpdateList();

	AppPage::OnShow();

	ResumeLayout();
}