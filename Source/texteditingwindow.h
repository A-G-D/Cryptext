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
#include "winformstemplate.h"

/*
*	TextEditingWindow Class
*/
ref class TextEditingWindow : public WinFormsTemplate::AppPage
{
private:

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

	int FindSelectionForwards(int &sStart, int &sLength);
	int FindSelectionBackwards(int &end, int &sStart, int &sLength);

	int DeleteTextForwards(String ^%s, int sStart, int sLength);
	int DeleteTextBackwards(String ^%s, int sStart, int sLength);

	void OnCBoxTranslationLostFocus(Object ^sender, EventArgs ^e);

	void OnTextboxInputKeyDown(Object ^sender, KeyEventArgs ^e);
	void OnTextboxInputKeyPress(Object ^sender, KeyPressEventArgs ^e);

	void OnBtnBackClick(Object ^sender, EventArgs ^e);
	void OnBtnSaveClick(Object ^sender, EventArgs ^e);
	void OnBtnImportClick(Object ^sender, EventArgs ^e);
	void OnBtnExportClick(Object ^sender, EventArgs ^e);

	bool LoadKey(String ^filePath);
	bool LoadData(String ^filePath);

protected:

	!TextEditingWindow()
	{
	}
	~TextEditingWindow()
	{
		this->!TextEditingWindow();
	}

	virtual void InitializeComponent() override;

	virtual void OnShow() override;

public:

	bool Load(String ^filePath, bool showError);

	TextEditingWindow();
};
#endif

#pragma endregion