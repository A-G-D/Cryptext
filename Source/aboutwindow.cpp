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
#include "window.h"
#include "utils.h"
#include "userdefinitions.h"
#include "macros.h"
#include "stringtable.h"
#include <gcroot.h>

extern gcroot<stringtable^> strtable;
bool licenseShown = false;

void AboutWindow::InitializeComponent()
{
	String ^aboutText(L"\r\nVersion: " + VERSION + L"\r\n\r\nCheck for latest updates at: \r\n" + SOURCE_LINK_TEXT + L"\r\n\r\n\r\n\r\n\r\nCopyright © 2019 Aloever Dulay\r\n\r\nThis program is licensed under the GNU General Public License. For more information, see the license file that you received along with this program, or go to " + LICENSE_LINK_TEXT + L".");

	CreatePanel(panelAbout, L"panelAbout", 12, 17, 310, 303, 1, AnchorType::CENTER, true);
	CreateLinkLabel(lnklabelBack, L"btnBack", L"Back", 147, 335, 20, 20, 0, AnchorType::BOTTOM, gcnew LinkLabelLinkClickedEventHandler(this, &AboutWindow::OnLnkLabelBackClick));
	CreateLinkLabel(lnklabelAboutInfo, L"lnkLabelAbout", aboutText, 8, 8, 280, 260, 2, AnchorType::CENTER, gcnew LinkLabelLinkClickedEventHandler(this, &AboutWindow::OnLnkLabelAboutClick));
	CreateTextBox(textboxLicense, L"textboxLicense", 12, 17, 310, 303, 3, AnchorType::CENTER, true);

	textboxLicense->ReadOnly = true;
	textboxLicense->WordWrap = false;
	textboxLicense->ScrollBars = ScrollBars::Both;

	try
	{
		textboxLicense->Font = gcnew Font(L"Courier New", textboxLicense->Font->Size);
	}
	catch (...)
	{
	}

	if (File::Exists(LICENSE_FILE_PATH))
		textboxLicense->Text = File::ReadAllText(LICENSE_FILE_PATH);

	panelAbout->BackColor = Color::White;

	lnklabelAboutInfo->AutoSize = false;
	lnklabelAboutInfo->Links->Add(aboutText->IndexOf(SOURCE_LINK_TEXT), ((String^)SOURCE_LINK_TEXT)->Length);
	lnklabelAboutInfo->Links->Add(aboutText->IndexOf(L"license "), 7);
	lnklabelAboutInfo->Links->Add(aboutText->IndexOf(LICENSE_LINK_TEXT), ((String^)LICENSE_LINK_TEXT)->Length);

	UserDefined::GetProperties(L"AboutPage.txt", lnklabelBack, lnklabelAboutInfo, panelAbout, textboxLicense);

	PauseLayout();

	panelAbout->Controls->Add(lnklabelAboutInfo);
	if (textboxLicense != nullptr)
	{
		panelAbout->Controls->Add(textboxLicense);
		textboxLicense->Hide();
	}

	Add(lnklabelBack);
	Add(panelAbout);
	Add(textboxLicense);
	textboxLicense->Hide();

	Hide();

	ResumeLayout();
}
void AboutWindow::OnLnkLabelBackClick(Object ^sender, LinkLabelLinkClickedEventArgs ^e)
{
	if (licenseShown)
	{
		licenseShown = false;
		textboxLicense->Hide();
		panelAbout->Show();
	}
	else
		Display(prevForm);
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
			if (File::Exists(LICENSE_FILE_PATH))
			{
				panelAbout->Hide();
				textboxLicense->Show();
				licenseShown = true;
			}
			else
				MessageBox::Show(MESSAGE_MISSING_LICENSE_ERROR, CAPTION_MISSING_LICENSE_ERROR, MessageBoxButtons::OK);
			break;

		case 2:
			e->Link->Visited = true;
			Diagnostics::Process::Start(LICENSE_LINK_URL);
			break;
	}
}
AboutWindow::AboutWindow(Window ^form)
	: prevForm(form)
{
	InitializeComponent();
}
void AboutWindow::Show()
{
	lnklabelBack->Show();
	panelAbout->Show();

	Window::Show();
}
void AboutWindow::Hide()
{
	lnklabelBack->Hide();
	panelAbout->Hide();

	Window::Hide();
}