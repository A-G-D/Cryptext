/*
*	<texteditingwindow.cpp>
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
#include "texteditingwindow.h"
#include "window.h"
#include "namespaces.h"
#include "macros.h"
#include "utils.h"
#include "userdefinitions.h"
#include "cypher.h"
#include "stringtable.h"
#include <gcroot.h>

extern gcroot<stringtable^> strtable;

void TextEditingWindow::InitializeComponent()
{
	CreateTextBox(textboxFileName, L"textboxFileName", 12, 26, 145, 20, 0, AnchorType::TOP_LEFT, false);

	CreateComboBox(cboxTranslation, L"cboxTranslation", 177, 26, 145, 20, 1, AnchorType::TOP_RIGHT, gcnew EventHandler(this, &TextEditingWindow::OnCBoxTranslationLostFocus));
	cboxTranslation->SelectedText = L"< Select Translation >";

	CreateTextBox(textboxInput, L"textboxInput", 12, 78, 310, 104, 2, AnchorType::CENTER, true);
	textboxInput->AcceptsReturn = true;
	textboxInput->AcceptsTab = true;
	textboxInput->MaxLength = 67108864 - 1;
	textboxInput->ScrollBars = ScrollBars::Both;
	textboxInput->KeyDown += gcnew KeyEventHandler(this, &TextEditingWindow::OnTextboxInputKeyDown);
	textboxInput->KeyPress += gcnew KeyPressEventHandler(this, &TextEditingWindow::OnTextboxInputKeyPress);

	CreateTextBox(textboxOutput, L"textboxOutput", 12, 68 + 145, 310, 104, 3, AnchorType::CENTER, true);
	textboxOutput->ReadOnly = true;
	textboxOutput->AcceptsReturn = true;
	textboxOutput->AcceptsTab = true;
	textboxOutput->MaxLength = (textboxInput->MaxLength + 1)*32 - 1;
	textboxOutput->ScrollBars = ScrollBars::Both;

	CreateButton(btnBack, L"btnBack", L"Back", 12, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 5, AnchorType::BOTTOM_LEFT, gcnew EventHandler(this, &TextEditingWindow::OnBtnBackClick));
	CreateButton(btnSave, L"btnSave", L"Save", 247, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 4, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TextEditingWindow::OnBtnSaveClick));
	CreateButton(btnImport, L"btnImport", L"Import", 93, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 6, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TextEditingWindow::OnBtnImportClick));
	CreateButton(btnExport, L"btnExport", L"Export", 170, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 7, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TextEditingWindow::OnBtnExportClick));

	CreateLabel(labelFileName, L"labelFileName", L"File Name", 12, 9, 54, 13, 4, AnchorType::TOP_LEFT);
	CreateLabel(labelTranslation, L"labelTranslation", L"Translation", 177, 9, 54, 13, 4, AnchorType::TOP_RIGHT);
	CreateLabel(labelInput, L"labelInput", L"Input Text", 12, 61, 54, 13, 4, AnchorType::TOP_LEFT);
	CreateLabel(labelOutput, L"labelOuput", L"\r\nOutput Text", 12, 196, 54, 13, 4, AnchorType::TOP_LEFT);

	tlpanelTextboxContainer = gcnew TableLayoutPanel;
	tlpanelTextboxContainer->Location = Point(9, 78);
	tlpanelTextboxContainer->Size = Size(316, 220);
	tlpanelTextboxContainer->RowCount = 4;
	tlpanelTextboxContainer->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	tlpanelTextboxContainer->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 50));
	tlpanelTextboxContainer->RowStyles->Add(gcnew RowStyle(SizeType::AutoSize));
	tlpanelTextboxContainer->RowStyles->Add(gcnew RowStyle(SizeType::Percent, 50));
	tlpanelTextboxContainer->Controls->Add(labelInput);
	tlpanelTextboxContainer->Controls->Add(textboxInput);
	tlpanelTextboxContainer->Controls->Add(labelOutput);
	tlpanelTextboxContainer->Controls->Add(textboxOutput);
	tlpanelTextboxContainer->SetRow(labelInput, 0);
	tlpanelTextboxContainer->SetRow(textboxInput, 1);
	tlpanelTextboxContainer->SetRow(labelOutput, 2);
	tlpanelTextboxContainer->SetRow(textboxOutput, 3);
	tlpanelTextboxContainer->Anchor = (AnchorStyles)AnchorType::CENTER;

	UserDefined::GetProperties(L"TextEditingPage.txt", btnBack, btnImport, btnExport, btnSave, labelFileName, labelTranslation, labelInput, labelOutput, textboxFileName, textboxInput, textboxOutput, cboxTranslation, tlpanelTextboxContainer);

	dialogImport = gcnew OpenFileDialog;
	dialogImport->CheckFileExists = true;
	dialogImport->CheckPathExists = true;
	dialogImport->ValidateNames = true;
	dialogImport->Filter = L"TXT Files (*.txt)|*.txt|All Files (*.*)|*.*";
	dialogImport->FilterIndex = 1;
	dialogImport->RestoreDirectory = true;

	dialogExport = gcnew SaveFileDialog;
	dialogExport->CreatePrompt = false;
	dialogExport->OverwritePrompt = true;
	dialogExport->ValidateNames = true;
	dialogExport->Filter = L"TXT Files (*.txt)|*.txt|All Files (*.*)|*.*";
	dialogExport->FilterIndex = 1;
	dialogExport->RestoreDirectory = true;

	Window::tooltip->SetToolTip(btnImport, L"Import a file as the input text");
	Window::tooltip->SetToolTip(btnExport, L"Export the output text as a file");

	PauseLayout();

	Add(btnBack);
	Add(btnSave);
	Add(btnImport);
	Add(btnExport);
	Add(labelFileName);
	Add(labelTranslation);
	Add(textboxFileName);
	Add(tlpanelTextboxContainer);
	Add(cboxTranslation);

	Hide();

	ResumeLayout();
}
int TextEditingWindow::FindSelectionForwards(int &sStart, int &sLength)
{
	int start(0);
	wchar_t c, nextC;

	if (!sLength)
	{
		++sLength;
		--sStart;
	}
	if (textboxInput->Text[sStart] == (wchar_t)'\n')
		--sStart;

	for (int i(0); i < sStart; ++i)
	{
		c = textboxInput->Text[i];
		(c == (wchar_t)'\r' || c == (wchar_t)'\n') ? ++start : start += Cypher::GetTranslationLength(c);

		if (i < textboxInput->Text->Length - 1)
		{
			nextC = textboxInput->Text[i + 1];
			if (c != (wchar_t)'\r' && c != (wchar_t)'\n' && nextC != (wchar_t)'\r' && nextC != (wchar_t)'\n')
				++start;
		}
	}
	return start;
}
int TextEditingWindow::FindSelectionBackwards(int &end, int &sStart, int &sLength)
{
	int start;
	wchar_t c, prevC;
	for (int i(textboxInput->Text->Length - 1); i > (sStart + sLength - 1); --i)
	{
		c = textboxInput->Text[i];
		(c == (wchar_t)'\r' || c == (wchar_t)'\n') ? --end : end -= Cypher::GetTranslationLength(c);

		if (i)
		{
			prevC = textboxInput->Text[i - 1];
			if (c != (wchar_t)'\r' && c != (wchar_t)'\n' && prevC != (wchar_t)'\r' && prevC != (wchar_t)'\n')
				--end;
		}
	}

	if (!sLength)
	{
		++sLength;
		--sStart;
	}
	start = end + 1;
	for (int i(sLength); i; --i)
	{
		c = textboxInput->Text[sStart + i - 1];
		if (c != (wchar_t)'\r')
		{
			--start;
			start -= Cypher::GetTranslationLength(c);
			if (c == (wchar_t)'\n')
				--start;
			if ((sStart + i - 1) == 0 || (c == (wchar_t)'\n' || textboxInput->Text[sStart + i - 2] == (wchar_t)'\n'))
				++start;
		}
	}
	return start;
}
int TextEditingWindow::DeleteTextForwards(String ^%s, int sStart, int sLength)
{
	int start(FindSelectionForwards(sStart, sLength)), end(start - 1);
	wchar_t c(0);
	for (int i(sLength); i; --i)
	{
		c = textboxInput->Text[sStart + sLength - i];
		if (c != (wchar_t)'\n')
		{
			++end;
			end += Cypher::GetTranslationLength(c);
			if (c == (wchar_t)'\r')
				end += 2;
			if ((sStart + sLength - i) == textboxInput->Text->Length || (c == (wchar_t)'\r' || textboxInput->Text[sStart + sLength - i + 1] == (wchar_t)'\r'))
				--end;
		}
	}
	if (start && s[start - 1] == Cypher::LetterSeparator() && (end < s->Length - 1) && s[end + 1] == (wchar_t)'\r')
		--start;

	s = s->Remove(start, end - start + 1);
	if ((start && s[start - 1] != (wchar_t)'\n') && (start < s->Length && s[start] != (wchar_t)'\r') && s[start - 1] != Cypher::LetterSeparator())
		s = s->Insert(start, String::Empty + Cypher::LetterSeparator());

	return start;
}
int TextEditingWindow::DeleteTextBackwards(String ^%s, int sStart, int sLength)
{
	int end(s->Length - 1), start(FindSelectionBackwards(end, sStart, sLength));
	if (end < s->Length - 1 && s[end + 1] == Cypher::LetterSeparator() && start && s[start - 1] == (wchar_t)'\n')
		++end;

	s = s->Remove(start, end - start + 1);
	if ((start && s[start - 1] != (wchar_t)'\n') && (start < s->Length && s[start] != (wchar_t)'\r') && s[start] != Cypher::LetterSeparator())
		s = s->Insert(start, String::Empty + Cypher::LetterSeparator());

	return start;
}
void TextEditingWindow::OnCBoxTranslationLostFocus(Object ^sender, EventArgs ^e)
{
	if (cboxTranslation->Text == String::Empty)
		cboxTranslation->SelectedIndex = -1;
	else
		cboxTranslation->SelectedIndex = cboxTranslation->FindString(cboxTranslation->Text);

	if (cboxTranslation->SelectedIndex == -1)
		if (activeTranslation == nullptr)
			cboxTranslation->Text = L"< Select Translation >";
		else
			cboxTranslation->SelectedIndex = cboxTranslation->FindString(activeTranslation);

	if (cboxTranslation->SelectedIndex == -1)
		activeTranslation = nullptr;
	else
	{
		bool rewriteOutput = activeTranslation != cboxTranslation->Text;
		activeTranslation = cboxTranslation->Text;
		Cypher::Load(TRANSLATION_FILES_FOLDER_NAME + L"\\" + activeTranslation + TRANSLATION_FILE_EXTENSION);
		if (rewriteOutput)
			textboxOutput->Text = Cypher::TranslateAllText(textboxInput->Text);
	}
}
void TextEditingWindow::OnTextboxInputKeyDown(Object ^sender, KeyEventArgs ^e)
{
	textboxInput->ClearUndo();
	if (e->KeyCode == Keys::Delete)
		OnTextboxInputKeyPress(sender, nullptr);
}
void TextEditingWindow::OnTextboxInputKeyPress(Object ^sender, KeyPressEventArgs ^e)
{
	String ^clipText(nullptr);
	bool deletePressed(e == nullptr);
	int sLength(textboxInput->SelectionLength), sStart(textboxInput->SelectionStart);
	wchar_t c(0);

	if ((Control::ModifierKeys & Keys::Control) == Keys::Control)
	{
		if (deletePressed)
			sLength = textboxInput->Text->Length - sStart;
		else
		{
			switch ((wchar_t)e->KeyChar)
			{
				case (wchar_t)24:
					deletePressed = true;
					break;

				case (wchar_t)22:
					clipText = Clipboard::GetText();
					break;

				case (wchar_t)8:
				case (wchar_t)9:
				case (wchar_t)10:
				case (wchar_t)13:
				case (wchar_t)127:
					break;

				case (wchar_t)1:
					textboxInput->SelectionStart = 0;
					textboxInput->SelectionLength = textboxInput->Text->Length;
					e->Handled = true;
					return;

				case (wchar_t)3:
					if (textboxInput->SelectedText != nullptr && textboxInput->SelectedText != String::Empty)
						Clipboard::SetText(textboxInput->SelectedText);
				default:
					e->Handled = true;
					return;
			}
		}
	}
	else if (deletePressed && sLength == 0 && sStart < textboxInput->Text->Length)
		sLength = 1;

	if (!deletePressed)
		c = ((wchar_t)e->KeyChar == (wchar_t)'\r') ? (wchar_t)'\n' : (wchar_t)e->KeyChar;

	String ^%internOutput(textboxOutput->Text);
	if ((deletePressed && sLength) || (!deletePressed && e->KeyChar == (wchar_t)Keys::Back))
	{
		if (!textboxInput->SelectionStart && !sLength)
			return;

		if (textboxInput->Text->Length - (sStart + sLength) > sStart)
			DeleteTextForwards(internOutput, sStart, sLength);
		else
			DeleteTextBackwards(internOutput, sStart, sLength);
	}
	else if (!deletePressed)
	{
		int start, selStart(sStart + 1);
		if (textboxInput->Text->Length - (sStart + sLength) > sStart)
		{
			start = (sLength) ? DeleteTextForwards(internOutput, sStart, sLength) : FindSelectionForwards(selStart, sLength);
			if (sStart)
				--start;
			if (internOutput[start] != Cypher::LetterSeparator() && start)
				++start;
		}
		else
		{
			if (sLength)
				start = DeleteTextBackwards(internOutput, sStart, sLength);
			else if (sStart == textboxInput->Text->Length)
				start = internOutput->Length;
			else
			{
				int end(internOutput->Length - 1);
				start = FindSelectionBackwards(end, selStart, sLength);
				if (internOutput[start] == (wchar_t)'\n')
					--start;
			}
		}

		String ^input((clipText == nullptr) ? Cypher::Translate(c) : Cypher::TranslateAllText(clipText));

		if (input == String::Empty)
			e->Handled = true;
		else if (input == L"\n")
		{
			if (start < internOutput->Length && internOutput[start] == Cypher::LetterSeparator())
				internOutput = internOutput->Remove(start, 1);
			else if (start && internOutput[start - 1] == Cypher::LetterSeparator())
				internOutput = internOutput->Remove(start - 1, 1);
			internOutput = internOutput->Insert(start, L"\r\n");
		}
		else if (internOutput->Length == 0)
			internOutput = internOutput->Insert(start, input);
		else if (start == 0)
			internOutput = internOutput->Insert(0, input + Cypher::LetterSeparator());
		else if (internOutput[start - 1] == (wchar_t)'\n')
		{
			if (start < internOutput->Length)
			{
				if (internOutput[start] == (wchar_t)'\r')
					internOutput = internOutput->Insert(start, input);
				else
					internOutput = internOutput->Insert(start, input + Cypher::LetterSeparator());
			}
			else
				internOutput = internOutput->Insert(start, input);
		}
		else
			internOutput = internOutput->Insert(start, Cypher::LetterSeparator() + input);
	}
	textboxOutput->Text = internOutput;
}
void TextEditingWindow::OnBtnBackClick(Object ^sender, EventArgs ^e)
{
	Cypher::Clear();

	activeFile = String::Empty;
	activeTranslation = nullptr;

	cboxTranslation->SelectedIndex = -1;
	cboxTranslation->Text = L"< Select Translation >";
	textboxFileName->Clear();
	textboxInput->Clear();
	textboxOutput->Clear();

	Display(prevForm);
}
void TextEditingWindow::OnBtnSaveClick(Object ^sender, EventArgs ^e)
{
	String ^newName(TEXT_FILES_FOLDER_NAME + L"\\" + textboxFileName->Text + L"\\" + textboxFileName->Text);
	if (textboxFileName->Text == String::Empty)
		MessageBox::Show(MESSAGE_CREATE_FILE_FAILURE, CAPTION_CREATE_FILE_FAILURE, MessageBoxButtons::OK);

	else
	{
		String
			^currentPath(TEXT_FILES_FOLDER_NAME + L"\\" + activeFile + L"\\" + activeFile + KEY_FILE_EXTENSION),
			^keyOutput(String::Empty);

		if (cboxTranslation->SelectedIndex > -1)
		{
			activeTranslation = cboxTranslation->SelectedItem->ToString();
			String ^translationText(activeTranslation + L"\n\n" + File::ReadAllText(TRANSLATION_FILES_FOLDER_NAME + L"\\" + activeTranslation + TRANSLATION_FILE_EXTENSION));

			Cypher::LoadInternal();
			keyOutput = Cypher::TranslateAllText(translationText);
			Cypher::LoadFromString(translationText);
		}
		else if (File::Exists(currentPath))
		{
			if (LoadKey(activeFile))
				keyOutput = File::ReadAllText(currentPath);
			else
			{
				MessageBox::Show(MESSAGE_MISSING_KEY_ERROR, CAPTION_MISSING_KEY_ERROR, MessageBoxButtons::OK);
				return;
			}
		}
		else
		{
			MessageBox::Show(MESSAGE_MISSING_KEY_ERROR, CAPTION_MISSING_KEY_ERROR, MessageBoxButtons::OK);
			return;
		}

		if (activeFile != textboxFileName->Text)
		{
			if (activeFile != String::Empty && activeFile != nullptr)
				Directory::Delete(TEXT_FILES_FOLDER_NAME + L"\\" + activeFile, true);
			Directory::CreateDirectory(TEXT_FILES_FOLDER_NAME + L"\\" + textboxFileName->Text);
			activeFile = textboxFileName->Text;
		}
		File::WriteAllText(newName + TEXT_FILE_EXTENSION, textboxOutput->Text);
		File::WriteAllText(newName + KEY_FILE_EXTENSION, keyOutput);
	}
}
void TextEditingWindow::OnBtnImportClick(Object ^sender, EventArgs ^e)
{
	if (dialogImport->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		textboxInput->Text = File::ReadAllText(Path::GetFullPath(dialogImport->FileName));
		if (cboxTranslation->SelectedIndex > -1)
		{
			Cypher::Load(TRANSLATION_FILES_FOLDER_NAME + L"\\" + cboxTranslation->SelectedItem->ToString() + TRANSLATION_FILE_EXTENSION);
			textboxOutput->Text = Cypher::TranslateAllText(textboxInput->Text);
			Cypher::Clear();
		}
	}
}
void TextEditingWindow::OnBtnExportClick(Object ^sender, EventArgs ^e)
{
	if (dialogExport->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		File::WriteAllText(Path::GetFullPath(dialogExport->FileName), textboxOutput->Text);
}
bool TextEditingWindow::LoadKey(String ^fileName)
{
	Cypher::LoadInternal();
	String ^decrypted(Cypher::ReadAllText(File::ReadAllText(TEXT_FILES_FOLDER_NAME + L"\\" + fileName + L"\\" + fileName + KEY_FILE_EXTENSION)));

	if (Cypher::LoadFromString(decrypted))
	{
		activeTranslation = Cypher::GetEqualTranslation(decrypted);
		activeFile = fileName;
		return true;
	}
	return false;
}
bool TextEditingWindow::LoadData(String ^fileName)
{
	Cypher::LoadInternal();
	String ^outputText(File::ReadAllText(TEXT_FILES_FOLDER_NAME + L"\\" + fileName + L"\\" + fileName + TEXT_FILE_EXTENSION));

	if (LoadKey(fileName))
	{
		textboxFileName->Text = activeFile;
		textboxInput->Text = Cypher::ReadAllText(outputText)->Replace(L"\n", L"\r\n");
		textboxOutput->Text = outputText;

		return true;
	}
	return false;
}
void TextEditingWindow::Show()
{
	PauseLayout();

	btnBack->Show();
	btnSave->Show();
	btnImport->Show();
	btnExport->Show();
	labelFileName->Show();
	labelTranslation->Show();
	textboxFileName->Show();
	tlpanelTextboxContainer->Show();
	cboxTranslation->Show();

	cboxTranslation->BeginUpdate();
	cboxTranslation->Items->Clear();
	if (!GetTranslations(cboxTranslation->Items))
		Directory::CreateDirectory(TRANSLATION_FILES_FOLDER_NAME);
	cboxTranslation->EndUpdate();
	cboxTranslation->SelectedIndex = cboxTranslation->FindStringExact(activeTranslation);

	Window::Show();

	ResumeLayout();
}
void TextEditingWindow::Hide()
{
	btnBack->Hide();
	btnSave->Hide();
	btnImport->Hide();
	btnExport->Hide();
	labelFileName->Hide();
	labelTranslation->Hide();
	textboxFileName->Hide();
	tlpanelTextboxContainer->Hide();
	cboxTranslation->Hide();

	Window::Hide();
}
bool TextEditingWindow::Load(String ^fileName)
{
	if (LoadKey(fileName))
	{
		LoadData(fileName);
		return true;
	}
	MessageBox::Show(MESSAGE_MISSING_KEY_ERROR, CAPTION_MISSING_KEY_ERROR, MessageBoxButtons::OK);
	return false;
}
void TextEditingWindow::SetupData(String ^fileName, String ^fileContent)
{
	textboxFileName->Text = fileName;
	textboxInput->Text = fileContent;
}
TextEditingWindow::TextEditingWindow(Window ^form)
	: prevForm(form)
{
	InitializeComponent();
}