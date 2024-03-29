#pragma once
#include "HookMaster.h"
#include "ScreenshotMaker.h"
#include "PressKeyForm.h"
#include <string>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>

namespace ScreenSaver 
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
		}

		property int ScreenButton
		{
			int get()
			{
				return this->screenButtonCode;
			}
		}

	protected:
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void WndProc(Message% m) override
		{
			switch (m.Msg)
			{
			case HookMaster::HOOKMASTER_SHOW_HIDE_CODE:
			{
				isVisible ? this->HideWindow() : this->ShowWindow();
				break;
			}
			
			case HookMaster::HOOKMASTER_MAKE_SCREENSHOT:
			{
				ScreenshotMaker maker;
				String ^pathManaged = screenFolderPath;
				if (!isSaverActive)
					return;
				std::string pathUnmanaged = msclr::interop::marshal_as<std::string>(pathManaged);
				maker.saveAsPng(maker.takeScreen(), pathUnmanaged);
				break;
			}

			case HookMaster::HOOKMASTER_NEW_SCREEN_KEY:
			{
				this->screenButtonCode = m.LParam.ToInt32();
				this->Enabled = true;
				this->BringToFront();
				SetScreenButtonLabel();
				break;
			}

			default:
				Form::WndProc(m);
			}
			return;
		}

	private: 
		const int WINDOW_WIDTH = 534;
		const int WINDOW_HEIGHT = 129;
		const String ^ WINDOW_TITLE = L"Screen Saver v1.0";
		const String ^ TEXTBOX_DEFAULT_PATH = L"Empty :(";
		const String ^ TEXTBOX_STATUS_ENABLED = L"Enabled";
		const String ^ TEXTBOX_STATUS_DISABLED = L"Disabled";
		const int NO_BUTTON = -1;

		System::Windows::Forms::Button^   buttonChangePath;
		System::Windows::Forms::TextBox^  textBoxPath;
		System::Windows::Forms::Button^   buttonChangeSaverStatus;
		System::Windows::Forms::Label^    labelCurrentSaverStatus;
		System::Windows::Forms::Label^    labelScreenKey;
		System::Windows::Forms::Label^    labelScreenKeyValue;
		System::Windows::Forms::Button^   buttonNewScreenKey;
		System::Windows::Forms::Label^    labelMinimizeOrShow;
		System::Windows::Forms::Label^    labelStatusValue;
		
		bool isVisible = true;
		bool isSaverActive = true;
		int screenButtonCode = NO_BUTTON;
		HHOOK keyboardHook;
		String ^screenFolderPath = (String ^) TEXTBOX_DEFAULT_PATH;
		System::ComponentModel::Container ^components;

		void HideWindow()
		{
			isVisible = false;
			this->Hide();
		}

		void ShowWindow()
		{
			isVisible = true;
			this->Show();
		}

		void SetScreenButtonLabel()
		{
			if (screenButtonCode == NO_BUTTON)
			{
				this->labelScreenKeyValue->Text = "-";
			}
			else
			{
				Keys key = (Keys)screenButtonCode;
				this->labelScreenKeyValue->Text = key.ToString();
			}
		}

		void SetSaverStatusLabel()
		{
			this->labelStatusValue->Text = (isSaverActive) ? (String ^)TEXTBOX_STATUS_ENABLED : (String ^)TEXTBOX_STATUS_DISABLED;
		}

		void SetTextBoxPath()
		{
			this->textBoxPath->Text = screenFolderPath;
		}

		void InitializeComponent(void)
		{
			this->MaximizeBox = false;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PressKeyForm::typeid));
			HWND k = static_cast<HWND>(Handle.ToPointer());
			HookMaster *master = HookMaster::createInstance(static_cast<HWND>(Handle.ToPointer()));
			master->setupHook();
			this->buttonChangePath = (gcnew System::Windows::Forms::Button());
			this->textBoxPath = (gcnew System::Windows::Forms::TextBox());
			this->buttonChangeSaverStatus = (gcnew System::Windows::Forms::Button());
			this->labelCurrentSaverStatus = (gcnew System::Windows::Forms::Label());
			this->labelScreenKey = (gcnew System::Windows::Forms::Label());
			this->labelScreenKeyValue = (gcnew System::Windows::Forms::Label());
			this->buttonNewScreenKey = (gcnew System::Windows::Forms::Button());
			this->labelMinimizeOrShow = (gcnew System::Windows::Forms::Label());
			this->labelStatusValue = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			// 
			// buttonChangePath
			// 
			this->buttonChangePath->Location = System::Drawing::Point(440, 20);
			this->buttonChangePath->Name = L"buttonChangePath";
			this->buttonChangePath->Size = System::Drawing::Size(75, 23);
			this->buttonChangePath->TabIndex = 0;
			this->buttonChangePath->Text = L"Set path";
			this->buttonChangePath->UseVisualStyleBackColor = true;
			this->buttonChangePath->Click += gcnew EventHandler(this, &MainWindow::ButtonChangePathClicked);
			// 
			// textBoxPath
			// 
			this->textBoxPath->Location = System::Drawing::Point(28, 22);
			this->textBoxPath->Name = L"textBoxPath";
			this->textBoxPath->Size = System::Drawing::Size(380, 20);
			this->textBoxPath->TabIndex = 1;
			this->SetTextBoxPath();
			// 
			// buttonChangeSaverStatus
			// 
			this->buttonChangeSaverStatus->Location = System::Drawing::Point(140, 72);
			this->buttonChangeSaverStatus->Name = L"buttonChangeSaverStatus";
			this->buttonChangeSaverStatus->Size = System::Drawing::Size(75, 23);
			this->buttonChangeSaverStatus->TabIndex = 2;
			this->buttonChangeSaverStatus->Text = L"Change";
			this->buttonChangeSaverStatus->UseVisualStyleBackColor = true;
			this->buttonChangeSaverStatus->Click += gcnew EventHandler(this, &MainWindow::ButtonChangeStatusClicked);
			// 
			// labelCurrentSaverStatus
			// 
			this->labelCurrentSaverStatus->AutoSize = true;
			this->labelCurrentSaverStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
												   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelCurrentSaverStatus->Location = System::Drawing::Point(25, 74);
			this->labelCurrentSaverStatus->Name = L"labelCurrentSaverStatus";
			this->labelCurrentSaverStatus->Size = System::Drawing::Size(52, 17);
			this->labelCurrentSaverStatus->TabIndex = 3;
			this->labelCurrentSaverStatus->Text = L"Status:";
			// 
			// labelScreenKey
			// 
			this->labelScreenKey->AutoSize = true;
			this->labelScreenKey->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelScreenKey->Location = System::Drawing::Point(280, 76);
			this->labelScreenKey->Name = L"labelScreenKey";
			this->labelScreenKey->Size = System::Drawing::Size(83, 17);
			this->labelScreenKey->TabIndex = 5;
			this->labelScreenKey->Text = L"Screen key:";
			// 
			// labelScreenKeyValue
			// 
			this->labelScreenKeyValue->AutoSize = true;
			this->labelScreenKeyValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular,
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->labelScreenKeyValue->Location = System::Drawing::Point(360, 76);
			this->labelScreenKeyValue->Name = L"labelScreenKeyValue";
			this->labelScreenKeyValue->Size = System::Drawing::Size(32, 17);
			this->labelScreenKeyValue->TabIndex = 6;
			this->SetScreenButtonLabel();
			// 
			// buttonNewScreenKey
			// 
			this->buttonNewScreenKey->Location = System::Drawing::Point(440, 74);
			this->buttonNewScreenKey->Name = L"buttonNewScreenKey";
			this->buttonNewScreenKey->Size = System::Drawing::Size(75, 23);
			this->buttonNewScreenKey->TabIndex = 7;
			this->buttonNewScreenKey->Text = L"New key";
			this->buttonNewScreenKey->UseVisualStyleBackColor = true;
			this->buttonNewScreenKey->Click += gcnew EventHandler(this, &MainWindow::ButtonSetNewKeyClicked);
			// 
			// labelMinimizeOrShow
			// 
			this->labelMinimizeOrShow->AutoSize = true;
			this->labelMinimizeOrShow->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelMinimizeOrShow->Location = System::Drawing::Point(25, 105);
			this->labelMinimizeOrShow->Name = L"labelMinimizeOrShow";
			this->labelMinimizeOrShow->Size = System::Drawing::Size(168, 15);
			this->labelMinimizeOrShow->TabIndex = 8;
			this->labelMinimizeOrShow->Text = L"Hide/Show: Alt + WIN + PrtScr";
			// 
			// labelStatusValue
			// 
			this->labelStatusValue->AutoSize = true;
			this->labelStatusValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->labelStatusValue->Location = System::Drawing::Point(77, 74);
			this->labelStatusValue->Name = L"labelStatusValue";
			this->labelStatusValue->Size = System::Drawing::Size(46, 17);
			this->labelStatusValue->TabIndex = 9;
			SetSaverStatusLabel();
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(WINDOW_WIDTH, WINDOW_HEIGHT);
			this->Controls->Add(this->labelStatusValue);
			this->Controls->Add(this->labelMinimizeOrShow);
			this->Controls->Add(this->buttonNewScreenKey);
			this->Controls->Add(this->labelScreenKeyValue);
			this->Controls->Add(this->labelScreenKey);
			this->Controls->Add(this->labelCurrentSaverStatus);
			this->Controls->Add(this->buttonChangeSaverStatus);
			this->Controls->Add(this->textBoxPath);
			this->Controls->Add(this->buttonChangePath);
			this->Name = (String ^)WINDOW_TITLE;
			this->Text = (String ^)WINDOW_TITLE;
			this->ResumeLayout(false);
			this->PerformLayout();
		}

		void ButtonSetNewKeyClicked(System::Object^  sender, EventArgs^ e)
		{
			PressKeyForm::OpenForm();
			this->Enabled = false;
		}

		void ButtonChangeStatusClicked(System::Object^  sender, EventArgs^ e)
		{
			isSaverActive = !isSaverActive;
			SetSaverStatusLabel();
		}

		void ButtonChangePathClicked(System::Object^  sender, EventArgs^ e)
		{
			FolderBrowserDialog ^dialog = gcnew FolderBrowserDialog();
			if (dialog->ShowDialog() == System::Windows::Forms::DialogResult::OK)
			{
				this->screenFolderPath = dialog->SelectedPath;
				this->SetTextBoxPath();
			}
		}
	};
}
