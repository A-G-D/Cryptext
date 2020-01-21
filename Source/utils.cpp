/*
*	<utils.cpp>
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
#include "utils.h"
#include "stringtable.h"
#include "macros.h"
#include <gcroot.h>

extern gcroot<StringTable^> strtable;

/*
*	Utility Functions
*/
void CreateTextBox(TextBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, bool multiline)
{
	object = gcnew TextBox;
	object->Name = name;
	object->Multiline = multiline;
	object->Location = Point(x, y);
	object->Size = Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->ContextMenu = gcnew ContextMenu;
}
void CreateLabel(Label ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor)
{
	object = gcnew Label;
	object->AutoSize = true;
	object->Name = name;
	object->Location = Point(x, y);
	object->Size = Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->Text = label;
}
void CreateLinkLabel(LinkLabel ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor, LinkLabelLinkClickedEventHandler ^onClickHandler)
{
	object = gcnew LinkLabel;
	object->AutoSize = true;
	object->Name = name;
	object->Text = label;
	object->Location = Point(x, y);
	object->Size = Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->LinkBehavior = LinkBehavior::AlwaysUnderline;
	object->LinkClicked += onClickHandler;
}
void CreateButton(Button ^%object, String ^name, String ^label, int x, int y, int width, int height, int tabIndex, AnchorType anchor, EventHandler ^onClickHandler)
{
	object = gcnew Button;
	object->UseVisualStyleBackColor = true;
	object->Name = name;
	object->Text = label;
	object->Location = Point(x, y);
	object->Size = Size(width, height);
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
	object->Location = Point(x, y);
	object->Size = Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->LostFocus += onLostFocus;
	object->ContextMenu = gcnew ContextMenu;
}
void CreateCheckBox(CheckBox ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, Appearance look, bool autoCheck, EventHandler ^onCheckStateChanged)
{
	object = gcnew CheckBox;
	object->Name = name;
	object->Location = Point(x, y);
	object->Size = Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
	object->Appearance = look;
	object->AutoCheck = autoCheck;
	object->CheckStateChanged += onCheckStateChanged;
}
void CreatePanel(Panel ^%object, String ^name, int x, int y, int width, int height, int tabIndex, AnchorType anchor, bool autoScroll)
{
	object = gcnew Panel;
	object->AutoScroll = autoScroll;
	object->Name = name;
	object->BorderStyle = BorderStyle::FixedSingle;
	object->Location = Point(x, y);
	object->Size = Size(width, height);
	object->Anchor = (AnchorStyles)anchor;
	object->TabIndex = tabIndex;
}

bool IsWhitespace(wchar_t c)
{
	return c == (wchar_t)' ' || c == (wchar_t)'\t';
}

bool GetTextFiles(Collections::IList ^%list)
{
	String ^directoryPath(AppDomain::CurrentDomain->BaseDirectory + L"\\" + TEXT_FILES_FOLDER_NAME);
	if (Directory::Exists(directoryPath))
	{
		int rootLength(directoryPath->Length);
		array<String^> ^dirs(Directory::GetDirectories(directoryPath));
		for (int i = 0; i < dirs->Length; ++i)
		{
			String ^foldername(dirs[i]->Substring(rootLength + 1));

			array<String^> ^files(Directory::GetFiles(dirs[i]));
			for (int j = 0; j < files->Length; ++j)
			{
				String ^fileName(Path::GetFileNameWithoutExtension(files[j]));
				if (files[j]->EndsWith(TEXT_FILE_EXTENSION) && foldername->Equals(fileName))
					list->Add(fileName);
			}
		}
		return true;
	}
	return false;
}

bool GetTranslations(Collections::IList ^%list)
{
	String ^archivePath(AppDomain::CurrentDomain->BaseDirectory + TRANSLATION_ARCHIVE_NAME + TRANSLATION_ARCHIVE_EXTENSION);
	if (File::Exists(archivePath))
	{
		ZipArchive ^archive(ZipFile::Open(archivePath, ZipArchiveMode::Update));
		for (int i(archive->Entries->Count - 1); i >= 0; --i)
			if (Path::GetExtension(archive->Entries[i]->FullName) == TRANSLATION_FILE_EXTENSION)
				list->Add(Path::GetFileNameWithoutExtension(archive->Entries[i]->FullName));
		archive->~ZipArchive();
		return true;
	}
	return false;
}

String ^ReadTranslationFile(String ^entryName)
{
	ZipArchive ^archive(ZipFile::Open(AppDomain::CurrentDomain->BaseDirectory + TRANSLATION_ARCHIVE_NAME + TRANSLATION_ARCHIVE_EXTENSION, ZipArchiveMode::Read));
	StreamReader ^sReader(gcnew StreamReader(archive->GetEntry(entryName)->Open()));
	String ^text(sReader->ReadToEnd());
	sReader->Close();
	archive->~ZipArchive();
	return text;
}