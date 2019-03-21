/*
*	<window.cpp>
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
#include "window.h"
#include "appform.h"
#include "namespaces.h"

void Window::Add(Control ^control)
{
	AppForm::Instance->Controls->Add(control);
}
void Window::Remove(Control ^control)
{
	AppForm::Instance->Controls->Remove(control);
}
void Window::PauseLayout()
{
	AppForm::Instance->SuspendLayout();
}
void Window::ResumeLayout()
{
	AppForm::Instance->ResumeLayout(true);
}
void Window::PerformLayout()
{
	AppForm::Instance->PerformLayout();
}