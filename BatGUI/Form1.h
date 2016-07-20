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
#include <algorithm> 
#include <vector>
#include <cliext/vector>
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
	using namespace System::Threading;
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

	private: System::Windows::Forms::DataVisualization::Charting::Chart^  costChart;
	private: System::Windows::Forms::TabPage^  tabPage2;
	private: System::Windows::Forms::DataGridView^  dataOutput;



















	private: System::Windows::Forms::TabPage^  tabPage1;
	private: System::Windows::Forms::Label^  label81;//label is inert text to define each textbox; there will be a label called label 81
	private: System::Windows::Forms::TextBox^  electronBox;//look under forms directory for Textbox^ and make text box called electronBox; there will be a textbox called electronBox
	private: System::Windows::Forms::TextBox^  LiVoltageBox;

	private: System::Windows::Forms::TextBox^  channelSepBox;

	private: System::Windows::Forms::TextBox^  FOWBox;
	private: System::Windows::Forms::TextBox^  FOHBox;
	private: System::Windows::Forms::TextBox^  MOBox;
	private: System::Windows::Forms::TextBox^  ThRedBox;
	private: System::Windows::Forms::TextBox^  PBox;
	private: System::Windows::Forms::TextBox^  KBox;
	private: System::Windows::Forms::TextBox^  ThicknessBox;
	private: System::Windows::Forms::TextBox^  CondBox;
	private: System::Windows::Forms::Label^  label51;

	private: System::Windows::Forms::Label^  label89;
	private: System::Windows::Forms::CheckBox^  interdigBox;

	private: System::Windows::Forms::Label^  label21;
	private: System::Windows::Forms::Label^  label19;
	private: System::Windows::Forms::Label^  label20;
	private: System::Windows::Forms::Label^  label18;
	private: System::Windows::Forms::Label^  label17;
	private: System::Windows::Forms::Label^  label16;
	private: System::Windows::Forms::Label^  textasf;
			 //Initializing panel 6 in GUI



	private: System::Windows::Forms::Panel^  panel5;
	private: System::Windows::Forms::RadioButton^  SplineButton;
	private: System::Windows::Forms::RadioButton^  ECModelButton;
	private: System::Windows::Forms::Panel^  panel4;
	private: System::Windows::Forms::RadioButton^  constcurrent;
	private: System::Windows::Forms::RadioButton^  constpower;
	private: System::Windows::Forms::DataGridView^  bestTable;




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

			 //there will be a button called calculate










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


private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  dataGridViewTextBoxColumn3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column30;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column31;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column33;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column34;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column35;
private: System::Windows::Forms::Panel^  panel7;

private: System::Windows::Forms::Label^  label31;
private: System::Windows::Forms::Label^  label30;
private: System::Windows::Forms::TextBox^  currentMinBox;
private: System::Windows::Forms::TextBox^  currentMaxBox;
private: System::Windows::Forms::TextBox^  currentValueBox;
private: System::Windows::Forms::CheckBox^  optCurrentBox;
private: System::Windows::Forms::Label^  label34;
private: System::Windows::Forms::Label^  label33;
private: System::Windows::Forms::TextBox^  DODMinBox;

private: System::Windows::Forms::TextBox^  DODMaxBox;

private: System::Windows::Forms::TextBox^  DODValueBox;
private: System::Windows::Forms::CheckBox^  optDODBox;


private: System::Windows::Forms::Label^  label32;
private: System::Windows::Forms::TextBox^  flowMinBox;

private: System::Windows::Forms::TextBox^  flowMaxBox;

private: System::Windows::Forms::TextBox^  flowValueBox;
private: System::Windows::Forms::CheckBox^  optFlowBox;


private: System::Windows::Forms::Label^  label35;
private: System::Windows::Forms::TextBox^  ARMinBox;
private: System::Windows::Forms::TextBox^  ARMaxBox;
private: System::Windows::Forms::TextBox^  ARValueBox;
private: System::Windows::Forms::CheckBox^  optARBox;
private: System::Windows::Forms::Label^  label36;
private: System::Windows::Forms::Label^  label37;
private: System::Windows::Forms::TextBox^  interpolationFileBox;
private: System::Windows::Forms::Button^  button2;
private: System::Windows::Forms::RadioButton^  InterpolationButton3d;
private: System::Windows::Forms::Label^  label38;
private: System::Windows::Forms::TextBox^  Int3dVBox;


private: System::Windows::Forms::TextBox^  Int3dFlowBox;
private: System::Windows::Forms::TextBox^  Int3dJBox;
private: System::Windows::Forms::Label^  label39;
private: System::Windows::Forms::Label^  label40;
private: System::Windows::Forms::Label^  label41;
private: System::Windows::Forms::TextBox^  Int3dSOCBox;

private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::TextBox^  PSlopeBox;
private: System::Windows::Forms::Label^  label42;
private: System::Windows::Forms::DataGridView^  componentCostGrid;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column27;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column28;
private: System::Windows::Forms::CheckBox^  stoichFlowBox;
private: System::Windows::Forms::Label^  label1;
private: System::Windows::Forms::TextBox^  gammaBox;
private: System::Windows::Forms::RadioButton^  FeCr;
private: System::Windows::Forms::TextBox^  FlowChanMinBox;
private: System::Windows::Forms::TextBox^  FlowChanMaxBox;
private: System::Windows::Forms::TextBox^  flowChanValueBox;
private: System::Windows::Forms::CheckBox^  optFlowChanBox;
private: System::Windows::Forms::Label^  label2;
private: System::Windows::Forms::DataGridView^  PerformanceTest;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column29;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column32;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column36;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column37;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column38;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column39;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column40;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column41;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column42;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column43;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column44;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column45;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column46;



