/*
*	<userdefinitions.cpp>
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
#include "userdefinitions.h"
#include "namespaces.h"
#include "macros.h"
#include "utils.h"

enum Property
{
	BackColor = 1,
	ForeColor,
	FontFamily,
	FontSize,
	FontStyle,
	Icon,
	Text,
	BackImage,
	BackImageLayout,
	BorderStyle,
	Height,
	Width,
	Left,
	Top,
	Anchor
};

Image ^ResizeImage(Image ^image, unsigned short width, unsigned short height)
{
	Bitmap ^bmp(gcnew Bitmap(width, height));
	Graphics ^graphic(Graphics::FromImage(bmp));
	graphic->DrawImage(image, 0, 0, width, height);
	return (Image^)bmp;
}

bool UserDefined::GetProperties(Form ^form)
{
	String ^filePath(AppDomain::CurrentDomain->BaseDirectory + LAYOUT_FOLDER_NAME + L"\\Window.txt");
	if (File::Exists(filePath))
	{
		String
			^text(File::ReadAllText(filePath)),
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
							property = Property::BackColor;
						}
						else if (str == L"ForeColor")
						{
							phase = 4;
							property = Property::ForeColor;
						}
						else if (str == L"FontFamily")
						{
							phase = 4;
							property = Property::FontFamily;
						}
						else if (str == L"FontSize")
						{
							phase = 4;
							property = Property::FontSize;
						}
						else if (str == L"FontStyle")
						{
							phase = 4;
							property = Property::FontStyle;
						}
						else if (str == L"Text")
						{
							phase = 4;
							property = Property::Text;
						}
						else if (str == L"Icon")
						{
							phase = 4;
							property = Property::Icon;
						}
						else if (str == L"BackImage")
						{
							phase = 4;
							property = Property::BackImage;
						}
						else if (str == L"BackImageLayout")
						{
							phase = 4;
							property = Property::BackImageLayout;
						}
						else if (str == L"BorderStyle")
						{
							phase = 4;
							property = Property::BorderStyle;
						}
						else if (str == L"Height")
						{
							phase = 4;
							property = Property::Height;
						}
						else if (str == L"Width")
						{
							phase = 4;
							property = Property::Width;
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
									case Property::BackColor:
										form->BackColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case Property::ForeColor:
										form->ForeColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case Property::FontSize:
										form->Font = gcnew Font(str, form->Font->Size, form->Font->Style);
										break;
									case Property::FontFamily:
										form->Font = gcnew Font(form->Font->FontFamily, Single::Parse(str), form->Font->Style);
										break;
									case Property::FontStyle:
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
									case Property::Text:
										form->Text = str;
										break;
									case Property::Icon:
										form->Icon = gcnew Drawing::Icon((Path::IsPathRooted(str)) ? str : AppDomain::CurrentDomain->BaseDirectory + L"\\" + str);
										break;
									case Property::BackImage:
										form->BackgroundImage = ResizeImage(Image::FromFile((Path::IsPathRooted(str)) ? str : AppDomain::CurrentDomain->BaseDirectory + L"\\" + str), BACKGROUND_IMAGE_WIDTH, BACKGROUND_IMAGE_HEIGHT);
										break;
									case Property::BackImageLayout:
										if (String::Equals(str, L"center", StringComparison::OrdinalIgnoreCase))
											form->BackgroundImageLayout = ImageLayout::Center;
										else if (String::Equals(str, L"none", StringComparison::OrdinalIgnoreCase))
											form->BackgroundImageLayout = ImageLayout::None;
										else if (String::Equals(str, L"stretch", StringComparison::OrdinalIgnoreCase))
											form->BackgroundImageLayout = ImageLayout::Stretch;
										else if (String::Equals(str, L"tile", StringComparison::OrdinalIgnoreCase))
											form->BackgroundImageLayout = ImageLayout::Tile;
										else if (String::Equals(str, L"zoom", StringComparison::OrdinalIgnoreCase))
											form->BackgroundImageLayout = ImageLayout::Zoom;
										break;
									case Property::BorderStyle:
										if (String::Equals(str, L"fixed3d", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::Fixed3D;
										else if (String::Equals(str, L"fixeddialog", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::FixedDialog;
										else if (String::Equals(str, L"fixedsingle", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::FixedSingle;
										else if (String::Equals(str, L"fixedtoolwindow", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::FixedToolWindow;
										else if (String::Equals(str, L"none", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::None;
										else if (String::Equals(str, L"sizable", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::Sizable;
										else if (String::Equals(str, L"sizabletoolwindow", StringComparison::OrdinalIgnoreCase))
											form->FormBorderStyle = FormBorderStyle::SizableToolWindow;
										break;
									case Property::Height:
										form->Height = Convert::ToInt32(str);
										break;
									case Property::Width:
										form->Width = Convert::ToInt32(str);
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
		return true;
	}
	return false;
}

bool UserDefined::GetProperties(String ^fileName, ...array<Control^> ^controls)
{
	String ^filePath(AppDomain::CurrentDomain->BaseDirectory + LAYOUT_FOLDER_NAME + L"\\" + fileName);
	if (File::Exists(filePath))
	{
		String
			^text(File::ReadAllText(filePath)),
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
							property = Property::BackColor;
						}
						else if (str == L"ForeColor")
						{
							phase = 4;
							property = Property::ForeColor;
						}
						else if (str == L"FontFamily")
						{
							phase = 4;
							property = Property::FontFamily;
						}
						else if (str == L"FontSize")
						{
							phase = 4;
							property = Property::FontSize;
						}
						else if (str == L"FontStyle")
						{
							phase = 4;
							property = Property::FontStyle;
						}
						else if (str == L"Text")
						{
							phase = 4;
							property = Property::Text;
						}
						else if (str == L"Height")
						{
							phase = 4;
							property = Property::Height;
						}
						else if (str == L"Width")
						{
							phase = 4;
							property = Property::Width;
						}
						else if (str == L"Left")
						{
							phase = 4;
							property = Property::Left;
						}
						else if (str == L"Top")
						{
							phase = 4;
							property = Property::Top;
						}
						else if (str == L"Anchor")
						{
							phase = 4;
							property = Property::Anchor;
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
									case Property::BackColor:
										controls[index]->BackColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case Property::ForeColor:
										controls[index]->ForeColor = Color::FromArgb(Convert::ToInt32(str, 16));
										break;
									case Property::FontFamily:
										controls[index]->Font = gcnew Font(str, controls[index]->Font->Size, controls[index]->Font->Style);
										break;
									case Property::FontSize:
										controls[index]->Font = gcnew Font(controls[index]->Font->FontFamily, Single::Parse(str), controls[index]->Font->Style);
										break;
									case Property::FontStyle:
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
									case Property::Text:
										controls[index]->Text = str->Replace(L"&&", L"&")->Replace(L"\\n", L"\r\n");
										break;
									case Property::Height:
										controls[index]->Height = Convert::ToInt32(str);
										break;
									case Property::Width:
										controls[index]->Width = Convert::ToInt32(str);
										break;
									case Property::Left:
										controls[index]->Left = Convert::ToInt32(str);
										break;
									case Property::Top:
										controls[index]->Top = Convert::ToInt32(str);
										break;
									case Property::Anchor:
										if (String::Equals(str, L"bottom", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::BOTTOM;
										else if (String::Equals(str, L"bottomleft", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::BOTTOM_LEFT;
										else if (String::Equals(str, L"bottomright", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::BOTTOM_RIGHT;
										else if (String::Equals(str, L"center", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::CENTER;
										else if (String::Equals(str, L"centerbottom", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::CENTER_BOTTOM;
										else if (String::Equals(str, L"centertop", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::CENTER_TOP;
										else if (String::Equals(str, L"left", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::LEFT;
										else if (String::Equals(str, L"right", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::RIGHT;
										else if (String::Equals(str, L"top", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::TOP;
										else if (String::Equals(str, L"topleft", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::TOP_LEFT;
										else if (String::Equals(str, L"topright", StringComparison::OrdinalIgnoreCase))
											controls[index]->Anchor = (AnchorStyles)AnchorType::TOP_RIGHT;
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
		return true;
	}
	return false;
}