/*
*	<translationeditingwindow.h>
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
#pragma once

#ifndef _TRANSLATIONEDITINGWINDOW_H_
#define _TRANSLATIONEDITINGWINDOW_H_

#include "namespaces.h"
#include "window.h"

/*
*	TranslationEditingWindow Class
*/
ref class TranslationEditingWindow : public Window
{
private:

	Window ^prevForm;
	Panel ^panelTranslations;
	TextBox ^textboxFileName;
	ComboBox ^cboxSeparatorChar;
	Label
		^labelFileName,
		^labelSeparatorChar,
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

	void CreateColumnElements(array<Label^> ^%label, array<TextBox^> ^%textbox, int size, int x, int charOffset, int tabOffset);

	void InitializeComponent();
	static void GetInputChars(array<Label^> ^label, array<TextBox^> ^textbox, String ^%output);
	static void LoadTranslations(array<Label^> ^label, array<TextBox^> ^textbox);

	void OnCBoxLostFocus(Object ^sender, EventArgs ^e);
	void OnBtnBackClick(Object ^sender, EventArgs ^e);
	void OnBtnSaveClick(Object ^sender, EventArgs ^e);

protected:

	!TranslationEditingWindow()
	{
	}
	~TranslationEditingWindow()
	{
		this->!TranslationEditingWindow();
	}

public:

	TranslationEditingWindow(Window ^form);

	bool Load(String ^filePath);

	virtual void Show() override;
	virtual void Hide() override;
};
#endif

#pragma endregion