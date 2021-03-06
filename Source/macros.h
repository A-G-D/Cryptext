/*
*	<macros.h>
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

#ifndef _MACROS_H_
#define _MACROS_H_

#include "stringtable.h"
#include "namespaces.h"

#define APPLICATION_NAME						L"Cryptext"
#define VERSION									L"1.4.2"
#define YEAR									L"2020"
#define AUTHOR_NAME								L"Aloever Dulay"
#define AUTHOR_PSEUDONYM						L"AGD"

#define TEXT_FILES_FOLDER_NAME					L"Texts"
#define TRANSLATION_ARCHIVE_NAME				L"Translations"
#define LAYOUT_FOLDER_NAME						L"Layout"
#define RESOURCES_FOLDER_NAME					L"Resources"
#define STRING_TABLE_FILE_NAME					L"stringtable"
#define TEXT_FILE_EXTENSION						L".txt"
#define TRANSLATION_FILE_EXTENSION				L".trln"
#define TRANSLATION_ARCHIVE_EXTENSION			L".czip"
#define KEY_FILE_EXTENSION						L".ckey"
#define STICKY_NOTE_FILE_NAME					L"__note__"
#define LICENSE_FILE_NAME						L"LICENSE.txt"
#define LICENSE_TEXT_FONT_FAMILY				L"Courier New"
#define LICENSE_LINK_TEXT						L"https://www.gnu.org/licenses/gpl-3.0.html/"
#define LICENSE_LINK_URL						L"https://www.gnu.org/licenses/gpl-3.0.html"
#define SOURCE_LINK_TEXT						L"https://github.com/A-G-D/Cryptext/"
#define SOURCE_LINK_URL							L"https://github.com/A-G-D/Cryptext/"

#define MESSAGE_CREATE_FILE_SUCCESS				gcnew String(((StringTable^)(strtable))[0])
#define CAPTION_CREATE_FILE_SUCCESS				gcnew String(((StringTable^)(strtable))[1])
#define MESSAGE_CREATE_FILE_FAILURE				gcnew String(((StringTable^)(strtable))[2])
#define CAPTION_CREATE_FILE_FAILURE				gcnew String(((StringTable^)(strtable))[3])
#define MESSAGE_CREATE_TRANSLATION_SUCCESS		gcnew String(((StringTable^)(strtable))[4])
#define CAPTION_CREATE_TRANSLATION_SUCCESS		gcnew String(((StringTable^)(strtable))[5])
#define MESSAGE_CREATE_TRANSLATION_FAILURE		gcnew String(((StringTable^)(strtable))[6])
#define CAPTION_CREATE_TRANSLATION_FAILURE		gcnew String(((StringTable^)(strtable))[7])
#define MESSAGE_MISSING_KEY_ERROR				gcnew String(((StringTable^)(strtable))[8])
#define CAPTION_MISSING_KEY_ERROR				gcnew String(((StringTable^)(strtable))[9])
#define MESSAGE_MISSING_LICENSE_ERROR			gcnew String(((StringTable^)(strtable))[10])
#define CAPTION_MISSING_LICENSE_ERROR			gcnew String(((StringTable^)(strtable))[11])
#define MESSAGE_FILE_DELETE_CONFIRM				gcnew String(((StringTable^)(strtable))[12])
#define CAPTION_FILE_DELETE_CONFIRM				gcnew String(((StringTable^)(strtable))[13])
#define ABOUT_TEXT								gcnew String(((StringTable^)(strtable))[14])


#define STRING_TABLE_SIZE						15
#define BUTTON_HEIGHT							28
#define BUTTON_WIDTH							75
#define BACKGROUND_IMAGE_HEIGHT					200
#define BACKGROUND_IMAGE_WIDTH					175

#endif

#pragma endregion