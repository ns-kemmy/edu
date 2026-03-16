#pragma once
#include<chrono>
#include<thread>
#include "RKutta.h"
#include<iostream>
#include<fstream>

void RHS(double* y, double* vy, double dt)
{
	vy[0] = y[2];
	vy[1] = y[3];
	vy[2] = -y[0]-2*y[0]*y[1];
	vy[3] = y[1]*y[1]-y[1]-y[0]*y[0];
}

namespace Poincaremap {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		RKutta* rung;
		bool iter, isPot;
		double dt; int N;
		double* Y;
		double* VY;
		double* X;
		double* VX;
		double W, H;
		double k;
		double xx, yy;
		double energy;
		array<Point>^ shtrih;
		Graphics^ graph;
		BufferedGraphics^ buffg;
		BufferedGraphicsContext^ bgc;
		Pen^ pen;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;

	private: System::Windows::Forms::TextBox^ textBox4;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::ComboBox^ comboBox1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::GroupBox^ groupBox1;

	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Label^ label3;

	private: System::ComponentModel::IContainer^ components;

		   /// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// panel1
			// 
			this->panel1->BackColor = System::Drawing::SystemColors::Window;
			this->panel1->Location = System::Drawing::Point(485, 30);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(849, 757);
			this->panel1->TabIndex = 0;
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(173, 45);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(156, 31);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = L"0";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(173, 111);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(156, 31);
			this->textBox2->TabIndex = 1;
			this->textBox2->Text = L"0,1";
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(173, 174);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(156, 31);
			this->textBox4->TabIndex = 3;
			this->textBox4->Text = L"0,1";
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox4_TextChanged);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(77, 51);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 25);
			this->label1->TabIndex = 0;
			this->label1->Text = L"X";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(77, 117);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(27, 25);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Y";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(77, 180);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(53, 25);
			this->label4->TabIndex = 7;
			this->label4->Text = L"P_Y";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(77, 242);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(26, 25);
			this->label5->TabIndex = 8;
			this->label5->Text = L"E";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(48, 443);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(160, 42);
			this->button1->TabIndex = 0;
			this->button1->Text = L"START";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// checkBox1
			// 
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(241, 494);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(140, 29);
			this->checkBox1->TabIndex = 0;
			this->checkBox1->Text = L"Trajectory";
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox1_CheckedChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(48, 521);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(160, 42);
			this->button2->TabIndex = 11;
			this->button2->Text = L"STOP";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::SystemColors::Info;
			this->button3->Location = System::Drawing::Point(154, 320);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(160, 42);
			this->button3->TabIndex = 12;
			this->button3->Text = L"Initialization";
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"1/12", L"1/8", L"1/6" });
			this->comboBox1->Location = System::Drawing::Point(173, 234);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(156, 33);
			this->comboBox1->TabIndex = 0;
			this->comboBox1->Text = L"choose";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::comboBox1_SelectedIndexChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->comboBox1);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Controls->Add(this->textBox1);
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->textBox4);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Location = System::Drawing::Point(48, 30);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(378, 312);
			this->groupBox1->TabIndex = 1;
			this->groupBox1->TabStop = false;
			// 
			// checkBox2
			// 
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(241, 534);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(164, 29);
			this->checkBox2->TabIndex = 13;
			this->checkBox2->Text = L"Map {p_x, x}";
			this->checkBox2->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(241, 417);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(160, 42);
			this->button4->TabIndex = 14;
			this->button4->Text = L"Pot";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// checkBox3
			// 
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(241, 571);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(164, 29);
			this->checkBox3->TabIndex = 15;
			this->checkBox3->Text = L"Map {p_y, y}";
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &MyForm::checkBox3_CheckedChanged);
			// 
			// textBox3
			// 
			this->textBox3->BackColor = System::Drawing::SystemColors::Info;
			this->textBox3->Location = System::Drawing::Point(130, 636);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(156, 31);
			this->textBox3->TabIndex = 9;
			this->textBox3->Text = L"-";
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &MyForm::textBox3_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(57, 639);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(52, 25);
			this->label3->TabIndex = 9;
			this->label3->Text = L"P_X";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1374, 807);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->checkBox3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->checkBox2);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->checkBox1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->panel1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
