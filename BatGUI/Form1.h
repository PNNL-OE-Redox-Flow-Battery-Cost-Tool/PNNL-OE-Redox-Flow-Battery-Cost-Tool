/*
PNNL Cost-Performance Tool (DOE-OE sponsored) for Estimation of Capital Costs for Redox Flow Batteries.
Battelle IPID 30401.
Copyright © 2013, Battelle Memorial Institute
All rights reserved.

                                                                                             .://:                      
                                                                                         .////:                         
                                                                                      :/##/.                            
                                                                                   /##/:                                
                                                                                /###/                                   
                                                                             /###/.                                     
                                                                         //###:                                         
                               ##/.                                 ://####/                                            
                               /####/.                          :/##//###:                                              
                                  :####/               .:://####/:/###/.                                                
                                  /########////#///###/:./###/   /##:                                                   
                                        ./#/./###///////###    /##:                                                     
                                         /####:     .###....:###.                                                       
                                        ./   /#/  /##/     ###/.                                                        
                                               ####.     /##/                                                           
                                              ##//#    /##/                                                             
                                              :   .#::###                                                               
                                                   .###.                                                                
                                                   ##//                                                                 
                                                       /                                                                
                                                             
    ____  ___   __________________________
   / __ \/   | / ____/  _/ ____/  _/ ____/
  / /_/ / /| |/ /    / // /_   / // /     
 / ____/ ___ / /____/ // __/ _/ // /___   
/_/   /_/  |_\____/___/_/   /___/\____/   
                                          
    _   ______  ____  ________  ___       ___________________
   / | / / __ \/ __ \/_  __/ / / / |     / / ____/ ___/_  __/
  /  |/ / / / / /_/ / / / / /_/ /| | /| / / __/  \__ \ / /   
 / /|  / /_/ / _, _/ / / / __  / | |/ |/ / /___ ___/ // /    
/_/ |_/\____/_/ |_| /_/ /_/ /_/  |__/|__/_____//____//_/     
                                                             
    _   _____  ______________  _   _____    __ 
   / | / /   |/_  __/  _/ __ \/ | / /   |  / / 
  /  |/ / /| | / /  / // / / /  |/ / /| | / /  
 / /|  / ___ |/ / _/ // /_/ / /|  / ___ |/ /___
/_/ |_/_/  |_/_/ /___/\____/_/ |_/_/  |_/_____/
                                               
    __    ___    ____  ____  ____  ___  __________  ______  __
   / /   /   |  / __ )/ __ \/ __ \/   |/_  __/ __ \/ __ \ \/ /
  / /   / /| | / __  / / / / /_/ / /| | / / / / / / /_/ /\  / 
 / /___/ ___ |/ /_/ / /_/ / _, _/ ___ |/ / / /_/ / _, _/ / /  
/_____/_/  |_/_____/\____/_/ |_/_/  |_/_/  \____/_/ |_| /_/                                       
*/

/*PNNL has developed an interactive tool to estimate the capital cost for PNNL 
all vanadium Gen 1, Gen2, and iron-vanadium chemistries. This tool has also been 
adapted for organic electrolyte redox flow batteries. The Gen 2 all vanadium 
system incorporates the PNNL-developed electrolyte with high concentration and 
wide operating temperature range. The tool allows determination of the most 
cost-effective chemistries and the optimum operating conditions for power or 
energy intensive applications, providing a strategy for a redox flow battery 
management system (BMS). 

This tool was developed with funding from The U. S. Department of Energy, 
Office of Electricity Delivery and Energy Reliability/Energy Storage Program, 
under the leadership of Dr. Imre Gyuk.*/




#pragma once
#define NOMINMAX
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <msclr\marshal_cppstd.h>
#include <iostream>
#include <fstream>
#include "exprtk.hpp"

using namespace std; //goes to access standard C++ functions
namespace BatGUI {//rest of program included within this bracket

