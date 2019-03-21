/*
*	<main.cpp>
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
#include "macros.h"
#include "appform.h"
#include "stringtable.h"
#include <gcroot.h>

using namespace System;
using namespace System::Threading;
using namespace System::Windows::Forms;

bool ADVANCED_FLAG = false;

gcroot<stringtable^> strtable(gcnew stringtable(L"Resources\\stringtable"));

[STAThread]
void Main(array<String^> ^args)
{
	Mutex ^mutex(gcnew Mutex(false, APPLICATION_NAME + L".exe"));

	if (mutex->WaitOne(0, false))
	{
		bool styled(true);

		for (int i(0); i < args->Length; ++i)
		{
			if (args[i] == L"-basicstyle")
				styled = false;
			else if (args[i] == L"-load" && i < args->Length - 1)
			{
				if (File::Exists(args[++i]))
					AppForm::defaultLoadFile = args[i];
			}
			else if (args[i] == L"-advanced")
			{
				// To be continued =======>
			}
		}
		if (styled)
		{
			Application::EnableVisualStyles();
			Application::SetCompatibleTextRenderingDefault(false);
		}
		Application::Run(gcnew AppForm);
	}
	else
		MessageBox::Show(L"Instance Already Running!", L"Error", MessageBoxButtons::OK, MessageBoxIcon::Hand);
}