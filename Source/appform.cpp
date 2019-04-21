/*
*	<appform.cpp>
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
#include "winformstemplate.h"

using namespace WinFormsTemplate;

AppForm::AppForm()
	: pages(gcnew ArrayList), ___p__currentPage(nullptr)
{
	SetStyle(ControlStyles::SupportsTransparentBackColor, true);
}
AppForm::~AppForm()
{
}

ArrayList ^AppForm::GetPages()
{
	return pages;
}
AppPage ^AppForm::GetCurrentPage()
{
	return ___p__currentPage;
}

void AppForm::Add(AppPage ^page)
{
	page->___p__appForm = this;
	page->Initialize();
	Controls->AddRange(static_cast<array<Control^>^>(page->GetControls()->ToArray()));
	pages->Add(page);
}
void AppForm::Add(...array<AppPage^> ^pages)
{
	for (int i(pages->Length); i; Add(pages[--i]));
}