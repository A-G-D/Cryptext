/*
*	<apppage.cpp>
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

AppPage::AppPage()
	: initialized(false), controls(gcnew ArrayList)
{
}
AppPage::~AppPage()
{
}

void AppPage::Initialize()
{
	if (!initialized)
	{
		InitializeComponent();
		initialized = true;
	}
}

void AppPage::OnHide()
{
	PauseLayout();
	for (int i = controls->Count; i; static_cast<Control^>(controls[--i])->Hide());
	ResumeLayout();
}
void AppPage::OnShow()
{
	PauseLayout();
	for (int i = controls->Count; i; static_cast<Control^>(controls[--i])->Show());
	ResumeLayout();
}

bool AppPage::IsVisible()
{
	return GetForm()->GetCurrentPage() == this;
}
bool AppPage::IsInitialized()
{
	return initialized;
}

bool AppPage::Display()
{
	if (GetForm()->GetCurrentPage() == this)
		return false;
	if (GetForm()->GetCurrentPage() != nullptr)
		GetForm()->GetCurrentPage()->OnHide();
	OnShow();
	GetForm()->___p__currentPage = this;
	return true;
}

void AppPage::PauseLayout()
{
	GetForm()->SuspendLayout();
}
void AppPage::ResumeLayout()
{
	GetForm()->ResumeLayout(true);
}
void AppPage::PerformLayout()
{
	GetForm()->PerformLayout();
}

void AppPage::AddControl(Control ^control)
{
	controls->Add((Object^)(control));
}
void AppPage::AddControl(...array<Control^> ^controls)
{
	this->controls->AddRange(controls);
}

ArrayList ^AppPage::GetControls()
{
	return controls;
}
AppForm ^AppPage::GetForm()
{
	return ___p__appForm;
}