private: System::Void label7_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
}
	   bool isWrote(TextBox ^text)
	   {
		   String ^str = Convert::ToString(text->Text);
		   if (!text->Text->Contains("0"))
		   {
			   if (String::IsNullOrEmpty(str))
			   {
				   MessageBox::Show("Не введены все параметры");
				   return false;
			   }
		   }

		   if (str->Contains("."))
		   {
			   MessageBox::Show("Параметры введены неверно");
			   return false;
		   }
		   return true;
	   }
	   bool Tic(double x, double y) //штрихи в цикл // убрала
	   {
		   Point tic = DrawPoint(x, y);
		   for (int i = 2; i < 6; i++)
		   {
			   if (abs(shtrih[i].X - tic.X) < 1e-2) 
			   { 
				   shtrih[i].X = 0; 
				   return true; 
			   } //=0 чтобы больше не сравнивалось
		   }
		   return false;
	   }

	   Point DrawPoint(double x, double y)//масштабирование точек
	   {
		   int X = W / 2 + W * x / k;
		   int Y = H / 2 - H * y / k;
		   return Point(X, Y);
	   }

	   void Axes() //главные оси и 0
	   {
		   double HW, HH;
		   HW = (W/2-7.5)/5;
		   HH = (H/2-7.5)/5;
		   double t;
		   pen = gcnew Pen(Color::Black);
		   graph->DrawLine(pen, 15, 15, 15, H - 15);
		   graph->DrawLine(pen, 15, H - 15, W - 15, H - 15);
		   //нули
		   graph->DrawLine(pen, int(W / 2), H - 15, int(W / 2), H - 22);
		   graph->DrawString("0", panel1->Font, Brushes::Black, W / 2 - 5, H - 35);

		   graph->DrawLine(pen, 15, int(H / 2), 22, int(H / 2));
		   graph->DrawString("0", panel1->Font, Brushes::Black, 25, H / 2 - 7);
		   

		   for (int i = 1; i < 5; i++)
		   {
			   // после половины
			   shtrih[i] = Point(W / 2 + i * HW, H / 2 + i * HH);
			   graph->DrawLine(pen, shtrih[i].X, H - 15, shtrih[i].X, H - 20);
			   graph->DrawLine(pen, 15, shtrih[i].Y, 20, shtrih[i].Y);
			   t = int(((shtrih[i].X - W / 2) / W * k) * 100);
			   t /= 100;
			   graph->DrawString(t.ToString(), panel1->Font, Brushes::Black, shtrih[i].X - 8, H - 35);
			   t = int(-((shtrih[i].Y - H / 2) / H * k) * 100);
			   t /= 100;
			   graph->DrawString(t.ToString(), panel1->Font, Brushes::Black, 25, shtrih[i].Y - 7);

			   // до половины
			   shtrih[i] = Point(W / 2 - i * HW, H / 2 - i * HH);
			   graph->DrawLine(pen, shtrih[i].X, H - 15, shtrih[i].X, H - 20);
			   graph->DrawLine(pen, 15, shtrih[i].Y, 20, shtrih[i].Y);
			   t = int(((shtrih[i].X - W / 2) / W * k) * 100);
			   t /= 100;
			   graph->DrawString(t.ToString(), panel1->Font, Brushes::Black, shtrih[i].X - 10, H - 35);
			   t = int(-((shtrih[i].Y - H / 2) / H * k) * 100);
			   t /= 100;
			   graph->DrawString(t.ToString(), panel1->Font, Brushes::Black, 25, shtrih[i].Y - 7);
			  
		   }
		   ///стрелочка сверху
		   graph->DrawLine(pen, 15, 15, 11, 19);
		   graph->DrawLine(pen, 15, 15, 19, 19);

		   //стрелочка снизу
		   graph->DrawLine(pen, int(W - 20), H - 20, W - 15, H - 15);
		   graph->DrawLine(pen, int(W - 20), H - 10, W - 15, H - 15);

	   }
	   void Pot() //отрисовка формы  траектории
	   {
		   if (isPot)
		   {
			   Brush^ pot = gcnew SolidBrush(Color::DarkViolet);
			   double* Xpot, * Ypot;
			   double yinit, yfin, ystep = 0.001;
			   int T = 0;
			   yinit = 0.0, yfin = 0.0;
			   Point XY;
			   std::ofstream fout("pot.txt");

			   if (energy < 0.01 && energy > 0.0001) //хорошо
			   {
				   yinit = -0.135, yfin = 0.15, T = int((yfin - yinit) / ystep);
			   }
			   if (energy <= 0.1 && energy >= 0.01) //хорошо
			   {
				   yinit = -0.4, yfin = 0.57, T = int((yfin - yinit) / ystep);
			   }
			   if (energy <= 0.12 && energy > 0.1) //хорошо
			   {
				   yinit = -0.53, yfin = 0.65, T = int((yfin - yinit) / ystep);
			   }
			   if (energy <= 0.145 && energy > 0.12)
			   {
				   yinit = -0.5, yfin = 0.78, T = int((yfin - yinit) / ystep);
			   }
			   if (energy <= 0.17 && energy > 0.145) //хорошо
			   {
				   yinit = -0.49, yfin = 1.0, T = int((yfin - yinit) / ystep);
			   }


			   Xpot = new double[T];
			   Ypot = new double[T];

			   for (int i = 0; i < T; i++)
			   {
				   Ypot[i] = yinit + i * 1e-3;
				   Xpot[i] = sqrt((energy + Ypot[i] * Ypot[i] * Ypot[i] / 3. - Ypot[i] * Ypot[i] / 2.) / (0.5 + Ypot[i]));
				   fout << Xpot[i] << "\t" << Ypot[i] << std::endl;
				   fout << -Xpot[i] << "\t" << Ypot[i] << std::endl;
			   }

			   for (int i = 0; i < T; i++)
			   {

				   XY = DrawPoint(Xpot[i], Ypot[i]);
				   if (checkUp(XY.X, XY.Y) && XY.X > 0 && XY.Y > 0) graph->FillEllipse(pot, XY.X, XY.Y, 2, 2);
				   XY = DrawPoint(-Xpot[i], Ypot[i]);
				   if (checkUp(XY.X, XY.Y) && XY.X > 0 && XY.Y > 0) graph->FillEllipse(pot, XY.X, XY.Y, 2, 2);

			   }

			   delete[]Ypot; delete[]Xpot;
		   }
	   }

	   bool checkUp(double xx, double yy) //проверка не вышли ли мы за пределы панели в рисовании
	   {
		   return abs(xx) < panel1->Width - 2 || abs(yy) < panel1->Height - 2;
	   }
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) 
{
	std::ofstream file("res.txt");
	double eps = 1e-3;
	//кнопка старт
	Brush^ p = gcnew SolidBrush(Color::Red);
	pen = gcnew Pen(Color::Black);
	Point xy;
	int a = 0;
	Point trick;
	double ortreat;
	if (checkBox1->Checked) //х и у
	{
		isPot = true;
		graph->DrawString("x", panel1->Font, Brushes::Black, W - 15, H - 30);
		graph->DrawString("y", panel1->Font, Brushes::Black, 25, 10);
		Axes();

		while(iter)
		{
		
			rung->Step();
			Application::DoEvents();
			xy = DrawPoint(rung->y0[0], rung->y0[1]);
			if (!checkUp(xy.X, xy.Y)) { MessageBox::Show("Точка за пределом графика"); break; }
			graph->FillEllipse(p, xy.X, xy.Y, 2, 2);
			//file << rung->y0[0] << "\t" << rung->y0[1] << std::endl;
		
			/*if (a < 5)
			{
				if (Tic(rung->y0[0], rung->y0[1]))
				{
					trick = DrawPoint(rung->y0[0], rung->y0[1]);
					ortreat = int(rung->y0[0]*100);
					graph->DrawString(ortreat.ToString(), panel1->Font, Brushes::Black, trick.X - 7, H - 35);
					trick = DrawPoint(-rung->y0[0], rung->y0[1]);
					graph->DrawString(( - ortreat).ToString(), panel1->Font, Brushes::Black, trick.X - 8, H - 35);
					a++;
				}
			}
			*/
			
			
			//std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
	if (checkBox3->Checked) //у и р_у
	{
		graph->DrawString("y", panel1->Font, Brushes::Black, W - 15, H - 30);
		graph->DrawString("P_y", panel1->Font, Brushes::Black, 25, 10);
		Axes();

		while (iter)
		{
			rung->Step();
			Application::DoEvents();
			xy = DrawPoint(rung->y0[1], rung->y0[3]);
			if (!checkUp(xy.X, xy.Y)) { MessageBox::Show("Точка за пределом графика"); break; }
			if (abs(rung->y1[0]) < eps && rung->y1[2]>0.0)
			{
				graph->FillEllipse(p, xy.X, xy.Y, 2, 2);
				//file << rung->y0[1] << "\t" << rung->y0[3] << std::endl;
			}
			//std::this_thread::sleep_for(std::chrono::microseconds(10));
		}
	}
		if (checkBox2->Checked) //х и р_х
		{
			graph->DrawString("x", panel1->Font, Brushes::Black, W - 15, H - 30);
			graph->DrawString("P_x", panel1->Font, Brushes::Black, 25, 10);
			Axes();

			while (iter)
			{
				rung->Step();
				Application::DoEvents();
				xy = DrawPoint(rung->y0[0], rung->y0[2]);
				if (!checkUp(xy.X, xy.Y)) { MessageBox::Show("Точка за пределом графика"); break; }
				//if (abs(rung->y1[1]) < eps) 
					graph->FillEllipse(p, xy.X, xy.Y, 2, 2);
					//file << rung->y0[0] << "\t" << rung->y0[2] << std::endl;
				//std::this_thread::sleep_for(std::chrono::microseconds(10));
			}
		}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	iter = false;
}
private: System::Void comboBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	//кнопка инициализации
	W = panel1->Width - 1;
	H = panel1->Height - 1;
	graph = panel1->CreateGraphics();
	graph->Clear(System::Drawing::SystemColors::Window);
	this->bgc = BufferedGraphicsManager::Current;
	this->bgc->MaximumBuffer = System::Drawing::Size(W + 1, H + 1);
	this->buffg = bgc->Allocate(graph, Rectangle(0, 0, W + 1, H + 1));
	this->buffg->Graphics->Clear(System::Drawing::SystemColors::Info);
	shtrih = gcnew array<Point>(11);
	N = 4;
	dt = 1e-3; 
	iter = false;
	X = new double[N];
	if (isWrote(textBox1)) X[0] = Convert::ToDouble(textBox1->Text);
	if (isWrote(textBox2)) X[1] = Convert::ToDouble(textBox2->Text);
	if (isWrote(textBox3)) X[3] = Convert::ToDouble(textBox4->Text);

	//Выбор пользователем энергии
	if (comboBox1->Text->Contains("."))
	{
		MessageBox::Show("Параметры введены неверно");
	}
	else if (comboBox1->Text->Contains("choose"))
	{
		MessageBox::Show("Не введены все параметры");
	}
	else 
	{
		int chooseE = comboBox1->SelectedIndex;
		if (chooseE == 0) { energy = 1. / 12; k = 1.5; }
		else if (chooseE == 1) { energy = 1. / 8; k = 2; }
		else if (chooseE == 2) { energy = 1. / 6; k = 3; }
		else { energy = Convert::ToDouble(comboBox1->Text); k = 3; }
	}

	rung = new RKutta(energy, N, dt, RHS);
	rung->setinit(X);
	iter = true;

	textBox3->Text = Convert::ToString(rung->y0[2]); /// выводим для пользователя значение импульса P_X
	/////всплывающее окошко для импульса P_X
	ToolTip^ tt = gcnew ToolTip();
	tt->SetToolTip(textBox3, "Проверьте допустимость значения");
	if (textBox3->Text->Contains("н")) 
	{ 
		MessageBox::Show("Некорректные входные данные"); 
		iter = false;
	}
	isPot = false;
}
private: System::Void checkedListBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
	Pot();
}
private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
}
};
}
