/*
*	<translatorwindow.cpp>
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
#include "translatorwindow.h"
#include "namespaces.h"
#include "macros.h"
#include "utils.h"
#include "userdefinitions.h"
#include "cypher.h"
#include "winformstemplate.h"
#include "mainwindow.h"
#include <gcroot.h>

using namespace WinFormsTemplate;

extern gcroot<MainWindow^> mainWindow;

/*
*	TranslatorWindow Class Definitions
*/
void TranslatorWindow::InitializeComponent()
{
	CreateComboBox(cboxTranslation, L"cboxTranslation", 12, 26, 145, 20, 1, AnchorType::TOP_LEFT, gcnew EventHandler(this, &TranslatorWindow::OnCBoxTranslationLostFocus));
	cboxTranslation->SelectedText = L"< Select Translation >";

	CreateTextBox(textboxInput, L"textboxInput", 12, 78, 310, 104, 2, AnchorType::CENTER, true);
	textboxInput->WordWrap = false;
	textboxInput->AcceptsReturn = true;
	textboxInput->AcceptsTab = true;
	textboxInput->MaxLength = 67108864 - 1;
	textboxInput->ScrollBars = ScrollBars::Both;

	CreateTextBox(textboxOutput, L"textboxOutput", 12, 68 + 145, 310, 104, 3, AnchorType::CENTER, true);
	textboxOutput->WordWrap = false;
	textboxOutput->AcceptsReturn = true;
	textboxOutput->AcceptsTab = true;
	textboxOutput->MaxLength = (textboxInput->MaxLength + 1)*32 - 1;
	textboxOutput->ScrollBars = ScrollBars::Both;

	CreateButton(btnBack, L"btnBack", L"Back", 12, 325, BUTTON_WIDTH, BUTTON_HEIGHT, 7, AnchorType::BOTTOM_LEFT, gcnew EventHandler(this, &TranslatorWindow::OnBtnBackClick));
	CreateButton(btnTranslateToText, L"btnTranslateToText", L"Translate To Text", 110, 325, BUTTON_WIDTH + 30, BUTTON_HEIGHT, 5, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TranslatorWindow::OnBtnTranslateToTextClick));
	CreateButton(btnTranslateToCode, L"btnTranslateToCode", L"Translate To Code", 217, 325, BUTTON_WIDTH + 30, BUTTON_HEIGHT, 6, AnchorType::BOTTOM_RIGHT, gcnew EventHandler(this, &TranslatorWindow::OnBtnTranslateToCodeClick));

	CreateLabel(labelTranslation, L"labelTranslation", L"Translation", 12, 9, 54, 13, 4, AnchorType::TOP_LEFT);
	CreateLabel(labelInput, L"labelInput", L"Text", 12, 61, 54, 13, 4, AnchorType::TOP_LEFT);
	CreateLabel(labelOutput, L"labelOutput", L"\r\nTranslation", 12, 196, 54, 13, 4, AnchorType::TOP_LEFT);

	tlpanelTextboxContainer = gcnew TableLayoutPanel;
	tlpanelTextboxContainer->Name = L"tlpanelTextboxContainer";
	tlpanelTextboxContainer->Location = Point(9, 78);
	tlpanelTextboxContainer->Size = Size(316, 220);
	tlpanelTextboxContainer->RowCount = 4;
	tlpanelTextboxContainer->Anchor = (AnchorStyles)AnchorType::CENTER;

	tlpanelTextboxContainer->SuspendLayout();

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

	tlpanelTextboxContainer->ResumeLayout();

	PauseLayout();

	AddControl(
		btnBack,
		btnTranslateToCode,
		btnTranslateToText,
		labelTranslation,
		tlpanelTextboxContainer,
		cboxTranslation
	);
	OnHide();

	UserDefined::GetProperties(L"TranslatorPage.txt", btnBack, btnTranslateToCode, btnTranslateToText, labelTranslation, labelInput, labelOutput, textboxInput, textboxOutput, cboxTranslation, tlpanelTextboxContainer);

	ResumeLayout();
}
void TranslatorWindow::OnBtnBackClick(Object ^sender, EventArgs ^e)
{
	Cypher::Clear();

	activeTranslation = nullptr;

	cboxTranslation->SelectedIndex = -1;
	cboxTranslation->Text = L"< Select Translation >";
	textboxInput->Clear();
	textboxOutput->Clear();

	mainWindow->Display(true);
}
void TranslatorWindow::OnBtnTranslateToCodeClick(Object ^sender, EventArgs ^e)
{
	textboxOutput->Text = Cypher::TranslateAllText(textboxInput->Text);
}
void TranslatorWindow::OnBtnTranslateToTextClick(Object ^sender, EventArgs ^e)
{
	textboxInput->Text = Cypher::ReadAllText(textboxOutput->Text);
}

void TranslatorWindow::OnCBoxTranslationLostFocus(Object ^sender, EventArgs ^e)
{
	cboxTranslation->SelectedIndex = (cboxTranslation->Text == String::Empty) ? -1 : cboxTranslation->FindString(cboxTranslation->Text);
	if (cboxTranslation->SelectedIndex == -1)
		if (activeTranslation == nullptr)
			cboxTranslation->Text = L"< Select Translation >";
		else
			cboxTranslation->SelectedIndex = cboxTranslation->FindString(activeTranslation);

	if (cboxTranslation->SelectedIndex == -1)
		activeTranslation = nullptr;
	else
	{
		activeTranslation = cboxTranslation->Text;
		Cypher::LoadFromString(ReadTranslationFile(activeTranslation + TRANSLATION_FILE_EXTENSION));
	}
}

TranslatorWindow::TranslatorWindow()
{
}

void TranslatorWindow::OnShow()
{
	cboxTranslation->BeginUpdate();
	cboxTranslation->Items->Clear();
	GetTranslations(cboxTranslation->Items);
	cboxTranslation->SelectedIndex = cboxTranslation->FindStringExact(activeTranslation);
	cboxTranslation->EndUpdate();

	AppPage::OnShow();
}