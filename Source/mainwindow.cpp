/*
*	<mainwindow.cpp>
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
#include "mainwindow.h"
#include "namespaces.h"
#include "winformstemplate.h"
#include "textfileswindow.h"
#include "translatorwindow.h"
#include "aboutwindow.h"
#include "utils.h"
#include "userdefinitions.h"
#include <gcroot.h>

using namespace WinFormsTemplate;

extern gcroot<TextFilesWindow^> textFilesWindow;
extern gcroot<TranslatorWindow^> translatorWindow;
extern gcroot<AboutWindow^> aboutWindow;

void OnBtnTextFilesClick(Object ^sender, EventArgs ^e);
void OnBtnTranslationFilesClick(Object ^sender, EventArgs ^e);
void OnBtnTranslatorClick(Object ^sender, EventArgs ^e);
void OnLnkLabelAboutClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e);

/*
*	MainWindow Class Definitions
*/
void MainWindow::InitializeComponent()
{
	CreateButton(btnTextFiles, L"btnTextFiles", L"Text Files", 12, 27, 310, 33, 0, AnchorType::CENTER_TOP, gcnew EventHandler(&OnBtnTextFilesClick));
	CreateButton(btnTranslationFiles, L"btnTranslationFiles", L"Translation Files", 12, 66, 310, 33, 1, AnchorType::CENTER_TOP, gcnew EventHandler(&OnBtnTranslationFilesClick));
	CreateButton(btnTranslator, L"btnTranslator", L"Translator", 12, 105, 310, 33, 2, AnchorType::CENTER_TOP, gcnew EventHandler(&OnBtnTranslatorClick));
	CreateLinkLabel(lnklabelAbout, L"lnklabelAbout", L"About", 147, 335, 20, 20, 2, AnchorType::BOTTOM, gcnew LinkLabelLinkClickedEventHandler(&OnLnkLabelAboutClick));

	PauseLayout();

	AddControl(
		btnTextFiles,
		btnTranslationFiles,
		btnTranslator,
		lnklabelAbout
	);

	UserDefined::GetProperties(L"MainPage.txt", btnTextFiles, btnTranslationFiles, btnTranslator, lnklabelAbout);

	ResumeLayout();
}
void OnBtnTextFilesClick(Object ^sender, EventArgs ^e)
{
	textFilesWindow->flag = true;
	textFilesWindow->Display(true);
}
void OnBtnTranslationFilesClick(Object ^sender, EventArgs ^e)
{
	textFilesWindow->flag = false;
	textFilesWindow->Display(true);
}
void OnBtnTranslatorClick(Object ^sender, EventArgs ^e)
{
	translatorWindow->Display(true);
}
void OnLnkLabelAboutClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e)
{
	aboutWindow->Display(true);
}
MainWindow::MainWindow()
{
}
void MainWindow::ClickTextFilesButton()
{
	OnBtnTextFilesClick(nullptr, nullptr);
}
void MainWindow::ClickTranslationFilesButton()
{
	OnBtnTranslationFilesClick(nullptr, nullptr);
}