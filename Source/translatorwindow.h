/*
*	<translatorwindow.h>
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

#ifndef __TRANSLATORWINDOW_H__
#define __TRANSLATORWINDOW_H__

#include "namespaces.h"
#include "window.h"

/*
*	TranslatorWindow Class
*/
ref class TranslatorWindow : public Window
{
private:

	Window ^prevForm;
	ComboBox ^cboxTranslation;
	TableLayoutPanel ^tlpanelTextboxContainer;
	Label
		^labelTranslation,
		^labelInput,
		^labelOutput;
	TextBox
		^textboxInput,
		^textboxOutput;
	Button
		^btnBack,
		^btnTranslateToCode,
		^btnTranslateToText;

	String ^activeTranslation;

	void InitializeComponent();

	void OnBtnBackClick(Object ^sender, EventArgs ^e);
	void OnBtnTranslateToCodeClick(Object ^sender, EventArgs ^e);
	void OnBtnTranslateToTextClick(Object ^sender, EventArgs ^e);

	void OnCBoxTranslationLostFocus(Object ^sender, EventArgs ^e);

protected:

	!TranslatorWindow()
	{
	}
	~TranslatorWindow()
	{
		this->!TranslatorWindow();
	}

public:

	TranslatorWindow(Window ^form);

	virtual void Show() override;
	virtual void Hide() override;
};
#endif

#pragma endregion