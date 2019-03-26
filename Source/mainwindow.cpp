/*
*	<mainwindow.cpp>
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
#include "mainwindow.h"
#include "namespaces.h"
#include "window.h"
#include "textfileswindow.h"
#include "aboutwindow.h"
#include "utils.h"
#include "userdefinitions.h"

void MainWindow::InitializeComponent()
{
	CreateButton(btnTextFiles, L"btnTextFiles", L"Text Files", 12, 27, 310, 33, 0, AnchorType::CENTER_TOP, gcnew EventHandler(this, &MainWindow::OnBtnTextFilesClick));
	CreateButton(btnTranslationFiles, L"btnTranslationFiles", L"Translation Files", 12, 66, 310, 33, 1, AnchorType::CENTER_TOP, gcnew EventHandler(this, &MainWindow::OnBtnTranslationFilesClick));
	CreateLinkLabel(lnklabelAbout, L"lnklabelAbout", L"About", 147, 335, 20, 20, 2, AnchorType::BOTTOM, gcnew LinkLabelLinkClickedEventHandler(this, &MainWindow::OnLnkLabelAboutClick));

	UserDefined::GetProperties(L"MainPage.txt", btnTextFiles, btnTranslationFiles, lnklabelAbout);

	PauseLayout();

	Add(btnTextFiles);
	Add(btnTranslationFiles);
	Add(lnklabelAbout);

	ResumeLayout();
}
void MainWindow::OnBtnTextFilesClick(Object ^sender, EventArgs ^e)
{
	textFilesWindow->flag = true;
	Display(textFilesWindow);
}
void MainWindow::OnBtnTranslationFilesClick(Object ^sender, EventArgs ^e)
{
	textFilesWindow->flag = false;
	Display(textFilesWindow);
}
void MainWindow::OnLnkLabelAboutClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e)
{
	Display(aboutWindow);
}
MainWindow::MainWindow()
{
	textFilesWindow = gcnew TextFilesWindow(this);
	aboutWindow = gcnew AboutWindow(this);
	InitializeComponent();
}
void MainWindow::Show()
{
	btnTextFiles->Show();
	btnTranslationFiles->Show();
	lnklabelAbout->Show();

	Window::Show();
}
void MainWindow::Hide()
{
	btnTextFiles->Hide();
	btnTranslationFiles->Hide();
	lnklabelAbout->Hide();

	Window::Hide();
}
void MainWindow::ClickTextFilesButton()
{
	OnBtnTextFilesClick(nullptr, nullptr);
}