	using namespace System;//for Windows system only
	using namespace System::ComponentModel;//sub-directory under System
	using namespace System::Collections;//sub-directory under System
	using namespace System::Collections::Generic;//sub-directory under Collections
	using namespace System::Windows::Forms;//sub-directory under System
	using namespace System::Data;//sub-directory under System
	using namespace System::Drawing;//sub-directory under System
	using namespace System::Data::OleDb;//sub-directory under System
	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form//Form1 is public access, everything after bracket below is Form1
	{
	public: static List<DataGridView^>^ ProcessList = gcnew List<DataGridView^>();//DataGridView means Table; ProcessList is list of tables pertaining to Processes
	public: static List<DataGridView^>^ VariableList = gcnew List<DataGridView^>();// VariableList is list of tables pertaining to Variables
	public: static List<TextBox^>^ UnitsList = gcnew List<TextBox^>();// list of text boxes - in this case for list of units/cell
	private: System::Windows::Forms::OpenFileDialog^  openProcess;//screen that appears when you look for a file is OpenFileDIalog; OpenProcess is specific OPenFileDialog for opening process files
	public: //full program has access to public; only parts of program have access to private
	private: System::Windows::Forms::SaveFileDialog^  saveProcess;//save is counterpart of Open
	private: System::Windows::Forms::TabPage^  tabPage5;//Lets us know there will be a tab called tabpage5
	private: System::Windows::Forms::DataGridView^  CostParameters;//This is one table - neither belongs to Process nor Variable list
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column22;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column23;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column24;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column25;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column26;
	private: System::Windows::Forms::TabPage^  tabPage3;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  costChart;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::DataGridView^  dataOutput;



















	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Label^  label81;//label is inert text to define each textbox; there will be a label called label 81
	private: System::Windows::Forms::TextBox^  electronBox;//look under forms directory for Textbox^ and make text box called electronBox; there will be a textbox called electronBox
	private: System::Windows::Forms::TextBox^  LiVoltageBox;
	private: System::Windows::Forms::TextBox^  flowCapBox;
	private: System::Windows::Forms::TextBox^  channelSepBox;
	private: System::Windows::Forms::TextBox^  aspectRatioBox;
	private: System::Windows::Forms::TextBox^  FOWBox;
	private: System::Windows::Forms::TextBox^  FOHBox;
	private: System::Windows::Forms::TextBox^  MOBox;
	private: System::Windows::Forms::TextBox^  ThRedBox;
	private: System::Windows::Forms::TextBox^  PBox;
	private: System::Windows::Forms::TextBox^  KBox;
	private: System::Windows::Forms::TextBox^  ThicknessBox;
	private: System::Windows::Forms::TextBox^  CondBox;
	private: System::Windows::Forms::Label^  label51;
	private: System::Windows::Forms::Label^  label90;
	private: System::Windows::Forms::Label^  label89;
	private: System::Windows::Forms::CheckBox^  interdigBox;
	private: System::Windows::Forms::Label^  label84;
	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  textasf;
	private: System::Windows::Forms::Panel^  panel6;//Initializing panel 6 in GUI
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  flowBox;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::RadioButton^  SplineButton;
	private: System::Windows::Forms::RadioButton^  ECModelButton;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::RadioButton^  constcurrent;
	private: System::Windows::Forms::RadioButton^  constpower;
	private: System::Windows::Forms::DataGridView^  bestTable;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column19;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column17;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column18;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column20;
	private: System::Windows::Forms::Panel^  panel3;
	private: System::Windows::Forms::Label^  label68;
	private: System::Windows::Forms::Label^  label67;
	private: System::Windows::Forms::TextBox^  stackBox;
	private: System::Windows::Forms::TextBox^  cellBox;
	private: System::Windows::Forms::Label^  label11;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  energyBox;
	private: System::Windows::Forms::TextBox^  epBox;
	private: System::Windows::Forms::TextBox^  powerBox;
	private: System::Windows::Forms::ProgressBar^  progressBar;
	private: System::Windows::Forms::Button^  calculate;//there will be a button called calculate
	private: System::Windows::Forms::Panel^  panel2;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::Label^  label13;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::NumericUpDown^  DODBox;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  jHighBox;
	private: System::Windows::Forms::NumericUpDown^  jLowBox;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::RadioButton^  LiOrgButton;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::RadioButton^  VVGen2;
	private: System::Windows::Forms::RadioButton^  VVGen1;
	private: System::Windows::Forms::RadioButton^  FeV;
	private: System::Windows::Forms::TabControl^  tabControl1;
private: System::Windows::Forms::Label^  label22;
private: System::Windows::Forms::TextBox^  LiConcBox;
private: System::Windows::Forms::Label^  label23;
private: System::Windows::Forms::TextBox^  spaBox;
private: System::Windows::Forms::DataGridView^  OutputGrid;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column27;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column28;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column29;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column10;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column11;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column12;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column13;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column15;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column16;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column14;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column21;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Digits;
private: System::Windows::Forms::TabPage^  tabPage4;
private: System::Windows::Forms::Button^  button1;
private: System::Windows::Forms::TextBox^  testBox;
private: System::Windows::Forms::TextBox^  testFlow;
private: System::Windows::Forms::TextBox^  testCurrent;
private: System::Windows::Forms::Label^  label26;
private: System::Windows::Forms::Label^  label25;
private: System::Windows::Forms::Label^  label24;
private: System::Windows::Forms::TextBox^  testPowerOrig;
private: System::Windows::Forms::TextBox^  testPowerNew;
private: System::Windows::Forms::Label^  label27;
private: System::Windows::Forms::Label^  label28;
private: System::Windows::Forms::Label^  label29;
private: System::Windows::Forms::TextBox^  testVEff;
private: System::Windows::Forms::DataGridView^  testGrid;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column32;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Power;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column30;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column31;





	public: static int c = 0;
	public:
		Form1(void)
		{
			InitializeComponent();//user defined function takes all the pieces of GUI that have been defined and assigns location and/or text values
			InitializeCostParameters();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ToolTip^  toolTip1;
	private: System::Data::DataSet^  dataSet1;
private: System::Data::DataTable^  dataTable1;
private: System::Data::DataSet^  dataSet2;
private: System::Data::DataTable^  dataTable2;
private: System::Data::DataColumn^  dataColumn1;
private: System::Data::DataColumn^  dataColumn2;
private: System::Data::DataColumn^  dataColumn3;
private: System::Windows::Forms::BindingSource^  bindingSource1;
private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	private: System::ComponentModel::IContainer^  components;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::Windows::Forms::DataVisualization::Charting::Title^  title2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->bindingSource1 = (gcnew System::Windows::Forms::BindingSource(this->components));
			this->dataSet2 = (gcnew System::Data::DataSet());
			this->dataTable2 = (gcnew System::Data::DataTable());
			this->dataColumn1 = (gcnew System::Data::DataColumn());
			this->dataColumn2 = (gcnew System::Data::DataColumn());
			this->dataColumn3 = (gcnew System::Data::DataColumn());
			this->dataSet1 = (gcnew System::Data::DataSet());
			this->dataTable1 = (gcnew System::Data::DataTable());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->openProcess = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveProcess = (gcnew System::Windows::Forms::SaveFileDialog());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->CostParameters = (gcnew System::Windows::Forms::DataGridView());
			this->Column22 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column23 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column24 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column25 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column26 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->costChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->dataOutput = (gcnew System::Windows::Forms::DataGridView());
			this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column6 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column7 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column8 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column9 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column10 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column11 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column12 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column13 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column15 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column16 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column14 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column21 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Digits = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->OutputGrid = (gcnew System::Windows::Forms::DataGridView());
			this->Column27 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column28 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column29 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->spaBox = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->LiConcBox = (gcnew System::Windows::Forms::TextBox());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->electronBox = (gcnew System::Windows::Forms::TextBox());
			this->LiVoltageBox = (gcnew System::Windows::Forms::TextBox());
			this->flowCapBox = (gcnew System::Windows::Forms::TextBox());
			this->channelSepBox = (gcnew System::Windows::Forms::TextBox());
			this->aspectRatioBox = (gcnew System::Windows::Forms::TextBox());
			this->FOWBox = (gcnew System::Windows::Forms::TextBox());
			this->FOHBox = (gcnew System::Windows::Forms::TextBox());
			this->MOBox = (gcnew System::Windows::Forms::TextBox());
			this->ThRedBox = (gcnew System::Windows::Forms::TextBox());
			this->PBox = (gcnew System::Windows::Forms::TextBox());
			this->KBox = (gcnew System::Windows::Forms::TextBox());
			this->ThicknessBox = (gcnew System::Windows::Forms::TextBox());
			this->CondBox = (gcnew System::Windows::Forms::TextBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label90 = (gcnew System::Windows::Forms::Label());
			this->label89 = (gcnew System::Windows::Forms::Label());
			this->interdigBox = (gcnew System::Windows::Forms::CheckBox());
			this->label84 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textasf = (gcnew System::Windows::Forms::Label());
			this->panel6 = (gcnew System::Windows::Forms::Panel());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->flowBox = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->SplineButton = (gcnew System::Windows::Forms::RadioButton());
			this->ECModelButton = (gcnew System::Windows::Forms::RadioButton());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->constcurrent = (gcnew System::Windows::Forms::RadioButton());
			this->constpower = (gcnew System::Windows::Forms::RadioButton());
			this->bestTable = (gcnew System::Windows::Forms::DataGridView());
			this->Column19 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column17 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column18 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column20 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->panel3 = (gcnew System::Windows::Forms::Panel());
			this->label68 = (gcnew System::Windows::Forms::Label());
			this->label67 = (gcnew System::Windows::Forms::Label());
			this->stackBox = (gcnew System::Windows::Forms::TextBox());
			this->cellBox = (gcnew System::Windows::Forms::TextBox());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->energyBox = (gcnew System::Windows::Forms::TextBox());
			this->epBox = (gcnew System::Windows::Forms::TextBox());
			this->powerBox = (gcnew System::Windows::Forms::TextBox());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->calculate = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->DODBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->jHighBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->jLowBox = (gcnew System::Windows::Forms::NumericUpDown());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->LiOrgButton = (gcnew System::Windows::Forms::RadioButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->VVGen2 = (gcnew System::Windows::Forms::RadioButton());
			this->VVGen1 = (gcnew System::Windows::Forms::RadioButton());
			this->FeV = (gcnew System::Windows::Forms::RadioButton());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->testGrid = (gcnew System::Windows::Forms::DataGridView());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->testVEff = (gcnew System::Windows::Forms::TextBox());
			this->testPowerOrig = (gcnew System::Windows::Forms::TextBox());
			this->testPowerNew = (gcnew System::Windows::Forms::TextBox());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->testFlow = (gcnew System::Windows::Forms::TextBox());
			this->testCurrent = (gcnew System::Windows::Forms::TextBox());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->testBox = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column30 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column31 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column32 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Power = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingSource1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataTable2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataTable1))->BeginInit();
			this->tabPage5->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CostParameters))->BeginInit();
			this->tabPage3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->costChart))->BeginInit();
			this->tabPage2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataOutput))->BeginInit();
			this->tabPage1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->OutputGrid))->BeginInit();
			this->panel6->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bestTable))->BeginInit();
			this->panel3->SuspendLayout();
			this->panel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DODBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->jHighBox))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->jLowBox))->BeginInit();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabPage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->testGrid))->BeginInit();
			this->SuspendLayout();
			// 
			// dataSet2
			// 
			this->dataSet2->DataSetName = L"NewDataSet";
			this->dataSet2->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) {this->dataTable2});
			// 
			// dataTable2
			// 
			this->dataTable2->Columns->AddRange(gcnew cli::array< System::Data::DataColumn^  >(3) {this->dataColumn1, this->dataColumn2, 
				this->dataColumn3});
			cli::array< System::String^ >^ __mcTemp__1 = gcnew cli::array< System::String^  >(1) {L"Component"};
			this->dataTable2->Constraints->AddRange(gcnew cli::array< System::Data::Constraint^  >(1) {(gcnew System::Data::UniqueConstraint(L"Constraint1", 
				__mcTemp__1, true))});
			this->dataTable2->PrimaryKey = gcnew cli::array< System::Data::DataColumn^  >(1) {this->dataColumn1};
			this->dataTable2->TableName = L"Table1";
			// 
			// dataColumn1
			// 
			this->dataColumn1->AllowDBNull = false;
			this->dataColumn1->ColumnName = L"Component";
			// 
			// dataColumn2
			// 
			this->dataColumn2->ColumnName = L"Value";
			this->dataColumn2->DataType = System::Double::typeid;
			// 
			// dataColumn3
			// 
			this->dataColumn3->ColumnName = L"Unit";
			// 
			// dataSet1
			// 
			this->dataSet1->DataSetName = L"NewDataSet";
			this->dataSet1->Tables->AddRange(gcnew cli::array< System::Data::DataTable^  >(1) {this->dataTable1});
			// 
			// dataTable1
			// 
			this->dataTable1->TableName = L"Table1";
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->Filter = L"CSV Files|*.csv";
			this->openFileDialog1->InitialDirectory = L"\\";
			// 
			// openProcess
			// 
			this->openProcess->Filter = L"DAT Files|*.dat";
			// 
			// saveProcess
			// 
			this->saveProcess->Filter = L"DAT Files|*.dat";
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->CostParameters);
			this->tabPage5->Location = System::Drawing::Point(4, 22);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(886, 746);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"Cost Parameters";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// CostParameters
			// 
			this->CostParameters->AllowUserToAddRows = false;
			this->CostParameters->AllowUserToDeleteRows = false;
			this->CostParameters->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::AllCells;
			this->CostParameters->AutoSizeRowsMode = System::Windows::Forms::DataGridViewAutoSizeRowsMode::AllCells;
			this->CostParameters->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->CostParameters->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->Column22, 
				this->Column23, this->Column24, this->Column25, this->Column26});
			this->CostParameters->Location = System::Drawing::Point(6, 0);
			this->CostParameters->Name = L"CostParameters";
			this->CostParameters->Size = System::Drawing::Size(768, 450);
			this->CostParameters->TabIndex = 0;
			// 
			// Column22
			// 
			this->Column22->HeaderText = L"Component";
			this->Column22->Name = L"Column22";
			this->Column22->Width = 86;
			// 
			// Column23
			// 
			this->Column23->HeaderText = L"Value (Present)";
			this->Column23->Name = L"Column23";
			this->Column23->Width = 96;
			// 
			// Column24
			// 
			this->Column24->HeaderText = L"Value (Near Term)";
			this->Column24->Name = L"Column24";
			this->Column24->Width = 108;
			// 
			// Column25
			// 
			this->Column25->HeaderText = L"Value (Optimistic)";
			this->Column25->Name = L"Column25";
			this->Column25->Width = 104;
			// 
			// Column26
			// 
			this->Column26->HeaderText = L"Unit";
			this->Column26->Name = L"Column26";
			this->Column26->Width = 51;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->costChart);
			this->tabPage3->Location = System::Drawing::Point(4, 22);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(886, 746);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Current vs Cost";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// costChart
			// 
			chartArea1->Name = L"ChartArea1";
			this->costChart->ChartAreas->Add(chartArea1);
			legend1->Enabled = false;
			legend1->Name = L"Legend1";
			this->costChart->Legends->Add(legend1);
			this->costChart->Location = System::Drawing::Point(0, 0);
			this->costChart->Name = L"costChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series1->IsXValueIndexed = true;
			series1->Legend = L"Legend1";
			series1->Name = L"Series1";
			this->costChart->Series->Add(series1);
			this->costChart->Size = System::Drawing::Size(883, 437);
			this->costChart->TabIndex = 0;
			this->costChart->Text = L"costChart";
			title1->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Left;
			title1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			title1->Name = L"Title1";
			title1->Text = L"$/kWh";
			title2->Docking = System::Windows::Forms::DataVisualization::Charting::Docking::Bottom;
			title2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 16));
			title2->Name = L"Title2";
			title2->Text = L"Current Density (mA/cm^2)";
			this->costChart->Titles->Add(title1);
			this->costChart->Titles->Add(title2);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->dataOutput);
			this->tabPage2->Location = System::Drawing::Point(4, 22);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Padding = System::Windows::Forms::Padding(3);
			this->tabPage2->Size = System::Drawing::Size(886, 746);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Raw Data";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// dataOutput
			// 
			this->dataOutput->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataOutput->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(19) {this->Column1, this->Column2, 
				this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8, this->Column9, this->Column10, this->Column11, 
				this->Column12, this->Column13, this->dataGridViewTextBoxColumn1, this->Column15, this->Column16, this->Column14, this->Column21, 
				this->Digits});
			this->dataOutput->Location = System::Drawing::Point(6, 6);
			this->dataOutput->Name = L"dataOutput";
			this->dataOutput->Size = System::Drawing::Size(877, 343);
			this->dataOutput->TabIndex = 0;
			this->dataOutput->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataOutput_CellContentClick);
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"j Low";
			this->Column1->Name = L"Column1";
			this->Column1->Width = 50;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Present Total $/kWh";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 50;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Near-Term Total $/kWh";
			this->Column3->Name = L"Column3";
			this->Column3->Width = 50;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Optimistic Total $/kWh";
			this->Column4->Name = L"Column4";
			this->Column4->Width = 50;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Average Effective Voltage";
			this->Column5->Name = L"Column5";
			this->Column5->Width = 50;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Cell Area (m^2)";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 50;
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"Efficiency (1way)";
			this->Column7->Name = L"Column7";
			this->Column7->Width = 60;
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Present $/kWh";
			this->Column8->Name = L"Column8";
			this->Column8->Width = 50;
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Near-Term $/kWh";
			this->Column9->Name = L"Column9";
			this->Column9->Width = 50;
			// 
			// Column10
			// 
			this->Column10->HeaderText = L"Optimistic $/kWh";
			this->Column10->Name = L"Column10";
			this->Column10->Width = 50;
			// 
			// Column11
			// 
			this->Column11->HeaderText = L"Present $/kW";
			this->Column11->Name = L"Column11";
			this->Column11->Width = 50;
			// 
			// Column12
			// 
			this->Column12->HeaderText = L"Near-Term $/kW";
			this->Column12->Name = L"Column12";
			this->Column12->Width = 50;
			// 
			// Column13
			// 
			this->Column13->HeaderText = L"Optimistic $/kW";
			this->Column13->Name = L"Column13";
			this->Column13->Width = 50;
			// 
			// dataGridViewTextBoxColumn1
			// 
			this->dataGridViewTextBoxColumn1->HeaderText = L"EC eff";
			this->dataGridViewTextBoxColumn1->Name = L"dataGridViewTextBoxColumn1";
			// 
			// Column15
			// 
			this->Column15->HeaderText = L"Pump Eff";
			this->Column15->Name = L"Column15";
			// 
			// Column16
			// 
			this->Column16->HeaderText = L"Shunt Eff";
			this->Column16->Name = L"Column16";
			// 
			// Column14
			// 
			this->Column14->HeaderText = L"Area";
			this->Column14->Name = L"Column14";
			// 
			// Column21
			// 
			this->Column21->HeaderText = L"Avg Flow";
			this->Column21->Name = L"Column21";
			// 
			// Digits
			// 
			this->Digits->HeaderText = L"High Flow";
			this->Digits->Name = L"Digits";
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->OutputGrid);
			this->tabPage1->Controls->Add(this->label23);
			this->tabPage1->Controls->Add(this->spaBox);
			this->tabPage1->Controls->Add(this->label22);
			this->tabPage1->Controls->Add(this->LiConcBox);
			this->tabPage1->Controls->Add(this->label81);
			this->tabPage1->Controls->Add(this->electronBox);
			this->tabPage1->Controls->Add(this->LiVoltageBox);
			this->tabPage1->Controls->Add(this->flowCapBox);
			this->tabPage1->Controls->Add(this->channelSepBox);
			this->tabPage1->Controls->Add(this->aspectRatioBox);
			this->tabPage1->Controls->Add(this->FOWBox);
			this->tabPage1->Controls->Add(this->FOHBox);
			this->tabPage1->Controls->Add(this->MOBox);
			this->tabPage1->Controls->Add(this->ThRedBox);
			this->tabPage1->Controls->Add(this->PBox);
			this->tabPage1->Controls->Add(this->KBox);
			this->tabPage1->Controls->Add(this->ThicknessBox);
			this->tabPage1->Controls->Add(this->CondBox);
			this->tabPage1->Controls->Add(this->label51);
			this->tabPage1->Controls->Add(this->label90);
			this->tabPage1->Controls->Add(this->label89);
			this->tabPage1->Controls->Add(this->interdigBox);
			this->tabPage1->Controls->Add(this->label84);
			this->tabPage1->Controls->Add(this->label21);
			this->tabPage1->Controls->Add(this->label19);
			this->tabPage1->Controls->Add(this->label20);
			this->tabPage1->Controls->Add(this->label18);
			this->tabPage1->Controls->Add(this->label17);
			this->tabPage1->Controls->Add(this->label16);
			this->tabPage1->Controls->Add(this->textasf);
			this->tabPage1->Controls->Add(this->panel6);
			this->tabPage1->Controls->Add(this->panel5);
			this->tabPage1->Controls->Add(this->panel4);
			this->tabPage1->Controls->Add(this->bestTable);
			this->tabPage1->Controls->Add(this->panel3);
			this->tabPage1->Controls->Add(this->progressBar);
			this->tabPage1->Controls->Add(this->calculate);
			this->tabPage1->Controls->Add(this->panel2);
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(886, 746);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Main";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// OutputGrid
			// 
			this->OutputGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->OutputGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->Column27, 
				this->Column28, this->Column29, this->Column32, this->Power});
			this->OutputGrid->Location = System::Drawing::Point(70, 507);
			this->OutputGrid->Name = L"OutputGrid";
			this->OutputGrid->Size = System::Drawing::Size(352, 182);
			this->OutputGrid->TabIndex = 56;
			// 
			// Column27
			// 
			this->Column27->HeaderText = L"SOC (%)";
			this->Column27->Name = L"Column27";
			// 
			// Column28
			// 
			this->Column28->HeaderText = L"Flow rate (ml/min/cell)";
			this->Column28->Name = L"Column28";
			// 
			// Column29
			// 
			this->Column29->HeaderText = L"Current (mA/cm^2)";
			this->Column29->Name = L"Column29";
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(486, 468);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(100, 13);
			this->label23->TabIndex = 55;
			this->label23->Text = L"Scale Specific Area";
			// 
			// spaBox
			// 
			this->spaBox->Location = System::Drawing::Point(592, 465);
			this->spaBox->Name = L"spaBox";
			this->spaBox->Size = System::Drawing::Size(65, 20);
			this->spaBox->TabIndex = 54;
			this->spaBox->Text = L"1";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(543, 442);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(43, 13);
			this->label22->TabIndex = 53;
			this->label22->Text = L"Li Conc";
			// 
			// LiConcBox
			// 
			this->LiConcBox->Location = System::Drawing::Point(592, 439);
			this->LiConcBox->Name = L"LiConcBox";
			this->LiConcBox->Size = System::Drawing::Size(65, 20);
			this->LiConcBox->TabIndex = 52;
			this->LiConcBox->Text = L"2000";
			// 
			// label81
			// 
			this->label81->AutoSize = true;
			this->label81->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label81->Location = System::Drawing::Point(119, 434);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(67, 17);
			this->label81->TabIndex = 51;
			this->label81->Text = L"Electrons";
			// 
			// electronBox
			// 
			this->electronBox->Location = System::Drawing::Point(192, 434);
			this->electronBox->Name = L"electronBox";
			this->electronBox->Size = System::Drawing::Size(50, 20);
			this->electronBox->TabIndex = 50;
			this->electronBox->Text = L"1";
			// 
			// LiVoltageBox
			// 
			this->LiVoltageBox->Location = System::Drawing::Point(194, 408);
			this->LiVoltageBox->Name = L"LiVoltageBox";
			this->LiVoltageBox->Size = System::Drawing::Size(50, 20);
			this->LiVoltageBox->TabIndex = 48;
			this->LiVoltageBox->Text = L"3.8";
			// 
			// flowCapBox
			// 
			this->flowCapBox->Location = System::Drawing::Point(194, 382);
			this->flowCapBox->Name = L"flowCapBox";
			this->flowCapBox->Size = System::Drawing::Size(50, 20);
			this->flowCapBox->TabIndex = 46;
			this->flowCapBox->Text = L"999999999999";
			// 
			// channelSepBox
			// 
			this->channelSepBox->Location = System::Drawing::Point(101, 344);
			this->channelSepBox->Name = L"channelSepBox";
			this->channelSepBox->Size = System::Drawing::Size(50, 20);
			this->channelSepBox->TabIndex = 43;
			this->channelSepBox->Text = L"0.1";
			// 
			// aspectRatioBox
			// 
			this->aspectRatioBox->Location = System::Drawing::Point(101, 295);
			this->aspectRatioBox->Name = L"aspectRatioBox";
			this->aspectRatioBox->Size = System::Drawing::Size(50, 20);
			this->aspectRatioBox->TabIndex = 40;
			this->aspectRatioBox->Text = L"1";
			// 
			// FOWBox
			// 
			this->FOWBox->Location = System::Drawing::Point(442, 435);
			this->FOWBox->Name = L"FOWBox";
			this->FOWBox->Size = System::Drawing::Size(65, 20);
			this->FOWBox->TabIndex = 38;
			this->FOWBox->Text = L"0.05";
			// 
			// FOHBox
			// 
			this->FOHBox->Location = System::Drawing::Point(442, 410);
			this->FOHBox->Name = L"FOHBox";
			this->FOHBox->Size = System::Drawing::Size(65, 20);
			this->FOHBox->TabIndex = 36;
			this->FOHBox->Text = L"0.14";
			// 
			// MOBox
			// 
			this->MOBox->Location = System::Drawing::Point(442, 384);
			this->MOBox->Name = L"MOBox";
			this->MOBox->Size = System::Drawing::Size(65, 20);
			this->MOBox->TabIndex = 34;
			this->MOBox->Text = L"0.038";
			// 
			// ThRedBox
			// 
			this->ThRedBox->Location = System::Drawing::Point(663, 361);
			this->ThRedBox->Name = L"ThRedBox";
			this->ThRedBox->Size = System::Drawing::Size(31, 20);
			this->ThRedBox->TabIndex = 33;
			this->ThRedBox->Text = L"1";
			// 
			// PBox
			// 
			this->PBox->Location = System::Drawing::Point(592, 413);
			this->PBox->Name = L"PBox";
			this->PBox->Size = System::Drawing::Size(65, 20);
			this->PBox->TabIndex = 31;
			this->PBox->Text = L"1";
			// 
			// KBox
			// 
			this->KBox->Location = System::Drawing::Point(592, 387);
			this->KBox->Name = L"KBox";
			this->KBox->Size = System::Drawing::Size(65, 20);
			this->KBox->TabIndex = 29;
			this->KBox->Text = L"1";
			// 
			// ThicknessBox
			// 
			this->ThicknessBox->Location = System::Drawing::Point(592, 361);
			this->ThicknessBox->Name = L"ThicknessBox";
			this->ThicknessBox->Size = System::Drawing::Size(65, 20);
			this->ThicknessBox->TabIndex = 27;
			this->ThicknessBox->Text = L"1";
			// 
			// CondBox
			// 
			this->CondBox->Location = System::Drawing::Point(592, 335);
			this->CondBox->Name = L"CondBox";
			this->CondBox->Size = System::Drawing::Size(65, 20);
			this->CondBox->TabIndex = 25;
			this->CondBox->Text = L"1";
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label51->Location = System::Drawing::Point(-1, 409);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(189, 17);
			this->label51->TabIndex = 49;
			this->label51->Text = L"Li+ Organic OCV (50% SOC)";
			// 
			// label90
			// 
			this->label90->AutoSize = true;
			this->label90->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label90->Location = System::Drawing::Point(5, 383);
			this->label90->Name = L"label90";
			this->label90->Size = System::Drawing::Size(183, 17);
			this->label90->TabIndex = 47;
			this->label90->Text = L"Flow Rate Cap (ml/min/m^2)";
			// 
			// label89
			// 
			this->label89->AutoSize = true;
			this->label89->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label89->Location = System::Drawing::Point(7, 345);
			this->label89->Name = L"label89";
			this->label89->Size = System::Drawing::Size(89, 17);
			this->label89->TabIndex = 44;
			this->label89->Text = L"Channel Sep";
			// 
			// interdigBox
			// 
			this->interdigBox->AutoSize = true;
			this->interdigBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->interdigBox->Location = System::Drawing::Point(9, 321);
			this->interdigBox->Name = L"interdigBox";
			this->interdigBox->Size = System::Drawing::Size(109, 21);
			this->interdigBox->TabIndex = 42;
			this->interdigBox->Text = L"Interdigitated";
			this->interdigBox->UseVisualStyleBackColor = true;
			// 
			// label84
			// 
			this->label84->AutoSize = true;
			this->label84->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label84->Location = System::Drawing::Point(7, 296);
			this->label84->Name = L"label84";
			this->label84->Size = System::Drawing::Size(88, 17);
			this->label84->TabIndex = 41;
			this->label84->Text = L"Aspect Ratio";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(350, 438);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(90, 13);
			this->label21->TabIndex = 39;
			this->label21->Text = L"Frame Overlap W";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(350, 413);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(87, 13);
			this->label19->TabIndex = 37;
			this->label19->Text = L"Frame Overlap H";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(339, 387);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(97, 13);
			this->label20->TabIndex = 35;
			this->label20->Text = L"Membrane Overlap";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(512, 416);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(67, 13);
			this->label18->TabIndex = 32;
			this->label18->Text = L"Scale PDrop";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(512, 390);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(74, 13);
			this->label17->TabIndex = 30;
			this->label17->Text = L"Scale Kinetics";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(500, 364);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(86, 13);
			this->label16->TabIndex = 28;
			this->label16->Text = L"Scale Thickness";
			// 
			// textasf
			// 
			this->textasf->AutoSize = true;
			this->textasf->Location = System::Drawing::Point(514, 338);
			this->textasf->Name = L"textasf";
			this->textasf->Size = System::Drawing::Size(72, 13);
			this->textasf->TabIndex = 26;
			this->textasf->Text = L"Scale E Cond";
			// 
			// panel6
			// 
			this->panel6->Controls->Add(this->label15);
			this->panel6->Controls->Add(this->flowBox);
			this->panel6->Controls->Add(this->label9);
			this->panel6->Location = System::Drawing::Point(213, 236);
			this->panel6->Name = L"panel6";
			this->panel6->Size = System::Drawing::Size(278, 49);
			this->panel6->TabIndex = 23;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label15->Location = System::Drawing::Point(192, 10);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(61, 17);
			this->label15->TabIndex = 27;
			this->label15->Text = L"ml/min/A";
			// 
			// flowBox
			// 
			this->flowBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->flowBox->Location = System::Drawing::Point(155, 7);
			this->flowBox->Name = L"flowBox";
			this->flowBox->Size = System::Drawing::Size(31, 23);
			this->flowBox->TabIndex = 26;
			this->flowBox->Text = L"5";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label9->Location = System::Drawing::Point(7, 10);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(203, 17);
			this->label9->TabIndex = 25;
			this->label9->Text = L"Flow rate used for interpolation";
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->SplineButton);
			this->panel5->Controls->Add(this->ECModelButton);
			this->panel5->Location = System::Drawing::Point(329, 92);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(107, 50);
			this->panel5->TabIndex = 22;
			// 
			// SplineButton
			// 
			this->SplineButton->AutoSize = true;
			this->SplineButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->SplineButton->Location = System::Drawing::Point(4, 23);
			this->SplineButton->Name = L"SplineButton";
			this->SplineButton->Size = System::Drawing::Size(104, 21);
			this->SplineButton->TabIndex = 19;
			this->SplineButton->Text = L"Interpolation";
			this->SplineButton->UseVisualStyleBackColor = true;
			// 
			// ECModelButton
			// 
			this->ECModelButton->AutoSize = true;
			this->ECModelButton->Checked = true;
			this->ECModelButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->ECModelButton->Location = System::Drawing::Point(4, 0);
			this->ECModelButton->Name = L"ECModelButton";
			this->ECModelButton->Size = System::Drawing::Size(86, 21);
			this->ECModelButton->TabIndex = 18;
			this->ECModelButton->TabStop = true;
			this->ECModelButton->Text = L"EC Model";
			this->ECModelButton->UseVisualStyleBackColor = true;
			// 
			// panel4
			// 
			this->panel4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel4->Controls->Add(this->constcurrent);
			this->panel4->Controls->Add(this->constpower);
			this->panel4->Location = System::Drawing::Point(3, 235);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(139, 50);
			this->panel4->TabIndex = 21;
			// 
			// constcurrent
			// 
			this->constcurrent->AutoSize = true;
			this->constcurrent->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->constcurrent->Location = System::Drawing::Point(4, 23);
			this->constcurrent->Name = L"constcurrent";
			this->constcurrent->Size = System::Drawing::Size(133, 21);
			this->constcurrent->TabIndex = 19;
			this->constcurrent->Text = L"Constant Current";
			this->constcurrent->UseVisualStyleBackColor = true;
			// 
			// constpower
			// 
			this->constpower->AutoSize = true;
			this->constpower->Checked = true;
			this->constpower->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->constpower->Location = System::Drawing::Point(4, 0);
			this->constpower->Name = L"constpower";
			this->constpower->Size = System::Drawing::Size(125, 21);
			this->constpower->TabIndex = 18;
			this->constpower->TabStop = true;
			this->constpower->Text = L"Constant Power";
			this->constpower->UseVisualStyleBackColor = true;
			// 
			// bestTable
			// 
			this->bestTable->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->bestTable->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->Column19, this->Column17, 
				this->Column18, this->Column20});
			this->bestTable->Location = System::Drawing::Point(466, 6);
			this->bestTable->Name = L"bestTable";
			this->bestTable->RowTemplate->DefaultCellStyle->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->bestTable->Size = System::Drawing::Size(414, 193);
			this->bestTable->TabIndex = 20;
			// 
			// Column19
			// 
			this->Column19->HeaderText = L"Quantity";
			this->Column19->Name = L"Column19";
			// 
			// Column17
			// 
			this->Column17->HeaderText = L"Present";
			this->Column17->Name = L"Column17";
			this->Column17->Width = 60;
			// 
			// Column18
			// 
			this->Column18->HeaderText = L"Near Term";
			this->Column18->Name = L"Column18";
			this->Column18->Width = 60;
			// 
			// Column20
			// 
			this->Column20->HeaderText = L"Optimistic";
			this->Column20->Name = L"Column20";
			this->Column20->Width = 60;
			// 
			// panel3
			// 
			this->panel3->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel3->Controls->Add(this->label68);
			this->panel3->Controls->Add(this->label67);
			this->panel3->Controls->Add(this->stackBox);
			this->panel3->Controls->Add(this->cellBox);
			this->panel3->Controls->Add(this->label11);
			this->panel3->Controls->Add(this->label10);
			this->panel3->Controls->Add(this->label8);
			this->panel3->Controls->Add(this->label7);
			this->panel3->Controls->Add(this->label6);
			this->panel3->Controls->Add(this->label5);
			this->panel3->Controls->Add(this->energyBox);
			this->panel3->Controls->Add(this->epBox);
			this->panel3->Controls->Add(this->powerBox);
			this->panel3->Location = System::Drawing::Point(117, 6);
			this->panel3->Name = L"panel3";
			this->panel3->Size = System::Drawing::Size(196, 136);
			this->panel3->TabIndex = 17;
			// 
			// label68
			// 
			this->label68->AutoSize = true;
			this->label68->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label68->Location = System::Drawing::Point(27, 106);
			this->label68->Name = L"label68";
			this->label68->Size = System::Drawing::Size(50, 17);
			this->label68->TabIndex = 23;
			this->label68->Text = L"Stacks";
			// 
			// label67
			// 
			this->label67->AutoSize = true;
			this->label67->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label67->Location = System::Drawing::Point(2, 84);
			this->label67->Name = L"label67";
			this->label67->Size = System::Drawing::Size(77, 17);
			this->label67->TabIndex = 22;
			this->label67->Text = L"Cells/Stack";
			// 
			// stackBox
			// 
			this->stackBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->stackBox->Location = System::Drawing::Point(83, 106);
			this->stackBox->Name = L"stackBox";
			this->stackBox->Size = System::Drawing::Size(65, 23);
			this->stackBox->TabIndex = 21;
			this->stackBox->Text = L"36";
			// 
			// cellBox
			// 
			this->cellBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->cellBox->Location = System::Drawing::Point(83, 82);
			this->cellBox->Name = L"cellBox";
			this->cellBox->Size = System::Drawing::Size(65, 23);
			this->cellBox->TabIndex = 20;
			this->cellBox->Text = L"60";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label11->Location = System::Drawing::Point(154, 38);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(21, 17);
			this->label11->TabIndex = 19;
			this->label11->Text = L"hr";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label10->Location = System::Drawing::Point(154, 60);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(36, 17);
			this->label10->TabIndex = 18;
			this->label10->Text = L"kWh";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label8->Location = System::Drawing::Point(154, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(28, 17);
			this->label8->TabIndex = 17;
			this->label8->Text = L"kW";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label7->Location = System::Drawing::Point(30, 58);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(53, 17);
			this->label7->TabIndex = 16;
			this->label7->Text = L"Energy";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label6->Location = System::Drawing::Point(47, 35);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(30, 17);
			this->label6->TabIndex = 15;
			this->label6->Text = L"E/P";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label5->Location = System::Drawing::Point(30, 12);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(47, 17);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Power";
			// 
			// energyBox
			// 
			this->energyBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->energyBox->Location = System::Drawing::Point(83, 57);
			this->energyBox->Name = L"energyBox";
			this->energyBox->Size = System::Drawing::Size(65, 23);
			this->energyBox->TabIndex = 14;
			this->energyBox->Text = L"4000";
			this->energyBox->TextChanged += gcnew System::EventHandler(this, &Form1::energyBox_TextChanged);
			// 
			// epBox
			// 
			this->epBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->epBox->Location = System::Drawing::Point(83, 32);
			this->epBox->Name = L"epBox";
			this->epBox->Size = System::Drawing::Size(65, 23);
			this->epBox->TabIndex = 13;
			this->epBox->Text = L"4";
			this->epBox->TextChanged += gcnew System::EventHandler(this, &Form1::epBox_TextChanged);
			// 
			// powerBox
			// 
			this->powerBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->powerBox->Location = System::Drawing::Point(83, 9);
			this->powerBox->Name = L"powerBox";
			this->powerBox->Size = System::Drawing::Size(65, 23);
			this->powerBox->TabIndex = 12;
			this->powerBox->Text = L"1000";
			// 
			// progressBar
			// 
			this->progressBar->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->progressBar->Location = System::Drawing::Point(753, 201);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(125, 28);
			this->progressBar->TabIndex = 3;
			// 
			// calculate
			// 
			this->calculate->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->calculate->Location = System::Drawing::Point(753, 236);
			this->calculate->Name = L"calculate";
			this->calculate->Size = System::Drawing::Size(125, 30);
			this->calculate->TabIndex = 0;
			this->calculate->Text = L"Calculate!";
			this->calculate->UseVisualStyleBackColor = true;
			this->calculate->Click += gcnew System::EventHandler(this, &Form1::calculate_Click);
			// 
			// panel2
			// 
			this->panel2->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel2->Controls->Add(this->label14);
			this->panel2->Controls->Add(this->label13);
			this->panel2->Controls->Add(this->label12);
			this->panel2->Controls->Add(this->label3);
			this->panel2->Controls->Add(this->DODBox);
			this->panel2->Controls->Add(this->label2);
			this->panel2->Controls->Add(this->label1);
			this->panel2->Controls->Add(this->jHighBox);
			this->panel2->Controls->Add(this->jLowBox);
			this->panel2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->panel2->Location = System::Drawing::Point(3, 148);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(310, 81);
			this->panel2->TabIndex = 11;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label14->Location = System::Drawing::Point(217, 56);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(58, 17);
			this->label14->TabIndex = 26;
			this->label14->Text = L"mA/cm2";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label13->Location = System::Drawing::Point(217, 30);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(58, 17);
			this->label13->TabIndex = 25;
			this->label13->Text = L"mA/cm2";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label12->Location = System::Drawing::Point(217, 4);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(20, 17);
			this->label12->TabIndex = 24;
			this->label12->Text = L"%";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(25, 4);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(130, 17);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Depth of Discharge";
			// 
			// DODBox
			// 
			this->DODBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->DODBox->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->DODBox->Location = System::Drawing::Point(164, 2);
			this->DODBox->Name = L"DODBox";
			this->DODBox->Size = System::Drawing::Size(45, 23);
			this->DODBox->TabIndex = 8;
			this->DODBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {70, 0, 0, 0});
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(8, 56);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(152, 17);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Min current at low SOC";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(5, 30);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(155, 17);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Max current at low SOC";
			// 
			// jHighBox
			// 
			this->jHighBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->jHighBox->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->jHighBox->Location = System::Drawing::Point(164, 28);
			this->jHighBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {275, 0, 0, 0});
			this->jHighBox->Name = L"jHighBox";
			this->jHighBox->Size = System::Drawing::Size(45, 23);
			this->jHighBox->TabIndex = 5;
			this->jHighBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {275, 0, 0, 0});
			this->jHighBox->ValueChanged += gcnew System::EventHandler(this, &Form1::jHighBox_ValueChanged);
			// 
			// jLowBox
			// 
			this->jLowBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->jLowBox->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->jLowBox->Location = System::Drawing::Point(164, 54);
			this->jLowBox->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {275, 0, 0, 0});
			this->jLowBox->Name = L"jLowBox";
			this->jLowBox->Size = System::Drawing::Size(45, 23);
			this->jLowBox->TabIndex = 4;
			this->jLowBox->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {100, 0, 0, 0});
			this->jLowBox->ValueChanged += gcnew System::EventHandler(this, &Form1::jLowBox_ValueChanged);
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->LiOrgButton);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->VVGen2);
			this->panel1->Controls->Add(this->VVGen1);
			this->panel1->Controls->Add(this->FeV);
			this->panel1->Location = System::Drawing::Point(3, 6);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(108, 104);
			this->panel1->TabIndex = 10;
			// 
			// LiOrgButton
			// 
			this->LiOrgButton->AutoSize = true;
			this->LiOrgButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LiOrgButton->Location = System::Drawing::Point(3, 82);
			this->LiOrgButton->Name = L"LiOrgButton";
			this->LiOrgButton->Size = System::Drawing::Size(99, 21);
			this->LiOrgButton->TabIndex = 12;
			this->LiOrgButton->Text = L"Li+ Organic";
			this->LiOrgButton->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(1, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(70, 17);
			this->label4->TabIndex = 11;
			this->label4->Text = L"Chemistry";
			// 
			// VVGen2
			// 
			this->VVGen2->AutoSize = true;
			this->VVGen2->Checked = true;
			this->VVGen2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->VVGen2->Location = System::Drawing::Point(3, 62);
			this->VVGen2->Name = L"VVGen2";
			this->VVGen2->Size = System::Drawing::Size(90, 21);
			this->VVGen2->TabIndex = 2;
			this->VVGen2->TabStop = true;
			this->VVGen2->Text = L"V-V Gen II";
			this->VVGen2->UseVisualStyleBackColor = true;
			// 
			// VVGen1
			// 
			this->VVGen1->AutoSize = true;
			this->VVGen1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->VVGen1->Location = System::Drawing::Point(3, 39);
			this->VVGen1->Name = L"VVGen1";
			this->VVGen1->Size = System::Drawing::Size(87, 21);
			this->VVGen1->TabIndex = 1;
			this->VVGen1->Text = L"V-V Gen I";
			this->VVGen1->UseVisualStyleBackColor = true;
			// 
			// FeV
			// 
			this->FeV->AutoSize = true;
			this->FeV->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FeV->Location = System::Drawing::Point(3, 16);
			this->FeV->Name = L"FeV";
			this->FeV->Size = System::Drawing::Size(56, 21);
			this->FeV->TabIndex = 0;
			this->FeV->Text = L"Fe-V";
			this->FeV->UseVisualStyleBackColor = true;
			// 
			// tabControl1
			// 
			this->tabControl1->Controls->Add(this->tabPage1);
			this->tabControl1->Controls->Add(this->tabPage2);
			this->tabControl1->Controls->Add(this->tabPage3);
			this->tabControl1->Controls->Add(this->tabPage5);
			this->tabControl1->Controls->Add(this->tabPage4);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->RightToLeftLayout = true;
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(894, 772);
			this->tabControl1->TabIndex = 18;
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->testGrid);
			this->tabPage4->Controls->Add(this->label29);
			this->tabPage4->Controls->Add(this->testVEff);
			this->tabPage4->Controls->Add(this->testPowerOrig);
			this->tabPage4->Controls->Add(this->testPowerNew);
			this->tabPage4->Controls->Add(this->label27);
			this->tabPage4->Controls->Add(this->label28);
			this->tabPage4->Controls->Add(this->testFlow);
			this->tabPage4->Controls->Add(this->testCurrent);
			this->tabPage4->Controls->Add(this->label26);
			this->tabPage4->Controls->Add(this->label25);
			this->tabPage4->Controls->Add(this->label24);
			this->tabPage4->Controls->Add(this->testBox);
			this->tabPage4->Controls->Add(this->button1);
			this->tabPage4->Location = System::Drawing::Point(4, 22);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(886, 746);
			this->tabPage4->TabIndex = 5;
			this->tabPage4->Text = L"Test tab";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// testGrid
			// 
			this->testGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->testGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {this->dataGridViewTextBoxColumn2, 
				this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn3, this->Column30, this->Column31});
			this->testGrid->Location = System::Drawing::Point(269, 192);
			this->testGrid->Name = L"testGrid";
			this->testGrid->Size = System::Drawing::Size(450, 182);
			this->testGrid->TabIndex = 57;
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Location = System::Drawing::Point(37, 195);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(46, 13);
			this->label29->TabIndex = 12;
			this->label29->Text = L"VEffAvg";
			// 
			// testVEff
			// 
			this->testVEff->Location = System::Drawing::Point(84, 192);
			this->testVEff->Name = L"testVEff";
			this->testVEff->Size = System::Drawing::Size(90, 20);
			this->testVEff->TabIndex = 11;
			// 
			// testPowerOrig
			// 
			this->testPowerOrig->Location = System::Drawing::Point(324, 44);
			this->testPowerOrig->Name = L"testPowerOrig";
			this->testPowerOrig->Size = System::Drawing::Size(90, 20);
			this->testPowerOrig->TabIndex = 10;
			// 
			// testPowerNew
			// 
			this->testPowerNew->Location = System::Drawing::Point(323, 70);
			this->testPowerNew->Name = L"testPowerNew";
			this->testPowerNew->Size = System::Drawing::Size(90, 20);
			this->testPowerNew->TabIndex = 9;
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Location = System::Drawing::Point(256, 47);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(56, 13);
			this->label27->TabIndex = 8;
			this->label27->Text = L"Old Power";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Location = System::Drawing::Point(256, 70);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(61, 13);
			this->label28->TabIndex = 7;
			this->label28->Text = L"New power";
			// 
			// testFlow
			// 
			this->testFlow->Location = System::Drawing::Point(85, 107);
			this->testFlow->Name = L"testFlow";
			this->testFlow->Size = System::Drawing::Size(90, 20);
			this->testFlow->TabIndex = 6;
			this->testFlow->Text = L"5798";
			// 
			// testCurrent
			// 
			this->testCurrent->Location = System::Drawing::Point(84, 133);
			this->testCurrent->Name = L"testCurrent";
			this->testCurrent->Size = System::Drawing::Size(90, 20);
			this->testCurrent->TabIndex = 5;
			this->testCurrent->Text = L"100";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Location = System::Drawing::Point(38, 115);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(26, 13);
			this->label26->TabIndex = 4;
			this->label26->Text = L"flow";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Location = System::Drawing::Point(38, 140);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(40, 13);
			this->label25->TabIndex = 3;
			this->label25->Text = L"current";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Location = System::Drawing::Point(38, 169);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(28, 13);
			this->label24->TabIndex = 2;
			this->label24->Text = L"area";
			// 
			// testBox
			// 
			this->testBox->Location = System::Drawing::Point(85, 166);
			this->testBox->Name = L"testBox";
			this->testBox->Size = System::Drawing::Size(90, 20);
			this->testBox->TabIndex = 1;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(28, 22);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Test";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"SOC (%)";
			this->dataGridViewTextBoxColumn2->Name = L"dataGridViewTextBoxColumn2";
			// 
			// dataGridViewTextBoxColumn4
			// 
			this->dataGridViewTextBoxColumn4->HeaderText = L"Current (mA/cm^2)";
			this->dataGridViewTextBoxColumn4->Name = L"dataGridViewTextBoxColumn4";
			// 
			// dataGridViewTextBoxColumn3
			// 
			this->dataGridViewTextBoxColumn3->HeaderText = L"Flow rate (ml/min/cell)";
			this->dataGridViewTextBoxColumn3->Name = L"dataGridViewTextBoxColumn3";
			// 
			// Column30
			// 
			this->Column30->HeaderText = L"VEff";
			this->Column30->Name = L"Column30";
			// 
			// Column31
			// 
			this->Column31->HeaderText = L"Power";
			this->Column31->Name = L"Column31";
			// 
			// Column32
			// 
			this->Column32->HeaderText = L"VEff";
			this->Column32->Name = L"Column32";
			// 
			// Power
			// 
			this->Power->HeaderText = L"Column33";
			this->Power->Name = L"Power";
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(909, 791);
			this->Controls->Add(this->tabControl1);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->Text = L"Flow Battery Calculator";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bindingSource1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataTable2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataSet1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataTable1))->EndInit();
			this->tabPage5->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->CostParameters))->EndInit();
			this->tabPage3->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->costChart))->EndInit();
			this->tabPage2->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->dataOutput))->EndInit();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->OutputGrid))->EndInit();
			this->panel6->ResumeLayout(false);
			this->panel6->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bestTable))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->DODBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->jHighBox))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->jLowBox))->EndInit();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->testGrid))->EndInit();
			this->ResumeLayout(false);

		}//GUI portion has ended
