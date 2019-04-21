/*
*	<translationeditingwindow.cpp>
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
#include "translationeditingwindow.h"
#include "namespaces.h"
#include "winformstemplate.h"
#include "textfileswindow.h"
#include "cypher.h"
#include "utils.h"
#include "userdefinitions.h"
#include "macros.h"
#include "stringtable.h"
#include <gcroot.h>

using namespace WinFormsTemplate;

extern gcroot<stringtable^> strtable;
extern gcroot<TextFilesWindow^> textFilesWindow;

#define upper(x) labelUppercase[x], textboxUppercase[x]
#define lower(x) labelLowercase[x], textboxLowercase[x]
#define number(x) labelNumerals[x], textboxNumerals[x]
#define symbol(x) labelSymbols[x], textboxSymbols[x]

/*
*	TranslationEditingWindow Class Definitions
*/
void CreateColumnElements(array<Label^> ^%label, array<TextBox^> ^%textbox, int size, int x, int charOffset, int tabOffset)
{
	label = gcnew array<Label^>(size);
	textbox = gcnew array<TextBox^>(size);
	for (int i(0); i < size; ++i)
	{
		CreateLabel(label[i], L"label_" + (wchar_t)(charOffset + i), String::Empty + (wchar_t)(charOffset + i), x, 12 + 26*i, 15, 13, 0, AnchorType::TOP_LEFT);
		CreateTextBox(textbox[i], L"textbox_" + (wchar_t)(charOffset + i), x + 20, 9 + 26*i, 31, 20, tabOffset + i, AnchorType::TOP_LEFT, false);
	}
}
void TranslationEditingWindow::InitializeComponent()
{
	PauseLayout();

	labelSymbols = gcnew array<Label^>(34);
	textboxSymbols = gcnew array<TextBox^>(34);

	CreateComboBox(cboxSeparatorChar, L"cboxSeparatorChar", 177, 26, 145, 20, 1, AnchorType::TOP_RIGHT, gcnew EventHandler(this, &TranslationEditingWindow::OnCBoxLostFocus));
	cboxSeparatorChar->BeginUpdate();
	cboxSeparatorChar->Items->Add(L"None");
	cboxSeparatorChar->Items->Add(L"Space");
	cboxSeparatorChar->EndUpdate();
	cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");

	CreateButton(btnBack, L"btnBack", L"Back", 12, 328, BUTTON_WIDTH, BUTTON_HEIGHT, 98, AnchorType::BOTTOM_LEFT, gcnew EventHandler(this, &TranslationEditingWindow::OnBtnBackClick));
	CreateButton(btnSave, L"btnSave", L"Save", 247, 328, BUTTON_WIDTH, BUTTON_HEIGHT, 99, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TranslationEditingWindow::OnBtnSaveClick));

	CreateLabel(labelFileName, L"labelFileName", L"Translation Name", 12, 9, 54, 13, 4, AnchorType::TOP_LEFT);
	CreateLabel(labelSeparatorChar, L"labelSeparatorChar", L"Letter Separator", 177, 9, 54, 13, 5, AnchorType::TOP_RIGHT);
	CreateLabel(labelTranslationTable, L"labelTranslationTable", L"Translation Table", 9, 62, 89, 13, 6, AnchorType::TOP_LEFT);

	CreateTextBox(textboxFileName, L"textboxFileName", 12, 26, 145, 20, 0, AnchorType::TOP_LEFT, false);

	CreateColumnElements(labelUppercase, textboxUppercase, 26, 5, 65, 2);
	CreateColumnElements(labelLowercase, textboxLowercase, 26, 85, 97, 28);
	CreateColumnElements(labelNumerals, textboxNumerals, 10, 165, 48, 54);

	int ascii(32);
	for (int i(0); i < 33; ++i)
	{
		CreateLabel(labelSymbols[i], L"label__" + Convert::ToString(i), (ascii == 38) ? L"&&" : String::Empty + (wchar_t)(ascii), 240, 12 + 26*i, 15, 13, 0, AnchorType::TOP_LEFT);
		CreateTextBox(textboxSymbols[i], L"textbox__" + Convert::ToString(i), 260, 9 + 26*i, 31, 20, 64 + i, AnchorType::TOP_LEFT, false);

		switch (ascii)
		{
			case 47:
				ascii = 58;
				break;
			case 64:
				ascii = 91;
				break;
			case 96:
				ascii = 123;
				break;
			default:
				++ascii;
		}
	}
	CreateLabel(labelSymbols[33], L"label__33", L"Tab", 240 - 10, 12 + 26*33, 15, 13, 0, AnchorType::TOP_LEFT);
	CreateTextBox(textboxSymbols[33], L"textbox__33", 260, 9 + 26*33, 31, 20, 64 + 33, AnchorType::TOP_LEFT, false);
	CreatePanel(panelTranslations, L"panelTranslations", 12, 82, 318, 240, 1, AnchorType::CENTER, true);

	panelTranslations->SuspendLayout();

	panelTranslations->Controls->AddRange(labelUppercase);
	panelTranslations->Controls->AddRange(labelLowercase);
	panelTranslations->Controls->AddRange(labelNumerals);
	panelTranslations->Controls->AddRange(labelSymbols);
	panelTranslations->Controls->AddRange(textboxUppercase);
	panelTranslations->Controls->AddRange(textboxLowercase);
	panelTranslations->Controls->AddRange(textboxNumerals);
	panelTranslations->Controls->AddRange(textboxSymbols);

	UserDefined::GetProperties(L"TranslationEditingPage.txt",
		btnBack, btnSave, labelFileName, labelSeparatorChar, labelTranslationTable, textboxFileName, cboxSeparatorChar, panelTranslations,
		upper(0), upper(1), upper(2), upper(3), upper(4), upper(5), upper(6), upper(7), upper(8), upper(9), upper(10), upper(11), upper(12), upper(13),
		upper(14), upper(15), upper(16), upper(17), upper(18), upper(19), upper(20), upper(21), upper(22), upper(23), upper(24), upper(25),
		lower(0), lower(1), lower(2), lower(3), lower(4), lower(5), lower(6), lower(7), lower(8), lower(9), lower(10), lower(11), lower(12), lower(13),
		lower(14), lower(15), lower(16), lower(17), lower(18), lower(19), lower(20), lower(21), lower(22), lower(23), lower(24), lower(25),
		number(0), number(1), number(2), number(3), number(4), number(5), number(6), number(7), number(8), number(9),
		symbol(0), symbol(1), symbol(2), symbol(3), symbol(4), symbol(5), symbol(6), symbol(7), symbol(8), symbol(9), symbol(10), symbol(11), symbol(12),
		symbol(13), symbol(14), symbol(15), symbol(16), symbol(17), symbol(18), symbol(19), symbol(20), symbol(21), symbol(22), symbol(23), symbol(24),
		symbol(25), symbol(26), symbol(27), symbol(28), symbol(29), symbol(30), symbol(31), symbol(32), symbol(33)
		);

	panelTranslations->ResumeLayout(false);
	panelTranslations->PerformLayout();

	AddControl(
		panelTranslations,
		textboxFileName,
		labelFileName,
		labelSeparatorChar,
		labelTranslationTable,
		btnBack,
		btnSave,
		cboxSeparatorChar
	);

	OnHide();

	ResumeLayout();
	PerformLayout();
}
void GetInputChars(array<Label^> ^label, array<TextBox^> ^textbox, String ^%output)
{
	output += L"\n";
	for (int i(0); i < textbox->Length; ++i)
		if (label[i]->Text == L"Tab")
			output += (L"@\t\t\t{" + textbox[i]->Text + L"}\n");
		else if (label[i]->Text == L"&&")
			output += (L"@&\t\t\t{" + textbox[i]->Text + L"}\n");
		else
			output += (L"@" + label[i]->Text + L"\t\t\t{" + textbox[i]->Text + L"}\n");
}
void LoadTranslations(array<Label^> ^label, array<TextBox^> ^textbox)
{
	for (int i(0); i < textbox->Length; ++i)
		textbox[i]->Text = (String^)(Cypher::Translate((wchar_t)((label[i]->Text == L"Tab") ? '\t' : label[i]->Text[0])));
}
void TranslationEditingWindow::OnCBoxLostFocus(Object ^sender, EventArgs ^e)
{
	if (cboxSeparatorChar->Text == String::Empty)
		cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(cboxSeparatorChar->Text);

	if (cboxSeparatorChar->SelectedIndex == -1)
		if (Cypher::LetterSeparator() == (wchar_t)31)
			cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"None");
		else if (Cypher::LetterSeparator() == (wchar_t)' ')
			cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");
		else
			cboxSeparatorChar->Text = String::Empty;
}
void TranslationEditingWindow::OnBtnBackClick(Object ^sender, EventArgs ^e)
{
	Cypher::Clear();
	activeFile = String::Empty;
	textboxFileName->Clear();
	cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");

	LoadTranslations(labelUppercase, textboxUppercase);
	LoadTranslations(labelLowercase, textboxLowercase);
	LoadTranslations(labelNumerals, textboxNumerals);
	LoadTranslations(labelSymbols, textboxSymbols);

	textFilesWindow->Display();
}
void TranslationEditingWindow::OnBtnSaveClick(Object ^sender, EventArgs ^e)
{
	String
		^directoryPath(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TRANSLATION_FILES_FOLDER_NAME),
		^filePath(directoryPath + L"\\" + textboxFileName->Text);

	if (activeFile == String::Empty)
		MessageBox::Show(MESSAGE_CREATE_TRANSLATION_SUCCESS, CAPTION_CREATE_TRANSLATION_SUCCESS, MessageBoxButtons::OK);

	else if (textboxFileName->Text == String::Empty)
	{
		MessageBox::Show(MESSAGE_CREATE_TRANSLATION_FAILURE, CAPTION_CREATE_TRANSLATION_FAILURE, MessageBoxButtons::OK);
		return;
	}
	else if (activeFile != textboxFileName->Text)
	{
		File::Delete(directoryPath + L"\\" + activeFile + TRANSLATION_FILE_EXTENSION);
		activeFile = textboxFileName->Text;
		filePath = directoryPath + L"\\" + activeFile;
	}

	String ^output(String::Empty);

	if (cboxSeparatorChar->SelectedIndex == -1)
		output += L"#LETTER_SEPARATOR = '" + Cypher::LetterSeparator() + L"'\n\n\n";
	else if (cboxSeparatorChar->SelectedIndex == cboxSeparatorChar->FindStringExact(L"None"))
		output += L"#LETTER_SEPARATOR = '" + (wchar_t)31 + "'\n\n\n";
	else if (cboxSeparatorChar->SelectedIndex == cboxSeparatorChar->FindStringExact(L"Space"))
		output += L"#LETTER_SEPARATOR = ' '\n\n\n";

	output += L"Char\t\tTranslation\n\n";
	GetInputChars(labelUppercase, textboxUppercase, output);
	GetInputChars(labelLowercase, textboxLowercase, output);
	GetInputChars(labelNumerals, textboxNumerals, output);
	GetInputChars(labelSymbols, textboxSymbols, output);
	output += L"@\n\t\t\t{\n}\n";

	File::WriteAllText(filePath + TRANSLATION_FILE_EXTENSION, output);
	textFilesWindow->Display();
}
bool TranslationEditingWindow::Load(String ^filePath)
{
	if (Cypher::Load(filePath))
	{
		String ^fileName(Path::GetFileNameWithoutExtension(filePath));

		activeFile = fileName;
		textboxFileName->Text = fileName;

		if (Cypher::LetterSeparator() == (wchar_t)31)
			cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"None");
		else if (Cypher::LetterSeparator() == (wchar_t)' ')
			cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");
		else
			cboxSeparatorChar->SelectedIndex = -1;

		LoadTranslations(labelUppercase, textboxUppercase);
		LoadTranslations(labelLowercase, textboxLowercase);
		LoadTranslations(labelNumerals, textboxNumerals);
		LoadTranslations(labelSymbols, textboxSymbols);
		return true;
	}
	return false;
}
TranslationEditingWindow::TranslationEditingWindow()
{
}
#undef upper
#undef lower
#undef number
#undef symbol