/*
*	<macros.h>
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

#ifndef _MACROS_H_
#define _MACROS_H_

#include "stringtable.h"

#define APPLICATION_NAME						L"Cryptext"
#define TEXT_FILES_FOLDER_NAME					L"Texts"
#define TEXT_FILE_EXTENSION						L".txt"
#define TRANSLATION_FILES_FOLDER_NAME			L"Translations"
#define TRANSLATION_FILE_EXTENSION				L".trln"
#define KEY_FILE_EXTENSION						L".ckey"
#define TRANSLATION_FILE_MISSING_ERROR			gcnew System::String(static_cast<stringtable^>(strtable)[0])
#define MESSAGE_CREATE_FILE_SUCCESS				gcnew System::String(static_cast<stringtable^>(strtable)[1])
#define MESSAGE_CREATE_FILE_FAILURE				gcnew System::String(static_cast<stringtable^>(strtable)[2])
#define MESSAGE_CREATE_TRANSLATION_SUCCESS		gcnew System::String(static_cast<stringtable^>(strtable)[3])
#define MESSAGE_CREATE_TRANSLATION_FAILURE		gcnew System::String(static_cast<stringtable^>(strtable)[4])
#define CAPTION_CREATE_FILE_SUCCESS				gcnew System::String(static_cast<stringtable^>(strtable)[5])
#define CAPTION_CREATE_FILE_FAILURE				gcnew System::String(static_cast<stringtable^>(strtable)[6])
#define CAPTION_CREATE_TRANSLATION_SUCCESS		gcnew System::String(static_cast<stringtable^>(strtable)[7])
#define CAPTION_CREATE_TRANSLATION_FAILURE		gcnew System::String(static_cast<stringtable^>(strtable)[8])
#define MESSAGE_MISSING_KEY_ERROR				gcnew System::String(static_cast<stringtable^>(strtable)[9])
#define CAPTION_MISSING_KEY_ERROR				gcnew System::String(static_cast<stringtable^>(strtable)[10])
#define ERROR_TITLE								gcnew System::String(static_cast<stringtable^>(strtable)[11])
#define STRING_TABLE_SIZE						12
#define BUTTON_HEIGHT							28
#define BUTTON_WIDTH							75

#define LETTER_SEPARATOR						' '

#endif

#pragma endregion