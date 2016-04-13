#pragma once


#include <opencv2\opencv.hpp>
#include <cstdio>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>

#include <opencv2\core\core.hpp>
#include <opencv2\highgui\highgui.hpp>
#include <iostream>

namespace Ass1 {
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace cv;

	/// <summary>
	/// Summary for GUI
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		Mat getOrgImage();
		void ApplyChanges();
		int getFilter();
		int getSettings();
		void createImages(int filter, int settings, int d0, int n);
		Mat CreateFourierImg(Mat org);
		Mat CreateFilterImg(Mat fourier, int filter, int settings, int d0, int n);
		Mat CreateFourierInverseImg(Mat filtered);
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	public: System::Windows::Forms::PictureBox^  pb_org;
	protected: 







	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::RadioButton^  rb_high;
	private: System::Windows::Forms::RadioButton^  rb_low;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::RadioButton^  rb_gau;
	private: System::Windows::Forms::RadioButton^  rb_butter;
	private: System::Windows::Forms::RadioButton^  rb_ideal;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  bt_filter;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  D0_max;
	private: System::Windows::Forms::Label^  D0_min;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TrackBar^  tb_d0;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::Label^  n_max;
	private: System::Windows::Forms::Label^  n_min;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::TrackBar^  tb_n;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pb_org = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->rb_high = (gcnew System::Windows::Forms::RadioButton());
			this->rb_low = (gcnew System::Windows::Forms::RadioButton());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->rb_gau = (gcnew System::Windows::Forms::RadioButton());
			this->rb_butter = (gcnew System::Windows::Forms::RadioButton());
			this->rb_ideal = (gcnew System::Windows::Forms::RadioButton());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->bt_filter = (gcnew System::Windows::Forms::Button());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->D0_max = (gcnew System::Windows::Forms::Label());
			this->D0_min = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->tb_d0 = (gcnew System::Windows::Forms::TrackBar());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->n_max = (gcnew System::Windows::Forms::Label());
			this->n_min = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->tb_n = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pb_org))->BeginInit();
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->panel3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tb_d0))->BeginInit();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tb_n))->BeginInit();
			this->SuspendLayout();
			// 
			// pb_org
			// 
			this->pb_org->ImageLocation = L"";
			this->pb_org->Location = System::Drawing::Point(26, 30);
			this->pb_org->Name = L"pb_org";
			this->pb_org->Size = System::Drawing::Size(130, 27);
			this->pb_org->TabIndex = 0;
			this->pb_org->TabStop = false;
			this->pb_org->Visible = false;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->rb_high);
			this->panel1->Controls->Add(this->rb_low);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Location = System::Drawing::Point(26, 30);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(196, 117);
			this->panel1->TabIndex = 8;
			// 
			// rb_high
			// 
			this->rb_high->AutoSize = true;
			this->rb_high->Location = System::Drawing::Point(7, 67);
			this->rb_high->Name = L"rb_high";
			this->rb_high->Size = System::Drawing::Size(72, 17);
			this->rb_high->TabIndex = 2;
			this->rb_high->TabStop = true;
			this->rb_high->Text = L"High pass";
			this->rb_high->UseVisualStyleBackColor = true;
			// 
			// rb_low
			// 
			this->rb_low->AutoSize = true;
			this->rb_low->Location = System::Drawing::Point(7, 32);
			this->rb_low->Name = L"rb_low";
			this->rb_low->Size = System::Drawing::Size(70, 17);
			this->rb_low->TabIndex = 1;
			this->rb_low->TabStop = true;
			this->rb_low->Text = L"Low pass";
			this->rb_low->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(4, 4);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(56, 13);
			this->label5->TabIndex = 0;
			this->label5->Text = L"Filter Type";
			// 
			// panel2
			// 
			this->panel2->Controls->Add(this->rb_gau);
			this->panel2->Controls->Add(this->rb_butter);
			this->panel2->Controls->Add(this->rb_ideal);
			this->panel2->Controls->Add(this->label6);
			this->panel2->Location = System::Drawing::Point(237, 30);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(196, 117);
			this->panel2->TabIndex = 9;
			// 
			// rb_gau
			// 
			this->rb_gau->AutoSize = true;
			this->rb_gau->Location = System::Drawing::Point(7, 95);
			this->rb_gau->Name = L"rb_gau";
			this->rb_gau->Size = System::Drawing::Size(69, 17);
			this->rb_gau->TabIndex = 3;
			this->rb_gau->TabStop = true;
			this->rb_gau->Text = L"Gaussian";
			this->rb_gau->UseVisualStyleBackColor = true;
			// 
			// rb_butter
			// 
			this->rb_butter->AutoSize = true;
			this->rb_butter->Location = System::Drawing::Point(7, 64);
			this->rb_butter->Name = L"rb_butter";
			this->rb_butter->Size = System::Drawing::Size(79, 17);
			this->rb_butter->TabIndex = 2;
			this->rb_butter->TabStop = true;
			this->rb_butter->Text = L"Butterworth";
			this->rb_butter->UseVisualStyleBackColor = true;
			// 
			// rb_ideal
			// 
			this->rb_ideal->AutoSize = true;
			this->rb_ideal->Checked = true;
			this->rb_ideal->Location = System::Drawing::Point(7, 29);
			this->rb_ideal->Name = L"rb_ideal";
			this->rb_ideal->Size = System::Drawing::Size(48, 17);
			this->rb_ideal->TabIndex = 1;
			this->rb_ideal->TabStop = true;
			this->rb_ideal->Text = L"Ideal";
			this->rb_ideal->UseVisualStyleBackColor = true;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(4, 4);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(45, 13);
			this->label6->TabIndex = 0;
			this->label6->Text = L"Settings";
			// 
			// bt_filter
			// 
			this->bt_filter->Location = System::Drawing::Point(709, 72);
			this->bt_filter->Name = L"bt_filter";
			this->bt_filter->Size = System::Drawing::Size(75, 23);
			this->bt_filter->TabIndex = 10;
			this->bt_filter->Text = L"Filter";
			this->bt_filter->UseVisualStyleBackColor = true;
			this->bt_filter->Click += gcnew System::EventHandler(this, &GUI::bt_filter_Click);
			// 
			// panel3
			// 
			this->panel3->Controls->Add(this->D0_max);
			this->panel3->Controls->Add(this->D0_min);
			this->panel3->Controls->Add(this->label8);
			this->panel3->Controls->Add(this->tb_d0);
			this->panel3->Location = System::Drawing::Point(455, 30);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(196, 49);
			this->panel3->TabIndex = 10;
			// 
			// D0_max
			// 
			this->D0_max->AutoSize = true;
			this->D0_max->Location = System::Drawing::Point(155, 32);
			this->D0_max->Name = L"D0_max";
			this->D0_max->Size = System::Drawing::Size(31, 13);
			this->D0_max->TabIndex = 5;
			this->D0_max->Text = L"1000";
			// 
			// D0_min
			// 
			this->D0_min->AutoSize = true;
			this->D0_min->Location = System::Drawing::Point(37, 32);
			this->D0_min->Name = L"D0_min";
			this->D0_min->Size = System::Drawing::Size(13, 13);
			this->D0_min->TabIndex = 4;
			this->D0_min->Text = L"0";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 6);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(24, 13);
			this->label8->TabIndex = 2;
			this->label8->Text = L"D0:";
			// 
			// tb_d0
			// 
			this->tb_d0->Location = System::Drawing::Point(40, 2);
			this->tb_d0->Name = L"tb_d0";
			this->tb_d0->Size = System::Drawing::Size(139, 45);
			this->tb_d0->TabIndex = 1;
			// 
			// panel4
			// 
			this->panel4->Controls->Add(this->n_max);
			this->panel4->Controls->Add(this->n_min);
			this->panel4->Controls->Add(this->label10);
			this->panel4->Controls->Add(this->tb_n);
			this->panel4->Location = System::Drawing::Point(455, 98);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(196, 49);
			this->panel4->TabIndex = 11;
			// 
			// n_max
			// 
			this->n_max->AutoSize = true;
			this->n_max->Location = System::Drawing::Point(155, 32);
			this->n_max->Name = L"n_max";
			this->n_max->Size = System::Drawing::Size(31, 13);
			this->n_max->TabIndex = 5;
			this->n_max->Text = L"1000";
			// 
			// n_min
			// 
			this->n_min->AutoSize = true;
			this->n_min->Location = System::Drawing::Point(37, 32);
			this->n_min->Name = L"n_min";
			this->n_min->Size = System::Drawing::Size(13, 13);
			this->n_min->TabIndex = 4;
			this->n_min->Text = L"0";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(3, 6);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(16, 13);
			this->label10->TabIndex = 2;
			this->label10->Text = L"n:";
			// 
			// tb_n
			// 
			this->tb_n->Location = System::Drawing::Point(40, 2);
			this->tb_n->Name = L"tb_n";
			this->tb_n->Size = System::Drawing::Size(139, 45);
			this->tb_n->TabIndex = 1;
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(816, 169);
			this->Controls->Add(this->panel4);
			this->Controls->Add(this->panel3);
			this->Controls->Add(this->bt_filter);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->pb_org);
			this->Name = L"GUI";
			this->Text = L"GUI";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pb_org))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tb_d0))->EndInit();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->tb_n))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void bt_filter_Click(System::Object^  sender, System::EventArgs^  e) {
				 ApplyChanges();
			 }
};
}
