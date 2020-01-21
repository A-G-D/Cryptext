/*
*	<stringtable.h>
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

#ifndef _STRINGTABLE_H_
#define _STRINGTABLE_H_

#include "namespaces.h"

ref class stringtable
{
private:

	List<System::String^> ^__table;

	stringtable();

protected:

	~stringtable();

public:

	String ^operator[](unsigned int i);
	unsigned int size();

	stringtable(String ^path);
};
#endif

#pragma endregion