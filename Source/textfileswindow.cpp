/*
*	<textfileswindow.cpp>
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

extern gcroot<stringtable^> strtable;
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
	listboxTextFiles->FormattingEnabled = true;
	listboxTextFiles->Location = Point(12, 17);
	listboxTextFiles->Name = L"listboxTextFiles";
	listboxTextFiles->Size = Size(310, 303);
	listboxTextFiles->Anchor = (AnchorStyles)AnchorType::CENTER;
	listboxTextFiles->TabIndex = 3;

	UserDefined::GetProperties(L"TextFilesPage.txt", btnBack, btnCreateText, btnEditText, btnDeleteText, listboxTextFiles);

	PauseLayout();

	AddControl(
		btnBack,
		btnCreateText,
		btnEditText,
		btnDeleteText,
		listboxTextFiles
	);

	OnHide();

	ResumeLayout();
}
void OnBtnBackClick(Object ^sender, EventArgs ^e)
{
	mainWindow->Display();
}
void TextFilesWindow::OnBtnEditTextClick(Object ^sender, EventArgs ^e)
{
	if (listboxTextFiles->SelectedItem != nullptr)
	{
		String ^itemName(listboxTextFiles->SelectedItem->ToString());
		if (flag)
		{
			if (textEditingWindow->Load(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TEXT_FILES_FOLDER_NAME + L"\\" + itemName + L"\\" + itemName + TEXT_FILE_EXTENSION, true))
				textEditingWindow->Display();
		}
		else if (translationEditingWindow->Load(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TRANSLATION_FILES_FOLDER_NAME + L"\\" + itemName + TRANSLATION_FILE_EXTENSION))
			translationEditingWindow->Display();
	}
}
void TextFilesWindow::OnBtnDeleteTextClick(Object ^sender, EventArgs ^e)
{
	if (listboxTextFiles->SelectedItem != nullptr)
	{
		if (flag)
			Directory::Delete(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TEXT_FILES_FOLDER_NAME + L"\\" + listboxTextFiles->SelectedItem->ToString(), true);
		else
			File::Delete(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TRANSLATION_FILES_FOLDER_NAME + L"\\" + listboxTextFiles->SelectedItem->ToString() + TRANSLATION_FILE_EXTENSION);
		UpdateList();
	}
}
void TextFilesWindow::OnBtnCreateTextClick(Object ^sender, EventArgs ^e)
{
	(flag ? (AppPage^)textEditingWindow : (AppPage^)translationEditingWindow)->Display();
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
			Directory::CreateDirectory(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TEXT_FILES_FOLDER_NAME);
	}
	else if (!GetTranslations(listboxTextFiles->Items))
		Directory::CreateDirectory(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TRANSLATION_FILES_FOLDER_NAME);
}
void TextFilesWindow::LoadTranslationOnInit(String ^filePath)
{
	translationEditingWindow->Load(filePath);
	translationEditingWindow->Display();
}
void TextFilesWindow::OnShow()
{
	PauseLayout();

	UpdateList();

	ResumeLayout();

	AppPage::OnShow();
}