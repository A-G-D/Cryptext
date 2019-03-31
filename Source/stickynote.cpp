/*
*	<stickynote.cpp>
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
#include "stickynote.h"
#include "namespaces.h"
#include "window.h"
#include "utils.h"
#include "userdefinitions.h"
#include "macros.h"
#include <gcroot.h>

extern gcroot<Window^> currentPage;

StickyNote::StickyNote()
{

	CreateTextBox(textboxStickyNote, L"textboxStickyNote", 6, 6, 322, 348, 0, AnchorType::CENTER, true);
	textboxStickyNote->KeyDown += gcnew KeyEventHandler(this, &StickyNote::OnEscKeyDown);

	if (File::Exists(RESOURCES_FOLDER_NAME + L"\\__note__"))
		textboxStickyNote->Text = File::ReadAllText(RESOURCES_FOLDER_NAME + L"\\__note__");

	UserDefined::GetProperties(L"StickyNotePage.txt", textboxStickyNote);

	PauseLayout();

	Add(textboxStickyNote);
	Hide();

	ResumeLayout();
}

void StickyNote::OnEscKeyDown(Object ^sender, KeyEventArgs ^e)
{
	if (e->KeyCode == Keys::Escape)
		Display(prevForm);
}

void StickyNote::Show()
{
	prevForm = currentPage;

	textboxStickyNote->Show();

	Window::Show();
}
void StickyNote::Hide()
{
	textboxStickyNote->Hide();

	Window::Hide();
}
String ^StickyNote::GetText()
{
	return textboxStickyNote->Text;
}