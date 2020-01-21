/*
*	<stickynote.cpp>
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
#include "stickynote.h"
#include "namespaces.h"
#include "winformstemplate.h"
#include "utils.h"
#include "userdefinitions.h"
#include "macros.h"
#include <gcroot.h>

using namespace WinFormsTemplate;

extern gcroot<AppForm^> appForm;

/*
*	StickyNote Class Definitions
*/
void StickyNote::InitializeComponent()
{
	CreateTextBox(textboxStickyNote, L"textboxStickyNote", 6, 6, 322, 348, 0, AnchorType::CENTER, true);
	textboxStickyNote->AcceptsTab = true;
	textboxStickyNote->WordWrap = false;
	textboxStickyNote->KeyDown += gcnew KeyEventHandler(this, &StickyNote::OnEscKeyDown);

	if (File::Exists(AppDomain::CurrentDomain->BaseDirectory + RESOURCES_FOLDER_NAME + L"\\" + STICKY_NOTE_FILE_NAME))
		textboxStickyNote->Text = File::ReadAllText(AppDomain::CurrentDomain->BaseDirectory + RESOURCES_FOLDER_NAME + L"\\" + STICKY_NOTE_FILE_NAME);

	PauseLayout();

	AddControl(textboxStickyNote);
	OnHide();

	UserDefined::GetProperties(L"StickyNotePage.txt", textboxStickyNote);

	ResumeLayout();
}

StickyNote::StickyNote()
{
}

void StickyNote::OnEscKeyDown(Object ^sender, KeyEventArgs ^e)
{
	if (e->KeyCode == Keys::Escape)
		prevForm->Display(true);
}

void StickyNote::OnShow()
{
	prevForm = appForm->GetCurrentPage();

	PauseLayout();

	AppPage::OnShow();

	ResumeLayout();
}
String ^StickyNote::GetText()
{
	return textboxStickyNote->Text;
}
void StickyNote::WriteText(String ^text)
{
	textboxStickyNote->Text = text;
}