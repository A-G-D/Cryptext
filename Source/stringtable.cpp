/*
*	<stringtable.cpp>
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
#include <stdexcept>
#include "stringtable.h"
#include "namespaces.h"
#include "macros.h"

StringTable::StringTable(String ^path)
	: __table(gcnew List<String^>)
{
	if (File::Exists(path))
	{
		String
			^text(Encoding::Default->GetString(File::ReadAllBytes(path))),
			^temp;

		for (int i(0); i < text->Length; ++i)
			if (text[i] != (wchar_t)'\n' && text[i] != (wchar_t)'\r')
			{
				if (i + 1 == text->Length)
				{
					__table->Add(temp);
					temp = String::Empty;
				}
				else
					temp += text[i];
			}
			else if (text[i] == (wchar_t)'\n' && !(temp == String::Empty))
			{
				__table->Add(temp);
				temp = String::Empty;
			}
	}
}
StringTable::StringTable()
{
}
StringTable::~StringTable()
{
	this->!StringTable();
}
StringTable::!StringTable()
{
}

String ^StringTable::operator[](unsigned int i)
{
	if (i >= STRING_TABLE_SIZE)
		throw std::out_of_range("Index Out of Range");
	else if (i >= size())
		return String::Empty;
	return __table[i];
}
unsigned int StringTable::size()
{
	return __table->Count;
}