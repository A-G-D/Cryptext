/*
*	<stickynote.h>
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

#ifndef __STICKYNOTE_H__
#define __STICKYNOTE_H__

#include "namespaces.h"
#include "winformstemplate.h"

/*
*	StickyNote Class
*/
ref class StickyNote : public WinFormsTemplate::AppPage
{
private:

	TextBox ^textboxStickyNote;

	void OnEscKeyDown(Object ^sender, KeyEventArgs ^e);

protected:

	!StickyNote();
	~StickyNote();

	virtual void InitializeComponent() override;

public:

	WinFormsTemplate::AppPage ^prevForm;

	StickyNote();

	virtual void OnShow() override;

	String ^GetText();
	void WriteText(String ^text);
};
#endif

#pragma endregion