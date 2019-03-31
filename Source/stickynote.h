/*
*	<stickynote.h>
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

#ifndef __STICKYNOTE_H__
#define __STICKYNOTE_H__

#include "namespaces.h"
#include "window.h"

/*
*	StickyNote Class
*/
ref class StickyNote : public Window
{
private:

	TextBox ^textboxStickyNote;

	void OnEscKeyDown(Object ^sender, KeyEventArgs ^e);

protected:

	!StickyNote()
	{
	}
	~StickyNote()
	{
		this->!StickyNote();
	}

public:

	Window ^prevForm;

	StickyNote();

	virtual void Show() override;
	virtual void Hide() override;

	String ^GetText();
};
#endif

#pragma endregion