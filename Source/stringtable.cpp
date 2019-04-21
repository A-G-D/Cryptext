/*
*	<stringtable.cpp>
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
#include <stdexcept>
#include "stringtable.h"
#include "namespaces.h"
#include "macros.h"

using namespace std;

String ^stringtable::operator[](unsigned int i)
{
	if (i >= STRING_TABLE_SIZE)
		throw out_of_range("Index Out of Range");
	else if (i >= size())
		return String::Empty;
	return __table[i];
}
unsigned int stringtable::size()
{
	return __table->Count;
}

stringtable::stringtable()
{
}
stringtable::stringtable(String ^path)
	: __table(gcnew List<String^>)
{
	if (File::Exists(path))
	{
		String
			^text(File::ReadAllText(path)),
			^temp;

		for (int i(0); i < text->Length; ++i)
			if (text[i] != (wchar_t)'\n' && text[i] != (wchar_t)'\r')
				temp += text[i];
			else if (text[i] == (wchar_t)'\n' && !(temp == String::Empty))
			{
				__table->Add(temp);
				temp = String::Empty;
			}
	}
}
stringtable::~stringtable()
{
}