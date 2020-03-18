/*
*	<translationeditingwindow.h>
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
#pragma once

#ifndef _TRANSLATIONEDITINGWINDOW_H_
#define _TRANSLATIONEDITINGWINDOW_H_

#include "namespaces.h"
#include "winformstemplate.h"

/*
*	TranslationEditingWindow Class
*/
ref class TranslationEditingWindow : public WinFormsTemplate::AppPage
{
private:

	Panel ^panelTranslations;
	CheckBox ^chkboxFixedLength;
	TextBox ^textboxFileName;
	ComboBox
		^cboxSeparatorChar,
		^cboxFixedLength;
	Label
		^labelFileName,
		^labelSeparatorChar,
		^labelFixedLength,
		^labelTranslationTable;
	Button
		^btnBack,
		^btnSave;
	array<Label^>
		^labelUppercase,
		^labelLowercase,
		^labelNumerals,
		^labelSymbols;
	array<TextBox^>
		^textboxUppercase,
		^textboxLowercase,
		^textboxNumerals,
		^textboxSymbols;
	String ^activeFile;

	unsigned short UpdateTextboxesCharLimit();

	void OnCBoxSeparatorCharLostFocus(Object ^sender, EventArgs ^e);
	void OnCBoxFixedLengthLostFocus(Object ^sender, EventArgs ^e);
	void OnChkBoxCheckStateChanged(Object ^sender, EventArgs ^e);
	void OnBtnBackClick(Object ^sender, EventArgs ^e);
	void OnBtnSaveClick(Object ^sender, EventArgs ^e);

protected:

	!TranslationEditingWindow();
	~TranslationEditingWindow();

	virtual void InitializeComponent() override;

public:

	TranslationEditingWindow();

	bool Load(String ^name, String ^text);
};
#endif

#pragma endregion