#pragma endregion
		public: void InitializeCostParameters()//InitializeCostParameters is a function that executes steps below
				{
								CostParameters->Rows->Add("Nafion Membrane","500","350","200","$/m^2");//0; CostParameters is a DatagridView
								CostParameters->Rows->Add("Daramic Membrane","10","10","10","$/m^2");//1
								CostParameters->Rows->Add("Carbon Felt","70","45","20","$/m^2");//2
								CostParameters->Rows->Add("PVC Frame","16.84","10.05","3.26","$/m^2");//3
								CostParameters->Rows->Add("Bipolar Plate","55","35","25","$/m^2");//4
								CostParameters->Rows->Add("HEX",".084",".056",".037","$/W");//5
								CostParameters->Rows->Add("PCS","0.18375","0.18375","0.18375","$/W");//6
								CostParameters->Rows->Add("Pump Base Cost","8343.10","8343.10","8343.10","$/unit");//7
								CostParameters->Rows->Add("Pump Cost per GPM","18","18","18","$/GPM");//8
								CostParameters->Rows->Add("Al Endplate","193","175","86","$/Unit");//9
								CostParameters->Rows->Add("Vanadium Pentoxide","24","16","8","$/kg");//10
								CostParameters->Rows->Add("Ferric Chloride","0.35","0.30","0.25","$/kg");//11
								CostParameters->Rows->Add("Chemical Sythesis","0.8","0.8","0.8","$/kg");//12
								CostParameters->Rows->Add("Tank","0.4061","0.3502","0.2943","$/gall");//13
								CostParameters->Rows->Add("Sulfuric Acid","85","70","50","$/ton");//14
								

				}
		public: std::vector<vector<double> > populateSpline2V(vector<double>& X,vector<double>& Y)
{//coming up with function that interpolates of dataset (Y vs X) using cubic splines
	

	vector<double> A;
	vector<double> C;
	vector<double> B;
	vector<double> D;
	const int m=(int) X.size();
	int n=m-1;
	int i=0;
	vector<vector<double> > splineMatrix;
	if(m==2)
	{

		B.push_back((Y[1]-Y[0])/(X[1]-X[0]));
		B.push_back(0);;
		while(i<=1)
		{
		C.push_back(0);
		D.push_back(0);
		i++;
		}
		splineMatrix.push_back(X);
		splineMatrix.push_back(Y);
		splineMatrix.push_back(B);
		splineMatrix.push_back(C);
		splineMatrix.push_back(D);
	}
	else
	{
	i=1;
	C.resize(n+1,0);
	D.resize(n+1,0);
	B.resize(n+1,0);
	C[0]=0;
	while(i<n)
	{
		B[i]=2/((X[i+1]-X[i])/(Y[i+1]-Y[i])+(X[i]-X[i-1])/(Y[i]-Y[i-1]));
		i++;
	}
	B[0]=1.5*(Y[1]-Y[0])/(X[1]-X[0])-B[1]/2;
	B[n]=1.5*(Y[n]-Y[n-1])/(X[n]-X[n-1])-B[n-1]/2;
	D[0]=(B[1]-B[0]-2*C[0]*(X[1]-X[0]))/(3*pow(X[1]-X[0],2));
	i=1;
	while(i<n)
	{
		double delX=X[i+1]-X[i];
		double e = Y[i+1]-Y[i]-B[i]*delX;
		double f = B[i+1]-B[i];
		double a = delX*delX;
		double b = delX*delX*delX;
		double c = 2*delX;
		double d = 3*delX*delX;
		C[i]=(e*d-b*f)/(a*d-b*c);
		D[i]=(a*f-e*c)/(a*d-b*c);
		i++;
	}
	i=0;
	splineMatrix.push_back(X);
	splineMatrix.push_back(Y);
	splineMatrix.push_back(B);
	splineMatrix.push_back(C);
	splineMatrix.push_back(D);
	}
	return splineMatrix;
}
		public: double interpolateSplineV(double x,vector<vector<double> > matrix)
{//uses above interpolation functions to get Y at some X
	int i = 0;
	double y=0;
	double delx;
	int size = matrix[0].size();
	while (i<size)
	{
		if(x>=matrix[0][i])
		{
			
			delx = x-matrix[0][i];
			y=matrix[1][i]+matrix[2][i]*delx+matrix[3][i]*delx*delx+matrix[4][i]*delx*delx*delx;
		}
		else if(x<matrix[0][i])
		{
			break;
			
		}
		i++;
	}
	return y;
}
		public: double interpolate2dSpline(vector<vector<vector<double> > > SuperMatrix, vector<double> j,double x,double y)
{//get Y as f(2 independent variables)
	vector<double> X1;
	int i = 0;
	int size=SuperMatrix.size();
	while (i<size)
	{
		X1.push_back(interpolateSplineV(x,SuperMatrix[i]));
		i++;
	}
	vector<vector<double > > Matrix=populateSpline2V(j,X1);
	return interpolateSplineV(y,Matrix);
}
		public: std::vector<vector<double > > fileRead(string file)
{//reads CSV file
	ifstream datafile;
	datafile.open(file);
	string line;
	vector<vector<double > > datamatrix;
	int i = 0;
	int j = 0;
	datamatrix.resize(1);
	while(datafile.good())
	{
	getline(datafile,line,',');
	if(line=="n")
	{
		j=0;
		i++;
		datamatrix.resize(datamatrix.size()+1);
		
		getline(datafile,line);
	
		getline(datafile,line,',');
	}
	
	datamatrix[i].push_back(atof(line.c_str()));
	
	j++;
	}
	datamatrix.resize(datamatrix.size()-1);
	datafile.close();
	return datamatrix;
}
	public: double asinh(double x)
{//mathematical function arc hyperbolic sine
    if(x>0)
        return log(x+sqrt(x*x+1));
    else
        return -log(x+sqrt(x*x+1));
}
	public: double voltage(double SOC, double area, double flow, double j,double aspectratio,int system, int membrane,vector<vector<vector<double> > >& SuperMatrix,vector<double>& J)
{
	//electrochemical model
	//SOC as fraction
	//area is active cell area in m^2
	//flow is flow rate ml/min/cell
	//j is current density in mA/cm^2
	//aspect ratio is height:width  (height being the direction of flow)
	//system is 0 for Fe-V, 1 for V-V
	//membrane is 0 for Daramic, 1 for Nafion
	//SuperMatrix and J are used for spline extrapolation
	
	int i = system; //0 for Fe-V, 1 for V-V
    const double F = 96485;// C/mol
    const double R = 8.314; // J/mol K
    double V;
    double width = sqrt(area/aspectratio); //cell width m
    double height = width*aspectratio;
	double V2[2] = {0.77,1.004}; //V
//	V2[1]+=2;
	double V1[2]={-0.085,-.41}; //V
    double Q = flow/(60*1000*1000); // m^3/s
	double TCent[2]={45,45};

	if (SplineButton->Checked)
	{
		return interpolate2dSpline(SuperMatrix,J,SOC,j);
	}
	if(VVGen1->Checked)
	{
		TCent[1]=35;
	}
    double T = TCent[i]+273.15; // K
    double Ci1 = 1750; // initial concentration of chemical 1, mol/m^3
	if(VVGen1->Checked)
	{
		Ci1=1500;
	}
	if(FeV->Checked)
	{
		Ci1=1750;
	}
	if(VVGen2->Checked)
	{
		Ci1=2000;
	}
	if(LiOrgButton->Checked)
	{
		Ci1= Convert::ToDouble(LiConcBox->Text);
	}
	double Ci2 = Ci1; // initial concentration of chemical 2, mol/m^3
	double tScaleFactor = Convert::ToDouble(ThicknessBox->Text);
    double t=0.004*tScaleFactor; //cell thickness m
    double I=j*width*height*100*100/1000; //current A
	double A[2] = {2,4};
	A[i]*= Convert::ToDouble(ThRedBox->Text);
	double chi[2] = {4,0};
	double n = Convert::ToDouble(electronBox->Text);
    double delSOC=I*A[i]/(n*2*Q*Ci1*F);
    double SOCrxn=SOC-delSOC;
    double Inew=j*(1+chi[i]*delSOC*2)*100*100/1000;
    double eps=0.94; //porosity
    double a = 39000*eps/4;//CHECK THIS
	a*=Convert::ToDouble(spaBox->Text);
    double Km=0.00016*pow(Q/(eps*width*t),0.4);
    double Conc1neg=Ci1*SOCrxn-Inew/(t*F*a*Km/eps); // V 2+
    double Conc1pos=Ci1-Conc1neg; //V 3+
    double Conc2pos=Ci2*SOCrxn-Inew/(t*F*a*Km/eps); // V 5+
    double Conc2neg=Ci2-Conc2pos; //V 4+
	double kScaleFactor = Convert::ToDouble(KBox->Text);
    double k1=8.7/1000000*exp((F*0.255/R)*(T-298)/(298*T));
	double k2[2]={1.6/100000*exp((F*0.77/R)*(T-298)/(298*T)),0.00000068*exp((F*V2[i]/R)*(T-298)/(298*T))};
    if(LiOrgButton->Checked)
	{
		k1*=1;
		k2[system]*=1;
	}
	double etaneg=-2*R*T/F*asinh(Inew/(2*t*a*F*k1*kScaleFactor*sqrt(Conc1neg*Conc1pos)));
    double etapos=2*R*T/F*asinh(Inew/(2*t*a*F*k2[i]*kScaleFactor*sqrt(Conc2neg*Conc2pos)));
	double mt[2]={450e-6,175e-6}; //membrane thickness m
	double condM[2]={53.65395346,(0.5139*9-.326)*exp(1268*(T-303)/(T*303))};
    double IRM = (j*100*100/1000)*(mt[membrane])/(condM[membrane]);
	double iconcH[2]={5300,1000};
	double concH[2]={iconcH[0],iconcH[1]+Ci1*SOCrxn-Inew/(t*F*a*Km)};
	double concCl[2]={1500,0};
	double concH2SO4[2]={3800,5000};
    int ZV2=2;
    int ZV3=3;
    int ZFe2=2;
    int ZFe3=3;
	int ZV4=2;
	int ZV5=1;
    int ZH=1;
    int ZCl=-1;
    int ZH2SO4=-1;
	double bruggman[2]={1.5,0};
	double reduction[2]={2.75/pow(eps,bruggman[i]),0.73/pow(eps,bruggman[i])};
	if(VVGen1->Checked)
	{
		reduction[1]=0.833/pow(eps,bruggman[i]);
	}
	double DV2=(2.4E-10)/reduction[system];
    double DV3=(2.4E-10)/reduction[system];
	double DV4=(3.9E-10)/reduction[system];
	double DV5=(3.9E-10)/reduction[system];
    double DFe2=(2.5E-10)/reduction[system];
    double DFe3=(2.5E-10)/reduction[system];
	double DH=(9.31E-09)/reduction[system];
    double DCl=(2.032E-09)/reduction[system];
    double DH2SO4=(1.33E-09)/reduction[system];
	double condScaleFactor = Convert::ToDouble(CondBox->Text);
	double pa=(F*F/(T*R))*(ZV2*ZV2*DV2*Conc1neg+ZV3*ZV3*DV3*Conc1pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i]);
    double pat=pa*(1+1.711464*(T-273-23)/100)*condScaleFactor;
	double pc[2]={(F*F/(T*R))*(ZFe2*ZFe2*DFe2*Conc2neg+ZFe3*ZFe3*DFe3*Conc2pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i]),(F*F/(T*R))*(ZV4*ZV4*DV4*Conc2neg+ZV5*ZV5*DV5*Conc2pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i])};
    double pct=pc[i]*(1+1.711464*(T-273-23)/100)*condScaleFactor;
    double Irea=t*Inew/pat;
    double Irec=t*Inew/pct;
    if(Conc1neg*Conc2pos/(Conc1pos*Conc2neg)>0)
    {
    V = V2[i]-V1[i]+(R*T/F)*(log(Conc1neg*Conc2pos/(Conc1pos*Conc2neg))+log(concH[i]/iconcH[i]))+etaneg-etapos-Irea-Irec-IRM;
    }
    else
    {
    V=0;
    }
	if(LiOrgButton->Checked)
	{
		double VLiA[] = {3.193552576,3.298606737,3.422420435,3.516218117,3.602508955,3.662540986,3.670044043,3.673797466,3.700060059,3.73382571,3.752585246,3.767595148,3.790104319,3.812617278,3.835126449,3.898911903,3.932295015,3.977286844,4.12524213,4.152428876};
		std::vector<double> VLi (&VLiA[0], &VLiA[0]+20);
		double SOCLiA[] = {0.009631481,0.015312908,0.026677674,0.039934338,0.05697862,0.085387667,0.115688613,0.168717178,0.195232417,0.252048601,0.316440021,0.388408589,0.469844291,0.538025241,0.600522852,0.674383318,0.721711346,0.797815335,0.972556012,1};
		std::vector<double> SOCLi (&SOCLiA[0], &SOCLiA[0]+20);
		std::vector<vector<double> > LiMatrix= populateSpline2V(SOCLi,VLi);
		double OCVLi = interpolateSplineV(SOC,LiMatrix)-3.8+Convert::ToDouble(LiVoltageBox->Text);
		
		//etaneg = 0;
		//etapos = 0;
		pat = A[1]*10*condScaleFactor/(10); //S/m
		pct = pat; //temp
		condM[membrane]=2.5/(10); //S/m
		//t=0.5/1000;
		Irea = t*Inew/pat;
		Irec = t*Inew/pct;
		mt[membrane]=7*(25e-6); // m
		IRM = 0.1*(j*100*100/1000)*(mt[membrane])/(condM[membrane]);
		V = OCVLi + etaneg-etapos-Irea-Irec-IRM;

	}
	if(Conc1neg<=0 || Conc2neg<=0 || Conc1pos<=0 || Conc2pos<=0)
	{
		V=0;
	}
	double scaleV=1/*1.138*/;
    return V*scaleV;
}
	public: double g_voltage(double SOC, double area, double flow, double j,double aspectratio,int system, int membrane)
{
	//electrochemical model
	//SOC as fraction
	//area is active cell area in m^2
	//flow is flow rate ml/min/cell
	//j is current density in mA/cm^2
	//aspect ratio is height:width  (height being the direction of flow)
	//system is 0 for Fe-V, 1 for V-V
	//membrane is 0 for Daramic, 1 for Nafion
	//SuperMatrix and J are used for spline extrapolation
	
	int i = system; //0 for Fe-V, 1 for V-V
    const double F = 96485;// C/mol
    const double R = 8.314; // J/mol K
    double V;
    double width = sqrt(area/aspectratio); //cell width m
    double height = width*aspectratio;
	double V2[2] = {0.77,1.004}; //V
//	V2[1]+=2;
	double V1[2]={-0.085,-.41}; //V
    double Q = flow/(60*1000*1000); // m^3/s
	double TCent[2]={45,45};
	if(VVGen1->Checked)
	{
		TCent[1]=35;
	}
    double T = TCent[i]+273.15; // K
    double Ci1 = 1750; // initial concentration of chemical 1, mol/m^3
	if(VVGen1->Checked)
	{
		Ci1=1500;
	}
	if(FeV->Checked)
	{
		Ci1=1750;
	}
	if(VVGen2->Checked)
	{
		Ci1=2000;
	}
	if(LiOrgButton->Checked)
	{
		Ci1= Convert::ToDouble(LiConcBox->Text);
	}
	double Ci2 = Ci1; // initial concentration of chemical 2, mol/m^3
	double tScaleFactor = Convert::ToDouble(ThicknessBox->Text);
    double t=0.004*tScaleFactor; //cell thickness m
    double I=j*width*height*100*100/1000; //current A
	double A[2] = {2,4};
	A[i]*= Convert::ToDouble(ThRedBox->Text);
	double chi[2] = {4,0};
	double n = Convert::ToDouble(electronBox->Text);
    double delSOC=I*A[i]/(n*2*Q*Ci1*F);
    double SOCrxn=SOC-delSOC;
    double Inew=j*(1+chi[i]*delSOC*2)*100*100/1000;
    double eps=0.94; //porosity
    double a = 39000*eps/4;//CHECK THIS
	a*=Convert::ToDouble(spaBox->Text);
    double Km=0.00016*pow(Q/(eps*width*t),0.4);
    double Conc1neg=Ci1*SOCrxn-Inew/(t*F*a*Km/eps); // V 2+
    double Conc1pos=Ci1-Conc1neg; //V 3+
    double Conc2pos=Ci2*SOCrxn-Inew/(t*F*a*Km/eps); // V 5+
    double Conc2neg=Ci2-Conc2pos; //V 4+
	double kScaleFactor = Convert::ToDouble(KBox->Text);
    double k1=8.7/1000000*exp((F*0.255/R)*(T-298)/(298*T));
	double k2[2]={1.6/100000*exp((F*0.77/R)*(T-298)/(298*T)),0.00000068*exp((F*V2[i]/R)*(T-298)/(298*T))};
    if(LiOrgButton->Checked)
	{
		k1*=1;
		k2[system]*=1;
	}
	double etaneg=-2*R*T/F*asinh(Inew/(2*t*a*F*k1*kScaleFactor*sqrt(Conc1neg*Conc1pos)));
    double etapos=2*R*T/F*asinh(Inew/(2*t*a*F*k2[i]*kScaleFactor*sqrt(Conc2neg*Conc2pos)));
	double mt[2]={450e-6,175e-6}; //membrane thickness m
	double condM[2]={53.65395346,(0.5139*9-.326)*exp(1268*(T-303)/(T*303))};
    double IRM = (j*100*100/1000)*(mt[membrane])/(condM[membrane]);
	double iconcH[2]={5300,1000};
	double concH[2]={iconcH[0],iconcH[1]+Ci1*SOCrxn-Inew/(t*F*a*Km)};
	double concCl[2]={1500,0};
	double concH2SO4[2]={3800,5000};
    int ZV2=2;
    int ZV3=3;
    int ZFe2=2;
    int ZFe3=3;
	int ZV4=2;
	int ZV5=1;
    int ZH=1;
    int ZCl=-1;
    int ZH2SO4=-1;
	double bruggman[2]={1.5,0};
	double reduction[2]={2.75/pow(eps,bruggman[i]),0.73/pow(eps,bruggman[i])};
	if(VVGen1->Checked)
	{
		reduction[1]=0.833/pow(eps,bruggman[i]);
	}
	double DV2=(2.4E-10)/reduction[system];
    double DV3=(2.4E-10)/reduction[system];
	double DV4=(3.9E-10)/reduction[system];
	double DV5=(3.9E-10)/reduction[system];
    double DFe2=(2.5E-10)/reduction[system];
    double DFe3=(2.5E-10)/reduction[system];
	double DH=(9.31E-09)/reduction[system];
    double DCl=(2.032E-09)/reduction[system];
    double DH2SO4=(1.33E-09)/reduction[system];
	double condScaleFactor = Convert::ToDouble(CondBox->Text);
	double pa=(F*F/(T*R))*(ZV2*ZV2*DV2*Conc1neg+ZV3*ZV3*DV3*Conc1pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i]);
    double pat=pa*(1+1.711464*(T-273-23)/100)*condScaleFactor;
	double pc[2]={(F*F/(T*R))*(ZFe2*ZFe2*DFe2*Conc2neg+ZFe3*ZFe3*DFe3*Conc2pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i]),(F*F/(T*R))*(ZV4*ZV4*DV4*Conc2neg+ZV5*ZV5*DV5*Conc2pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i])};
    double pct=pc[i]*(1+1.711464*(T-273-23)/100)*condScaleFactor;
    double Irea=t*Inew/pat;
    double Irec=t*Inew/pct;
    if(Conc1neg*Conc2pos/(Conc1pos*Conc2neg)>0)
    {
    V = V2[i]-V1[i]+(R*T/F)*(log(Conc1neg*Conc2pos/(Conc1pos*Conc2neg))+log(concH[i]/iconcH[i]))+etaneg-etapos-Irea-Irec-IRM;
    }
    else
    {
    V=0;
    }
	if(LiOrgButton->Checked)
	{
		double VLiA[] = {3.193552576,3.298606737,3.422420435,3.516218117,3.602508955,3.662540986,3.670044043,3.673797466,3.700060059,3.73382571,3.752585246,3.767595148,3.790104319,3.812617278,3.835126449,3.898911903,3.932295015,3.977286844,4.12524213,4.152428876};
		std::vector<double> VLi (&VLiA[0], &VLiA[0]+20);
		double SOCLiA[] = {0.009631481,0.015312908,0.026677674,0.039934338,0.05697862,0.085387667,0.115688613,0.168717178,0.195232417,0.252048601,0.316440021,0.388408589,0.469844291,0.538025241,0.600522852,0.674383318,0.721711346,0.797815335,0.972556012,1};
		std::vector<double> SOCLi (&SOCLiA[0], &SOCLiA[0]+20);
		std::vector<vector<double> > LiMatrix= populateSpline2V(SOCLi,VLi);
		double OCVLi = interpolateSplineV(SOC,LiMatrix)-3.8+Convert::ToDouble(LiVoltageBox->Text);
		
		//etaneg = 0;
		//etapos = 0;
		pat = A[1]*10*condScaleFactor/(10); //S/m
		pct = pat; //temp
		condM[membrane]=2.5/(10); //S/m
		//t=0.5/1000;
		Irea = t*Inew/pat;
		Irec = t*Inew/pct;
		mt[membrane]=7*(25e-6); // m
		IRM = 0.1*(j*100*100/1000)*(mt[membrane])/(condM[membrane]);
		V = OCVLi + etaneg-etapos-Irea-Irec-IRM;

	}
	if(Conc1neg<=0 || Conc2neg<=0 || Conc1pos<=0 || Conc2pos<=0)
	{
		V=0;
	}
	double scaleV=1/*1.138*/;
    return V*scaleV;
}
	public: double CostTab(int column,int row,double units)
			{//this function is used to get data from cost table.
				String^ function = (this->CostParameters->Rows[row]->Cells[column]->Value->ToString());
				return unitFunction<double>(function,units);
			}
	public: template<typename T>
			double unitFunction(String^ function, double units)
			{//takes string, evaluates as function with "units" as variable
				std::string expression_string = msclr::interop::marshal_as< std::string >( function);
				T  tUnits = T(0.0);
				exprtk::symbol_table<T> symbol_table;
				symbol_table.add_variable("units",tUnits);
				tUnits=units;
				exprtk::expression<T> expression;
				expression.register_symbol_table(symbol_table);

				exprtk::parser<T> parser;
			   parser.compile(expression_string,expression);
			  return expression.value();
			}
	public: double *powerCost(double area,double flow,double cells,double aspectratio,double power,double stacks,int system,int membrane)
{//calculates cost of power components (stack and pump). based on:
	//area - active cell area in m^2
	//flow - maximum flow rate in ml/min/cell
	//cells - cells per stack
	//aspect ratio - height to width
	//power - power of battery in W
	//stacks - stacks per battery
	//system - 0 for Fe-V, 1 for V-V
	//membrane - 0 for Daramic, 1 for Nafion
	double units=0;
	double *powerCost=new double[3];
	int i = system;
    double cellheight = sqrt(aspectratio*area);
    double cellwidth = cellheight/aspectratio;
    double Moverlap=Convert::ToDouble(MOBox->Text);
    double membranearea=(cellheight+Moverlap)*(cellwidth+Moverlap)*cells*stacks;
	double membranecost[3][3]={{CostTab(3,1,units),CostTab(2,1,units),CostTab(1,1,units)},{CostTab(3,0,units),CostTab(2,0,units),CostTab(1,0,units)},{43.06,75.35,107.64}}; //$/m^2
    double feltarea=area*cells*2*stacks;
	double feltcost[3]={CostTab(3,2,units),CostTab(2,2,units),CostTab(1,2,units)}; // $/m^2
    double framearea=(cellheight+Convert::ToDouble(FOHBox->Text))*(cellwidth+Convert::ToDouble(FOWBox->Text))*2*cells*stacks;
	double framecost[3]={CostTab(3,3,units),CostTab(2,3,units),CostTab(1,3,units)}; //$/m^2
    double bipolararea=framearea/2; // should be "area"
	double bipolarcost[3]={CostTab(3,4,units),CostTab(2,4,units),CostTab(1,4,units)};
	double HEX[3]={CostTab(3,5,units),CostTab(2,5,units),CostTab(1,5,units)}; //$/W
    double pcs[3]={CostTab(3,6,units),CostTab(2,6,units),CostTab(1,6,units)}; // $/W
    double GPM=flow*cells*stacks/(1000*3.78);
	double pumpBaseCost[3]={CostTab(3,7,units),CostTab(2,7,units),CostTab(1,7,units)};
	double pumpGPMCost[3]={CostTab(3,8,units),CostTab(2,8,units),CostTab(1,8,units)};
    double AIplates=cells*stacks/stacks*2;
	double AIplatecost[3]={CostTab(3,9,units),CostTab(2,9,units),CostTab(1,9,units)};
	int j = 0;
	while (j<3)
	{

    double totcost=AIplates*AIplatecost[j]+pcs[j]*power+(feltcost[j]*feltarea)+(membranearea*membranecost[membrane][j])+2*(pumpBaseCost[i]+pumpGPMCost[i]*GPM)+framearea*framecost[j]+bipolararea*bipolarcost[j];
	if(VVGen1->Checked)
	{
	totcost+=HEX[j]*power;
	}
	double other=1/0.982; //bolts, pvc, other minor costs
    totcost*=other;
	powerCost[j]=totcost;
	j++;
	}
    return powerCost;
}
	public: double *energyCost(double Veff,double DOD,double molarity,int system)
{//Calculates energy cost of battery in $/kWh.
	//Veff - average effective voltage in V.
	//DOD - depth of discharge, fraction
	//molarity - concentration, mol/L
	//system - 0 for Fe-V, 1 for V-V
	double n = Convert::ToDouble(electronBox->Text);
    const double F = 96485;
	double units;
	double chemcost[2][3]={{CostTab(3,10,units),CostTab(2,10,units),CostTab(1,10,units)},{CostTab(3,11,units),CostTab(2,11,units),CostTab(1,11,units)}}; //$/kg
    double chemMW[2]={181.88,162.2}; // g/mol
    double chemmult[2]={2,1};// mol e/mol
    double sythesis=0.98;
	double sythcost[3]={CostTab(3,12,units),CostTab(2,12,units),CostTab(1,12,units)}; //$/kg;
	double labourcost[3]={1,1,1};
	double chemtotal;
	double TEF = 1.25;
    double gallons=TEF*2*3600/(Veff*F*DOD*(molarity/1000)*3.78);
	double costpergallon[3]={CostTab(3,13,units),CostTab(2,13,units),CostTab(1,13,units)};
    double molH2SO4=3.8;
	double H2SO4cost[3]={CostTab(3,14,units)/(1000000),CostTab(2,14,units)/(1000000),CostTab(1,14,units)/(1000000)}; //$/g
	double H2SO4total[3];
	int i = 0;
	while (i<3)
	{
		H2SO4total[i]=98*H2SO4cost[i]*molH2SO4*2*3600/(Veff*F*DOD*(molarity/1000));
		i++;
	}
	double *energyCost=new double[3];
	i = 0;
	while (i<3)
	{
		if(system==0)
		{
			chemtotal=(2*chemMW[0]*(chemcost[0][i]+sythcost[i])*3600)/(Veff*F*chemmult[0]*DOD*sythesis)+2*chemMW[1]*chemcost[1][2]*3600/(Veff*F*chemmult[1]*DOD*sythesis);
		}
		if(system==1)
		{
			chemtotal=(2*chemMW[0]*(chemcost[0][i]+sythcost[i])*3600)/(Veff*F*chemmult[0]*DOD*sythesis);
		}
		energyCost[i]=chemtotal/n+costpergallon[i]*gallons+labourcost[i]+H2SO4total[i];
		i++;
	}
    return energyCost;
}
	public: double shuntLoss(double Vd,double area,double cwidth,double cdepth,double aspectratio,int channels,int cells)
{//Calculates shunt loss in Watts. uses finite difference method.
	//Vd - discharge voltage (V)
	//area - active cell area, m^2
	//cwidth - channel width, m
	//cdepth - channel depth, m
	//aspect ratio - height/width of cell
	//channels - number of flow channels in cell
	//cells - cells per stack
	double resistivity=0.05;//ohm m
	double length=sqrt(area/aspectratio);
	double carea=cdepth*cwidth*channels;
	double Rs=resistivity*length/carea;
	double Rm=resistivity*0.009/(0.0254*0.0254*3.14);
	double Ik=Vd/Rm;
	double r = sqrt(Rs/Rm);
	double powerLoss=0;
	double im;
	double is;
	for (double j = (-(cells-2)/2);j<=((cells-2)/2);j++)
	{
		im=Ik*(1-(cosh(j/r)/cosh(0.5*cells/r)));
		is=(Ik/r)*(sinh(j/r)/cosh(0.5*cells/r));
		powerLoss+=4*Rm*im*im+4*Rs*is*is;
	}
	return powerLoss;
}
	public: double pLoss(double area, double flow,double aspectratio, double cwidth, double cdepth,int channels)
{ //calculates power loss due to pressure drop in cell in W
    double width = sqrt(area/aspectratio); //cell width m
    double height = width*aspectratio;
	double Dh=2*cdepth*cwidth/(cdepth+cwidth);
	double carea=cdepth*cwidth;
    double Q = flow/(60*1000*1000); // m^3/s
    double K = 1.09438E-10; // m^2
	double visc = 6.60E-03;
	double tScaleFactor = Convert::ToDouble(ThicknessBox->Text);
	double t = 0.004*tScaleFactor;
	double Pdrop=0;
	if(interdigBox->Checked)
	{
		Pdrop=(Q/(t*width))*visc*width/K+32*width*Q*visc/(carea*Dh*Dh*channels);
	}
	else
	{
		Pdrop=(Q/(t*width))*visc*width/K+2*32*width*Q*visc/(carea*Dh*Dh*channels);
	}
  
	
    double PEff=0.67; // pump efficiency
    double powerLoss=Pdrop*Q/PEff;
    return powerLoss;
}
	public: void MarshalString ( String ^ s, string& os ) {
						//used to convert between managed and unmanaged strings
   using namespace Runtime::InteropServices;
   const char* chars = 
      (const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}		
	public: void MarshalString ( String ^ s, wstring& os ) {
					//used to convert between managed and unmanaged strings
   using namespace Runtime::InteropServices;
   const wchar_t* chars = 
      (const wchar_t*)(Marshal::StringToHGlobalUni(s)).ToPointer();
   os = chars;
   Marshal::FreeHGlobal(IntPtr((void*)chars));
}
	public: static double slope(double y2,double y1,double x2, double x1)
			{//calculates slope given 4 points.
				return (y2-y1)/(x2-x1);
			}
	public: int g_system;
	public: int g_membrane;
	public: double g_area;
	public: double g_jLow;
	public: double g_qhigh;
	public: double g_reqpower;
	public: double g_cells;
	public: double g_stacks;
	public: double g_reqpowerpercell;
	public: double g_DOD;
	public: double g_SOC;
	public: double g_aspectratio;
	public: double g_cwidth;
	public: double g_cdepth;
	public: double g_CE;
	public: double g_qhighpercurrent;
	public: int g_channels;
	public: int g_k;
	public: double g_power;
	public: double g_ep;
	public: bool g_areaReal;
	public: void global_initialization()
			{
				//temp
				g_k=2;
				g_jLow=Convert::ToDouble(testCurrent->Text);
				g_qhigh=Convert::ToDouble(testFlow->Text);
				g_qhighpercurrent=g_qhigh/g_jLow;
				g_DOD=(double)DODBox->Value;
				//end temp
				g_power=Convert::ToDouble(powerBox->Text)*1000;
				g_ep=Convert::ToDouble(epBox->Text);
				g_reqpower=Convert::ToDouble(powerBox->Text)*1000;
				g_cells=Convert::ToDouble(cellBox->Text);
				g_stacks=Convert::ToDouble(stackBox->Text);
				g_reqpowerpercell=g_reqpower/(g_cells*g_stacks);
				g_aspectratio=Convert::ToDouble(aspectRatioBox->Text);
				g_cwidth=0.005;
				g_cdepth=0.002;
				g_channels=10;
				g_CE=0.98;
				if(FeV->Checked)
	{
		g_system=0;
		g_membrane=0;
	}
	if(VVGen1->Checked || VVGen2->Checked)
	{
		g_system=1;
		g_membrane=1;
	}
	if(LiOrgButton->Checked)
	{
		g_system=1;
		g_membrane=1;
	}
			}
	public: void calculateArea(double jLow, double qhighpercurrent)
			{
				g_SOC = (100-g_DOD)/200;
				double V=g_voltage(g_SOC,1,10e9,jLow,g_aspectratio,g_system,g_membrane);
				g_area=g_reqpowerpercell/(10*jLow*V);
				double qhigh=qhighpercurrent*jLow;
				int i = 0;		
				double a;
				double b;
				double c;
				while (i<20)
				{
					V=g_voltage(g_SOC,g_area,qhigh*g_area,jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*jLow*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					if((4*a*c)>(b*b))
					{
						if(V==0)
						{
							while((4*a*c)>(b*b))
							{
								qhigh+=100;
								V=g_voltage(g_SOC,g_area,qhigh*g_area,jLow,g_aspectratio,g_system,g_membrane);
								a= pLoss(g_area,qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
								b=-10*jLow*V/sqrt(g_CE);
								c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

							}
							g_qhighpercurrent=qhigh/jLow;
						}
						else
						{
						MessageBox::Show("Fixing area!");
						g_areaReal=false;
						fixArea();
						}

					}
					
					g_area=(-b-sqrt(b*b-4*a*c))/(2*a);
					i++;

				}
				double power = V*10*g_jLow*g_area/sqrt(0.98) - a*g_area*g_area -shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
				testPowerNew->Text=power.ToString();
			}
	public: void fixArea()
			{
				double g_qhigh = g_qhighpercurrent*g_jLow;
				double a;
				double b;
				double c;
				double V=g_voltage(g_SOC,g_area,g_qhigh*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
				a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
				b=-10*g_jLow*V/sqrt(g_CE);
				c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
				double F = b*b-4*a*c;
				double hq=10;
				double hj=1;
				double F_f;
				double F_b;
				double D_qF;
				double D_qqF;
				double D_jF;
				double D_jjF;
				while(V<=0)
				{
					g_qhigh+=10;
					V=g_voltage(g_SOC,g_area,g_qhigh*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
				}
				V=g_voltage(g_SOC,g_area,g_qhigh*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
				a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
				b=-10*g_jLow*V/sqrt(g_CE);
				c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
				while(F<0)
				{

					V=g_voltage(g_SOC,g_area,g_qhigh*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*g_jLow*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

					F=b*b-4*a*c;

					V=g_voltage(g_SOC,g_area,(g_qhigh+hq)*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,(g_qhigh+hq)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*g_jLow*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					F_f=b*b-4*a*c;

					V=g_voltage(g_SOC,g_area,(g_qhigh-hq)*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,(g_qhigh-hq)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*g_jLow*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					F_b=b*b-4*a*c;

					D_qF = (F_f - F_b)/(2*hq);
					D_qqF = (F_f+F_b-2*F)/(hq*hq);
					g_qhigh-=D_qF/D_qqF;

					V=g_voltage(g_SOC,g_area,g_qhigh*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*g_jLow*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

					F=b*b-4*a*c;
					
					V=g_voltage(g_SOC,g_area,g_qhigh*g_area,(g_jLow+hj),g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*(g_jLow+hj)*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

					F_f=b*b-4*a*c;

					V=g_voltage(g_SOC,g_area,g_qhigh*g_area,(g_jLow-hj),g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*(g_jLow-hj)*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

					F_b=b*b-4*a*c;

					D_jF = (F_f - F_b)/(2*hj);
					D_jjF = (F_f + F_b - 2*F)/(hj*hj);
					if(D_jjF!=0)
					{
					g_jLow-=0.1*D_jF/D_jjF;
					}


					MessageBox::Show(F.ToString() +"," + g_qhigh.ToString()+"," + g_jLow.ToString()+"," + V.ToString());
					
					
				}
				
				g_qhighpercurrent=g_qhigh/g_jLow;

			}

	public: double calculateCost(double jLow, double qhighpercurrent)
			{
				calculateArea(jLow,qhighpercurrent);
				if(!g_areaReal)
				{
					return 999999;
				}
				double VeffAvg=calculateVeffAvg(jLow,qhighpercurrent);
				double pcost=powerCost(g_area,qhighpercurrent*jLow,g_cells,g_aspectratio,g_power,g_stacks,g_system,g_membrane)[g_k]*1000/g_power;
				double ecost=energyCost(VeffAvg,g_DOD/100,1500,g_system)[g_k];
				double totcost=pcost/g_ep+ecost;
				return totcost;
			}
	public: double D_xcostoverD_xxcost(double % x, double jLow, double qhighpercurrent)
			{
				g_qhighpercurrent=qhighpercurrent;
				g_jLow=jLow;
				g_qhigh=g_qhighpercurrent*g_jLow;
				g_areaReal=true;
				double h = 0.1;
				double cost = calculateCost(g_jLow,g_qhighpercurrent);
				if(!g_areaReal)
				{
					return 0;
				}
				(x)-=(h);
				double costB=calculateCost(g_jLow,g_qhighpercurrent);
				if(!g_areaReal)
				{
					return 0;
				}
				(x)+=(2*h);
				double costF=calculateCost(g_jLow,g_qhighpercurrent);
				if(!g_areaReal)
				{
					return 0;
				}
				double D_xcost = (costF-costB)/(2*h);
				double D_xxcost = (costF+costB-2*cost)/(h*h);
				//testGrid->Rows->Add(cost,x-h,costB,costF);
				return (D_xcost/D_xxcost);
			}
	public: double optimizeFlow(double j,double flow, double SOC)
			{
				double V;
				double VEff;
				double VEffF;
				double VEffB;
				bool optFlow=false;
				double powerproduced;
				double powerloss;
				double flowres=1;
				double D_flowVeff;
				double D_flow2Veff;
				while((!optFlow))
				{
						V=g_voltage(SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEff = V*(powerproduced-powerloss)/powerproduced;
						V=g_voltage(SOC,g_area,(flow+flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,(flow+flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEffF = V*(powerproduced-powerloss)/powerproduced;
						V=g_voltage(SOC,g_area,(flow-flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,(flow-flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEffB = V*(powerproduced-powerloss)/powerproduced;
						D_flowVeff=(VEffF-VEffB)/(2*flowres);
						D_flow2Veff=(VEffF+VEffB-2*VEff)/(flowres*flowres);
						flow-=(D_flowVeff/D_flow2Veff);
						if(abs(D_flowVeff/D_flow2Veff)<=0.01)
						{
							optFlow=true;
						}
				}
				if (flow>=g_qhighpercurrent*g_jLow)
				{

				}
				return flow;
			}
	public: double calculateVeffAvg(double jLow, double qhighpercurrent)
			{
				double delSOC = 0.01;
				double SOCLow = (100-g_DOD)/200;
				double SOCHigh = 1.0000001-SOCLow;
				double flow=qhighpercurrent*jLow;
				double V;
				double VEff;
				bool powerAttained;
				double j = jLow;
				double jres=0.01;
				double VEffAvg=0;
				double power;
				V=g_voltage(SOCLow,g_area,flow*g_area,jLow,g_aspectratio,g_system,g_membrane);
				VEff =V*(V*j*g_area*10-pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)-shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells))/(V*j*g_area*10);
				VEffAvg+=VEff;
				int i = 1;

				double SOC = SOCLow+delSOC;
				double powerproduced;
				double powerloss;
				double D_jP;
				double Pb;
				while (SOC<= SOCHigh)
				{
					powerAttained=false;
					while(!powerAttained)


					{
					flow=optimizeFlow(j,flow,SOC);
					V=g_voltage(SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
					powerproduced=V*j*g_area*10;
					powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					VEff =V*(powerproduced-powerloss)/powerproduced;
					power = powerproduced-powerloss;
					flow=optimizeFlow(j-jres,flow,SOC);
					V=g_voltage(SOC,g_area,flow*g_area,(j-jres),g_aspectratio,g_system,g_membrane);
					powerproduced=V*(j-jres)*g_area*10;
					powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					Pb=powerproduced-powerloss;
					D_jP=((power-Pb)/jres);
					j-=((power-g_reqpowerpercell)/D_jP);
					if(abs((power-g_reqpowerpercell)/D_jP)<=0.001)
					{
						powerAttained=true;
					}
					}
					i++;
					VEffAvg+=VEff;
					SOC+=delSOC;
				}
				VEffAvg/=i;
				return VEffAvg;
			}
 	private: System::Void calculate_Click(System::Object^  sender, System::EventArgs^  e) {
	//This executes when the calculate button is clicked, this is the bulk of the program.

	dataOutput->Rows->Clear();
	bestTable->Rows->Clear();
	costChart->Series[0]->Points->Clear();
	int system; // 0 for Fe-V, 1 for V-V
	int membrane; // 0 for Daramic, 1 for Nafion, 2 for IEX
	if(FeV->Checked)
	{
		system=0;
		membrane=0;
	}
	if(VVGen1->Checked || VVGen2->Checked)
	{
		system=1;
		membrane=1;
	}
	if(LiOrgButton->Checked)
	{
		system=1;
		membrane=1;
	}

	double SOCLow=(100-(double)DODBox->Value)/200;
	double battime=Convert::ToDouble(epBox->Text);
	double SOC=SOCLow;
	double SOCHigh=1.0001-SOCLow;
	double jres=0.1;
	double j=jres;
	double areares=0.01;
	double SOCres=0.01;
	double highflow=0;
	double flow=0;
	double optFlow=0;
	double flowres=0;
	double flowdensres=0.001;
	double area=areares;
	double V=0;
	double VEff=0;
	double optV=0;
	double power=Convert::ToDouble(powerBox->Text)*1000;
	double cells=Convert::ToDouble(cellBox->Text);	
	double stacks=Convert::ToDouble(stackBox->Text);
	double jLow=(double)jLowBox->Value;
	double jHigh=(double)jHighBox->Value;
	double jLowRes=5;
	progressBar->Value=0;
	progressBar->Maximum=((jHigh-jLow)/jLowRes);
	double cellPower=power/(cells*stacks);
	double aspectratio=Convert::ToDouble(aspectRatioBox->Text);
	double digitSep = Convert::ToDouble(channelSepBox->Text);
	int digits=1;
	double powerloss=0;
	double powerproduced=0;
	double prevPower=0;
	bool optflow;
	double Vavg;
	double pcost[3];
	double ecost[3];
	double totcost[3];
	int i=0;
	int k=0;
	int h=0;
	int z=0;
	double units=0;
	typedef exprtk::expression<double>     expression_t;

	double manucost=0;
	double bestpcost[3]={0,0,0};
	double bestecost[3]={0,0,0};
	double besttcost[3]={0,0,0};
	double bestj[3]={0,0,0};
	double lastj=0;
	double flowavg=0;
	double CE[3]={0.90,0.98,0.95};
	bool powerAttained=false;
	double cdepth=0.002;//0.002//m
	double cwidth=0.005;//m
	double pumpEff;
	double shuntEff;
	double electrochemEff;
	double pumpEffAvg;
	double shuntEffAvg;
	double electrochemEffAvg;
	double Kred=2.4886;//2.4886
	double jCap[3]={300,180,100};
	double pDropFactor =  Convert::ToDouble(PBox->Text);
	int channels=10;
	vector<vector<double> > dataMatrix;
	vector<vector<vector<double> > > SuperMatrix;
	vector<double> J;
	double iflow=Convert::ToDouble(flowBox->Text);

	if(SplineButton->Checked)
	{
		//loads spline interpolation
	i=0;
	k=0;
	vector<double> X1;
	string file;
	if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{	
	String^ filename=openFileDialog1->FileName;
	MarshalString(filename,file);
	}
	else
	{
		return;
	}

	vector<vector<double> > dataMatrix=fileRead(file);
	vector<vector<double> > YMatrix;
	i=1;
	while(i<dataMatrix[0].size())
	{
		X1.push_back(dataMatrix[0][i]);
		i++;
	}
	i=1;
	while(i<dataMatrix.size())
	{
		k=1;
		J.push_back(dataMatrix[i][0]);
		YMatrix.resize(YMatrix.size()+1);
		while(k<dataMatrix[0].size())
		{
			YMatrix[i-1].push_back(dataMatrix[i][k]);
			k++;
		}
		i++;
	}
	vector<vector<double> > VMatrix;
	
	i=0;
	while(i<YMatrix.size())
	{
		VMatrix=populateSpline2V(X1,YMatrix[i]);
		SuperMatrix.push_back(VMatrix);
		i++;
	}
	}
	double prevpowerloss;
	double powerslope;
	double cellheight;
	double cellwidth;
	double flowcap = Convert::ToDouble(flowCapBox->Text);
	while(jLow<=jHigh)
	{
	i=0;
	Vavg=0;
	SOC=SOCLow;
	flowavg=0;
	pumpEffAvg=0;
	shuntEffAvg=0;
	electrochemEffAvg=0;
	while (SOC<=SOCHigh)
	{
		if(SOC==SOCLow)
		{
			j=jLow;
			V=voltage(SOC,1,10e9,j,aspectratio,system,membrane,SuperMatrix,J);
			area=cellPower/(10*j*V);
			if (area<=0)
			{
				MessageBox::Show("Cannot produce the required power at the following current: " +j+ " mA/cm^2. This current may be too high. Try adjusting current density range.");
				return;
			}
			
		}
		prevPower=0;
		powerAttained=false;
		while(!powerAttained)
		{
			flowres=area*100*100*flowdensres;
			optflow=false;
			optV=0;
			flow=flowres;
			powerproduced=0;
			prevpowerloss=0;
			if(interdigBox->Checked)
			{
			cellwidth = sqrt(area/aspectratio);
			cellheight = sqrt(area*aspectratio);
			digits = cellheight/digitSep;
			if(digits%2==0)
			{
				digits--;
			}
			channels=1;
			}
			while(!optflow)
			{
				if(SplineButton->Checked)
				{
					flow=iflow*area*100*100*j/1000;
					optflow=true;
				}
				V=voltage(SOC,area,flow,j,aspectratio,system,membrane,SuperMatrix,J);
				powerloss=pLoss(area,flow,aspectratio,cwidth,cdepth,channels);
				if(interdigBox->Checked)
				{
					V=voltage(SOC,area/digits,flow/digits,j,1/(aspectratio*digits),system,membrane,SuperMatrix,J);
					powerloss = digits*pLoss(area/digits,flow/digits,1/(aspectratio*digits),cwidth,cdepth,channels);
					if ((flow/area)>=flowcap)
					{
						optflow=true;
					}
				}
				powerslope=slope(V*10*j*area,powerproduced,powerloss,prevpowerloss);

				if((powerslope<1)&&(V>0)&&(VEff=0))
				{

					MessageBox::Show("Can't support this current!");
					return;

				}
				powerproduced=V*j*10*area;
			
				if((powerproduced-powerloss)>0)
				{
					VEff=V*(powerproduced-powerloss)/powerproduced;
				}
				else
				{
					VEff=0;
				}
				if(VEff>=optV)
				{
					optV=VEff;
					flow+=flowres;
					
				}
				else
				{
					
					optflow=true;
				}
				prevpowerloss=powerloss;
			}
			if(interdigBox->Checked)
			{
			powerloss*=1/(aspectratio*digits*digits);
			}
			powerloss*=pDropFactor;
			pumpEff=powerloss/powerproduced;
			shuntEff=shuntLoss(V,area,cwidth,cdepth,aspectratio,channels,cells)/(cells*powerproduced);
			electrochemEff=1-(V/voltage(SOC,area,flow,0,aspectratio,system,membrane,SuperMatrix,J));

			powerloss+=(shuntLoss(V,area,cwidth,cdepth,aspectratio,channels,cells)/(cells));
			VEff=V*(powerproduced*sqrt(CE[membrane])-powerloss)/powerproduced;
			if(SOC==SOCLow)
			{
				
				
				if(j*VEff*area*10>=cellPower)
				{
					powerAttained=true;
					testPowerOrig->Text=(j*VEff*area*10).ToString();
					highflow=flow;
				}
				else
				{

						areares=0.0005;
						if(j*VEff*area*10>=prevPower)
						{
							prevPower=j*VEff*area*10;
							if(prevPower*2<cellPower)
							{
								area*=cellPower/prevPower;
							}
							else
							{
							area+=areares;
							}
						}
						else
						{
							if(V*j>((j+jres)*voltage(SOC,area,flow,j+jres,aspectratio,system,membrane,SuperMatrix,J)))
							{
							MessageBox::Show("Cannot produce the required power at the following current: " +j+ " mA/cm^2. This current may be too high. Try adjusting current density range.");
							}
							else
							{
							MessageBox::Show("Cannot produce the required power at the following current: " +j+ " mA/cm^2. This current may be too low. Try adjusting current density range.");
							}
							return;
						}
						
						/*
						if(abs(cellPower-prevPower)>(cellPower*0.5))
						{
						area*=cellPower/prevPower;
						}
						else
						{
							if(prevPower>cellPower)
							{
								area-=areares;
							}
							else
							{
								area+=areares;
							}
						}*/

					

				
				}
				
			}
			else
			{
				if(constpower->Checked)
				{
				if(j*VEff*area*10<=cellPower)
				{
					powerAttained=true;
					
				}
				else
				{
					j-=jres;
				}
				}
				else
				{
					powerAttained=true;
				}
			}
			

		}

		pumpEffAvg+=pumpEff;
		shuntEffAvg+=shuntEff;
		electrochemEffAvg+=electrochemEff;
		
		Vavg+=VEff;
		i++;
		OutputGrid->Rows->Add(SOC,flow,j,VEff,powerproduced*sqrt(CE[membrane])-powerloss);
		SOC+=SOCres;;
	
		flowavg+=flow;
	}
	
	flowavg/=i;
	Vavg/=i;
	pumpEffAvg/=i;
	shuntEffAvg/=i;
	electrochemEffAvg/=i;
	k = 0;
	while (k<3)
	{
	pcost[k]=powerCost(area,highflow,cells,aspectratio,power,stacks,system,membrane)[k]*1000/power;
	ecost[k]=energyCost(Vavg,SOCHigh-SOCLow,1500,system)[k];
	totcost[k]=pcost[k]/battime+ecost[k];
	k++;
	}
	
	k=0;
	while(k<3)
	{

		if(((jLow<=jCap[k]) && (totcost[k] < besttcost[k])) || besttcost[k]==0)
		{
			bestj[k]=jLow;

			besttcost[k]=totcost[k];
			bestecost[k]=ecost[k];
			bestpcost[k]=pcost[k];

			

		}
		k++;
	}
	k=0;
	costChart->Series[0]->Points->AddXY(jLow,totcost[2]);
	progressBar->Increment(1);
	double onewayEff=1-pumpEffAvg-shuntEffAvg-electrochemEffAvg;
	dataOutput->Rows->Add(jLow,totcost[2].ToString("C"),totcost[1].ToString("C"),totcost[0].ToString("C"),Vavg.ToString("F3"),area.ToString("F4"),onewayEff.ToString("F3"),ecost[2].ToString("C"),ecost[1].ToString("C"),ecost[0].ToString("C"),pcost[2].ToString("C"),pcost[1].ToString("C"),pcost[0].ToString("C"),electrochemEffAvg,pumpEffAvg,shuntEffAvg,area,flowavg,highflow);
	jLow+=jLowRes;
	}
	bestTable->Rows->Add("High current density",bestj[2],bestj[1],bestj[0]);
	bestTable->Rows->Add("Total $/kWh",besttcost[2].ToString("C"),besttcost[1].ToString("C"),besttcost[0].ToString("C"));
	bestTable->Rows->Add("Energy $/kWh",bestecost[2].ToString("C"),bestecost[1].ToString("C"),bestecost[0].ToString("C"));
	bestTable->Rows->Add("Power $/kW",bestpcost[2].ToString("C"),bestpcost[1].ToString("C"),bestpcost[0].ToString("C"));
				 
			 }
private: System::Void epBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 //Runs when energy to power ratio box is changed to update energy box
			 double power = Convert::ToDouble(powerBox->Text);
			 double ep = Convert::ToDouble(epBox->Text);
			 energyBox->Text=(power*ep).ToString();
		 }
private: System::Void energyBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 //Runs when energy box is changed to update energy to power ratio box
			 double power = Convert::ToDouble(powerBox->Text);
			 double energy = Convert::ToDouble(energyBox->Text);
			 epBox->Text=(energy/power).ToString();
		 }
private: System::Void jHighBox_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 if ((jHighBox->Value)<(jLowBox->Value))
			 {
				 jLowBox->Value=(jHighBox->Value);
			 }
		 }
private: System::Void jLowBox_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 if ((jHighBox->Value)<(jLowBox->Value))
			 {
				 jHighBox->Value=(jLowBox->Value);
			 }
		 }
private: System::Void dataOutput_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 global_initialization();
			 int i = 0;
			 g_qhigh=Convert::ToDouble(testFlow->Text);
			 g_jLow=Convert::ToDouble(testCurrent->Text);
			 g_qhighpercurrent=g_qhigh/g_jLow;
			 double cost = calculateCost(g_jLow,g_qhighpercurrent);
			 double delcost=cost;


			 while (abs(delcost)>=0.0001)
			 {

				 MessageBox::Show("Cost: " + cost);
				 g_qhighpercurrent-=D_xcostoverD_xxcost((g_qhighpercurrent),g_jLow,g_qhighpercurrent);


				 g_jLow-=D_xcostoverD_xxcost((g_jLow),g_jLow,g_qhighpercurrent);


				 delcost=calculateCost(g_jLow,g_qhighpercurrent)-cost;
				 cost=cost + delcost;
				 
				 testGrid->Rows->Add(cost,g_jLow,(g_qhighpercurrent*g_jLow));
				 i++;
			 }
			 testBox->Text=cost.ToString();
		 }
};
}

