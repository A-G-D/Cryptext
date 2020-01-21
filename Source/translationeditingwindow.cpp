/*
*	<translationeditingwindow.cpp>
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

extern gcroot<StringTable^> strtable;
extern gcroot<TextFilesWindow^> textFilesWindow;

wchar_t separatorCharInput(0);

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

	CreateComboBox(cboxSeparatorChar, L"cboxSeparatorChar", 12, 70, 145, 20, 1, AnchorType::TOP_LEFT, gcnew EventHandler(this, &TranslationEditingWindow::OnCBoxSeparatorCharLostFocus));
	cboxSeparatorChar->BeginUpdate();
	cboxSeparatorChar->Items->Add(L"None");
	cboxSeparatorChar->Items->Add(L"Space");
	cboxSeparatorChar->EndUpdate();
	cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");

	CreateComboBox(cboxFixedLength, L"cboxFixedLength", 300, 70, 30, 20, 0, AnchorType::TOP_RIGHT, gcnew EventHandler(this, &TranslationEditingWindow::OnCBoxFixedLengthLostFocus));
	cboxFixedLength->BeginUpdate();
	for (int i(0); ++i <= 0x40; cboxFixedLength->Items->Add(Convert::ToString(i)));
	cboxFixedLength->EndUpdate();
	cboxFixedLength->SelectedIndex = cboxFixedLength->FindStringExact(L"1");
	cboxFixedLength->Enabled = false;

	CreateCheckBox(chkboxFixedLength, L"chkboxFixedLength", 210, 70, 20, 20, 0, AnchorType::TOP_RIGHT, Appearance::Normal, true, gcnew EventHandler(this, &TranslationEditingWindow::OnChkBoxCheckStateChanged));

	CreateButton(btnBack, L"btnBack", L"Back", 12, 328, BUTTON_WIDTH, BUTTON_HEIGHT, 98, AnchorType::BOTTOM_LEFT, gcnew EventHandler(this, &TranslationEditingWindow::OnBtnBackClick));
	CreateButton(btnSave, L"btnSave", L"Save", 247, 328, BUTTON_WIDTH, BUTTON_HEIGHT, 99, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TranslationEditingWindow::OnBtnSaveClick));

	CreateLabel(labelFileName, L"labelFileName", L"Translation Name", 12, 9, 54, 13, 4, AnchorType::TOP_LEFT);
	CreateLabel(labelSeparatorChar, L"labelSeparatorChar", L"Letter Separator", 12, 56, 54, 13, 5, AnchorType::TOP_LEFT);
	CreateLabel(labelFixedLength, L"labelFixedLength", L"Fixed Length", 227, 72, 54, 13, 0, AnchorType::TOP_RIGHT);
	CreateLabel(labelTranslationTable, L"labelTranslationTable", L"Translation Table", 9, 112, 89, 13, 6, AnchorType::TOP_LEFT);

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
	CreatePanel(panelTranslations, L"panelTranslations", 12, 132, 318, 190, 1, AnchorType::CENTER, true);

	panelTranslations->SuspendLayout();

	panelTranslations->Controls->AddRange(labelUppercase);
	panelTranslations->Controls->AddRange(labelLowercase);
	panelTranslations->Controls->AddRange(labelNumerals);
	panelTranslations->Controls->AddRange(labelSymbols);
	panelTranslations->Controls->AddRange(textboxUppercase);
	panelTranslations->Controls->AddRange(textboxLowercase);
	panelTranslations->Controls->AddRange(textboxNumerals);
	panelTranslations->Controls->AddRange(textboxSymbols);

	panelTranslations->ResumeLayout(false);
	panelTranslations->PerformLayout();

	AddControl(
		panelTranslations,
		textboxFileName,
		labelFileName,
		labelSeparatorChar,
		labelFixedLength,
		labelTranslationTable,
		btnBack,
		btnSave,
		cboxSeparatorChar,
		cboxFixedLength,
		chkboxFixedLength
	);
	OnHide();

	UserDefined::GetProperties(L"TranslationEditingPage.txt",
		btnBack, btnSave, chkboxFixedLength, labelFileName, labelSeparatorChar, labelFixedLength, labelTranslationTable, textboxFileName, cboxSeparatorChar, cboxFixedLength, panelTranslations,
		upper(0), upper(1), upper(2), upper(3), upper(4), upper(5), upper(6), upper(7), upper(8), upper(9), upper(10), upper(11), upper(12), upper(13),
		upper(14), upper(15), upper(16), upper(17), upper(18), upper(19), upper(20), upper(21), upper(22), upper(23), upper(24), upper(25),
		lower(0), lower(1), lower(2), lower(3), lower(4), lower(5), lower(6), lower(7), lower(8), lower(9), lower(10), lower(11), lower(12), lower(13),
		lower(14), lower(15), lower(16), lower(17), lower(18), lower(19), lower(20), lower(21), lower(22), lower(23), lower(24), lower(25),
		number(0), number(1), number(2), number(3), number(4), number(5), number(6), number(7), number(8), number(9),
		symbol(0), symbol(1), symbol(2), symbol(3), symbol(4), symbol(5), symbol(6), symbol(7), symbol(8), symbol(9), symbol(10), symbol(11), symbol(12),
		symbol(13), symbol(14), symbol(15), symbol(16), symbol(17), symbol(18), symbol(19), symbol(20), symbol(21), symbol(22), symbol(23), symbol(24),
		symbol(25), symbol(26), symbol(27), symbol(28), symbol(29), symbol(30), symbol(31), symbol(32), symbol(33)
	);

	ResumeLayout();

	activeFile = String::Empty;
}
void GetInputChars(array<Label^> ^label, array<TextBox^> ^textbox, String ^%output, unsigned short length)
{
	output += L"\n";

	array<String^> ^suffix = gcnew array<String^>(length + 1);

	if (length)
		for (unsigned short i(length + 1); i--;)
		{
			suffix[i] = String::Empty;
			for (unsigned short j(i); j--; suffix[i] += L" ");
		}

	for (int i(0); i < textbox->Length; ++i)
		if (separatorCharInput != 0 && textbox[i]->Text->Contains(String::Empty + separatorCharInput))
			throw true;
		else if (label[i]->Text == L"Tab")
		{
			output += (L"@\t    \t{" + textbox[i]->Text);
			if (length && textbox[i]->Text != String::Empty)
				output += suffix[length - textbox[i]->Text->Length];
			output += L"}\n";
		}
		else if (label[i]->Text == L"&&")
		{
			output += (L"@&  \t\t{" + textbox[i]->Text);
			if (length && textbox[i]->Text != String::Empty)
				output += suffix[length - textbox[i]->Text->Length];
			output += L"}\n";
		}
		else
		{
			output += (L"@" + label[i]->Text + L"  \t\t{" + textbox[i]->Text);
			if (length && textbox[i]->Text != String::Empty)
				output += suffix[length - textbox[i]->Text->Length];
			output += L"}\n";
		}
}
void LoadTranslations(array<Label^> ^label, array<TextBox^> ^textbox)
{
	for (int i(0); i < textbox->Length; ++i)
		textbox[i]->Text = (String^)(Cypher::Translate((wchar_t)((label[i]->Text == L"Tab") ? '\t' : label[i]->Text[0])));
}
unsigned short TranslationEditingWindow::UpdateTextboxesCharLimit()
{
	unsigned short length(Convert::ToByte(cboxFixedLength->SelectedItem->ToString()));
	for (int i(0); i < textboxUppercase->Length; ++i)
	{
		textboxUppercase[i]->MaxLength = length;
		textboxLowercase[i]->MaxLength = length;

		textboxUppercase[i]->Text = textboxUppercase[i]->Text->Substring(0, MIN(length, textboxUppercase[i]->Text->Length));
		textboxLowercase[i]->Text = textboxLowercase[i]->Text->Substring(0, MIN(length, textboxLowercase[i]->Text->Length));
	}
	for (int i(0); i < textboxNumerals->Length; ++i)
	{
		textboxNumerals[i]->MaxLength = length;
		textboxNumerals[i]->Text = textboxNumerals[i]->Text->Substring(0, MIN(length, textboxNumerals[i]->Text->Length));
	}
	for (int i(0); i < textboxSymbols->Length; ++i)
	{
		textboxSymbols[i]->MaxLength = length;
		textboxSymbols[i]->Text = textboxSymbols[i]->Text->Substring(0, MIN(length, textboxSymbols[i]->Text->Length));
	}
	return length;
}
void TranslationEditingWindow::OnCBoxSeparatorCharLostFocus(Object ^sender, EventArgs ^e)
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
void TranslationEditingWindow::OnCBoxFixedLengthLostFocus(Object ^sender, EventArgs ^e)
{
	cboxFixedLength->SelectedIndex = cboxFixedLength->FindString(cboxFixedLength->Text);
	UpdateTextboxesCharLimit();
}
void TranslationEditingWindow::OnChkBoxCheckStateChanged(Object ^sender, EventArgs ^e)
{
	cboxSeparatorChar->Enabled = !chkboxFixedLength->Checked;
	cboxFixedLength->Enabled = chkboxFixedLength->Checked;

	if (chkboxFixedLength->Checked)
		UpdateTextboxesCharLimit();
}
void TranslationEditingWindow::OnBtnBackClick(Object ^sender, EventArgs ^e)
{
	Cypher::Clear();
	activeFile = String::Empty;
	textboxFileName->Clear();
	cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");
	cboxFixedLength->SelectedIndex = cboxFixedLength->FindStringExact(L"1");
	chkboxFixedLength->CheckState = CheckState::Unchecked;

	LoadTranslations(labelUppercase, textboxUppercase);
	LoadTranslations(labelLowercase, textboxLowercase);
	LoadTranslations(labelNumerals, textboxNumerals);
	LoadTranslations(labelSymbols, textboxSymbols);

	textFilesWindow->Display(true);
}
void TranslationEditingWindow::OnBtnSaveClick(Object ^sender, EventArgs ^e)
{
	if (textboxFileName->Text == String::Empty)
	{
		MessageBox::Show(MESSAGE_CREATE_TRANSLATION_FAILURE, CAPTION_CREATE_TRANSLATION_FAILURE, MessageBoxButtons::OK);
		return;
	}

	String
		^archivePath(AppDomain::CurrentDomain->BaseDirectory + TRANSLATION_ARCHIVE_NAME + TRANSLATION_ARCHIVE_EXTENSION),
		^output(String::Empty);

	if (chkboxFixedLength->Checked)
	{
		output += L"#TRANSLATION_LENGTH = " + cboxFixedLength->SelectedItem->ToString() + L"\n\n\n";
		separatorCharInput = 0;
	}
	else if (cboxSeparatorChar->SelectedIndex == -1)
	{
		output += L"#LETTER_SEPARATOR = '" + Cypher::LetterSeparator() + L"'\n\n\n";
		separatorCharInput = Cypher::LetterSeparator();
	}
	else if (cboxSeparatorChar->SelectedIndex == cboxSeparatorChar->FindStringExact(L"None"))
	{
		output += L"#LETTER_SEPARATOR = '" + (wchar_t)31 + "'\n\n\n";
		separatorCharInput = (wchar_t)31;
	}
	else if (cboxSeparatorChar->SelectedIndex == cboxSeparatorChar->FindStringExact(L"Space"))
	{
		output += L"#LETTER_SEPARATOR = ' '\n\n\n";
		separatorCharInput = (wchar_t)' ';
	}

	output += L"Char\t\tTranslation\n\n";

	try
	{
		unsigned short length(Convert::ToByte(cboxFixedLength->SelectedItem->ToString()));
		GetInputChars(labelUppercase, textboxUppercase, output, length);
		GetInputChars(labelLowercase, textboxLowercase, output, length);
		GetInputChars(labelNumerals, textboxNumerals, output, length);
		GetInputChars(labelSymbols, textboxSymbols, output, length);
	}
	catch (bool)
	{
		MessageBox::Show(L"Separator Character '" + separatorCharInput + L"' is also used as a translation character.", L"Translation File Error", MessageBoxButtons::OK);
		Cypher::Clear();
		separatorCharInput = 0;
		return;
	}
	output += L"@\n    \t\t{\n}\n";

	if (!File::Exists(archivePath))
	{
		FileStream ^fileStream(gcnew FileStream(archivePath, FileMode::Create));
		(gcnew ZipArchive(fileStream, ZipArchiveMode::Create))->~ZipArchive();
		fileStream->Close();
	}

	if (activeFile == String::Empty)
	{
		activeFile = textboxFileName->Text;
		ZipArchive ^archive(ZipFile::Open(archivePath, ZipArchiveMode::Update));
		StreamWriter ^inputStream(gcnew StreamWriter(archive->CreateEntry(activeFile + TRANSLATION_FILE_EXTENSION)->Open()));
		inputStream->Write(output);
		inputStream->Close();
		archive->~ZipArchive();
		MessageBox::Show(MESSAGE_CREATE_TRANSLATION_SUCCESS, CAPTION_CREATE_TRANSLATION_SUCCESS, MessageBoxButtons::OK);
	}
	else if (activeFile != textboxFileName->Text)
	{
		ZipArchive ^archive(ZipFile::Open(archivePath, ZipArchiveMode::Update));
		archive->GetEntry(activeFile + TRANSLATION_FILE_EXTENSION)->Delete();
		activeFile = textboxFileName->Text;
		StreamWriter ^inputStream(gcnew StreamWriter(archive->CreateEntry(activeFile + TRANSLATION_FILE_EXTENSION)->Open()));
		inputStream->Write(output);
		inputStream->Close();
		archive->~ZipArchive();
	}
	else
	{
		ZipArchive ^archive(ZipFile::Open(archivePath, ZipArchiveMode::Update));
		StreamWriter ^inputStream(gcnew StreamWriter(archive->GetEntry(activeFile + TRANSLATION_FILE_EXTENSION)->Open()));
		inputStream->Write(output);
		inputStream->Close();
		archive->~ZipArchive();
	}
}
bool TranslationEditingWindow::Load(String ^name, String ^text)
{
	if (Cypher::LoadFromString(text))
	{
		String ^fileName(Path::GetFileNameWithoutExtension(name));

		activeFile = fileName;
		textboxFileName->Text = fileName;

		if (Cypher::FixedLength() > 0)
		{
			cboxSeparatorChar->SelectedIndex = -1;
			cboxFixedLength->SelectedIndex = cboxFixedLength->FindStringExact(Convert::ToString(Cypher::FixedLength()));
			chkboxFixedLength->CheckState = CheckState::Checked;
		}
		else
		{
			chkboxFixedLength->CheckState = CheckState::Unchecked;
			if (Cypher::LetterSeparator() == (wchar_t)31)
				cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"None");
			else if (Cypher::LetterSeparator() == (wchar_t)' ')
				cboxSeparatorChar->SelectedIndex = cboxSeparatorChar->FindStringExact(L"Space");
			else
				cboxSeparatorChar->SelectedIndex = -1;
		}
		
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