private: System::Windows::Forms::TabPage^  tabPage3;
private: System::Windows::Forms::TabPage^  tabpage4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column1;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column2;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column3;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column4;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column5;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column6;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column7;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column8;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column9;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column19;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column17;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column18;
private: System::Windows::Forms::DataGridViewTextBoxColumn^  Column20;












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
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->gammaBox = (gcnew System::Windows::Forms::TextBox());
			this->stoichFlowBox = (gcnew System::Windows::Forms::CheckBox());
			this->componentCostGrid = (gcnew System::Windows::Forms::DataGridView());
			this->Column27 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column28 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->PSlopeBox = (gcnew System::Windows::Forms::TextBox());
			this->label42 = (gcnew System::Windows::Forms::Label());
			this->panel7 = (gcnew System::Windows::Forms::Panel());
			this->FlowChanMinBox = (gcnew System::Windows::Forms::TextBox());
			this->FlowChanMaxBox = (gcnew System::Windows::Forms::TextBox());
			this->flowChanValueBox = (gcnew System::Windows::Forms::TextBox());
			this->optFlowChanBox = (gcnew System::Windows::Forms::CheckBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->ARMinBox = (gcnew System::Windows::Forms::TextBox());
			this->ARMaxBox = (gcnew System::Windows::Forms::TextBox());
			this->ARValueBox = (gcnew System::Windows::Forms::TextBox());
			this->optARBox = (gcnew System::Windows::Forms::CheckBox());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->flowMinBox = (gcnew System::Windows::Forms::TextBox());
			this->flowMaxBox = (gcnew System::Windows::Forms::TextBox());
			this->flowValueBox = (gcnew System::Windows::Forms::TextBox());
			this->optFlowBox = (gcnew System::Windows::Forms::CheckBox());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->DODMinBox = (gcnew System::Windows::Forms::TextBox());
			this->DODMaxBox = (gcnew System::Windows::Forms::TextBox());
			this->DODValueBox = (gcnew System::Windows::Forms::TextBox());
			this->optDODBox = (gcnew System::Windows::Forms::CheckBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->currentMinBox = (gcnew System::Windows::Forms::TextBox());
			this->currentMaxBox = (gcnew System::Windows::Forms::TextBox());
			this->currentValueBox = (gcnew System::Windows::Forms::TextBox());
			this->optCurrentBox = (gcnew System::Windows::Forms::CheckBox());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->spaBox = (gcnew System::Windows::Forms::TextBox());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->LiConcBox = (gcnew System::Windows::Forms::TextBox());
			this->label81 = (gcnew System::Windows::Forms::Label());
			this->electronBox = (gcnew System::Windows::Forms::TextBox());
			this->LiVoltageBox = (gcnew System::Windows::Forms::TextBox());
			this->channelSepBox = (gcnew System::Windows::Forms::TextBox());
			this->FOWBox = (gcnew System::Windows::Forms::TextBox());
			this->FOHBox = (gcnew System::Windows::Forms::TextBox());
			this->MOBox = (gcnew System::Windows::Forms::TextBox());
			this->ThRedBox = (gcnew System::Windows::Forms::TextBox());
			this->PBox = (gcnew System::Windows::Forms::TextBox());
			this->KBox = (gcnew System::Windows::Forms::TextBox());
			this->ThicknessBox = (gcnew System::Windows::Forms::TextBox());
			this->CondBox = (gcnew System::Windows::Forms::TextBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->label89 = (gcnew System::Windows::Forms::Label());
			this->interdigBox = (gcnew System::Windows::Forms::CheckBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->textasf = (gcnew System::Windows::Forms::Label());
			this->panel5 = (gcnew System::Windows::Forms::Panel());
			this->InterpolationButton3d = (gcnew System::Windows::Forms::RadioButton());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->interpolationFileBox = (gcnew System::Windows::Forms::TextBox());
			this->SplineButton = (gcnew System::Windows::Forms::RadioButton());
			this->ECModelButton = (gcnew System::Windows::Forms::RadioButton());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->constcurrent = (gcnew System::Windows::Forms::RadioButton());
			this->constpower = (gcnew System::Windows::Forms::RadioButton());
			this->bestTable = (gcnew System::Windows::Forms::DataGridView());
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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->FeCr = (gcnew System::Windows::Forms::RadioButton());
			this->LiOrgButton = (gcnew System::Windows::Forms::RadioButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->VVGen2 = (gcnew System::Windows::Forms::RadioButton());
			this->VVGen1 = (gcnew System::Windows::Forms::RadioButton());
			this->FeV = (gcnew System::Windows::Forms::RadioButton());
			this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			this->tabpage4 = (gcnew System::Windows::Forms::TabPage());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->PerformanceTest = (gcnew System::Windows::Forms::DataGridView());
			this->Column29 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column32 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column36 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column37 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column38 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column39 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column40 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column41 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column42 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column43 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column44 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column45 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column46 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->Int3dVBox = (gcnew System::Windows::Forms::TextBox());
			this->Int3dFlowBox = (gcnew System::Windows::Forms::TextBox());
			this->Int3dJBox = (gcnew System::Windows::Forms::TextBox());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label41 = (gcnew System::Windows::Forms::Label());
			this->Int3dSOCBox = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->testGrid = (gcnew System::Windows::Forms::DataGridView());
			this->dataGridViewTextBoxColumn2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->dataGridViewTextBoxColumn3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column30 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column31 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column33 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column34 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column35 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
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
			this->Column19 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column17 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column18 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->Column20 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->componentCostGrid))->BeginInit();
			this->panel7->SuspendLayout();
			this->panel5->SuspendLayout();
			this->panel4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bestTable))->BeginInit();
			this->panel3->SuspendLayout();
			this->panel1->SuspendLayout();
			this->tabControl1->SuspendLayout();
			this->tabpage4->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PerformanceTest))->BeginInit();
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
			this->tabPage5->Size = System::Drawing::Size(886, 459);
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
			this->tabPage3->Size = System::Drawing::Size(886, 459);
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
			this->tabPage2->Size = System::Drawing::Size(886, 459);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Raw Data";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// dataOutput
			// 
			this->dataOutput->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->dataOutput->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(9) {this->Column1, this->Column2, 
				this->Column3, this->Column4, this->Column5, this->Column6, this->Column7, this->Column8, this->Column9});
			this->dataOutput->Location = System::Drawing::Point(6, 6);
			this->dataOutput->Name = L"dataOutput";
			this->dataOutput->Size = System::Drawing::Size(877, 343);
			this->dataOutput->TabIndex = 0;
			// 
			// Column1
			// 
			this->Column1->HeaderText = L"SOC";
			this->Column1->Name = L"Column1";
			this->Column1->Width = 50;
			// 
			// Column2
			// 
			this->Column2->HeaderText = L"Power/cell (W)";
			this->Column2->Name = L"Column2";
			this->Column2->Width = 50;
			// 
			// Column3
			// 
			this->Column3->HeaderText = L"Pumping loss/cell (W)";
			this->Column3->Name = L"Column3";
			this->Column3->Width = 50;
			// 
			// Column4
			// 
			this->Column4->HeaderText = L"Shunt loss/ cell (W)";
			this->Column4->Name = L"Column4";
			this->Column4->Width = 50;
			// 
			// Column5
			// 
			this->Column5->HeaderText = L"Average Effective Voltage";
			this->Column5->Name = L"Column5";
			this->Column5->ToolTipText = L"OCV (V)";
			this->Column5->Width = 50;
			// 
			// Column6
			// 
			this->Column6->HeaderText = L"Voltage (V)";
			this->Column6->Name = L"Column6";
			this->Column6->Width = 50;
			// 
			// Column7
			// 
			this->Column7->HeaderText = L"V Effective (V)";
			this->Column7->Name = L"Column7";
			this->Column7->Width = 60;
			// 
			// Column8
			// 
			this->Column8->HeaderText = L"Current (mA/cm^2)";
			this->Column8->Name = L"Column8";
			this->Column8->Width = 50;
			// 
			// Column9
			// 
			this->Column9->HeaderText = L"Flow rate (ml/min/cell)";
			this->Column9->Name = L"Column9";
			this->Column9->Width = 50;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->gammaBox);
			this->tabPage1->Controls->Add(this->stoichFlowBox);
			this->tabPage1->Controls->Add(this->componentCostGrid);
			this->tabPage1->Controls->Add(this->PSlopeBox);
			this->tabPage1->Controls->Add(this->label42);
			this->tabPage1->Controls->Add(this->panel7);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->label23);
			this->tabPage1->Controls->Add(this->spaBox);
			this->tabPage1->Controls->Add(this->label22);
			this->tabPage1->Controls->Add(this->LiConcBox);
			this->tabPage1->Controls->Add(this->label81);
			this->tabPage1->Controls->Add(this->electronBox);
			this->tabPage1->Controls->Add(this->LiVoltageBox);
			this->tabPage1->Controls->Add(this->channelSepBox);
			this->tabPage1->Controls->Add(this->FOWBox);
			this->tabPage1->Controls->Add(this->FOHBox);
			this->tabPage1->Controls->Add(this->MOBox);
			this->tabPage1->Controls->Add(this->ThRedBox);
			this->tabPage1->Controls->Add(this->PBox);
			this->tabPage1->Controls->Add(this->KBox);
			this->tabPage1->Controls->Add(this->ThicknessBox);
			this->tabPage1->Controls->Add(this->CondBox);
			this->tabPage1->Controls->Add(this->label51);
			this->tabPage1->Controls->Add(this->label89);
			this->tabPage1->Controls->Add(this->interdigBox);
			this->tabPage1->Controls->Add(this->label21);
			this->tabPage1->Controls->Add(this->label19);
			this->tabPage1->Controls->Add(this->label20);
			this->tabPage1->Controls->Add(this->label18);
			this->tabPage1->Controls->Add(this->label17);
			this->tabPage1->Controls->Add(this->label16);
			this->tabPage1->Controls->Add(this->textasf);
			this->tabPage1->Controls->Add(this->panel5);
			this->tabPage1->Controls->Add(this->panel4);
			this->tabPage1->Controls->Add(this->bestTable);
			this->tabPage1->Controls->Add(this->panel3);
			this->tabPage1->Controls->Add(this->panel1);
			this->tabPage1->Location = System::Drawing::Point(4, 22);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(886, 459);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Main";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(704, 434);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(43, 13);
			this->label1->TabIndex = 63;
			this->label1->Text = L"Gamma";
			// 
			// gammaBox
			// 
			this->gammaBox->Location = System::Drawing::Point(753, 431);
			this->gammaBox->Name = L"gammaBox";
			this->gammaBox->Size = System::Drawing::Size(65, 20);
			this->gammaBox->TabIndex = 62;
			this->gammaBox->Text = L"0.1";
			// 
			// stoichFlowBox
			// 
			this->stoichFlowBox->AutoSize = true;
			this->stoichFlowBox->Location = System::Drawing::Point(128, 319);
			this->stoichFlowBox->Name = L"stoichFlowBox";
			this->stoichFlowBox->Size = System::Drawing::Size(109, 17);
			this->stoichFlowBox->TabIndex = 61;
			this->stoichFlowBox->Text = L"Stoichmetric Flow";
			this->stoichFlowBox->UseVisualStyleBackColor = true;
			// 
			// componentCostGrid
			// 
			this->componentCostGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->componentCostGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {this->Column27, 
				this->Column28});
			this->componentCostGrid->Location = System::Drawing::Point(257, 346);
			this->componentCostGrid->Name = L"componentCostGrid";
			this->componentCostGrid->Size = System::Drawing::Size(301, 107);
			this->componentCostGrid->TabIndex = 60;
			// 
			// Column27
			// 
			this->Column27->HeaderText = L"Component";
			this->Column27->Name = L"Column27";
			// 
			// Column28
			// 
			this->Column28->HeaderText = L"Cost ($/kWh)";
			this->Column28->Name = L"Column28";
			// 
			// PSlopeBox
			// 
			this->PSlopeBox->Location = System::Drawing::Point(753, 357);
			this->PSlopeBox->Name = L"PSlopeBox";
			this->PSlopeBox->Size = System::Drawing::Size(65, 20);
			this->PSlopeBox->TabIndex = 59;
			this->PSlopeBox->Text = L"0";
			// 
			// label42
			// 
			this->label42->AutoSize = true;
			this->label42->Location = System::Drawing::Point(653, 361);
			this->label42->Name = L"label42";
			this->label42->Size = System::Drawing::Size(97, 13);
			this->label42->TabIndex = 58;
			this->label42->Text = L"Scale PDrop Slope";
			// 
			// panel7
			// 
			this->panel7->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel7->Controls->Add(this->FlowChanMinBox);
			this->panel7->Controls->Add(this->FlowChanMaxBox);
			this->panel7->Controls->Add(this->flowChanValueBox);
			this->panel7->Controls->Add(this->optFlowChanBox);
			this->panel7->Controls->Add(this->label2);
			this->panel7->Controls->Add(this->ARMinBox);
			this->panel7->Controls->Add(this->ARMaxBox);
			this->panel7->Controls->Add(this->ARValueBox);
			this->panel7->Controls->Add(this->optARBox);
			this->panel7->Controls->Add(this->label36);
			this->panel7->Controls->Add(this->flowMinBox);
			this->panel7->Controls->Add(this->flowMaxBox);
			this->panel7->Controls->Add(this->flowValueBox);
			this->panel7->Controls->Add(this->optFlowBox);
			this->panel7->Controls->Add(this->label35);
			this->panel7->Controls->Add(this->DODMinBox);
			this->panel7->Controls->Add(this->DODMaxBox);
			this->panel7->Controls->Add(this->DODValueBox);
			this->panel7->Controls->Add(this->optDODBox);
			this->panel7->Controls->Add(this->label32);
			this->panel7->Controls->Add(this->currentMinBox);
			this->panel7->Controls->Add(this->currentMaxBox);
			this->panel7->Controls->Add(this->currentValueBox);
			this->panel7->Controls->Add(this->optCurrentBox);
			this->panel7->Controls->Add(this->label34);
			this->panel7->Controls->Add(this->label33);
			this->panel7->Controls->Add(this->label31);
			this->panel7->Controls->Add(this->label30);
			this->panel7->Location = System::Drawing::Point(3, 157);
			this->panel7->Name = L"panel7";
			this->panel7->Size = System::Drawing::Size(457, 157);
			this->panel7->TabIndex = 57;
			this->panel7->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &Form1::panel7_Paint);
			// 
			// FlowChanMinBox
			// 
			this->FlowChanMinBox->Location = System::Drawing::Point(389, 128);
			this->FlowChanMinBox->Name = L"FlowChanMinBox";
			this->FlowChanMinBox->ReadOnly = true;
			this->FlowChanMinBox->Size = System::Drawing::Size(58, 20);
			this->FlowChanMinBox->TabIndex = 40;
			this->FlowChanMinBox->Text = L"1";
			// 
			// FlowChanMaxBox
			// 
			this->FlowChanMaxBox->Location = System::Drawing::Point(313, 128);
			this->FlowChanMaxBox->Name = L"FlowChanMaxBox";
			this->FlowChanMaxBox->ReadOnly = true;
			this->FlowChanMaxBox->Size = System::Drawing::Size(58, 20);
			this->FlowChanMaxBox->TabIndex = 39;
			this->FlowChanMaxBox->Text = L"40";
			// 
			// flowChanValueBox
			// 
			this->flowChanValueBox->Location = System::Drawing::Point(164, 128);
			this->flowChanValueBox->Name = L"flowChanValueBox";
			this->flowChanValueBox->Size = System::Drawing::Size(58, 20);
			this->flowChanValueBox->TabIndex = 38;
			this->flowChanValueBox->Text = L"5";
			// 
			// optFlowChanBox
			// 
			this->optFlowChanBox->AutoSize = true;
			this->optFlowChanBox->Location = System::Drawing::Point(230, 130);
			this->optFlowChanBox->Name = L"optFlowChanBox";
			this->optFlowChanBox->Size = System::Drawing::Size(66, 17);
			this->optFlowChanBox->TabIndex = 37;
			this->optFlowChanBox->Text = L"Optimize";
			this->optFlowChanBox->UseVisualStyleBackColor = true;
			this->optFlowChanBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::optFlowChanBox_CheckedChanged);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(25, 130);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(127, 13);
			this->label2->TabIndex = 36;
			this->label2->Text = L"Flow Channel Width (mm)";
			// 
			// ARMinBox
			// 
			this->ARMinBox->Location = System::Drawing::Point(389, 103);
			this->ARMinBox->Name = L"ARMinBox";
			this->ARMinBox->ReadOnly = true;
			this->ARMinBox->Size = System::Drawing::Size(58, 20);
			this->ARMinBox->TabIndex = 35;
			this->ARMinBox->Text = L"0.25";
			// 
			// ARMaxBox
			// 
			this->ARMaxBox->Location = System::Drawing::Point(313, 103);
			this->ARMaxBox->Name = L"ARMaxBox";
			this->ARMaxBox->ReadOnly = true;
			this->ARMaxBox->Size = System::Drawing::Size(58, 20);
			this->ARMaxBox->TabIndex = 34;
			this->ARMaxBox->Text = L"4";
			// 
			// ARValueBox
			// 
			this->ARValueBox->Location = System::Drawing::Point(164, 103);
			this->ARValueBox->Name = L"ARValueBox";
			this->ARValueBox->Size = System::Drawing::Size(58, 20);
			this->ARValueBox->TabIndex = 33;
			this->ARValueBox->Text = L"1";
			// 
			// optARBox
			// 
			this->optARBox->AutoSize = true;
			this->optARBox->Location = System::Drawing::Point(230, 105);
			this->optARBox->Name = L"optARBox";
			this->optARBox->Size = System::Drawing::Size(66, 17);
			this->optARBox->TabIndex = 32;
			this->optARBox->Text = L"Optimize";
			this->optARBox->UseVisualStyleBackColor = true;
			this->optARBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::optARBox_CheckedChanged);
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Location = System::Drawing::Point(25, 105);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(136, 13);
			this->label36->TabIndex = 31;
			this->label36->Text = L"Aspect Ratio (width/height)";
			// 
			// flowMinBox
			// 
			this->flowMinBox->Location = System::Drawing::Point(389, 50);
			this->flowMinBox->Name = L"flowMinBox";
			this->flowMinBox->Size = System::Drawing::Size(58, 20);
			this->flowMinBox->TabIndex = 30;
			this->flowMinBox->Text = L"0";
			// 
			// flowMaxBox
			// 
			this->flowMaxBox->Location = System::Drawing::Point(313, 50);
			this->flowMaxBox->Name = L"flowMaxBox";
			this->flowMaxBox->Size = System::Drawing::Size(58, 20);
			this->flowMaxBox->TabIndex = 29;
			this->flowMaxBox->Text = L"1000";
			// 
			// flowValueBox
			// 
			this->flowValueBox->Location = System::Drawing::Point(164, 49);
			this->flowValueBox->Name = L"flowValueBox";
			this->flowValueBox->Size = System::Drawing::Size(58, 20);
			this->flowValueBox->TabIndex = 28;
			this->flowValueBox->Text = L"5";
			// 
			// optFlowBox
			// 
			this->optFlowBox->AutoSize = true;
			this->optFlowBox->Checked = true;
			this->optFlowBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->optFlowBox->Location = System::Drawing::Point(230, 52);
			this->optFlowBox->Name = L"optFlowBox";
			this->optFlowBox->Size = System::Drawing::Size(66, 17);
			this->optFlowBox->TabIndex = 27;
			this->optFlowBox->Text = L"Optimize";
			this->optFlowBox->UseVisualStyleBackColor = true;
			this->optFlowBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::optFlowBox_CheckedChanged);
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Location = System::Drawing::Point(6, 53);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(153, 13);
			this->label35->TabIndex = 26;
			this->label35->Text = L"Low SOC Flow Rate (ml/min-A)";
			// 
			// DODMinBox
			// 
			this->DODMinBox->Location = System::Drawing::Point(389, 78);
			this->DODMinBox->Name = L"DODMinBox";
			this->DODMinBox->Size = System::Drawing::Size(58, 20);
			this->DODMinBox->TabIndex = 25;
			this->DODMinBox->Text = L"0";
			// 
			// DODMaxBox
			// 
			this->DODMaxBox->Location = System::Drawing::Point(313, 78);
			this->DODMaxBox->Name = L"DODMaxBox";
			this->DODMaxBox->Size = System::Drawing::Size(58, 20);
			this->DODMaxBox->TabIndex = 24;
			this->DODMaxBox->Text = L"100";
			// 
			// DODValueBox
			// 
			this->DODValueBox->Location = System::Drawing::Point(164, 78);
			this->DODValueBox->Name = L"DODValueBox";
			this->DODValueBox->Size = System::Drawing::Size(58, 20);
			this->DODValueBox->TabIndex = 23;
			this->DODValueBox->Text = L"70";
			// 
			// optDODBox
			// 
			this->optDODBox->AutoSize = true;
			this->optDODBox->Checked = true;
			this->optDODBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->optDODBox->Location = System::Drawing::Point(230, 80);
			this->optDODBox->Name = L"optDODBox";
			this->optDODBox->Size = System::Drawing::Size(66, 17);
			this->optDODBox->TabIndex = 22;
			this->optDODBox->Text = L"Optimize";
			this->optDODBox->UseVisualStyleBackColor = true;
			this->optDODBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::optDODBox_CheckedChanged);
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Location = System::Drawing::Point(79, 81);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(81, 13);
			this->label32->TabIndex = 21;
			this->label32->Text = L"SOC Range (%)";
			// 
			// currentMinBox
			// 
			this->currentMinBox->Location = System::Drawing::Point(389, 25);
			this->currentMinBox->Name = L"currentMinBox";
			this->currentMinBox->Size = System::Drawing::Size(58, 20);
			this->currentMinBox->TabIndex = 20;
			this->currentMinBox->Text = L"50";
			// 
			// currentMaxBox
			// 
			this->currentMaxBox->Location = System::Drawing::Point(313, 25);
			this->currentMaxBox->Name = L"currentMaxBox";
			this->currentMaxBox->Size = System::Drawing::Size(58, 20);
			this->currentMaxBox->TabIndex = 19;
			this->currentMaxBox->Text = L"400";
			// 
			// currentValueBox
			// 
			this->currentValueBox->Location = System::Drawing::Point(164, 23);
			this->currentValueBox->Name = L"currentValueBox";
			this->currentValueBox->Size = System::Drawing::Size(58, 20);
			this->currentValueBox->TabIndex = 18;
			this->currentValueBox->Text = L"320";
			this->currentValueBox->TextChanged += gcnew System::EventHandler(this, &Form1::currentValueBox_TextChanged);
			// 
			// optCurrentBox
			// 
			this->optCurrentBox->AutoSize = true;
			this->optCurrentBox->Checked = true;
			this->optCurrentBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->optCurrentBox->Location = System::Drawing::Point(230, 27);
			this->optCurrentBox->Name = L"optCurrentBox";
			this->optCurrentBox->Size = System::Drawing::Size(66, 17);
			this->optCurrentBox->TabIndex = 17;
			this->optCurrentBox->Text = L"Optimize";
			this->optCurrentBox->UseVisualStyleBackColor = true;
			this->optCurrentBox->CheckedChanged += gcnew System::EventHandler(this, &Form1::optCurrentBox_CheckedChanged);
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label34->Location = System::Drawing::Point(399, 0);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(30, 17);
			this->label34->TabIndex = 16;
			this->label34->Text = L"Min";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label33->Location = System::Drawing::Point(327, 0);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(33, 17);
			this->label33->TabIndex = 15;
			this->label33->Text = L"Max";
			this->label33->Click += gcnew System::EventHandler(this, &Form1::label33_Click);
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Location = System::Drawing::Point(14, 28);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(144, 13);
			this->label31->TabIndex = 13;
			this->label31->Text = L"Low SOC Current (mA/cm^2)";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label30->Location = System::Drawing::Point(2, 0);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(81, 17);
			this->label30->TabIndex = 12;
			this->label30->Text = L"Parameters";
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button1->Location = System::Drawing::Point(753, 223);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(125, 30);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Calculate";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click);
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Location = System::Drawing::Point(647, 412);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(100, 13);
			this->label23->TabIndex = 55;
			this->label23->Text = L"Scale Specific Area";
			// 
			// spaBox
			// 
			this->spaBox->Location = System::Drawing::Point(753, 409);
			this->spaBox->Name = L"spaBox";
			this->spaBox->Size = System::Drawing::Size(65, 20);
			this->spaBox->TabIndex = 54;
			this->spaBox->Text = L"1";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Location = System::Drawing::Point(651, 386);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(96, 13);
			this->label22->TabIndex = 53;
			this->label22->Text = L"Nonaqueous Conc";
			// 
			// LiConcBox
			// 
			this->LiConcBox->Location = System::Drawing::Point(753, 383);
			this->LiConcBox->Name = L"LiConcBox";
			this->LiConcBox->Size = System::Drawing::Size(65, 20);
			this->LiConcBox->TabIndex = 52;
			this->LiConcBox->Text = L"1000";
			// 
			// label81
			// 
			this->label81->AutoSize = true;
			this->label81->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label81->Location = System::Drawing::Point(120, 390);
			this->label81->Name = L"label81";
			this->label81->Size = System::Drawing::Size(67, 17);
			this->label81->TabIndex = 51;
			this->label81->Text = L"Electrons";
			// 
			// electronBox
			// 
			this->electronBox->Location = System::Drawing::Point(198, 389);
			this->electronBox->Name = L"electronBox";
			this->electronBox->Size = System::Drawing::Size(50, 20);
			this->electronBox->TabIndex = 50;
			this->electronBox->Text = L"1";
			// 
			// LiVoltageBox
			// 
			this->LiVoltageBox->Location = System::Drawing::Point(198, 364);
			this->LiVoltageBox->Name = L"LiVoltageBox";
			this->LiVoltageBox->Size = System::Drawing::Size(50, 20);
			this->LiVoltageBox->TabIndex = 48;
			this->LiVoltageBox->Text = L"1.94";
			// 
			// channelSepBox
			// 
			this->channelSepBox->Location = System::Drawing::Point(105, 341);
			this->channelSepBox->Name = L"channelSepBox";
			this->channelSepBox->Size = System::Drawing::Size(50, 20);
			this->channelSepBox->TabIndex = 43;
			this->channelSepBox->Text = L"0.06";
			// 
			// FOWBox
			// 
			this->FOWBox->Location = System::Drawing::Point(570, 318);
			this->FOWBox->Name = L"FOWBox";
			this->FOWBox->Size = System::Drawing::Size(65, 20);
			this->FOWBox->TabIndex = 38;
			this->FOWBox->Text = L"0.05";
			// 
			// FOHBox
			// 
			this->FOHBox->Location = System::Drawing::Point(570, 293);
			this->FOHBox->Name = L"FOHBox";
			this->FOHBox->Size = System::Drawing::Size(65, 20);
			this->FOHBox->TabIndex = 36;
			this->FOHBox->Text = L"0.14";
			// 
			// MOBox
			// 
			this->MOBox->Location = System::Drawing::Point(570, 267);
			this->MOBox->Name = L"MOBox";
			this->MOBox->Size = System::Drawing::Size(65, 20);
			this->MOBox->TabIndex = 34;
			this->MOBox->Text = L"0.038";
			// 
			// ThRedBox
			// 
			this->ThRedBox->Location = System::Drawing::Point(824, 285);
			this->ThRedBox->Name = L"ThRedBox";
			this->ThRedBox->Size = System::Drawing::Size(31, 20);
			this->ThRedBox->TabIndex = 33;
			this->ThRedBox->Text = L"1";
			this->ThRedBox->Visible = false;
			// 
			// PBox
			// 
			this->PBox->Location = System::Drawing::Point(753, 336);
			this->PBox->Name = L"PBox";
			this->PBox->Size = System::Drawing::Size(65, 20);
			this->PBox->TabIndex = 31;
			this->PBox->Text = L"1";
			this->PBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Right;
			// 
			// KBox
			// 
			this->KBox->Location = System::Drawing::Point(753, 311);
			this->KBox->Name = L"KBox";
			this->KBox->Size = System::Drawing::Size(65, 20);
			this->KBox->TabIndex = 29;
			this->KBox->Text = L"1";
			// 
			// ThicknessBox
			// 
			this->ThicknessBox->Location = System::Drawing::Point(753, 285);
			this->ThicknessBox->Name = L"ThicknessBox";
			this->ThicknessBox->Size = System::Drawing::Size(65, 20);
			this->ThicknessBox->TabIndex = 27;
			this->ThicknessBox->Text = L"0.35";
			// 
			// CondBox
			// 
			this->CondBox->Location = System::Drawing::Point(753, 259);
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
			this->label51->Location = System::Drawing::Point(6, 364);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(197, 17);
			this->label51->TabIndex = 49;
			this->label51->Text = L"Nonaqueous OCV (50% SOC)";
			// 
			// label89
			// 
			this->label89->AutoSize = true;
			this->label89->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label89->Location = System::Drawing::Point(10, 341);
			this->label89->Name = L"label89";
			this->label89->Size = System::Drawing::Size(89, 17);
			this->label89->TabIndex = 44;
			this->label89->Text = L"Channel Sep";
			// 
			// interdigBox
			// 
			this->interdigBox->AutoSize = true;
			this->interdigBox->Checked = true;
			this->interdigBox->CheckState = System::Windows::Forms::CheckState::Checked;
			this->interdigBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->interdigBox->Location = System::Drawing::Point(13, 317);
			this->interdigBox->Name = L"interdigBox";
			this->interdigBox->Size = System::Drawing::Size(109, 21);
			this->interdigBox->TabIndex = 42;
			this->interdigBox->Text = L"Interdigitated";
			this->interdigBox->UseVisualStyleBackColor = true;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Location = System::Drawing::Point(478, 321);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(90, 13);
			this->label21->TabIndex = 39;
			this->label21->Text = L"Frame Overlap W";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(478, 296);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(87, 13);
			this->label19->TabIndex = 37;
			this->label19->Text = L"Frame Overlap H";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(467, 270);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(97, 13);
			this->label20->TabIndex = 35;
			this->label20->Text = L"Membrane Overlap";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(673, 340);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(67, 13);
			this->label18->TabIndex = 32;
			this->label18->Text = L"Scale PDrop";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(673, 314);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(74, 13);
			this->label17->TabIndex = 30;
			this->label17->Text = L"Scale Kinetics";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(661, 288);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(86, 13);
			this->label16->TabIndex = 28;
			this->label16->Text = L"Scale Thickness";
			// 
			// textasf
			// 
			this->textasf->AutoSize = true;
			this->textasf->Location = System::Drawing::Point(675, 262);
			this->textasf->Name = L"textasf";
			this->textasf->Size = System::Drawing::Size(72, 13);
			this->textasf->TabIndex = 26;
			this->textasf->Text = L"Scale E Cond";
			// 
			// panel5
			// 
			this->panel5->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel5->Controls->Add(this->InterpolationButton3d);
			this->panel5->Controls->Add(this->button2);
			this->panel5->Controls->Add(this->label37);
			this->panel5->Controls->Add(this->interpolationFileBox);
			this->panel5->Controls->Add(this->SplineButton);
			this->panel5->Controls->Add(this->ECModelButton);
			this->panel5->Location = System::Drawing::Point(319, 9);
			this->panel5->Name = L"panel5";
			this->panel5->Size = System::Drawing::Size(132, 142);
			this->panel5->TabIndex = 22;
			// 
			// InterpolationButton3d
			// 
			this->InterpolationButton3d->AutoSize = true;
			this->InterpolationButton3d->Location = System::Drawing::Point(4, 43);
			this->InterpolationButton3d->Name = L"InterpolationButton3d";
			this->InterpolationButton3d->Size = System::Drawing::Size(98, 17);
			this->InterpolationButton3d->TabIndex = 60;
			this->InterpolationButton3d->TabStop = true;
			this->InterpolationButton3d->Text = L"3d Interpolation";
			this->InterpolationButton3d->UseVisualStyleBackColor = true;
			this->InterpolationButton3d->Visible = false;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(3, 117);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 20);
			this->button2->TabIndex = 59;
			this->button2->Text = L"Load File";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label37->Location = System::Drawing::Point(3, 63);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(112, 17);
			this->label37->TabIndex = 36;
			this->label37->Text = L"Interpolation File";
			// 
			// interpolationFileBox
			// 
			this->interpolationFileBox->Location = System::Drawing::Point(3, 91);
			this->interpolationFileBox->Name = L"interpolationFileBox";
			this->interpolationFileBox->Size = System::Drawing::Size(117, 20);
			this->interpolationFileBox->TabIndex = 58;
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
			this->SplineButton->CheckedChanged += gcnew System::EventHandler(this, &Form1::SplineButton_CheckedChanged);
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
			this->panel4->Location = System::Drawing::Point(470, 217);
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
			this->constpower->Location = System::Drawing::Point(4, 3);
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
			this->bestTable->Size = System::Drawing::Size(414, 209);
			this->bestTable->TabIndex = 20;
			this->bestTable->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::bestTable_CellContentClick);
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
			this->panel3->Size = System::Drawing::Size(196, 145);
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
			this->powerBox->TextChanged += gcnew System::EventHandler(this, &Form1::powerBox_TextChanged);
			// 
			// panel1
			// 
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->FeCr);
			this->panel1->Controls->Add(this->LiOrgButton);
			this->panel1->Controls->Add(this->label4);
			this->panel1->Controls->Add(this->VVGen2);
			this->panel1->Controls->Add(this->VVGen1);
			this->panel1->Controls->Add(this->FeV);
			this->panel1->Location = System::Drawing::Point(3, 6);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(108, 145);
			this->panel1->TabIndex = 10;
			// 
			// FeCr
			// 
			this->FeCr->AutoSize = true;
			this->FeCr->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FeCr->Location = System::Drawing::Point(3, 104);
			this->FeCr->Name = L"FeCr";
			this->FeCr->Size = System::Drawing::Size(61, 21);
			this->FeCr->TabIndex = 13;
			this->FeCr->Text = L"Fe-Cr";
			this->FeCr->UseVisualStyleBackColor = true;
			// 
			// LiOrgButton
			// 
			this->LiOrgButton->AutoSize = true;
			this->LiOrgButton->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->LiOrgButton->Location = System::Drawing::Point(3, 82);
			this->LiOrgButton->Name = L"LiOrgButton";
			this->LiOrgButton->Size = System::Drawing::Size(107, 21);
			this->LiOrgButton->TabIndex = 12;
			this->LiOrgButton->Text = L"Nonaqueous";
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
			this->tabControl1->Controls->Add(this->tabpage4);
			this->tabControl1->Location = System::Drawing::Point(12, 12);
			this->tabControl1->Name = L"tabControl1";
			this->tabControl1->RightToLeftLayout = true;
			this->tabControl1->SelectedIndex = 0;
			this->tabControl1->Size = System::Drawing::Size(894, 485);
			this->tabControl1->TabIndex = 18;
			// 
			// tabpage4
			// 
			this->tabpage4->Controls->Add(this->button4);
			this->tabpage4->Controls->Add(this->PerformanceTest);
			this->tabpage4->Controls->Add(this->label38);
			this->tabpage4->Controls->Add(this->Int3dVBox);
			this->tabpage4->Controls->Add(this->Int3dFlowBox);
			this->tabpage4->Controls->Add(this->Int3dJBox);
			this->tabpage4->Controls->Add(this->label39);
			this->tabpage4->Controls->Add(this->label40);
			this->tabpage4->Controls->Add(this->label41);
			this->tabpage4->Controls->Add(this->Int3dSOCBox);
			this->tabpage4->Controls->Add(this->button3);
			this->tabpage4->Controls->Add(this->testGrid);
			this->tabpage4->Controls->Add(this->label29);
			this->tabpage4->Controls->Add(this->testVEff);
			this->tabpage4->Controls->Add(this->testPowerOrig);
			this->tabpage4->Controls->Add(this->testPowerNew);
			this->tabpage4->Controls->Add(this->label27);
			this->tabpage4->Controls->Add(this->label28);
			this->tabpage4->Controls->Add(this->testFlow);
			this->tabpage4->Controls->Add(this->testCurrent);
			this->tabpage4->Controls->Add(this->label26);
			this->tabpage4->Controls->Add(this->label25);
			this->tabpage4->Controls->Add(this->label24);
			this->tabpage4->Controls->Add(this->testBox);
			this->tabpage4->Location = System::Drawing::Point(4, 22);
			this->tabpage4->Name = L"tabpage4";
			this->tabpage4->Padding = System::Windows::Forms::Padding(3);
			this->tabpage4->Size = System::Drawing::Size(886, 459);
			this->tabpage4->TabIndex = 5;
			this->tabpage4->Text = L"Test tab";
			this->tabpage4->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(261, 456);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(75, 23);
			this->button4->TabIndex = 68;
			this->button4->Text = L"Test";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::button4_Click);
			// 
			// PerformanceTest
			// 
			this->PerformanceTest->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->PerformanceTest->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(13) {this->Column29, 
				this->Column32, this->Column36, this->Column37, this->Column38, this->Column39, this->Column40, this->Column41, this->Column42, 
				this->Column43, this->Column44, this->Column45, this->Column46});
			this->PerformanceTest->Location = System::Drawing::Point(261, 318);
			this->PerformanceTest->Name = L"PerformanceTest";
			this->PerformanceTest->Size = System::Drawing::Size(460, 131);
			this->PerformanceTest->TabIndex = 67;
			this->PerformanceTest->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &Form1::dataGridView1_CellContentClick);
			// 
			// Column29
			// 
			this->Column29->HeaderText = L"SOC";
			this->Column29->Name = L"Column29";
			// 
			// Column32
			// 
			this->Column32->HeaderText = L"teffpos";
			this->Column32->Name = L"Column32";
			// 
			// Column36
			// 
			this->Column36->HeaderText = L"teffneg";
			this->Column36->Name = L"Column36";
			// 
			// Column37
			// 
			this->Column37->HeaderText = L"SOCrxnpos";
			this->Column37->Name = L"Column37";
			// 
			// Column38
			// 
			this->Column38->HeaderText = L"SOCrxnneg";
			this->Column38->Name = L"Column38";
			// 
			// Column39
			// 
			this->Column39->HeaderText = L"V";
			this->Column39->Name = L"Column39";
			// 
			// Column40
			// 
			this->Column40->HeaderText = L"A";
			this->Column40->Name = L"Column40";
			// 
			// Column41
			// 
			this->Column41->HeaderText = L"B";
			this->Column41->Name = L"Column41";
			// 
			// Column42
			// 
			this->Column42->HeaderText = L"D";
			this->Column42->Name = L"Column42";
			// 
			// Column43
			// 
			this->Column43->HeaderText = L"G";
			this->Column43->Name = L"Column43";
			// 
			// Column44
			// 
			this->Column44->HeaderText = L"H";
			this->Column44->Name = L"Column44";
			// 
			// Column45
			// 
			this->Column45->HeaderText = L"tmin";
			this->Column45->Name = L"Column45";
			// 
			// Column46
			// 
			this->Column46->HeaderText = L"beta";
			this->Column46->Name = L"Column46";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Location = System::Drawing::Point(47, 475);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(14, 13);
			this->label38->TabIndex = 66;
			this->label38->Text = L"V";
			// 
			// Int3dVBox
			// 
			this->Int3dVBox->Location = System::Drawing::Point(94, 472);
			this->Int3dVBox->Name = L"Int3dVBox";
			this->Int3dVBox->Size = System::Drawing::Size(90, 20);
			this->Int3dVBox->TabIndex = 65;
			// 
			// Int3dFlowBox
			// 
			this->Int3dFlowBox->Location = System::Drawing::Point(95, 387);
			this->Int3dFlowBox->Name = L"Int3dFlowBox";
			this->Int3dFlowBox->Size = System::Drawing::Size(90, 20);
			this->Int3dFlowBox->TabIndex = 64;
			this->Int3dFlowBox->Text = L"5";
			// 
			// Int3dJBox
			// 
			this->Int3dJBox->Location = System::Drawing::Point(94, 413);
			this->Int3dJBox->Name = L"Int3dJBox";
			this->Int3dJBox->Size = System::Drawing::Size(90, 20);
			this->Int3dJBox->TabIndex = 63;
			this->Int3dJBox->Text = L"160";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Location = System::Drawing::Point(48, 395);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(26, 13);
			this->label39->TabIndex = 62;
			this->label39->Text = L"flow";
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Location = System::Drawing::Point(48, 420);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(40, 13);
			this->label40->TabIndex = 61;
			this->label40->Text = L"current";
			// 
			// label41
			// 
			this->label41->AutoSize = true;
			this->label41->Location = System::Drawing::Point(48, 449);
			this->label41->Name = L"label41";
			this->label41->Size = System::Drawing::Size(29, 13);
			this->label41->TabIndex = 60;
			this->label41->Text = L"SOC";
			// 
			// Int3dSOCBox
			// 
			this->Int3dSOCBox->Location = System::Drawing::Point(95, 446);
			this->Int3dSOCBox->Name = L"Int3dSOCBox";
			this->Int3dSOCBox->Size = System::Drawing::Size(90, 20);
			this->Int3dSOCBox->TabIndex = 59;
			this->Int3dSOCBox->Text = L"0.1";
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(40, 350);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(124, 24);
			this->button3->TabIndex = 58;
			this->button3->Text = L"Interpolation Test";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click);
			// 
			// testGrid
			// 
			this->testGrid->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->testGrid->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(8) {this->dataGridViewTextBoxColumn2, 
				this->dataGridViewTextBoxColumn4, this->dataGridViewTextBoxColumn3, this->Column30, this->Column31, this->Column33, this->Column34, 
				this->Column35});
			this->testGrid->Location = System::Drawing::Point(259, 96);
			this->testGrid->Name = L"testGrid";
			this->testGrid->Size = System::Drawing::Size(587, 182);
			this->testGrid->TabIndex = 57;
			// 
			// dataGridViewTextBoxColumn2
			// 
			this->dataGridViewTextBoxColumn2->HeaderText = L"Cost";
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
			this->Column30->HeaderText = L"DOD";
			this->Column30->Name = L"Column30";
			// 
			// Column31
			// 
			this->Column31->HeaderText = L"Power";
			this->Column31->Name = L"Column31";
			// 
			// Column33
			// 
			this->Column33->HeaderText = L"Power Cost";
			this->Column33->Name = L"Column33";
			// 
			// Column34
			// 
			this->Column34->HeaderText = L"Energy Cost";
			this->Column34->Name = L"Column34";
			// 
			// Column35
			// 
			this->Column35->HeaderText = L"VEffAvg";
			this->Column35->Name = L"Column35";
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
			// Column19
			// 
			this->Column19->HeaderText = L"Quantity";
			this->Column19->Name = L"Column19";
			this->Column19->Width = 120;
			// 
			// Column17
			// 
			this->Column17->HeaderText = L"Present";
			this->Column17->Name = L"Column17";
			this->Column17->Width = 80;
			// 
			// Column18
			// 
			this->Column18->HeaderText = L"Near Term";
			this->Column18->Name = L"Column18";
			this->Column18->Width = 80;
			// 
			// Column20
			// 
			this->Column20->HeaderText = L"Optimistic";
			this->Column20->Name = L"Column20";
			this->Column20->Width = 80;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(909, 504);
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->componentCostGrid))->EndInit();
			this->panel7->ResumeLayout(false);
			this->panel7->PerformLayout();
			this->panel5->ResumeLayout(false);
			this->panel5->PerformLayout();
			this->panel4->ResumeLayout(false);
			this->panel4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->bestTable))->EndInit();
			this->panel3->ResumeLayout(false);
			this->panel3->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->tabControl1->ResumeLayout(false);
			this->tabpage4->ResumeLayout(false);
			this->tabpage4->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->PerformanceTest))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->testGrid))->EndInit();
			this->ResumeLayout(false);

		}//GUI portion has ended
