/*
*	<cypher.cpp>
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
#include "namespaces.h"
#include "cypher.h"
#include "utils.h"
#include "stringtable.h"
#include "macros.h"
#include <gcroot.h>

extern gcroot<stringtable^> strtable;

int *Cypher::LengthStorage()
{
	static int length[0xFFFF];
	return length;
}
void Cypher::InitLengths(int length[])
{
	for (int i(0xFFFF); i--; length[i] = Translate((wchar_t)i)->Length);
}
void Cypher::ClearLengths(int length[])
{
	for (int i(0xFFFF); i--; length[i] = 0);
}
bool Cypher::IsEqual(String ^string1, String ^string2)
{
	Hashtable
		tempAlphaTable1,
		tempAlphaTable2;
	wchar_t
		separator1(0),
		separator2(0);
	unsigned short
		fixedLength1(0),
		fixedLength2(0);

	LoadFromString(string1, *(Hashtable^)nullptr, tempAlphaTable1, *(Hashtable^)nullptr, nullptr, separator1, fixedLength1);
	LoadFromString(string2, *(Hashtable^)nullptr, tempAlphaTable2, *(Hashtable^)nullptr, nullptr, separator2, fixedLength2);

	if (separator1 != separator2 || tempAlphaTable1.Count != tempAlphaTable2.Count)
		return false;

	IDictionaryEnumerator ^node(tempAlphaTable1.GetEnumerator());
	while (node->MoveNext())
		if (!(tempAlphaTable2.Contains(((DictionaryEntry^)(node->Current))->Key))
			&& tempAlphaTable1[((DictionaryEntry^)(node->Current))->Key] != tempAlphaTable2[((DictionaryEntry^)(node->Current))->Key])
			return false;

	return true;
}
void Cypher::Pair(wchar_t c, String ^s)
{
	translationTable[c] = s;
	alphaTable[s] = c;
	if (c != (wchar_t)'{' && c != (wchar_t)' ')
		translationFlag[c] = true;
}
bool Cypher::LoadFromString(String ^text, Hashtable %translationTable, Hashtable %alphaTable, Hashtable %translationFlag, int lengths[], wchar_t %separator, unsigned short %length)
{
	String ^str(String::Empty);
	short phase(0);
	bool lengthFixed(false);
	/*
	*	Look for the user-definition of the letter separator character
	*/
	for (int i(0); i < text->Length; ++i)
	{

		switch (phase)
		{
			case 0:
				if (text[i] == (wchar_t)'#')
					phase = 1;
				break;

			case 1:
				if (text[i] == (wchar_t)'\n')
					phase = 0;
				else
				{
					str += text[i];
					if (str == L"LETTER_SEPARATOR")
					{
						phase = 2;
						str = String::Empty;
					}
					else if (str == L"TRANSLATION_LENGTH")
					{
						lengthFixed = true;
						phase = 2;
						str = String::Empty;
					}
				}
				break;

			case 2:
				if (text[i] == (wchar_t)'=')
				{
					phase = (lengthFixed) ? 5 : 3;
				}
				else if (text[i] != (wchar_t)' ' && text[i] != (wchar_t)'\t')
					phase = 0;
				break;

			case 3:
				if (text[i] == (wchar_t)'\'')
					phase = 4;
				else if (text[i] != (wchar_t)' ' && text[i] != (wchar_t)'\t')
					phase = 0;
				break;

			case 4:
				if ((i + 1) < text->Length && text[i + 1] == (wchar_t)'\'')
					separator = text[i];
				phase = 0;
				break;

			case 5:
				if (text[i] == (wchar_t)' ' || text[i] == (wchar_t)'\t')
				{
					if ((i + 1) < text->Length && text[i + 1] != (wchar_t)' ' && text[i + 1] != (wchar_t)'\t' && text[i + 1] != (wchar_t)'\n')
						phase = 6;
				}
				else if (text[i] == (wchar_t)'\n')
					phase = 0;
				break;

			case 6:
				if (text[i] == (wchar_t)' ' || text[i] == (wchar_t)'\t' || text[i] == (wchar_t)'\n')
				{
					length = Convert::ToByte(str);
					str = String::Empty;
					phase = 0;
				}
				else
					str += text[i];
				break;
		}
	}

	if (separator == 0 && !lengthFixed)
		separator = LETTER_SEPARATOR;

	phase = 0;
	str = String::Empty;
	/*
	*	Load the translation data from the translation file
	*/
	wchar_t c(0);
	for (int i(0); i < text->Length; ++i)
	{
		switch (phase)
		{
			/*
			*	Phase 1: Look for the '@' marker
			*/
			case 0:
				if (text[i] == (wchar_t)'@')
					phase = 1;
				break;
			/*
			*	Phase 2: Save the character next to the '@' marker
			*/
			case 1:
				c = text[i];
				phase = 2;
				break;
			/*
			*	Phase 3: Save the translation string found inside the '{' and '}' delimiters
			*/
			case 2:
				if (text[i] == (wchar_t)'{')
					phase = 3;
				else if (text[i] == (wchar_t)'@')
					phase = 1;
				else if (!IsWhitespace(text[i]))
					phase = 0;
				break;

			case 3:
				if (text[i] == (wchar_t)'}')
				{
					if (%translationTable != nullptr)
						translationTable[c] = str;
					if (str != String::Empty)
					{
						alphaTable[str] = c;
						str = String::Empty;
					}
					c = 0;
					phase = 0;
				}
				else if (text[i] == separator)
				{
					MessageBox::Show(L"Separator Character '" + text[i] + L"' is also used as a translation character.", L"Translation File Error", MessageBoxButtons::OK);
					Cypher::Clear();
					return false;
				}
				else
				{
					str += text[i];
					if (%translationFlag != nullptr)
						translationFlag[text[i]] = true;
				}
				break;
		}
	}
	if (lengths != nullptr)
		InitLengths(lengths);
	return true;
}
wchar_t Cypher::LetterSeparator()
{
	return letterSeparator;
}
unsigned short Cypher::FixedLength()
{
	return fixedLength;
}
wchar_t Cypher::ToAlpha(String ^key)
{
	return (alphaTable.Contains(key)) ? (wchar_t)(alphaTable[key]) : (wchar_t)'\0';
}
String ^Cypher::Translate(wchar_t key)
{
	return (translationTable.Contains(key)) ? (String^)(translationTable[key]) : String::Empty;
}
bool Cypher::IsTranslationChar(wchar_t c)
{
	return (bool)(translationFlag.Contains(c));
}
void Cypher::Clear()
{
	alphaTable.Clear();
	translationTable.Clear();
	translationFlag.Clear();
	ClearLengths(LengthStorage());
	letterSeparator = 0;
	fixedLength = 0;
}
bool Cypher::LoadFromString(String ^text)
{
	Clear();
	return LoadFromString(text, translationTable, alphaTable, translationFlag, LengthStorage(), letterSeparator, fixedLength);
}
void Cypher::LoadInternal()
{
	Clear();
	letterSeparator = 31;
	for (int i(0xFFFF); --i; Pair((wchar_t)i, String::Empty + (wchar_t)((i - 0xA0 > 0) ? (i - 0xA0) : (0xFFFF - 0x9F + i))));
}
int Cypher::GetTranslationLength(wchar_t c)
{
	return LengthStorage()[c];
}
String ^Cypher::ReadAllText(String ^text)
{
	String
		^output(String::Empty),
		^letter(String::Empty);
	wchar_t alpha;

	if (fixedLength)
	{
		unsigned short length(0);
		for (int i(0); i < text->Length; ++i)
		{
			letter += text[i];
			if (++length == fixedLength || text[i] == (wchar_t)'\n')
			{
				if (letter != String::Empty)
				{
					alpha = ToAlpha(letter);
					if (alpha != (wchar_t)'\0')
						output += alpha;
				}
				if (text[i] == (wchar_t)'\n')
					output += ToAlpha(L"\n");
				letter = String::Empty;
				length = 0;
			}
		}
	}
	else
	{
		for (int i(0); i < text->Length; ++i)
		{
			if (!IsTranslationChar(text[i]) || text[i] == letterSeparator || text[i] == (wchar_t)'\n')
			{
				if (letter != String::Empty)
				{
					alpha = ToAlpha(letter);
					if (alpha != (wchar_t)'\0')
						output += alpha;
				}
				if (text[i] == (wchar_t)'\n')
					output += ToAlpha(L"\n");
				letter = String::Empty;
			}
			else
				letter += text[i];
		}
	}

	if (letter != String::Empty)
		output += ToAlpha(letter);

	return output;
}
String ^Cypher::TranslateAllText(String ^text)
{
	String
		^output(String::Empty),
		^s;

	for (int i(0); i < text->Length; ++i)
	{
		s = Cypher::Translate(text[i]);
		if (s != String::Empty)
		{
			if (output == String::Empty || output[output->Length - 1] == (wchar_t)'\n' || s == L"\n")
				output += (s == L"\n") ? L"\r\n" : s;
			else if (fixedLength)
				output += s;
			else
				(output += letterSeparator) += s;
		}
	}

	return output;
}
String ^Cypher::GetEqualTranslation(String ^string)
{
	String
		^archivePath(AppDomain::CurrentDomain->BaseDirectory + TRANSLATION_ARCHIVE_NAME + TRANSLATION_ARCHIVE_EXTENSION),
		^matchedString(String::Empty);

	if (File::Exists(archivePath))
	{
		ZipArchive ^archive(ZipFile::Open(archivePath, ZipArchiveMode::Read));
		for (int i(archive->Entries->Count - 1); i >= 0; --i)
			if (Path::GetExtension(archive->Entries[i]->FullName) == TRANSLATION_FILE_EXTENSION)
			{
				StreamReader ^sReader(gcnew StreamReader(archive->Entries[i]->Open()));
				if (IsEqual(string, sReader->ReadToEnd()))
				{
					sReader->Close();
					matchedString = Path::GetFileNameWithoutExtension(archive->Entries[i]->Name);
					break;
				}
				else
					sReader->Close();
			}
		archive->~ZipArchive();
	}
	return matchedString;
}