/*
*	<userdefinitions.cpp>
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
#include "userdefinitions.h"
#include "namespaces.h"
#include "utils.h"

void UserDefined::GetProperties(Form ^form)
{
	if (File::Exists(L"Layout\\Window.txt"))
	{
		String
			^text(File::ReadAllText(L"Layout\\Window.txt")),
			^str(String::Empty);
		short
			phase(0),
			property;
		for (int i(0); i < text->Length; ++i)
		{
			switch (phase)
			{
				case 0:
					if (text[i] == (wchar_t)'[')
						phase = 1;
					break;

				case 1:
					if (text[i] == (wchar_t)'\n')
					{
						phase = 0;
						str = String::Empty;
					}
					else if (text[i] == (wchar_t)']')
					{
						phase = (str == L"Window") ? 2 : 0;
						str = String::Empty;
					}
					else
						str += text[i];
					break;

				case 2:
					if (text[i] == (wchar_t)'.')
						phase = 3;
					else if (text[i] == (wchar_t)'[')
						phase = 1;
					else if (!IsWhitespace(text[i]) && text[i] != (wchar_t)'\n' && text[i] != (wchar_t)'\r')
						phase = 0;
					break;

				case 3:
					if (text[i] == (wchar_t)'=')
					{
						if (str == L"BackColor")
						{
							phase = 4;
							property = 1;
						}
						else if (str == L"ForeColor")
						{
							phase = 4;
							property = 2;
						}
						else if (str == L"FontFamily")
						{
							phase = 4;
							property = 3;
						}
						else if (str == L"FontSize")
						{
							phase = 4;
							property = 4;
						}
						else if (str == L"FontStyle")
						{
							phase = 4;
							property = 5;
						}
						else if (str == L"Text")
						{
							phase = 4;
							property = 6;
						}
						else if (str == L"Icon")
						{
							phase = 4;
							property = 7;
						}
						else
							phase = 0;
						str = String::Empty;
					}
					else if (IsWhitespace(text[i]) || text[i] == (wchar_t)'\n' || text[i] == (wchar_t)'\r')
					{
						phase = 0;
						str = String::Empty;
					}
					else
						str += text[i];
					break;

				case 4:
					if (text[i] == (wchar_t)'\n' || text[i] == (wchar_t)'\r' || i == text->Length - 1)
					{
						if (i == text->Length - 1)
							str += text[i];

						if (str != String::Empty)
						{
							try
							{
								switch (property)
								{
									case 1:
										form->BackColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case 2:
										form->ForeColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case 3:
										form->Font = gcnew Font(str, form->Font->Size, form->Font->Style);
										break;
									case 4:
										form->Font = gcnew Font(form->Font->FontFamily, Single::Parse(str), form->Font->Style);
										break;
									case 5:
										if (String::Equals(str, L"regular", StringComparison::OrdinalIgnoreCase))
											form->Font = gcnew Font(form->Font, FontStyle::Regular);
										else if (String::Equals(str, L"bold", StringComparison::OrdinalIgnoreCase))
											form->Font = gcnew Font(form->Font, FontStyle::Bold);
										else if (String::Equals(str, L"italic", StringComparison::OrdinalIgnoreCase))
											form->Font = gcnew Font(form->Font, FontStyle::Italic);
										else if (String::Equals(str, L"underline", StringComparison::OrdinalIgnoreCase))
											form->Font = gcnew Font(form->Font, FontStyle::Underline);
										else if (String::Equals(str, L"strikeout", StringComparison::OrdinalIgnoreCase))
											form->Font = gcnew Font(form->Font, FontStyle::Strikeout);
										break;
									case 6:
										form->Text = str;
										break;
									case 7:
										form->Icon = gcnew Icon(str);
										break;
								}
							}
							catch (...)
							{
							}
						}
						phase = 2;
						str = String::Empty;
					}
					else
						str += text[i];
					break;
			}
		}
	}
}

void UserDefined::GetProperties(String ^fileName, ...array<Control^> ^controls)
{
	if (File::Exists(L"Layout\\" + fileName))
	{
		String
			^text(File::ReadAllText(L"Layout\\" + fileName)),
			^str(String::Empty);
		short
			phase(0),
			index,
			property;
		for (int i(0); i < text->Length; ++i)
		{
			switch (phase)
			{
				case 0:
					if (text[i] == (wchar_t)'[')
						phase = 1;
					break;

				case 1:
					if (text[i] == (wchar_t)'\n')
					{
						phase = 0;
						str = String::Empty;
					}
					else if (text[i] == (wchar_t)']')
					{
						index = -1;
						for (int j(0); j < controls->Length; ++j)
							if (str == controls[j]->Name)
							{
								index = j;
								break;
							}

						phase = (index > -1) ? 2 : 0;
						str = String::Empty;
					}
					else
						str += text[i];
					break;

				case 2:
					if (text[i] == (wchar_t)'.')
						phase = 3;
					else if (text[i] == (wchar_t)'[')
						phase = 1;
					else if (!IsWhitespace(text[i]) && text[i] != (wchar_t)'\n' && text[i] != (wchar_t)'\r')
						phase = 0;
					break;

				case 3:
					if (text[i] == (wchar_t)'=')
					{
						if (str == L"BackColor")
						{
							phase = 4;
							property = 1;
						}
						else if (str == L"ForeColor")
						{
							phase = 4;
							property = 2;
						}
						else if (str == L"FontFamily")
						{
							phase = 4;
							property = 3;
						}
						else if (str == L"FontSize")
						{
							phase = 4;
							property = 4;
						}
						else if (str == L"FontStyle")
						{
							phase = 4;
							property = 5;
						}
						else if (str == L"Text")
						{
							phase = 4;
							property = 6;
						}
						else
							phase = 0;
						str = String::Empty;
					}
					else if (IsWhitespace(text[i]) || text[i] == (wchar_t)'\n' || text[i] == (wchar_t)'\r')
					{
						phase = 0;
						str = String::Empty;
					}
					else
						str += text[i];
					break;

				case 4:
					if (text[i] == (wchar_t)'\n' || text[i] == (wchar_t)'\r' || i == text->Length - 1)
					{
						if (i == text->Length - 1)
							str += text[i];

						if (str != String::Empty)
						{
							try
							{
								switch (property)
								{
									case 1:
										controls[index]->BackColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case 2:
										controls[index]->ForeColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case 3:
										controls[index]->Font = gcnew Font(str, controls[index]->Font->Size, controls[index]->Font->Style);
										break;
									case 4:
										controls[index]->Font = gcnew Font(controls[index]->Font->FontFamily, Single::Parse(str), controls[index]->Font->Style);
										break;
									case 5:
										if (String::Equals(str, L"regular", StringComparison::OrdinalIgnoreCase))
											controls[index]->Font = gcnew Font(controls[index]->Font, FontStyle::Regular);
										else if (String::Equals(str, L"bold", StringComparison::OrdinalIgnoreCase))
											controls[index]->Font = gcnew Font(controls[index]->Font, FontStyle::Bold);
										else if (String::Equals(str, L"italic", StringComparison::OrdinalIgnoreCase))
											controls[index]->Font = gcnew Font(controls[index]->Font, FontStyle::Italic);
										else if (String::Equals(str, L"underline", StringComparison::OrdinalIgnoreCase))
											controls[index]->Font = gcnew Font(controls[index]->Font, FontStyle::Underline);
										else if (String::Equals(str, L"strikeout", StringComparison::OrdinalIgnoreCase))
											controls[index]->Font = gcnew Font(controls[index]->Font, FontStyle::Strikeout);
										break;
										break;
									case 6:
										controls[index]->Text = str;
										break;
								}
							}
							catch (...)
							{
							}
						}
						phase = 2;
						str = String::Empty;
					}
					else
						str += text[i];
					break;
			}
		}
	}
}