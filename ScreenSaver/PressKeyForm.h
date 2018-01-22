#pragma once
namespace ScreenSaver {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class PressKeyForm : public System::Windows::Forms::Form
	{
	public:
		static property bool IsWaiting
		{
			bool get()
			{
				return instance->isWaiting;
			}
		}

		static void CloseForm()
		{
			if (!instance)
				return;
			instance->Close();
			instance->isWaiting = false;
		}

		static void OpenForm()
		{
			instance = gcnew PressKeyForm();
			instance->Show();
			instance->isWaiting = true;
		}

	protected:
		~PressKeyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: 
		System::Windows::Forms::Label^  pressKeyLabel;
		System::ComponentModel::Container ^components;
		static PressKeyForm ^instance;
		bool isWaiting = false;

		PressKeyForm(void)
		{
			InitializeComponent();
			isWaiting = true;
		}

		void InitializeComponent(void)
		{
			this->ControlBox = false;
			this->MaximizeBox = false;
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(PressKeyForm::typeid));
			this->pressKeyLabel = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			// 
			// pressKeyLabel
			// 
			this->pressKeyLabel->AutoSize = true;
			this->pressKeyLabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->pressKeyLabel->Location = System::Drawing::Point(18, 28);
			this->pressKeyLabel->Name = L"pressKeyLabel";
			this->pressKeyLabel->Size = System::Drawing::Size(242, 20);
			this->pressKeyLabel->TabIndex = 0;
			this->pressKeyLabel->Text = L"Press any key . . . . . . . . . . . . . . . . .";
			// 
			// PressKeyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(273, 80);
			this->Controls->Add(this->pressKeyLabel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Name = L"PressKeyForm";
			this->Text = L"Press Key";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	};
}
