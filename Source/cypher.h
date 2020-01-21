/*
*	<cypher.h>
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

#ifndef _CYPHER_H_
#define _CYPHER_H_

#include "namespaces.h"

ref class Cypher
{
private:

	static Hashtable
		alphaTable,
		translationTable,
		translationFlag;

	static wchar_t letterSeparator = 0;
	static unsigned short fixedLength = 0;

	Cypher()
	{
	}

	static int *LengthStorage();

	static void InitLengths(int length[]);
	static void ClearLengths(int length[]);

	static bool IsEqual(String ^string1, String ^string2);

	static void Pair(wchar_t c, String ^s);

	static bool LoadFromString(String ^text, Hashtable %translationTable, Hashtable %alphaTable, Hashtable %translationFlag, int lengths[], wchar_t %separator, unsigned short %length);

public:

	static wchar_t LetterSeparator();
	static unsigned short FixedLength();

	static wchar_t ToAlpha(String ^key);
	static String ^Translate(wchar_t key);

	static bool IsTranslationChar(wchar_t c);

	static void Clear();

	static bool LoadFromString(String ^text);

	static void LoadInternal();

	static int GetTranslationLength(wchar_t c);

	static String ^ReadAllText(String ^text);

	static String ^TranslateAllText(String ^text);

	static String ^GetEqualTranslation(String ^string);
};
#endif

#pragma endregion