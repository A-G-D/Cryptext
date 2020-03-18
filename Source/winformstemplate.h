/*
*	<winformstemplate.h>
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

#ifndef _WINFORMSTEMPLATE_H_
#define _WINFORMSTEMPLATE_H_

using namespace System;
using namespace System::Collections;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace WinFormsTemplate
{

	ref class AppForm;

	public ref class AppPage abstract
	{
	protected:

		ArrayList ^controls;
		bool initialized;

		virtual ~AppPage();

		virtual void InitializeComponent() = 0;

		virtual void OnShow();
		virtual void OnHide();

	public:

		AppForm ^__appForm;

		AppPage();

		bool IsVisible();
		bool IsInitialized();
		bool Display();
		bool Display(bool suspendLayout);

		void Initialize();

		void PauseLayout();
		void ResumeLayout();
		void PerformLayout();

		void AddControl(Control ^control);
		void AddControl(...array<Control^> ^controls);

		ArrayList ^GetControls();
		AppForm ^GetForm();
	};

	public ref class AppForm : public Form
	{
	private:

		ArrayList ^pages;

	protected:

		virtual ~AppForm();

	public:

		AppPage ^__currentPage;

		AppForm();

		ArrayList ^GetPages();
		AppPage ^GetCurrentPage();

		void Add(AppPage ^page);
		void Add(...array<AppPage^> ^pages);
	};
}
#endif

#pragma endregion