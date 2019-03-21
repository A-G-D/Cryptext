/*
*	<userdefinitions.h>
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

#ifndef _USERDEFINITIONS_H_
#define _USERDEFINITIONS_H_

#include "namespaces.h"

/*
*	For Reading User Definitions of Layout Attributes
*/
namespace UserDefined
{
	void GetProperties(Form^);
	void GetProperties(String^, ...array<Control^>^);
}
#endif

#pragma endregion