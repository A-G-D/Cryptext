/*
*	<aboutwindow.cpp>
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
#include "aboutwindow.h"
#include "namespaces.h"
#include "winformstemplate.h"
#include "mainwindow.h"
#include "utils.h"
#include "userdefinitions.h"
#include "macros.h"
#include "stringtable.h"
#include <gcroot.h>

using namespace WinFormsTemplate;

extern gcroot<stringtable^> strtable;
extern gcroot<MainWindow^> mainWindow;
extern gcroot<AboutWindow^> aboutWindow;
extern gcroot<LicenseWindow^> licenseWindow;

void OnLnkLabelBackClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e);

/*
*	AboutWindow Class Definitiona
*/
void AboutWindow::InitializeComponent()
{
	String ^aboutText(L"\r\nVersion: " + VERSION + L"\r\n\r\nCheck for latest updates at: \r\n" + SOURCE_LINK_TEXT + L"\r\n\r\n\r\n\r\n\r\nCopyright © " + YEAR + L" " + AUTHOR_NAME + L"\r\n\r\nThis program is licensed under the GNU General Public License. For more information, see the license file that you received along with this program, or go to " + LICENSE_LINK_TEXT + L".");

	CreatePanel(panelAbout, L"panelAbout", 12, 17, 310, 303, 1, AnchorType::CENTER, true);
	CreateLinkLabel(lnklabelBack, L"lnklabelBack", L"Back", 147, 335, 20, 20, 0, AnchorType::BOTTOM, gcnew LinkLabelLinkClickedEventHandler(&OnLnkLabelBackClick));
	CreateLinkLabel(lnklabelAboutInfo, L"lnkLabelAbout", aboutText, 8, 8, 280, 260, 2, AnchorType::CENTER, gcnew LinkLabelLinkClickedEventHandler(this, &AboutWindow::OnLnkLabelAboutClick));

	panelAbout->BackColor = Color::White;

	lnklabelAboutInfo->AutoSize = false;
	lnklabelAboutInfo->Links->Add(aboutText->IndexOf(SOURCE_LINK_TEXT), ((String^)SOURCE_LINK_TEXT)->Length);
	lnklabelAboutInfo->Links->Add(aboutText->IndexOf(L"license "), 7);
	lnklabelAboutInfo->Links->Add(aboutText->IndexOf(LICENSE_LINK_TEXT), ((String^)LICENSE_LINK_TEXT)->Length);

	UserDefined::GetProperties(L"AboutPage.txt", lnklabelBack, lnklabelAboutInfo, panelAbout);

	PauseLayout();

	panelAbout->Controls->Add(lnklabelAboutInfo);

	AddControl(lnklabelBack, panelAbout);

	OnHide();

	ResumeLayout();
}
void OnLnkLabelBackClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e)
{
	mainWindow->Display();
}
void AboutWindow::OnLnkLabelAboutClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e)
{
	switch (lnklabelAboutInfo->Links->IndexOf(e->Link))
	{
		case 0:
			e->Link->Visited = true;
			Diagnostics::Process::Start(SOURCE_LINK_URL);
			break;

		case 1:
			if (File::Exists(AppDomain::CurrentDomain->BaseDirectory + L"\\" + LICENSE_FILE_NAME))
				licenseWindow->Display();
			else
				MessageBox::Show(MESSAGE_MISSING_LICENSE_ERROR, CAPTION_MISSING_LICENSE_ERROR, MessageBoxButtons::OK);
			break;

		case 2:
			e->Link->Visited = true;
			Diagnostics::Process::Start(LICENSE_LINK_URL);
			break;
	}
}
AboutWindow::AboutWindow()
{
}

/*
*	LicenseWindow Class
*/
void LicenseWindow::InitializeComponent()
{
	CreateLinkLabel(lnklabelBack, L"lnklabelBack", L"Back", 147, 335, 20, 20, 0, AnchorType::BOTTOM, gcnew LinkLabelLinkClickedEventHandler(this, &LicenseWindow::OnLnkLabelBackClick));
	CreateTextBox(textboxLicense, L"textboxLicense", 12, 17, 310, 303, 3, AnchorType::CENTER, true);

	textboxLicense->ReadOnly = true;
	textboxLicense->WordWrap = false;
	textboxLicense->ScrollBars = ScrollBars::Both;

	try
	{
		textboxLicense->Font = gcnew Font(LICENSE_TEXT_FONT_FAMILY, textboxLicense->Font->Size);
	}
	catch (...)
	{
	}

	UserDefined::GetProperties(L"AboutPage.txt", textboxLicense);

	PauseLayout();

	AddControl(
		lnklabelBack,
		textboxLicense
	);

	OnHide();

	ResumeLayout();
}
void LicenseWindow::OnLnkLabelBackClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e)
{
	aboutWindow->Display();
}

LicenseWindow::LicenseWindow()
{
}
void LicenseWindow::OnShow()
{
	textboxLicense->Text = File::ReadAllText(AppDomain::CurrentDomain->BaseDirectory + L"\\" + LICENSE_FILE_NAME);

	AppPage::OnShow();
}
void LicenseWindow::OnHide()
{
	textboxLicense->Text = String::Empty;

	AppPage::OnHide();
}