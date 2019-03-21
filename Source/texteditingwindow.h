/*
*	<texteditingwindow.h>
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

#ifndef _TEXTEDITINGWINDOW_H_
#define _TEXTEDITINGWINDOW_H_

#include "namespaces.h"
#include "window.h"

/*
*	TextEditingWindow Class
*/
ref class TextEditingWindow : public Window
{
private:
	Window ^prevForm;
	Label
		^labelFileName,
		^labelTranslation,
		^labelInput,
		^labelOutput;
	TextBox
		^textboxFileName,
		^textboxInput,
		^textboxOutput;
	TableLayoutPanel ^tlpanelTextboxContainer;
	ComboBox ^cboxTranslation;
	SaveFileDialog ^dialogExport;
	OpenFileDialog ^dialogImport;
	Button
		^btnExport,
		^btnImport,
		^btnBack,
		^btnSave;

	String
		^activeFile,
		^activeTranslation;

	void InitializeComponent();

	int FindSelectionForwards(int &sStart, int &sLength);
	int FindSelectionBackwards(int &end, int &sStart, int &sLength);

	int DeleteTextForwards(String ^%s, int sStart, int sLength);
	int DeleteTextBackwards(String ^%s, int sStart, int sLength);

	void OnCBoxLostFocus(Object ^sender, EventArgs ^e);

	void OnTextboxInputKeyDown(Object ^sender, KeyEventArgs ^e);
	void OnTextboxInputKeyPress(Object ^sender, KeyPressEventArgs ^e);

	void OnBtnBackClick(Object ^sender, EventArgs ^e);
	void OnBtnSaveClick(Object ^sender, EventArgs ^e);
	void OnBtnImportClick(Object ^sender, EventArgs ^e);
	void OnBtnExportClick(Object ^sender, EventArgs ^e);

	bool LoadKey(String ^fileName);
	bool LoadData(String ^fileName);

protected:

	!TextEditingWindow()
	{
	}

	~TextEditingWindow()
	{
		this->!TextEditingWindow();
	}

public:

	virtual void Show() override;

	virtual void Hide() override;

	bool Load(String ^fileName);

	void SetupData(String ^fileName, String ^fileContent);

	TextEditingWindow(Window ^form);
};
#endif

#pragma endregion