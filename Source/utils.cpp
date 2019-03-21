/*
*	<utils.cpp>
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
#include "namespaces.h"
#include "utils.h"
#include "stringtable.h"
#include "macros.h"
#include <gcroot.h>

extern gcroot<stringtable^> strtable;

/*
*	Utility Functions
*/
void CreateTextBox(TextBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, bool multiline)
{
	object = gcnew TextBox;
	object->Location = Drawing::Point(x, y);
	object->Name = name;
	object->Multiline = multiline;
	object->Size = Drawing::Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->ContextMenu = gcnew ContextMenu;
}
void CreateLabel(Label ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor)
{
	object = gcnew Label;
	object->AutoSize = true;
	object->Name = name;
	object->Location = Drawing::Point(x, y);
	object->Size = Drawing::Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->Text = label;
}
void CreateButton(Button ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onClickHandler)
{
	object = gcnew Button;
	object->UseVisualStyleBackColor = true;
	object->Name = name;
	object->Text = label;
	object->Location = Drawing::Point(x, y);
	object->Size = Drawing::Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->Click += onClickHandler;
}
void CreateComboBox(ComboBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onLostFocus)
{
	object = gcnew ComboBox;
	object->FormattingEnabled = true;
	object->Sorted = true;
	object->Name = name;
	object->Location = System::Drawing::Point(x, y);
	object->Size = System::Drawing::Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->LostFocus += onLostFocus;
	object->ContextMenu = gcnew ContextMenu;
}
bool IsWhitespace(wchar_t c)
{
	return c == (wchar_t)' ' || c == (wchar_t)'\t';
}

bool GetTextFiles(Collections::IList ^%list)
{
	if (Directory::Exists(TEXT_FILES_FOLDER_NAME))
	{
		int
			suffixLength(((String^)TEXT_FILE_EXTENSION)->Length),
			rootLength(((String^)TEXT_FILES_FOLDER_NAME)->Length);
		array<String^> ^%dirs(Directory::GetDirectories(TEXT_FILES_FOLDER_NAME));
		for (int i = 0; i < dirs->Length; ++i)
		{
			String ^foldername(dirs[i]->Substring(rootLength + 1));

			array<String^> ^%files(Directory::GetFiles(dirs[i]));
			for (int j = 0; j < files->Length; ++j)
			{
				String ^filename(files[j]->Substring(dirs[i]->Length + 1, files[j]->Length - dirs[i]->Length - (suffixLength + 1)));
				if (files[j]->EndsWith(TEXT_FILE_EXTENSION) && foldername->Equals(filename))
					list->Add(filename);
			}
		}
		return true;
	}
	return false;
}

bool GetTranslations(Collections::IList ^%list)
{
	if (Directory::Exists(TRANSLATION_FILES_FOLDER_NAME))
	{
		int suffixLength(((String^)TRANSLATION_FILE_EXTENSION)->Length),
			dirLength(((String^)TRANSLATION_FILES_FOLDER_NAME)->Length);
		array<String^> ^%files = Directory::GetFiles(TRANSLATION_FILES_FOLDER_NAME);
		for (int i = 0; i < files->Length; ++i)
			if (files[i]->EndsWith(TRANSLATION_FILE_EXTENSION))
				list->Add(files[i]->Substring(dirLength + 1, files[i]->Length - dirLength - (suffixLength + 1)));
		return true;
	}
	return false;
}