#pragma endregion
		public: void InitializeCostParameters()//InitializeCostParameters is a function that executes steps below
				{
								CostParameters->Rows->Add("Nafion Membrane","235","165","95","$/m^2");//0; CostParameters is a DatagridView
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
								CostParameters->Rows->Add("Chromium Chloride","3.2","2.9","2.6","$/kg");//15
								tabControl1->TabPages->Remove(tabPage3);
								tabControl1->TabPages->Remove(tabpage4);

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
		public: cliext::vector<cliext::vector<double > > cli_fileRead(string file)
{//reads CSV file
	ifstream datafile;
	datafile.open(file);
	string line;
	cliext::vector<cliext::vector<double > > datamatrix;
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
	
	datamatrix.at(i).push_back(atof(line.c_str()));
	
	j++;
	}
	datamatrix.resize(datamatrix.size()-1);
	datafile.close();
	return datamatrix;
}
		public: cliext::vector<cliext::vector<double> > cli_populateSpline2V(cliext::vector<double> X,cliext::vector<double> Y)
{//coming up with function that interpolates of dataset (Y vs X) using cubic splines
	

	cliext::vector<double> A;
	cliext::vector<double> C;
	cliext::vector<double> B;
	cliext::vector<double> D;
	const int m=(int) X.size();
	int n=m-1;
	int i=0;
	cliext::vector<cliext::vector<double> > splineMatrix;
	if(m==2)
	{

		B.push_back((Y.at(1)-Y.at(0))/(X.at(1)-X.at(0)));
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
	C.at(0)=0;
	while(i<n)
	{
		B.at(i)=2/((X.at(i+1)-X.at(i))/(Y.at(i+1)-Y.at(i))+(X.at(i)-X.at(i-1))/(Y.at(i)-Y.at(i-1)));
		i++;
	}
	B.at(0)=1.5*(Y.at(1)-Y.at(0))/(X.at(1)-X.at(0))-B.at(1)/2;
	B.at(n)=1.5*(Y.at(n)-Y.at(n-1))/(X.at(n)-X.at(n-1))-B.at(n-1)/2;
	D.at(0)=(B.at(1)-B.at(0)-2*C.at(0)*(X.at(1)-X.at(0)))/(3*pow(X.at(1)-X.at(0),2));
	i=1;
	while(i<n)
	{
		double delX=X.at(i+1)-X.at(i);
		double e = Y.at(i+1)-Y.at(i)-B.at(i)*delX;
		double f = B.at(i+1)-B.at(i);
		double a = delX*delX;
		double b = delX*delX*delX;
		double c = 2*delX;
		double d = 3*delX*delX;
		C.at(i)=(e*d-b*f)/(a*d-b*c);
		D.at(i)=(a*f-e*c)/(a*d-b*c);
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
		public: double cli_interpolate2dSpline(cliext::vector<cliext::vector<cliext::vector<double> > > SuperMatrix, cliext::vector<double> j,double x,double y)
{//get Y as f(2 independent variables)
	cliext::vector<double> X1;
	int i = 0;
	int size=SuperMatrix.size();
	while (i<size)
	{
		X1.push_back(cli_interpolateSplineV(x,SuperMatrix.at(i)));
		i++;
	}
	cliext::vector<cliext::vector<double > > Matrix=cli_populateSpline2V(j,X1);
	return cli_interpolateSplineV(y,Matrix);
}	
		public: double cli_interpolateSplineV(double x,cliext::vector<cliext::vector<double> > matrix)
{//uses above interpolation functions to get Y at some X
	int i = 0;
	double y=0;
	double delx;
	int size = matrix.at(0).size();
	while (i<size)
	{
		if(x>=matrix.at(0)[i])
		{
			
			delx = x-matrix.at(0)[i];
			y=matrix.at(1)[i]+matrix.at(2)[i]*delx+matrix.at(3)[i]*delx*delx+matrix.at(4)[i]*delx*delx*delx;
		}
		else if(x<matrix.at(0)[i])
		{
			break;
			
		}
		i++;
	}
	return y;
}		
		public: double asinh(double x)
{//mathematical function arc hyperbolic sine
    if(x>0)
        return log(x+sqrt(x*x+1));
    else
        return -log(x+sqrt(x*x+1));
}
	public: double g_voltage(double SOC, double area, double flow, double j,double aspectratio,int system, int membrane)
{
	if(area!=area)
	{
		return 0;
	}
	//electrochemical model
	//SOC as fraction
	//area is active cell area in m^2
	//flow is flow rate ml/min/cell
	//j is current density in mA/cm^2
	//aspect ratio is height:width  (height being the direction of flow)
	//system is 0 for Fe-V, 1 for V-V
	//membrane is 0 for Daramic, 1 for Nafion
	//SuperMatrix and J are used for spline extrapolation
	if(SplineButton->Checked)
	{

		return cli_interpolate2dSpline(g_SuperMatrix,g_J,SOC,j);
	}
	if(InterpolationButton3d->Checked)
	{
		if(g_area==0)
		{
		return Interpolation3d(g_3dFlowRange.at(g_3dFlowRange.size()-1),j,SOC);
		}
		else
		{
		return Interpolation3d(flow/g_area,j,SOC);
		}
	}
	int i = system; //0 for Fe-V, 1 for V-V
    const double F = 96485;// C/mol
    const double R = 8.314; // J/mol K
    double V;
    double width = sqrt(area/aspectratio); //cell width m
    double height = width*aspectratio;
	double V2 = 1.004; //V
//	V2[1]+=2;
	double V1=-.41; //V
    double Q = flow/(60*1000*1000); // m^3/s
	double TCent=45;
	double T = TCent+273.15; // K
    double Ci1 = 1750; // initial concentration of chemical 1, mol/m^3
	double pa=(26.94+6.63*SOC)*1.05; //S/m
	double pc=(27.96+20.57*SOC)*1.05; //S/m
	double kScaleFactor = Convert::ToDouble(KBox->Text);
	double condScaleFactor = Convert::ToDouble(CondBox->Text);
    double k1=kScaleFactor*8.7/1000000*exp((F*0.255/R)*(T-298)/(298*T));
	double k2=kScaleFactor*0.00000068*exp((F*V2/R)*(T-298)/(298*T));//{1.6/100000*exp((F*0.77/R)*(T-298)/(298*T)),0.00000068*exp((F*V2[i]/R)*(T-298)/(298*T))};
	if(VVGen1->Checked)
	{
		V2 = 1.004;
		V1=-.41;
		Ci1=1500;
		TCent=35;
		T = TCent+273.15;
		pa=(26.94+6.63*SOC); //S/m
		pc=(27.96+20.57*SOC); //S/m
		k1=kScaleFactor*8.7/1000000*exp((F*0.255/R)*(T-298)/(298*T));
		k2=kScaleFactor*0.00000068*exp((F*V2/R)*(T-298)/(298*T));
	}
	if(FeV->Checked)
	{
		V2=0.77;
		V1=-0.085;
		Ci1=1750;
		TCent=45;
		T = TCent+273.15;
		pa=50;
		pc=50;
		k1=kScaleFactor*8.7/1000000*exp((F*0.255/R)*(T-298)/(298*T));
		k2=kScaleFactor*1.6/100000*exp((F*0.77/R)*(T-298)/(298*T));
	}
	if(VVGen2->Checked)
	{
		V2 = 1.004;
		V1=-0.301630478;
		Ci1=2000;
		TCent=50;
		T = TCent+273.15;
		pa=(26.94+6.63*SOC)*1.05*condScaleFactor; //S/m
		pc=(27.96+20.57*SOC)*1.05*condScaleFactor; //S/m
		k1=kScaleFactor*3.55666666666667E-06;
		k2=kScaleFactor*7.06666666666667E-06;
	}
	if(LiOrgButton->Checked)
	{
		V2=Convert::ToDouble(LiVoltageBox->Text);
		V1=0;
		TCent=60;
		T = TCent+273.15;
		Ci1= Convert::ToDouble(LiConcBox->Text);
		pa = 10*condScaleFactor/(10); //S/m
		pc = pa;
		k1=kScaleFactor*3.55666666666667E-06;
		k2=kScaleFactor*7.06666666666667E-06;
	}

	double Ci2 = Ci1; // initial concentration of chemical 2, mol/m^3
	double tScaleFactor = Convert::ToDouble(ThicknessBox->Text);
    double t=0.0019*tScaleFactor; //cell thickness m
	double teff[2]={t,t};
    double I=j*width*height*100*100/1000; //current A
	//double A[2] = {2,4};
	//A[i]*= Convert::ToDouble(ThRedBox->Text);
	//double chi[2] = {4,0};
	double n = Convert::ToDouble(electronBox->Text);

    //double Inew=j*(1+chi[i]*delSOC*2)*100*100/1000;
    double eps=0.93; //porosity
    double a = 17000;//39000*eps/4;//CHECK THIS
	a*=Convert::ToDouble(spaBox->Text);
    double Km=0.00016*pow(100*Q/(eps*width*t),0.385);
	double C1=Ci1*SOC;
	double C2=Ci2*(1-SOC);
	double CT=j*10/(F*a*Km)+I*t/(n*Q*F);
	double A = R*T/F;
	double B[2] = {C1*C2*pow(2*a*F*k1/(j*100*100/1000),2),C1*C2*pow(2*a*F*k2/(j*100*100/1000),2)};
	double D[2] = {CT*(C1-C2)*pow(2*a*F*k1/(j*100*100/1000),2),CT*(C1-C2)*pow(2*a*F*k2/(j*100*100/1000),2)};
	double G[2] = {CT*CT*pow(2*a*F*k1/(j*100*100/1000),2),CT*CT*pow(2*a*F*k2/(j*100*100/1000),2)};
	double H[2] = {0.5*j*100*100/1000/pa,0.5*j*100*100/1000/pc};
	double tmin[2]={(-D[0]+sqrt(D[0]*D[0]+4*B[0]*G[0]))/(2*B[0]),(-D[1]+sqrt(D[1]*D[1]+4*B[1]*G[1]))/(2*B[1])};
	if(tmin[0]>t || tmin[1]>t)
	{
		return 0;
	}
	double beta[2]={sqrt(D[0]*D[0]+4*B[0]*G[0])/B[0],sqrt(D[1]*D[1]+4*B[1]*G[1])/B[1]};
	//minimization begins
	double alpha[2]={A/sqrt(B[0]),A/sqrt(B[1])};
	double x[2]={pow(0.5*alpha[0]/H[0]/sqrt(beta[0]),0.6666666667),pow(0.5*alpha[1]/H[1]/sqrt(beta[1]),0.6666666667)};
	double xi;

	int k=0;
	/*k=8;
	teff[0]=t;
	teff[1]=t;*/
	while(k<=7)
	{
	xi=x[0];
	x[0]=pow((2*H[0]/alpha[0])*sqrt((B[0]*x[0]*(beta[0]+x[0])+1)/(B[0]*x[0]))-1/sqrt(x[0]*(x[0]+beta[0])*(x[0]+beta[0])),-0.6666666667);
	xi=x[1];
	x[1]=pow((2*H[1]*sqrt(B[1])/A)*sqrt((B[1]*xi*(xi+beta[1])+1)/(B[1]*xi))-1/(sqrt(xi)*(xi+beta[1])),-0.6666666667);
	k++;
	}
	
	//minimization ends
	teff[0]=min(tmin[0]+x[0],t);
	teff[1]=min(tmin[1]+x[1],t);
	if(teff[0]!=teff[0])
	{
		teff[0]=t;
	}
	if(teff[1]!=teff[1])
	{
		teff[1]=t;
	}
	double delSOC[2]={I*t/(teff[0]*n*Q*Ci1*F),I*t/(teff[1]*n*Q*Ci1*F)};
	double SOCrxn[2]={SOC-delSOC[0],SOC-delSOC[1]};
	double Conc1neg=Ci1*SOCrxn[0]-j*10/(teff[0]*F*a*Km); // V 2+
    double Conc1pos=Ci1*(1-SOCrxn[0])+j*10/(teff[0]*F*a*Km); //V 3+
    double Conc2neg=Ci2*(1-SOCrxn[1])+j*10/(teff[1]*F*a*Km); //V 4+
    double Conc2pos=Ci2*SOCrxn[1]-j*10/(teff[1]*F*a*Km); // V 5+
	double etaneg=-R*T/F*asinh(j*10/(2*teff[0]*a*F*k1*kScaleFactor*sqrt(Conc1neg*Conc1pos)));
    double etapos=R*T/F*asinh(j*10/(2*teff[1]*a*F*k2*kScaleFactor*sqrt(Conc2neg*Conc2pos)));
	double Irea=teff[0]*0.5*j*100*100/1000/pa;
    double Irec=teff[1]*0.5*j*100*100/1000/pc;
	double mt[2]={450e-6,2*(25.4e-6)/*175e-6*/}; //membrane thickness m
	double condM[2]={23.0769,(0.5139*22-.326)*exp(1268*(T-303)/(T*303))};
    double IRM = (j*100*100/1000)*(mt[membrane])/(condM[membrane]);
	double iconcH[2]={5300,6000};
	double concH[2]={iconcH[0],iconcH[1]+Ci1*SOCrxn[1]-I/(t*F*a*Km)};
	/*double concCl[2]={1500,0};
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
	
	double pa=(F*F/(T*R))*(ZV2*ZV2*DV2*Conc1neg+ZV3*ZV3*DV3*Conc1pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i]);
    double pat=pa*(1+1.711464*(T-273-23)/100)*condScaleFactor;
	double pc[2]={(F*F/(T*R))*(ZFe2*ZFe2*DFe2*Conc2neg+ZFe3*ZFe3*DFe3*Conc2pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i]),(F*F/(T*R))*(ZV4*ZV4*DV4*Conc2neg+ZV5*ZV5*DV5*Conc2pos+ZH*ZH*DH*concH[i]+ZH2SO4*ZH2SO4*DH2SO4*concH2SO4[i]+ZCl*ZCl*DCl*concCl[i])};
    double pct=pc[i]*(1+1.711464*(T-273-23)/100)*condScaleFactor;*/

	g_etapos=etapos;
	g_etaneg=etaneg;
	g_Irea=Irea;
	g_Irec=Irec;
    if(Conc1neg*Conc2pos/(Conc1pos*Conc2neg)>0)
    {
    V = V2-V1+(R*T/F)*(log(Conc1neg*Conc2pos/(Conc1pos*Conc2neg))+2*log(concH[i]/1000))+etaneg-etapos-Irea-Irec-IRM;
    }
    else
    {
    V=0;
    }

	if(LiOrgButton->Checked)
	{
		/*double VLiA[] = {3.193552576,3.298606737,3.422420435,3.516218117,3.602508955,3.662540986,3.670044043,3.673797466,3.700060059,3.73382571,3.752585246,3.767595148,3.790104319,3.812617278,3.835126449,3.898911903,3.932295015,3.977286844,4.12524213,4.152428876};
		std::vector<double> VLi (&VLiA[0], &VLiA[0]+20);
		double SOCLiA[] = {0.009631481,0.015312908,0.026677674,0.039934338,0.05697862,0.085387667,0.115688613,0.168717178,0.195232417,0.252048601,0.316440021,0.388408589,0.469844291,0.538025241,0.600522852,0.674383318,0.721711346,0.797815335,0.972556012,1};
		std::vector<double> SOCLi (&SOCLiA[0], &SOCLiA[0]+20);
		std::vector<vector<double> > LiMatrix= populateSpline2V(SOCLi,VLi);*/
		double OCVLi = V2+(R*T/(1*F/2.9))*2*log(SOCrxn[0]/(1-SOCrxn[0]));//interpolateSplineV(SOC,LiMatrix)-3.8+Convert::ToDouble(LiVoltageBox->Text);
		
		//etaneg = 0;
		//etapos = 0;
 //temp
		condM[membrane]=0.32;//2.5/(10); //S/m
		//t=0.5/1000;
		Irea = t*I/pa/2;
		Irec = t*I/pc/2;
		mt[membrane]=25e-6;//7*(25e-6); // m
		IRM = 0.1*(j*100*100/1000)*(mt[membrane])/(condM[membrane]);
		V = OCVLi + etaneg-etapos-Irea-Irec-IRM;

	}
	if(Conc1neg<=0 || Conc2neg<=0 || Conc1pos<=0 || Conc2pos<=0)
	{
		V=0;
	}
	double scaleV=1/*1.138*/;
	//PerformanceTest->Rows->Add(V);
	//PerformanceTest->Rows->Add(SOC,SOCrxn[1],SOCrxn[0],teff[1],teff[0],V,A,B[0],D[0],G[0],H[0],tmin[0],beta[0]);
	PerformanceTest->Rows->Add(SOC,V,etaneg,etapos,Irea,Irec,IRM,teff[1],teff[0]);
	if (V<=0)
	{
		return 0;
	}
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
	if (FeCr->Checked)
	{
		AIplatecost[j]*=1.1;
		pcs[j]*=1.1;
		membranecost[membrane][j]*=1.1;
		pumpBaseCost[i]*=1.1;
		pumpGPMCost[i]*=1.1;
		framecost[j]*=1.1;
		bipolarcost[j]*=1.1;
		feltcost[j]*=1.21;
	}
    double totcost=AIplates*AIplatecost[j]+pcs[j]*power+(feltcost[j]*feltarea)+(membranearea*membranecost[membrane][j])+2*(pumpBaseCost[i]+pumpGPMCost[i]*GPM)+framearea*framecost[j]+bipolararea*bipolarcost[j];
	if(VVGen1->Checked)
	{
	totcost+=HEX[j]*power;
	}
	double other=1/0.982; //bolts, pvc, other minor costs
    totcost*=other;
	powerCost[j]=totcost;
	if(j==2)
	{
		g_AlPlateCost=AIplates*AIplatecost[j]*1000/g_power/g_ep;
		g_PCSCost=pcs[j]*power*1000/g_power/g_ep;
		g_feltCost=(feltcost[j]*feltarea)*1000/g_power/g_ep;
		g_membraneCost=(membranearea*membranecost[membrane][j])*1000/g_power/g_ep;
		g_pumpsCost=2*(pumpBaseCost[i]+pumpGPMCost[i]*GPM)*1000/g_power/g_ep;
		g_frameCost=framearea*framecost[j]*1000/g_power/g_ep;
		g_bipolarPlateCost=bipolararea*bipolarcost[j]*1000/g_power/g_ep;
	}
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
	double chemcost[3][3]={{CostTab(3,10,units),CostTab(2,10,units),CostTab(1,10,units)},{CostTab(3,11,units),CostTab(2,11,units),CostTab(1,11,units)},{CostTab(3,15,units),CostTab(2,15,units),CostTab(1,15,units)}}; //$/kg
    double chemMW[3]={181.88,162.2,158.4}; // g/mol
    double chemmult[3]={2,1,1};// mol e/mol
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
			if(FeCr->Checked)
			{
				chemtotal=(2*chemMW[2]*(chemcost[2][i]+sythcost[i])*3600)/(Veff*F*chemmult[2]*DOD*sythesis)+2*chemMW[1]*chemcost[1][2]*3600/(Veff*F*chemmult[1]*DOD*sythesis);
			}
			else
			{
				chemtotal=(2*chemMW[0]*(chemcost[0][i]+sythcost[i])*3600)/(Veff*F*chemmult[0]*DOD*sythesis)+2*chemMW[1]*chemcost[1][2]*3600/(Veff*F*chemmult[1]*DOD*sythesis);
			}
			
		}
		if(system==1)
		{
			chemtotal=(2*chemMW[0]*(chemcost[0][i]+sythcost[i])*3600)/(Veff*F*chemmult[0]*DOD*sythesis);
		}
		if(i==2)
		{
			g_chemCost=chemtotal/n;
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
	//return 0;
	cwidth=g_cwidth;
	double resistivity=0.05;//ohm m (1/Convert::ToDouble(CondBox->Text))
	if(LiOrgButton->Checked)
	{
		resistivity=1/3.2;
	}
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
    double width = sqrt(area*aspectratio); //cell width m
    double height = width/aspectratio;
	cwidth=g_cwidth;
	double Dh=2*cdepth*cwidth/(cdepth+cwidth);
	double carea=cdepth*cwidth;
    double Q = flow/(60*1000*1000); // m^3/s
    double K = 3.982E-10;//1.09438E-10 // m^2
	double visc = 6.60E-03;
	double tScaleFactor = Convert::ToDouble(ThicknessBox->Text);
	double t = 0.0019*tScaleFactor;
	double segments = width/Convert::ToDouble(channelSepBox->Text);//ceil(width/Convert::ToDouble(channelSepBox->Text));
	double Pdrop=0;
	if(interdigBox->Checked)
	{
		Pdrop=(Q/(t*height))*visc*width/K/segments+32*width*Q*visc/(carea*Dh*Dh*segments);
	}
	else
	{
		Pdrop=(Q/(t*width))*visc*height/K+2*32*width*Q*visc/(carea*Dh*Dh*channels);
	}
  
	
    double PEff=0.67; // pump efficiency
    double powerLoss=2*(g_pDropFactor+g_SOC*g_pDropFactorSlope)*Pdrop*Q/PEff;
	if(stoichFlowBox->Checked)
	{
		powerLoss/=g_SOC;
	}
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
	public: double g_VEffAvg;
	public: double g_pCost;
	public: double g_eCost;
	public: array<double,3>^ g_interpolationMatrix;
	public: int g_interpolationSizeX;
	public: int g_interpolationSizeY;
	public: cliext::vector <double> g_J;
	public: cliext::vector <cliext::vector <cliext::vector <double>>> g_SuperMatrix;
	public: double g_pDropFactor;
	public: double g_pDropFactorSlope;
	public: cliext::vector <cliext::vector <cliext::vector <double>>> g_3dinterpolation;
	public: cliext::vector <double> g_3dSOCRange;
	public: cliext::vector <double> g_3dJRange;
	public: cliext::vector <double> g_3dFlowRange;
	public: cliext::vector <double>finalECost;
	public: cliext::vector <double>finalPCost;
	public: cliext::vector <double>finalTCost;
	public: double g_chemCost;
	public: double g_AlPlateCost;
	public: double g_PCSCost;
	public: double g_feltCost;
	public: double g_membraneCost;
	public: double g_pumpsCost;
	public: double g_frameCost;
	public: double g_bipolarPlateCost;
	public: double g_etapos;
	public: double g_etaneg;
	public: double g_Irea;
	public: double g_Irec;





	public: double conductivity(double SOC, double T, int posneg)
			{
				vector<vector<double> > condDataA = fileRead("ConductivityVA.csv");
				vector<vector<double> > condDataC = fileRead("ConductivityVC.csv");
				vector<vector<vector<double> > > g_condMatrixA;
				vector<double> g_condTA;
				vector<vector<vector<double> > > g_condMatrixC;
				vector<double> g_condTC;
				int i = 0;
				int j = 0;
				vector<double> X1;
				vector<vector<double> > YMatrix;

				i=1;
	while(i<condDataA[0].size())
	{
		X1.push_back(condDataA[0][i]);
		i++;
	}
	i=1;
	while(i<condDataA.size())
	{
		j=1;
		g_condTA.push_back(condDataA[i][0]);
		YMatrix.resize(YMatrix.size()+1);
		while(j<condDataA[0].size())
		{
			YMatrix[i-1].push_back(condDataA[i][j]);
			j++;
		}
		i++;
	}
	vector<vector<double> > VMatrix;
	
	i=0;
	while(i<YMatrix.size())
	{
		VMatrix=populateSpline2V(X1,YMatrix[i]);
		g_condMatrixA.push_back(VMatrix);
		i++;
	}

	/***************/
	X1.clear();
	YMatrix.clear();
	VMatrix.clear();
		i=1;
	while(i<condDataC[0].size())
	{
		X1.push_back(condDataC[0][i]);
		i++;
	}
	i=1;
	while(i<condDataC.size())
	{
		j=1;
		g_condTC.push_back(condDataC[i][0]);
		YMatrix.resize(YMatrix.size()+1);
		while(j<condDataC[0].size())
		{
			YMatrix[i-1].push_back(condDataC[i][j]);
			j++;
		}
		i++;
	}
	
	i=0;
	while(i<YMatrix.size())
	{
		VMatrix=populateSpline2V(X1,YMatrix[i]);
		g_condMatrixC.push_back(VMatrix);
		i++;
	}

				if (posneg==0)
				{
				return interpolate2dSpline(g_condMatrixA,g_condTA,SOC,T);
				}
				if (posneg==1)
				{
					return interpolate2dSpline(g_condMatrixC,g_condTC,SOC,T);
				}
				else
				{
					return 0;
				}
			}
	public: double Interpolation3d(double flow, double j, double SOC)
			{
				int i = 0;
				double f;

				if(flow<g_3dFlowRange.at(0))
				{
					return 0;
				}
				if(flow>g_3dFlowRange.at(g_3dFlowRange.size()-1)||(flow!=flow))
				{
					flow=g_3dFlowRange.at(g_3dFlowRange.size()-1);
				}
				if(j<g_3dJRange.at(0)||j>g_3dJRange.at(g_3dJRange.size()-1))
				{
					return 0;
				}
				if(SOC<g_3dSOCRange.at(0)||SOC>g_3dSOCRange.at(g_3dSOCRange.size()-1))
				{
					return 0;
				}
				while((g_3dFlowRange.at(i)<=flow)&&(i<(g_3dFlowRange.size()-1)))
				{
					i++;
				}
				i--;
				if(i>=3)
				{
					//MessageBox::Show("Out of bounds!");
				}
				if(i<0)
				{
					//MessageBox::Show("Out of bounds!");
					return 0;
				}
				double flowLow=g_3dFlowRange.at(i);
				double flowHigh=g_3dFlowRange.at(i+1);
				int k=0;
								while((g_3dJRange.at(k)<=j)&&(k<(g_3dJRange.size()-1)))
				{
					k++;
				}
				double jLow=g_3dJRange.at(k-1);
				double jHigh=g_3dJRange.at(k);
				int l=0;
								while((g_3dSOCRange.at(l)<=SOC)&&(l<(g_3dSOCRange.size()-1)))
				{
					l++;
				}
				double SOCLow=g_3dSOCRange.at(l-1);
				double SOCHigh=g_3dSOCRange.at(l);
				double vertices [2][2][2] = {{{g_3dinterpolation.at(i)[k][l],g_3dinterpolation.at(i)[k][l+1]},{g_3dinterpolation.at(i)[k+1][l],g_3dinterpolation.at(i)[k+1][l+1]}},{{g_3dinterpolation.at(i+1)[k][l],g_3dinterpolation.at(i+1)[k][l+1]},{g_3dinterpolation.at(i+1)[k+1][l],g_3dinterpolation.at(i+1)[k+1][l+1]}}};
				double d = (flow-flowLow)/(flowHigh-flowLow);
				//double corners [2][2] = {{vertices[0][0][0]*(1-d)+d*vertices[1][0][0],vertices[0][0][1]*(1-d)+d*vertices[1][0][1]},{vertices[0][1][0]*(1-d)+d*vertices[1][1][0],vertices[0][1][1]*(1-d)+d*vertices[1][1][1]}};
				double c00=vertices[0][0][0]*(1-d)+d*vertices[1][0][0];
				double c01=vertices[0][0][1]*(1-d)+d*vertices[1][0][1];
				double c10=vertices[0][1][0]*(1-d)+d*vertices[1][1][0];
				double c11=vertices[0][1][1]*(1-d)+d*vertices[1][1][1];
				d=(j-jLow)/(jHigh-jLow);
				//double points [2] = {corners[0][0]*(1-d)+d*corners[1][0],corners[0][1]*(1-d)+d*corners[1][1]};
				double c0=c00*(1-d)+d*c01;
				double c1=c10*(1-d)+d*c11;
				d=(SOC-SOCLow)/(SOCHigh-SOCLow);
				//f=points[0]*(1-d)+d*points[1];
				f=c0*(1-d)+d*c1;
				return f;

			}
	public: void global_initialization()
			{
				
				//temp vector initialization
				/*g_3dJRange.clear();
				g_3dJRange.push_back(0);
				g_3dJRange.push_back(160);
				g_3dJRange.push_back(240);
				g_3dJRange.push_back(320);
				g_3dFlowRange.clear();
				g_3dFlowRange.push_back(0*1000/(3*0.26*0.3));
				g_3dFlowRange.push_back(1.2*1000/(3*0.26*0.3));
				g_3dFlowRange.push_back(2.4*1000/(3*0.26*0.3));
				g_3dFlowRange.push_back(3.6*1000/(3*0.26*0.3));
				g_3dFlowRange.push_back(4.8*1000/(3*0.26*0.3));
				g_3dinterpolation.clear();
				g_3dinterpolation.push_back(cli_fileRead("3CellLID0LPM.csv"));
				g_3dinterpolation.push_back(cli_fileRead("3CellLID1.2LPM.csv"));
				g_3dinterpolation.push_back(cli_fileRead("3CellLID2.4LPM.csv"));
				g_3dinterpolation.push_back(cli_fileRead("3CellLID3.6LPM.csv"));
				g_3dinterpolation.push_back(cli_fileRead("3CellLID4.8LPM.csv"));
				int k = 1;
				g_3dSOCRange.clear();
				while (k<g_3dinterpolation[0][0].size())
				{
					g_3dSOCRange.push_back(g_3dinterpolation.at(0)[0][k]);
					k++;
				}*/
				//double a = Interpolation3d(1.8*1000/(3*0.26*0.3),160,0.5);

				//temp
				g_J.clear();
				g_SuperMatrix.clear();
				g_k=2;
				g_jLow=Convert::ToDouble(testCurrent->Text);
				g_qhigh=Convert::ToDouble(testFlow->Text);
				g_qhighpercurrent=g_qhigh/g_jLow;
				g_DOD=Convert::ToDouble(DODValueBox->Text);
				//end temp
				g_power=Convert::ToDouble(powerBox->Text)*1000;
				g_ep=Convert::ToDouble(epBox->Text);
				g_reqpower=Convert::ToDouble(powerBox->Text)*1000;
				g_cells=Convert::ToDouble(cellBox->Text);
				g_stacks=Convert::ToDouble(stackBox->Text);
				g_reqpowerpercell=g_reqpower/(g_cells*g_stacks);
				g_aspectratio=Convert::ToDouble(ARValueBox->Text);
				g_cwidth=0.005;
				g_cdepth=0.002;
				g_channels=10;
				g_CE=0.98;
				g_pDropFactor =  Convert::ToDouble(PBox->Text);
				g_pDropFactorSlope = Convert::ToDouble(PSlopeBox->Text);
				finalECost.resize(3,0);
				finalPCost.resize(3,0);
				finalTCost.resize(3,0);
				if(FeV->Checked)
	{
		g_system=0;
		g_membrane=0;
	}
				if(FeCr->Checked)
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
				while (i<5)
				{
					V=g_voltage(g_SOC,g_area,qhigh*g_area,jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*jLow*V;
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					if((4*a*c)>(b*b))
					{
						while(V==0)
						{
							//while((4*a*c)>(b*b)){
								qhigh+=100;
								V=g_voltage(g_SOC,g_area,qhigh*g_area,jLow,g_aspectratio,g_system,g_membrane);
							/*	a= pLoss(g_area,qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
								b=-10*jLow*V/sqrt(g_CE);
								c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

							}*/
							g_qhighpercurrent=qhigh/jLow;
						}
						//MessageBox::Show("Fixing area!");
						g_areaReal=false;
						fixArea();
						i=20;

						/*V=g_voltage(g_SOC,1,10e9,jLow,g_aspectratio,g_system,g_membrane);
						g_area=g_reqpowerpercell/(10*jLow*V);
						while(i<20)
						{
						V=g_voltage(g_SOC,1,10e9,jLow,g_aspectratio,g_system,g_membrane);
						a= pLoss(g_area,qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
						b=-10*jLow*V/sqrt(g_CE);
						c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
						i++;
						}*/

					}
					else
					{
					g_area=(-b-sqrt(b*b-4*a*c))/(2*a);
					}
					i++;

				}
				double power = V*10*g_jLow*g_area - a*g_area*g_area -shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
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
				F=b*b-4*a*c;
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
					//g_qhigh-=D_qF/D_qqF;
					g_qhigh-=1.5*F/D_qF;

					V=g_voltage(g_SOC,g_area,g_qhigh*g_area,g_jLow,g_aspectratio,g_system,g_membrane);
					a= pLoss(g_area,g_qhigh*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)/(g_area*g_area);
					b=-10*g_jLow*V/sqrt(g_CE);
					c=g_reqpowerpercell+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);

					F=b*b-4*a*c;
					/*
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
					
					if (D_jF>0)
					{
						g_jLow+=1;
					}
					else
					{
						g_jLow-=1;
					}
					*/

					//MessageBox::Show(F.ToString() +"," + g_qhigh.ToString()+"," + g_jLow.ToString()+"," + V.ToString());
					
					
				}
				
				g_qhighpercurrent=g_qhigh/g_jLow;

			}
	public: double calculateCost(double jLow, double qhighpercurrent)
			{
				calculateArea(jLow,qhighpercurrent);

				if(g_area!=g_area)
				{
					return 999999+jLow+qhighpercurrent;
				}

				double VeffAvg=calculateVeffAvg(jLow,qhighpercurrent);


				double pcost=powerCost(g_area,qhighpercurrent*jLow*g_area,g_cells,g_aspectratio,g_power,g_stacks,g_system,g_membrane)[g_k]*1000/g_power;
				

				double ecost=energyCost(VeffAvg,g_DOD/100,1500,g_system)[g_k];
				g_VEffAvg=VeffAvg;
				g_pCost=pcost;
				g_eCost=ecost;

				double totcost=pcost/g_ep+ecost;
				return totcost;
			}
	public: double D_xcostoverD_xxcost(double % x, double jLow, double qhighpercurrent)
			{
				g_qhighpercurrent=qhighpercurrent;
				g_jLow=jLow;
				g_qhigh=g_qhighpercurrent*g_jLow;
				g_areaReal=true;
				double h = 0.001;
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
				if(D_xxcost==0)
				{
					return 0;
				}
				testGrid->Rows->Add(cost,x-h,costB,costF);
				return (D_xcost/D_xxcost);
			}
	public: double optimizeFlow(double j,double flow, double SOC)
			{
				if(SplineButton->Checked)
				{
					return flow;
				}
				double V;
				double VEff;
				double VEffF;
				double VEffB;
				bool optFlow=false;
				double powerproduced;
				double powerloss;
				double flowres=10;
				double D_flowVeff;
				double D_flow2Veff;
				int k =0;
				while((!optFlow)&&k<5)
				{

						V=g_voltage(SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
						while(V==0 || flow!=flow)
						{
							if(flow!=flow)
							{
								flow=0;
							}
							k=0;
							flow+=10;
							V=g_voltage(SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
						}

						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
					
						VEff = V*(powerproduced-powerloss)/powerproduced;
						//VEff=0;
						V=g_voltage(SOC,g_area,(flow+flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,(flow+flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEffF = V*(powerproduced-powerloss)/powerproduced;
						V=g_voltage(SOC,g_area,(flow-flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,(flow-flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEffB = V*(powerproduced-powerloss)/powerproduced;
						if(VEffB!=VEffB)
						{
						while(V==0)
						{
							flowres/=2;
							V=g_voltage(SOC,g_area,(flow-flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						}
						V=g_voltage(SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
						VEff = V*(powerproduced-powerloss)/powerproduced;
						V=g_voltage(SOC,g_area,(flow+flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,(flow+flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEffF = V*(powerproduced-powerloss)/powerproduced;
						V=g_voltage(SOC,g_area,(flow-flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,(flow-flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels);
						VEffB = V*(powerproduced-powerloss)/powerproduced;
						}
						D_flowVeff=(VEffF-VEffB)/(2*flowres);
						D_flow2Veff=(VEffF+VEffB-2*VEff)/(flowres*flowres);
						if(D_flow2Veff!=0)
						{
						flow-=0.5*(D_flowVeff/D_flow2Veff);
						k++;
						}
						if(abs(D_flowVeff*D_flowVeff/D_flow2Veff)<=0.0001)
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
				double delSOC = g_DOD/100/20;
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
				double powerproduced;
				double powerloss;
				/*V=g_voltage(SOCLow,g_area,flow*g_area,jLow,g_aspectratio,g_system,g_membrane);
				VEff =V*(V*j*g_area*10-pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)-shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells))/(V*j*g_area*10);
				*/
				V=g_voltage(g_SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
				powerproduced=V*j*g_area*10;
				powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
				power = powerproduced-powerloss;
				VEff =V*(powerproduced-powerloss)/powerproduced;
				VEffAvg+=VEff;
				int i = 1;
				dataOutput->Rows->Add(g_SOC,powerproduced,pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth,g_cdepth,g_channels),shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells),g_voltage(g_SOC,g_area,flow*g_area,0,g_aspectratio,g_system,g_membrane),g_voltage(g_SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane),VEff,j,flow,g_etapos,g_etaneg,g_Irea,g_Irec);
				g_SOC = SOCLow+delSOC;
				
				double D_jP;
				double Pb;
				double Pf;
				double D_fP;
				double D_ffP;

				double flowres=50;
				double del;
				while (g_SOC<= SOCHigh)
				{
					if(constpower->Checked)
					{
					powerAttained=false;
					while(!powerAttained)


					{

					V=g_voltage(g_SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
					powerproduced=V*j*g_area*10;
					powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					VEff =V*(powerproduced-powerloss)/powerproduced;
					power = powerproduced-powerloss;

					V=g_voltage(g_SOC,g_area,flow*g_area,(j-jres),g_aspectratio,g_system,g_membrane);
					powerproduced=V*(j-jres)*g_area*10;
					powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					Pb=powerproduced-powerloss;

					D_jP=((power-Pb)/jres);
					j-=((power-g_reqpowerpercell)/D_jP);

					
					V=g_voltage(g_SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
					powerproduced=V*j*g_area*10;
					powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					VEff =V*(powerproduced-powerloss)/powerproduced;
					power = powerproduced-powerloss;

					V=g_voltage(g_SOC,g_area,(flow-flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
					powerproduced=V*(j)*g_area*10;
					powerloss=pLoss(g_area,(flow-flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					Pb=powerproduced-powerloss;

					V=g_voltage(g_SOC,g_area,(flow+flowres)*g_area,j,g_aspectratio,g_system,g_membrane);
					powerproduced=V*(j)*g_area*10;
					powerloss=pLoss(g_area,(flow+flowres)*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
					Pf=powerproduced-powerloss;

					D_fP=(Pf-Pb)/flowres;
					D_ffP=(Pf+Pb-2*power)/(flowres*flowres);

					flow-=0.1*D_fP/D_ffP;

/*=======
					del=0.1*((power-g_reqpowerpercell)/D_jP);
					if(del>=0)
					{
						j-=del;
					}
					else
					{
						j=j;
					}
>>>>>>> refs/remotes/origin/master*/
					if(abs((power-g_reqpowerpercell)/D_jP)<=0.001)
					{
						powerAttained=true;
					}
					}
					}
					else
					{
						//flow=optimizeFlow(j,flow,g_SOC);
						V=g_voltage(g_SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane);
						powerproduced=V*j*g_area*10;
						powerloss=pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth, g_cdepth,g_channels)+shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells);
						VEff =V*(powerproduced-powerloss)/powerproduced;
					}

					i++;
					VEffAvg+=VEff;
					dataOutput->Rows->Add(g_SOC,powerproduced,pLoss(g_area,flow*g_area,g_aspectratio,g_cwidth,g_cdepth,g_channels),shuntLoss(V,g_area,g_cwidth,g_cdepth,g_aspectratio,g_channels,g_cells)/(g_cells),g_voltage(g_SOC,g_area,flow*g_area,0,g_aspectratio,g_system,g_membrane),g_voltage(g_SOC,g_area,flow*g_area,j,g_aspectratio,g_system,g_membrane),VEff,j,flow,g_etapos,g_etaneg,g_Irea,g_Irec);
					g_SOC+=delSOC;
				}

				VEffAvg/=i;
				return VEffAvg;
			}
	public: void interpolationSetup()
			{
	int i;
	int k;
	string file;
	String^ filename;
	if((interpolationFileBox->Text)->Length==0)
		{
			if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{	
					filename=openFileDialog1->FileName;
					MarshalString(filename,file);
					interpolationFileBox->Text=filename;
				}
			else
				{
					return;
				}
		}
	else
		{
			filename=interpolationFileBox->Text;
			MarshalString(filename,file);
		}
	cliext::vector<cliext::vector<double> > dataMatrix=cli_fileRead(file);
	i=0;
	k=0;
	cliext::vector<double> X1;
	cliext::vector<cliext::vector<double> > YMatrix;
	i=1;
	while(i<dataMatrix[0].size())
	{
		X1.push_back(dataMatrix.at(0)[i]);
		i++;
	}

	i=1;
	while(i<dataMatrix.size())
	{

		k=1;
		g_J.push_back(dataMatrix.at(i)[0]);
		YMatrix.resize(YMatrix.size()+1);
		while(k<dataMatrix.at(0).size())
		{
			YMatrix.at(i-1).push_back(dataMatrix.at(i)[k]);
			k++;
		}
		i++;
	}
	cliext::vector<cliext::vector<double> > VMatrix;
	
	i=0;
	while(i<YMatrix.size())
	{
		VMatrix=cli_populateSpline2V(X1,YMatrix.at(i));
		g_SuperMatrix.push_back(VMatrix);
		i++;
	}
	double DODMax=(100*(X1.at(X1.size()-1)-X1.at(0))-1);
	double jMin=(g_J.at(0));
	double jMax=(g_J.at(g_J.size()-1));
		if(Convert::ToDouble(DODMaxBox->Text)>DODMax)
	{
		DODMaxBox->Text=DODMax.ToString();
	}
		if(Convert::ToDouble(currentMinBox->Text)<jMin)
	{
		currentMinBox->Text=jMin.ToString();
	}
		if(Convert::ToDouble(currentMaxBox->Text)>jMax)
	{
		currentMaxBox->Text=jMax.ToString();
	}

			}
	public: void optimize()
			{
				 
			 global_initialization();
			 int i = 0;
			 	if(SplineButton->Checked)
			 {
				 interpolationSetup();
			 }
			 g_jLow=Convert::ToDouble(currentValueBox->Text);
			 bool jLowOpt=(optCurrentBox->Checked);
			 double jLowMax=Convert::ToDouble(currentMaxBox->Text);
			 double jLowMin=Convert::ToDouble(currentMinBox->Text);

			 g_qhighpercurrent=Convert::ToDouble(flowValueBox->Text)*100*100/1000;
			 g_qhigh=g_qhighpercurrent*g_jLow;
			 bool flowOpt=(optFlowBox->Checked);
			 double flowMax=10*Convert::ToDouble(flowMaxBox->Text);
			 double flowMin=10*Convert::ToDouble(flowMinBox->Text);

			 g_DOD=Convert::ToDouble(DODValueBox->Text);
			 bool DODOpt=(optDODBox->Checked);
			 double DODMax=Convert::ToDouble(DODMaxBox->Text);
			 double DODMin=Convert::ToDouble(DODMinBox->Text);

			 g_aspectratio=Convert::ToDouble(ARValueBox->Text);
			 bool AROpt=(optARBox->Checked);
			 double ARMax=Convert::ToDouble(ARMaxBox->Text);
			 double ARMin=Convert::ToDouble(ARMinBox->Text);

			 g_cwidth=0.001*Convert::ToDouble(flowChanValueBox->Text);
			 bool FlowChanOpt=(optFlowChanBox->Checked);
			 double FlowChanMax=0.001*Convert::ToDouble(FlowChanMaxBox->Text);
			 double FlowChanMin=0.001*Convert::ToDouble(FlowChanMinBox->Text);

			 g_areaReal=true;
			 double cost = calculateCost(g_jLow,g_qhighpercurrent);
			 double delcost=cost;
			 double gamma=Convert::ToDouble(gammaBox->Text);

			 while ((abs(delcost)>=0.01) && (i<1))
			 {

				 //MessageBox::Show("Cost: " + cost);
				 if(flowOpt)
				 {
				 g_qhighpercurrent-=gamma*D_xcostoverD_xxcost((g_qhighpercurrent),g_jLow,g_qhighpercurrent);
				 if(g_qhighpercurrent>flowMax){g_qhighpercurrent=flowMax;}
				 if(g_qhighpercurrent<flowMin){g_qhighpercurrent=flowMin;}
				 }
				 if(jLowOpt)
				 {
				 //MessageBox::Show(del.ToString("F3"));
				 g_jLow-=gamma*D_xcostoverD_xxcost((g_jLow),g_jLow,g_qhighpercurrent);
				 if(g_jLow>jLowMax){g_jLow=jLowMax;}
				 if(g_jLow<jLowMin){g_jLow=jLowMin;}
				 }
				 if(DODOpt)
				 {
				 g_DOD-=gamma*D_xcostoverD_xxcost((g_DOD),g_jLow,g_qhighpercurrent);
				 if(g_DOD>DODMax){g_DOD=DODMax;}
				 if(g_DOD<DODMin){g_DOD=DODMin;}
				 }
				 if(AROpt)
				 {
				 g_aspectratio-=2*gamma*D_xcostoverD_xxcost((g_aspectratio),g_jLow,g_qhighpercurrent);
				 if(g_aspectratio>ARMax){g_aspectratio=ARMax;}
				 if(g_aspectratio<ARMin){g_aspectratio=ARMin;}
				 }
				 if(FlowChanOpt)
				 {
				 g_cwidth-=gamma*D_xcostoverD_xxcost((g_cwidth),g_jLow,g_qhighpercurrent);
				 if(g_cwidth>FlowChanMax){g_cwidth=FlowChanMax;}
				 if(g_cwidth<FlowChanMin){g_cwidth=FlowChanMin;}
				 }

				 delcost=calculateCost(g_jLow,g_qhighpercurrent)-cost;
				 cost=cost + delcost;
				 
				 //testGrid->Rows->Add(cost,g_jLow,(g_qhighpercurrent*g_jLow),g_DOD,g_area,g_pCost,g_eCost,g_VEffAvg);
				 i++;
			 }
			 int k=0;
			 while(k<3)
			 {
				 finalPCost.at(k)=(powerCost(g_area,g_qhighpercurrent*g_jLow*g_area,g_cells,g_aspectratio,g_power,g_stacks,g_system,g_membrane)[k]*1000/g_power);
				 finalECost.at(k)=(energyCost(g_VEffAvg,g_DOD/100,1500,g_system)[k]);
				 finalTCost.at(k)=(finalECost.at(k)+finalPCost.at(k)/g_ep);
				 k++;
			 }
			}
public: void Finished()
		{
			 bestTable->Rows->Add("Total $/kWh",finalTCost.at(2).ToString("C"),finalTCost.at(1).ToString("C"),finalTCost.at(0).ToString("C"));
			 bestTable->Rows->Add("Energy $/kWh",finalECost.at(2).ToString("C"),finalECost.at(1).ToString("C"),finalECost.at(0).ToString("C"));
			 bestTable->Rows->Add("Power $/kW",finalPCost.at(2).ToString("C"),finalPCost.at(1).ToString("C"),finalPCost.at(0).ToString("C"));
			 bestTable->Rows->Add("Current mA/cm^2",g_jLow.ToString("F2"));
			 bestTable->Rows->Add("Flow ml/min-A",(g_qhighpercurrent*1000/(100*100)).ToString("F2"));
			 bestTable->Rows->Add("SOC Range %",g_DOD.ToString("F2"));
			 bestTable->Rows->Add("Aspect Ratio",g_aspectratio.ToString("F2"));
			 bestTable->Rows->Add("Area cm^2",(g_area*100*100).ToString("F2"));
			 bestTable->Rows->Add("V Effective V",g_VEffAvg.ToString("F3"));
			 bestTable->Rows->Add("Channel Width mm",(g_cwidth*1000).ToString("F2"));
			 componentCostGrid->Rows->Add("Chemicals",g_chemCost.ToString("C"));
			 componentCostGrid->Rows->Add("Al End Plate",g_AlPlateCost.ToString("C"));
			 componentCostGrid->Rows->Add("PCS",g_PCSCost.ToString("C"));
			 componentCostGrid->Rows->Add("Felt",g_feltCost.ToString("C"));
			 componentCostGrid->Rows->Add("Membrane",g_membraneCost.ToString("C"));
			 componentCostGrid->Rows->Add("Pumps",g_pumpsCost.ToString("C"));
			 componentCostGrid->Rows->Add("PVC Frame",g_frameCost.ToString("C"));
			 componentCostGrid->Rows->Add("Bipolar Plate",g_bipolarPlateCost.ToString("C"));
			 currentValueBox->Text=g_jLow.ToString("F2");
			 flowValueBox->Text=(g_qhighpercurrent*1000/(100*100)).ToString("F2");
			 DODValueBox->Text=g_DOD.ToString("F2");
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
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
			 dataOutput->Rows->Clear();
			 bestTable->Rows->Clear();
			 componentCostGrid->Rows->Clear();
			 /*Thread^ thisThread = gcnew Thread(
         gcnew ThreadStart(this,&Form1::optimize));
         thisThread->Start();
		 Finished();*/
			 optimize();
			 Finished();

		 }
private: System::Void label33_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void optCurrentBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if (optCurrentBox->Checked)
			 {
				 currentMaxBox->ReadOnly=false;
				 currentMinBox->ReadOnly=false;
			 }
			 else
			 {
				 currentMaxBox->ReadOnly=true;
				 currentMinBox->ReadOnly=true;
			 }
		 }
private: System::Void optDODBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 			 if (optDODBox->Checked)
			 {
				 DODMaxBox->ReadOnly=false;
				 DODMinBox->ReadOnly=false;
			 }
			 else
			 {
				 DODMaxBox->ReadOnly=true;
				 DODMinBox->ReadOnly=true;
			 }

		 }
private: System::Void optFlowBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 			 			 if (optFlowBox->Checked)
			 {
				 flowMaxBox->ReadOnly=false;
				 flowMinBox->ReadOnly=false;
			 }
			 else
			 {
				 flowMaxBox->ReadOnly=true;
				 flowMinBox->ReadOnly=true;
			}

		 }
private: System::Void optARBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 			 			 			 if (optARBox->Checked)
			 {
				 ARMaxBox->ReadOnly=false;
				 ARMinBox->ReadOnly=false;
			 }
			 else
			 {
				 ARMaxBox->ReadOnly=true;
				 ARMinBox->ReadOnly=true;
			}
		 }
private: System::Void SplineButton_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 if(SplineButton->Checked)
			 {
				 flowMaxBox->ReadOnly=true;
				 flowMinBox->ReadOnly=true;
				 optFlowBox->Checked=false;
			 }
		 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				{	
					interpolationFileBox->Text=(openFileDialog1->FileName);
				}
			else
				{
					return;
				}

		 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
			 global_initialization();
			 double flow = Convert::ToDouble(Int3dFlowBox->Text);
			 double j = Convert::ToDouble(Int3dJBox->Text);
			 double SOC = Convert::ToDouble(Int3dSOCBox->Text);
			 flow=flow*j*100*100/1000;
			 double V = Interpolation3d(flow,j,SOC);

			 Int3dVBox->Text=V.ToString();
		 }
private: System::Void powerBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 double power = Convert::ToDouble(powerBox->Text);
			 double ep = Convert::ToDouble(epBox->Text);
			 energyBox->Text=(power*ep).ToString();

		 }
private: System::Void panel7_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
		 }
private: System::Void optFlowChanBox_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
			 			 			 			 			 if (optFlowChanBox->Checked)
			 {
				 FlowChanMaxBox->ReadOnly=false;
				 FlowChanMinBox->ReadOnly=false;
			 }
			 else
			 {
				 FlowChanMaxBox->ReadOnly=true;
				 FlowChanMinBox->ReadOnly=true;
			}

		 }
private: System::Void dataGridView1_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void button4_Click(System::Object^  sender, System::EventArgs^  e) {
			 double SOC=0.025;
			 double V;
			 double VEff;
			 double flow=0;
			 //V=g_voltage(0.15, .26*.30,1200,320,1,1,1);
			 double powerproduced;
			 double powerloss;
			 g_cwidth=0.005;
			g_cdepth=0.002;
			g_channels=10;
			g_pDropFactor=1;
			V=g_voltage(0.1, .26*.30,1200,320,1,1,1);
			/* while (flow<=12800)
			 {
				V=g_voltage(0.135,0.12729494167510302,flow*0.12729494167510302,320,1,1,1);
				powerproduced=V*320*0.12729494167510302*10;
				powerloss=pLoss(0.12729494167510302,flow*0.12729494167510302,1,g_cwidth, g_cdepth,g_channels);
				VEff = V*(powerproduced-powerloss)/powerproduced;
				PerformanceTest->Rows->Add(flow,VEff,V,powerloss);
				flow +=5;
			 }*/
		 }
private: System::Void currentValueBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void bestTable_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
};
}

