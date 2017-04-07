/*	
	Project: Bank Management System
	Created Date: 28/November/2014
	Last Update: 24/December/2014
	Names: Bilal
	IDs: 13K-2314
	CP Project 2014				
	Compile: Visual Studio 2013	
									*/

/* TURN OFF _CRT_SECURE_NO_WARNINGS */
#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

/* Libraries */
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <windows.h>
#include <stdlib.h>
#include <cstdlib>
#include <conio.h>
#include <time.h>
#include <iomanip>
#include <cmath>

/* Header File (Classes) */
#include "Authentication.h"
#include "Account_Profile.h"
#include "Account.h"
#include "Current_Account.h"
#include "Saving_Account.h"
#include "Administrator.h"
#include "Loan.h"

/* Reference for ... */
int main();

/* Namespace */
using namespace std;

/* Global Variables */
COORD CursorPosition = { 0, 0 };	// For gotoXY Function
const int ESC = 27;					// ASCI ESC
const int BS = 8;					// ASCI BACKSPACE

/* Functions */
void gotoXY(int x, int y);			// Prototype of a gotoXY Function
void Printing(char Prt, char Spc);	// Prototype of a Printing Function
void Welcome();						// Prototype of Welcome Function
char Main_Display();				// Prototype of Main_Display Function
void Instructions();				// Prototype of Instructions Function
string Generate_DateandTime();		// Prototype of Generate_DateandTime Function
void PRESS_ESC(char CH);			// Prototype of PRESS_ESC Function

	/* CLASSES FUNCTIONS */

/* Account_Profile Class Functions */
Account_Profile::Account_Profile()
	: Name("Not Name Yet") {}

/* Account Class Functions */
Account::Account() : Account_No("Not Account Number Generated Yet."),
				Account_Type("Not Account Type Generated Yet."), Balance(0.0)
{
	Profile = new Account_Profile;
	Auth = new Authentication;
}

Account::~Account() {
	delete Profile;
	delete Auth;
}

/* User_Account_Display Function */
char Account::Account_Display()
{
	system("cls");
	Printing('*', ' ');
	gotoXY(28, 02);
	cout << "Welcome to your Account" << endl;
	gotoXY(8, 5);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 6);
	cout << "Press \"1\" for Check Account Status.";
	gotoXY(12, 8);
	cout << "Press \"2\" for Transfer Money to Other Bank Account.";
	gotoXY(12, 10);
	cout << "Press \"3\" for Deposit.";
	gotoXY(12, 12);
	cout << "Press \"4\" for Withdraw.";
	gotoXY(12, 14);
	cout << "Press \"5\" for Transfer Account (Current/Saving).";
	gotoXY(12, 16);
	cout << "Press \"6\" for Change Account Password.";
	gotoXY(12, 18);
	cout << "Press \"7\" for Main Menu.";
	gotoXY(8, 21);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 20);
	cout << "Enter Seletion: ";
	char CH;
	CH = _getche();
	Sleep(300);
	return CH;
} //end User_Account_Display Function

void Account::Account_Instructions()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
		gotoXY(29, 1);
		cout << "Account Instructions";
		gotoXY(4, 5);
		cout << "You can check your status, withdraw/deposit money by login your account.";
		gotoXY(4, 7);
		cout << "You cannot change your Account ID because it's fixed for all user.";
		gotoXY(4, 9);
		cout << "If you have Saving Account your initial Account Id letter will be \"S\".";
		gotoXY(4, 11);
		cout << "If you have Current Account your initial Account Id letter will be \"C\".";
		gotoXY(4, 13);
		cout << "You can change your password by providing some information.";
		gotoXY(4, 15);
		cout << "You can see your profile by login your account.";
		gotoXY(4, 17);
		cout << "If you want to close your account, So you have to Contact Administrator.";
}

void Account::Registration_Instructions()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
		gotoXY(27, 1);
		cout << "Registration Instructions \b";
		gotoXY(4, 5);
		cout << "You can Register new account by providing personal details and address.";
		gotoXY(4, 7);
		cout << "You cannot change your Account ID because it's fixed for all user.";
		gotoXY(4, 9);
		cout << "If you have Saving Account your initial Account Id letter will be \"S\".";
		gotoXY(4, 11);
		cout << "If you have Current Account your initial Account Id letter will be \"C\".";
		gotoXY(4, 13);
		cout << "In Account Type you write only Saving or Current.";
		gotoXY(4, 15);
		cout << "After Registration, your Account ID and Password will be shown by Auto.";
		gotoXY(4, 17);
		cout << "If you want to close your account, So you have to Contact Administrator.";
}

void Account::Generate_AC_DT()
{
	Profile->AC_Created_Date = Generate_DateandTime();
}

void Account::Change_Pass(string AC_No)
{
	system("cls");
	ReadToFile(AC_No);
	Auth->Change_Password();
	ModifyToFile(AC_No);
}

void Account::Change_Type(string AC_No)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Account Type Changed";
	gotoXY(3, 23);
	cout << "Status: Successfully Change...";
	ReadToFile(AC_No);
	if (Account_Type == "Saving")
	{
		Account_Type = "Current";
		Account_No.erase(Account_No.begin() + 0);
		Account_No.insert(Account_No.begin() + 0, 'C');
		string Pass = Auth->Get_Password();
		if (Pass.find("S") == 0){
			Pass.erase(Pass.begin() + 0);
			Pass.insert(Pass.begin() + 0, 'C');
			Auth->Set_Password(Pass);
		}
	}
	else if (Account_Type == "Current")
	{
		Account_Type = "Saving";
		Account_No.erase(Account_No.begin() + 0);
		Account_No.insert(Account_No.begin() + 0, 'S');
		string Pass = Auth->Get_Password();
		if (Pass.find("C") == 0){
			Pass.erase(Pass.begin() + 0);
			Pass.insert(Pass.begin() + 0, 'S');
			Auth->Set_Password(Pass);
		}
	}
	ModifyToFile(AC_No);
	gotoXY(17, 8);
	cout << "==============================================";
	gotoXY(20, 10);
	cout << "Account Type: " << this->Account_Type;
	gotoXY(20, 12);
	cout << "New Account ID: " << this->Account_No;
	gotoXY(20, 14);
	cout << "New Account Password: " << this->Get_Account_Password();
	gotoXY(17, 16);
	cout << "==============================================";
}

ostream& operator <<(ostream& out, Account& Obj)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		out << '-';
		gotoXY(j, 22);
		out << '-';
	}
	gotoXY(30, 1);
	out << "Account Status";
	gotoXY(3, 23);
	out << "Status: Successfully Login...";
	gotoXY(21, 7);
	out << "Account Type:    " << Obj.Account_Type;
	gotoXY(21, 9);
	out << "Account ID:      " << Obj.Account_No;
	gotoXY(21, 11);
	out << "Account Balance: " << Obj.Balance;
	gotoXY(21, 13);
	out << "Account Status:  ";
	if (Obj.Balance < 500)
	{
		out << "You Have Balance Less Then 500.";
		gotoXY(39, 14);
		out << "Please Contact Bank Manager.";
	}
	else
	{
		out << "Normal";
	}
	gotoXY(79, 24);
	return out;
}

void Account::Withdraw(double Amount)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Withdraw Status";
	if (Amount <= Balance)
	{
		gotoXY(3, 23);
		cout << "Status: Successfully Withdraw...";
		Balance = Balance - Amount;
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Unsuccessful...";
	}
	gotoXY(21, 7);
	cout << "Account Type:    " << this->Account_Type;
	gotoXY(21, 9);
	cout << "Account ID:      " << this->Account_No;
	gotoXY(21, 11);
	cout << "New Balance:     " << this->Balance;
}

void Account::Deposit(double Amount)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Deposit Status";
	if (Amount > 0)
	{
		gotoXY(3, 23);
		cout << "Status: Successfully Deposit...";
		Balance = Balance + Amount;
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Unsuccessful...";
	}
	gotoXY(21, 7);
	cout << "Account Type:    " << this->Account_Type;
	gotoXY(21, 9);
	cout << "Account ID:      " << this->Account_No;
	gotoXY(21, 11);
	cout << "New Balance:     " << this->Balance;
}

void Account::Transfer_Balance(string AC_No, int Amount)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	} //end for
	gotoXY(24, 1);
	cout << "Welcome To Transfer Balance...";
	gotoXY(3, 23);
	cout << "Status: Pending...";
	Account* New;
	if (AC_No == "" && Amount == 0)
	{
		gotoXY(16, 8);
		cout << "-------------------------------------------------";
		gotoXY(20, 10);
		cout << "Enter Account Number: ";
		gotoXY(20, 12);
		cout << "Enter Amount to Transfer: ";
		gotoXY(16, 14);
		cout << "-------------------------------------------------";
		gotoXY(46, 10);
		cin >> AC_No;
		gotoXY(46, 12);
		cin >> Amount;
	} //end if
	if (AC_No == Account_No) {
		gotoXY(3, 23);
		cout << "Status: Unsuccessful Transfered Money because Same Account...";
	}
	else
	{
		if (this->Account_Type == "Current")
			New = new Current_Account;
		else
			New = new Saving_Account;
		New->ReadToFile(AC_No);
		if (New->Account_No == AC_No)
		{
			if (this->Balance >= Amount)
			{
				New->Balance += Amount;
				Balance -= Amount;
				New->ModifyToFile(AC_No);
				this->ModifyToFile(this->Account_No);
				gotoXY(3, 23);
				cout << "Status: Successfully Transfered Money...";
			} //end inner if
			else{
				gotoXY(3, 23);
				cout << "Status: Unsuccessful Transfered Money...";
			} //end else-if
		} //end outer if
		else
		{
			gotoXY(3, 23);
			cout << "Status: Unsuccessful Transfered Money because Account Not Exist...";
		}
	}
}

void Account::Change_Balance(char CH, double Amount)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Balance Status";
	if (Amount > 0 && CH == '+')
	{
		gotoXY(3, 23);
		cout << "Status: Successfully Deposit...";
		Balance = Balance + Amount;
	}
	else if (Amount > 0 && CH == '-')
	{
		gotoXY(3, 23);
		cout << "Status: Successfully Deposit...";
		Balance = Balance - Amount;
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Unsuccessful...";
	}
	gotoXY(21, 7);
	cout << "Account Type:    " << this->Account_Type;
	gotoXY(21, 9);
	cout << "Account ID:      " << this->Account_No;
	gotoXY(21, 11);
	cout << "New Balance:     " << this->Balance;
}

void Account::Accounts_Status()
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv", ios::in);
	std::string line;
	int i = 0, j = 0;
	while (std::getline(file, line))
	{
		if (j == 12 || i == 0)
		{
			if (i != 0)
			{
				Sleep(1000);
				gotoXY(11, 23);
				cout << "Press Enter Key to Continue...";
				if (_getch() == ESC)
					break;
			}
			system("cls");
			Printing('-', '-');
			for (int j = 0; j < 79; j++)
			{
				gotoXY(j, 2);
				cout << '-';
				gotoXY(j, 22);
				cout << '-';
			}
			gotoXY(32, 1);
			cout << "Accounts Status";
			gotoXY(3, 23);
			cout << "Status: Pending...";
		}
		const char *begin = line.c_str();

		// strip beyond first comma
		if (const char *end = strchr(begin, ','))
		{
			string column1(begin, end - begin);
			if (i > 2)
			{
				if (j == 12){
					j = 3;
				}
				gotoXY(4, (j - 1) * 2);
				cout << "Account \"" << column1 << "\" ";
				Account *NEW = new Saving_Account;
				NEW->ReadToFile(column1);
				if (NEW->Balance > 500) {
					cout << "is in Normal.";
				}
				else {
					cout << "is not in Normal.";
				}
				delete NEW;
			}
			i++;
			j++;
		}
	}
}

void Account::WriteToFile()
{
	ofstream Out_Data;
	Out_Data.open("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv", ios::app);
	Out_Data << Account_No << ","
		<< Auth->Get_Password() << ","
		<< Account_Type << ","
		<< Balance << ","
		<< Profile->Name << ","
		<< Profile->Father_Husband_Name << ","
		<< Profile->DateofBirth << ","
		<< Profile->Gender << ","
		<< Profile->Occupation << ","
		<< Profile->Education_Qualification << ","
		<< Profile->Phone_No << ","
		<< Profile->AC_Created_Date << ","
		<< Profile->Address << ","
		<< Profile->City << ","
		<< Profile->State << ","
		<< Profile->Postal_Code << "," << endl;
	Out_Data.close();
}

void Account::ReadToFile(string AC_No)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv", ios::in);
	string csvLine, Tmp_AC_No = "", Tmp_AC_Pass = "";
	int i = 0;
	// read every line from the stream
	while (getline(file, csvLine))
	{
		istringstream csvStream(csvLine);
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 15)
			{
				if (i == 1)
					Auth->Set_Password(csvElement);
				if (i == 2)
					Account_Type = csvElement;
				if (i == 3)
					Balance = atof(csvElement.c_str());
				if (i == 4)
					Profile->Name = csvElement;
				if (i == 5)
					Profile->Father_Husband_Name = csvElement;
				if (i == 6)
					Profile->DateofBirth = csvElement;
				if (i == 7)
					Profile->Gender = csvElement;
				if (i == 8)
					Profile->Occupation = csvElement;
				if (i == 9)
					Profile->Education_Qualification = csvElement;
				if (i == 10)
					Profile->Phone_No = csvElement;
				if (i == 11)
					Profile->AC_Created_Date = csvElement;
				if (i == 12)
					Profile->Address = csvElement;
				if (i == 13)
					Profile->City = csvElement;
				if (i == 14)
					Profile->State = csvElement;
				if (i == 15)
					Profile->Postal_Code = csvElement;
				i++;
			}
			if (csvElement == AC_No)
			{
				Account_No = csvElement;
				i++;
			}
		}
	}
}

void Account::ModifyToFile(string AC_No)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv", ios::in);
	myfile.open("Tmp.csv");
	if (!file.is_open())
	{
		cout << "File not found!\n";
		return;
	}
	// typedef to save typing for the following object
	typedef vector< vector<string> > csvVector;
	csvVector csvData;

	modifyCSV(file, csvData, AC_No);
	// print out read data to prove reading worked
	for (csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
	{
		for (vector<string>::iterator j = i->begin(); j != i->end(); ++j)
		{
			a = *j;
			myfile << a << ",";
		}
		myfile << "\n";
	}
	myfile.close();
	file.close();
	remove("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
	rename("Tmp.csv", "BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
}

/* Modify CSV File Function */
void Account::modifyCSV(istream &input, vector< vector<string> > &output, string AC_No)
{
	int i = 0;
	string csvLine;
	// read every line from the stream
	while (getline(input, csvLine))
	{
		istringstream csvStream(csvLine);
		vector<string> csvColumn;
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 15)
			{
				if (i == 1)
					csvElement = Auth->Get_Password();
				if (i == 2)
					csvElement = Account_Type;
				if (i == 3)
					csvElement = to_string(Balance);
				if (i == 4)
					csvElement = Profile->Name;
				if (i == 5)
					csvElement = Profile->Father_Husband_Name;
				if (i == 6)
					csvElement = Profile->DateofBirth;
				if (i == 7)
					csvElement = Profile->Gender;
				if (i == 8)
					csvElement = Profile->Occupation;
				if (i == 9)
					csvElement = Profile->Education_Qualification;
				if (i == 10)
					csvElement = Profile->Phone_No;
				if (i == 11)
					csvElement = Profile->AC_Created_Date;
				if (i == 12)
					csvElement = Profile->Address;
				if (i == 13)
					csvElement = Profile->City;
				if (i == 14)
					csvElement = Profile->State;
				if (i == 15)
					csvElement = Profile->Postal_Code;
				i++;
			}
			if (csvElement == AC_No)
			{
				csvElement = Account_No;
				i++;
			}
			csvColumn.push_back(csvElement);

		}
		output.push_back(csvColumn);
	}
}

void Account::deleteAccount(string AC_No)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv", ios::in);
	myfile.open("Tmp.csv");
	if (!file.is_open())
	{
		cout << "File not found!\n";
		return;
	}
	// typedef to save typing for the following object
	typedef vector< vector<string> > csvVector;
	csvVector csvData;

	deleteCSV(file, csvData, AC_No);
	// print out read data to prove reading worked
	for (csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
	{
		for (vector<string>::iterator j = i->begin(); j != i->end(); ++j)
		{
			a = *j;
			myfile << a << ",";
		}
		myfile << "\n";
	}
	myfile.close();
	file.close();
	remove("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
	rename("Tmp.csv", "BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
}

/* Delete CSV File Function */
void Account::deleteCSV(istream &input, vector< vector<string> > &output, string AC_No)
{
	int i = 0, Flag = 0;
	string csvLine;
	// read every line from the stream
	while (getline(input, csvLine))
	{
		istringstream csvStream(csvLine);
		vector<string> csvColumn;
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 16)
			{
				i++;
				if (i < 3)
					Flag = 1;
			}
			if (csvElement == AC_No)
			{
				i++;
			}
			if (i <= 0 || i >= 17)
				csvColumn.push_back(csvElement);
		}
		if (Flag == 0){
			output.push_back(csvColumn);
		}
		Flag = 0;
	}
}

bool Account::Login_Account(string AC_N, string AC_Pas)
{
	return (Auth->Login(AC_N, AC_Pas));
}

/* Current_Account Class Functions */
Current_Account::Current_Account() : Account() { }

void Current_Account::Generate_AC_No()
{
	ifstream is("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
	string AC_No, No;
	int Flag = 0;
	while (getline(is, No))
	{
		const char *begin = No.c_str();
		// strip beyond first comma
		if (const char *end = strchr(begin, ','))
		{
			string No(begin, end - begin);
			AC_No = No;
		}
	}
	string N = AC_No;
	N.erase(N.begin() + 0);
	int Tmp = atoi(N.c_str());
	if (Tmp == 0)
	{
		AC_No = "C001";
	}
	else if (Tmp > 0 && Tmp < 9)
	{
		AC_No.erase(AC_No.begin() + 3, AC_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		AC_No = AC_No + STR;
	}
	else if (Tmp >= 9 && Tmp < 99)
	{
		AC_No.erase(AC_No.begin() + 2, AC_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		AC_No = AC_No + STR;
	}
	else if (Tmp >= 99 && Tmp < 999)
	{
		AC_No.erase(AC_No.begin() + 1, AC_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		AC_No = AC_No + STR;
	}
	else
	{
		AC_No = "Account Number Not Generated, It\'s Full.";
		Flag = 1;
	}
	if (Flag == 0)
	{
		AC_No.erase(AC_No.begin() + 0);
		AC_No.insert(0, "C");
	}
	Account_No = AC_No;
}

/* Saving_Account Class Functions */
Saving_Account::Saving_Account() : Account() {}

void Saving_Account::Generate_AC_No()
{
	ifstream is("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
	string AC_No, No;
	int Flag = 0;
	while (getline(is, No))
	{
		const char *begin = No.c_str();

		// strip beyond first comma
		if (const char *end = strchr(begin, ','))
		{
			string No(begin, end - begin);
			AC_No = No;
		}
	}
	string N = AC_No;
	N.erase(N.begin() + 0);
	int Tmp = atoi(N.c_str());
	if (Tmp == 0)
	{
		AC_No = "S001";
	}
	else if (Tmp > 0 && Tmp < 9)
	{
		AC_No.erase(AC_No.begin() + 3, AC_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		AC_No = AC_No + STR;
	}
	else if (Tmp >= 9 && Tmp < 99)
	{
		AC_No.erase(AC_No.begin() + 2, AC_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		AC_No = AC_No + STR;
	}
	else if (Tmp >= 99 && Tmp < 999)
	{
		AC_No.erase(AC_No.begin() + 1, AC_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		AC_No = AC_No + STR;
	}
	else
	{
		AC_No = "Account Number Not Generated, It\'s Full.";
		Flag = 1;
	}
	if (Flag == 0)
	{
		AC_No.erase(AC_No.begin() + 0);
		AC_No.insert(0, "S");
	}
	Account_No = AC_No;
}

/* Authentication Class Functions */
Authentication::Authentication() 
	: AC_Password("Not Account Password Generated Yet.") { }

void Authentication::Password_Display()
{
	for (int i = 9; i < 30; i++)
	{
		gotoXY(i * 2, 13);
		cout << '-';
		gotoXY(i * 2, 15);
		cout << '-';
		if (i < 18)
		{
			if (i != 17 && i != 16) {
				gotoXY(18, i + 5);
				cout << '-';
			}
			gotoXY(60, i + 4);
			cout << '-';
		}
		gotoXY(i * 2, 21);
		cout << '-';
	}
	gotoXY(28, 14);
	cout << "Account ID and Password";
	gotoXY(28, 17);
	cout << "Account ID: ";
	gotoXY(28, 19);
	cout << "AC Password: ";
	gotoXY(79, 24);
}

void Authentication::Generate_AC_Password(string Account_No)
{
	ifstream is("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv");
	string AC_Pass = Account_No, No;
	int Flag = 0;
	srand(static_cast<unsigned int>(time(NULL)));
	string N = AC_Pass;
	N.erase(N.begin() + 0);
	int Tmp = atoi(N.c_str());
	if (Tmp == 0)
	{
		AC_Pass = "Account Password Not Generated, Please Generate your Account.";
	}
	else
	{
		AC_Pass.erase(AC_Pass.begin() + 1, AC_Pass.end());
		stringstream S;
		S << Tmp + rand() % 99898 + 100;
		string STR = S.str();
		AC_Pass = AC_Pass + STR;
	}
	AC_Password = AC_Pass;
}

void Authentication::Change_Password()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Password Changing";
	gotoXY(3, 23);
	cout << "Status: Pending...";
	gotoXY(17, 8);
	cout << "==============================================";
	gotoXY(20, 10);
	cout << "Enter Old Password: ";
	gotoXY(20, 12);
	cout << "Enter New Password: ";
	gotoXY(17, 14);
	cout << "==============================================";
	string Old, New;
	gotoXY(41, 10);
	fflush(stdin);
	getline(cin, Old);
	gotoXY(41, 12);
	fflush(stdin);
	getline(cin, New);
	if (Old == AC_Password)
	{
		AC_Password = New;
		gotoXY(3, 23);
		cout << "Status: Successfully Changed...";
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Wrong Password...";
	}
}

bool Authentication::Login(string AC_No, string AC_Pass)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ACCOUNT DATA.csv", ios::in);
	string csvLine, Tmp_AC_No = "", Tmp_AC_Pass = "";
	int i = 0;
	// read every line from the stream
	while (getline(file, csvLine))
	{
		istringstream csvStream(csvLine);
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i == 1)
			{
				Tmp_AC_Pass = csvElement;
				i++;
			}
			if (csvElement == AC_No)
			{
				Tmp_AC_No = csvElement;
				i++;
			}
		}
	}
	if ((Tmp_AC_No == AC_No) && (Tmp_AC_Pass == AC_Pass))
	{
		return 1;
	}
	return 0;
}

/* Administrator Class Function */
Administrator::Administrator() : Account(), Admin_Name("Not Admin Name Yet")
							, Admin_Password("Not Admin Password Yet") {}

char Administrator::Administrator_Dispaly()
{
	system("cls");
	Printing('*', ' ');
	gotoXY(28, 02);
	cout << "Welcome to Admin Account" << endl;
	gotoXY(8, 5);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 6);
	cout << "Press \"1\" for (Check/Modify/Delete) Accounts.";
	gotoXY(12, 8);
	cout << "Press \"2\" for Check Accounts Status.";
	gotoXY(12, 10);
	cout << "Press \"3\" for Check Loan Status.";
	gotoXY(12, 12);
	cout << "Press \"4\" for Register (New Admin Account).";
	gotoXY(12, 14);
	cout << "Press \"5\" for Change Admin Name.";
	gotoXY(12, 16);
	cout << "Press \"6\" for Change Admin Password.";
	gotoXY(12, 18);
	cout << "Press \"7\" for Main Menu.";
	gotoXY(8, 21);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 20);
	cout << "Enter Seletion: ";
	char CH;
	CH = _getche();
	Sleep(300);
	return CH;
}

char Administrator::Manage_Accounts_Display()
{
	system("cls");
	Printing('*', ' ');
	gotoXY(28, 02);
	cout << "Welcome to \"" << this->Get_Account_No() << "\" Account" << endl;
	gotoXY(8, 5);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 7);
	cout << "Press \"1\" for Check Account Status.";
	gotoXY(12, 9);
	cout << "Press \"2\" for Change Account Balance.";
	gotoXY(12, 11);
	cout << "Press \"3\" for Modify Account Profile.";
	gotoXY(12, 13);
	cout << "Press \"4\" for Reset Account Password.";
	gotoXY(12, 15);
	cout << "Press \"5\" for Delete Account.";
	gotoXY(12, 17);
	cout << "Press \"6\" to Go Admin Account.";
	gotoXY(8, 21);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 19);
	cout << "Enter Seletion: ";
	char CH;
	CH = _getche();
	Sleep(300);
	return CH;
}

void Administrator::Administator_Instructions()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
		gotoXY(27, 1);
		cout << "Administrator Instructions";
		gotoXY(4, 5);
		cout << "You can check any Account status, change money by provide Account ID.";
		gotoXY(4, 7);
		cout << "You can create new Administartor Account by providing existing Account.";
		gotoXY(4, 9);
		cout << "You can Modify any Account Details, Profile and more by provide AC ID.";
		gotoXY(4, 11);
		cout << "You can reset any Account password by provide Account ID.";
		gotoXY(4, 13);
		cout << "You can change your Admin Password and as well as Admin Name.";
		gotoXY(4, 15);
		cout << "You can also close any Account by provide Account ID.";
		gotoXY(4, 17);
		cout << "You cannot close admin Account, It's fixed but change name or password.";
}

void Administrator::Generate_AC_No()
{
	srand(static_cast<unsigned int>(time(NULL)));
	string N = "A";
	stringstream S;
	S << rand() % 99000 + 999;
	string STR = S.str();
	N = N + STR;
	Admin_Password = N;
}

bool Administrator::Login_ADM(string ADM_No, string ADM_Pass)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ADMIN DATA.csv", ios::in);
	string csvLine, Tmp_ADM_No = "Not Tmp_ADM_No Yet" , Tmp_ADM_Pass = "Not Tmp_ADM_Pass Yet";
	int i = 0;
	// read every line from the stream
	while (getline(file, csvLine))
	{
		istringstream csvStream(csvLine);
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i == 1)
			{
				Tmp_ADM_Pass = csvElement;
				i++;
			}
			if (csvElement == ADM_No)
			{
				Tmp_ADM_No = csvElement;
				i++;
			}
		}
	}
	if ((Tmp_ADM_No == ADM_No) && (Tmp_ADM_Pass == ADM_Pass))
	{
		if (Tmp_ADM_No == "" && Tmp_ADM_Pass == "")
			return 0;
		return 1;
	}
	return 0;
}

void Administrator::WriteToFile_ADM()
{
	ofstream Out_Data;
	Out_Data.open("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ADMIN DATA.csv", ios::app);
	Out_Data << Admin_Name << ","				// Admin Name
		<< Admin_Password << ","				// Admin Password
		<< Admin_Type << ","					// Admin Type
		<< Profile->Name << ","
		<< Profile->Father_Husband_Name << ","
		<< Profile->DateofBirth << ","
		<< Profile->Gender << ","
		<< Profile->Occupation << ","
		<< Profile->Education_Qualification << ","
		<< Profile->Phone_No << ","
		<< Profile->AC_Created_Date << ","		// Admin Creation Date
		<< Profile->Address << ","
		<< Profile->City << ","
		<< Profile->State << ","
		<< Profile->Postal_Code << "," << endl;
	Out_Data.close();
}

void Administrator::ReadToFile_ADM(string ADM_No)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ADMIN DATA.csv", ios::in);
	string csvLine;
	int i = 0;
	// read every line from the stream
	while (getline(file, csvLine))
	{
		istringstream csvStream(csvLine);
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 14)
			{
				if (i == 1)
					Admin_Password = csvElement;
				if (i == 2)
					Admin_Type = csvElement;
				if (i == 3)
					Profile->Name = csvElement;
				if (i == 4)
					Profile->Father_Husband_Name = csvElement;
				if (i == 5)
					Profile->DateofBirth = csvElement;
				if (i == 6)
					Profile->Gender = csvElement;
				if (i == 7)
					Profile->Occupation = csvElement;
				if (i == 8)
					Profile->Education_Qualification = csvElement;
				if (i == 9)
					Profile->Phone_No = csvElement;
				if (i == 10)
					Profile->AC_Created_Date = csvElement;
				if (i == 11)
					Profile->Address = csvElement;
				if (i == 12)
					Profile->City = csvElement;
				if (i == 13)
					Profile->State = csvElement;
				if (i == 14)
					Profile->Postal_Code = csvElement;
				i++;
			}
			if (csvElement == ADM_No)
			{
				Admin_Name = csvElement;
				ADM_No = "Not ADM_No Yet...";
				i++;
			}
		}
	}
}

void Administrator::Change_Pass_ADM(string ADM)
{
	system("cls");
	ReadToFile_ADM(ADM);
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Password Changing";
	gotoXY(3, 23);
	cout << "Status: Pending...";
	gotoXY(17, 8);
	cout << "==============================================";
	gotoXY(20, 10);
	cout << "Enter Old Password: ";
	gotoXY(20, 12);
	cout << "Enter New Password: ";
	gotoXY(17, 14);
	cout << "==============================================";
	string Old, New;
	gotoXY(41, 10);
	fflush(stdin);
	getline(cin, Old);
	gotoXY(41, 12);
	fflush(stdin);
	getline(cin, New);
	if (Old == Admin_Password)
	{
		Admin_Password = New;
		gotoXY(3, 23);
		cout << "Status: Successfully Changed...";
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Wrong Password...";
	}
	ModifyToFile_ADM(ADM);
}

void Administrator::Change_Name_ADM(string ADM)
{
	system("cls");
	ReadToFile_ADM(ADM);
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Password Changing";
	gotoXY(3, 23);
	cout << "Status: Pending...";
	gotoXY(17, 8);
	cout << "==============================================";
	gotoXY(20, 10);
	cout << "Enter Old Name: ";
	gotoXY(20, 12);
	cout << "Enter New Name: ";
	gotoXY(17, 14);
	cout << "==============================================";
	string Old, New;
	gotoXY(37, 10);
	fflush(stdin);
	getline(cin, Old);
	gotoXY(37, 12);
	fflush(stdin);
	getline(cin, New);
	if (Old == Admin_Name)
	{
		Admin_Name = New;
		gotoXY(3, 23);
		cout << "Status: Successfully Changed...";
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Wrong Password...";
	}
	ModifyToFile_ADM(ADM);
}

void Administrator::Change_Balance(double Amount)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Amount Status";
	if (Amount > 0)
	{
		gotoXY(3, 23);
		cout << "Status: Successfully Done...";
		Balance = Balance + Amount;
	}
	else
	{
		gotoXY(3, 23);
		cout << "Status: Unsuccessful...";
	}
	gotoXY(21, 7);
	cout << "Account Type:    " << this->Account_Type;
	gotoXY(21, 9);
	cout << "Account ID:      " << this->Account_No;
	gotoXY(21, 11);
	cout << "New Balance:     " << this->Balance;
}

void Administrator::ModifyToFile_ADM(string ADM)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ADMIN DATA.csv", ios::in);
	myfile.open("Tmp.csv");
	if (!file.is_open())
	{
		cout << "File not found!\n";
		return;
	}
	// typedef to save typing for the following object
	typedef vector< vector<string> > csvVector;
	csvVector csvData;

	modifyCSV_ADM(file, csvData, ADM);
	// print out read data to prove reading worked
	for (csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
	{
		for (vector<string>::iterator j = i->begin(); j != i->end(); ++j)
		{
			a = *j;
			myfile << a << ",";
		}
		myfile << "\n";
	}
	myfile.close();
	file.close();
	remove("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ADMIN DATA.csv");
	rename("Tmp.csv", "BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - ADMIN DATA.csv");
}

/* Modify CSV File Function */
void Administrator::modifyCSV_ADM(istream &input, vector< vector<string> > &output, string ADM)
{
	int i = 0;
	string csvLine;
	// read every line from the stream
	while (getline(input, csvLine))
	{
		istringstream csvStream(csvLine);
		vector<string> csvColumn;
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 14)
			{
				if (i == 1)
					csvElement = Admin_Password;
				if (i == 2)
					csvElement = Admin_Type;
				if (i == 3)
					csvElement = Profile->Name;
				if (i == 4)
					csvElement = Profile->Father_Husband_Name;
				if (i == 5)
					csvElement = Profile->DateofBirth;
				if (i == 6)
					csvElement = Profile->Gender;
				if (i == 7)
					csvElement = Profile->Occupation;
				if (i == 8)
					csvElement = Profile->Education_Qualification;
				if (i == 9)
					csvElement = Profile->Phone_No;
				if (i == 10)
					csvElement = Profile->AC_Created_Date;
				if (i == 11)
					csvElement = Profile->Address;
				if (i == 12)
					csvElement = Profile->City;
				if (i == 13)
					csvElement = Profile->State;
				if (i == 14)
					csvElement = Profile->Postal_Code;
				i++;
			}
			if (csvElement == ADM)
			{
				csvElement = Admin_Name;
				ADM = "Not ADM Yet...";
				i++;
			}
			csvColumn.push_back(csvElement);
		}
		output.push_back(csvColumn);
	}
}

/* Loan Class Functions */
Loan::Loan() : LastPaid("Not Paid Yet.")
{ /* Intentionally Empty */ }

void Loan::Loan_Instruction(bool T)
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(30, 1);
	cout << "Loan Instructions";
	gotoXY(4, 5);
	cout << "Proof of income latest salary slip.";
	gotoXY(4, 7);
	cout << "Eligibility:";
	gotoXY(4, 9);
	cout << "Salaried individual with minimum monthly income of rupees 25000.";
	gotoXY(4, 11);
	cout << "Features:";
	gotoXY(4, 13);
	cout << "Loan upto 2 million.";
	gotoXY(4, 15);
	cout << "No interest or markup.";
	gotoXY(4, 17);
	cout << "If you agree terms and condition Enter to proceed or ESC.";
	if (T == true)
	{
		gotoXY(4, 23);
		cout << "Status: Press Enter or ESC Key.";
		char CH = _getch();
		PRESS_ESC(CH);
	}
	else
	{
		gotoXY(4, 23);
		cout << "Status: Press any Key to Continue...";
	}
}

void Loan::Generate_Loan_No()
{
	ifstream is("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv");
	string L_No, No;
	int Flag = 0;
	while (getline(is, No))
	{
		const char *begin = No.c_str();
		// strip beyond first comma
		if (const char *end = strchr(begin, ','))
		{
			string No(begin, end - begin);
			L_No = No;
		}
	}
	string N = L_No;
	N.erase(N.begin() + 0);
	int Tmp = atoi(N.c_str());
	if (Tmp == 0)
	{
		L_No = "L001";
	}
	else if (Tmp > 0 && Tmp < 9)
	{
		L_No.erase(L_No.begin() + 3, L_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		L_No = L_No + STR;
	}
	else if (Tmp >= 9 && Tmp < 99)
	{
		L_No.erase(L_No.begin() + 2, L_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		L_No = L_No + STR;
	}
	else if (Tmp >= 99 && Tmp < 999)
	{
		L_No.erase(L_No.begin() + 1, L_No.end());
		stringstream S;
		S << Tmp + 1;
		string STR = S.str();
		L_No = L_No + STR;
	}
	else
	{
		L_No = "Loan Number Not Generated, It\'s Full.";
		Flag = 1;
	}
	if (Flag == 0)
	{
		L_No.erase(L_No.begin() + 0);
		L_No.insert(0, "L");
	}
	Loan_No = L_No;
}

void Loan::Set_CreationDate()
{
	CreationDate = Generate_DateandTime();
}

void Loan::WriteToFile()
{
	ofstream Out_Data;
	Out_Data.open("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv", ios::app);
	Out_Data << Loan_No << ","
		<< Name << ","
		<< CNIC << ","
		<< Email << ","
		<< Contact << ","
		<< City << ","
		<< Monthly_Income << ","
		<< Company_Name << ","
		<< Segment << ","
		<< BestDayToContactYou << ","
		<< CreationDate << ","
		<< LoanAmount << ","
		<< AnnualInterestRate << ","
		<< MonthlyInterestRate << ","
		<< MonthlyPayment << ","
		<< TotalPaidBack << ","
		<< TotalInterestPaid << ","
		<< NumPayments << "," 
		<< LastPaid << "," << endl;
	Out_Data.close();
}

void Loan::ReadToFile(string Loan_No)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv", ios::in);
	string csvLine;
	int i = 0;
	// read every line from the stream
	while (getline(file, csvLine))
	{
		istringstream csvStream(csvLine);
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 18)
			{
				if (i == 1)
					Name = csvElement;
				if (i == 2)
					CNIC = csvElement;
				if (i == 3)
					Email = csvElement;
				if (i == 4)
					Contact = csvElement;
				if (i == 5)
					City = csvElement;
				if (i == 6)
					Monthly_Income = csvElement;
				if (i == 7)
					Company_Name = csvElement;
				if (i == 8)
					Segment = csvElement;
				if (i == 9)
					BestDayToContactYou = csvElement;
				if (i == 10)
					CreationDate = csvElement;
				if (i == 11)
					LoanAmount = atof(csvElement.c_str());
				if (i == 12)
					AnnualInterestRate = atof(csvElement.c_str());
				if (i == 13)
					MonthlyInterestRate = atof(csvElement.c_str());
				if (i == 14)
					MonthlyPayment = atof(csvElement.c_str());
				if (i == 15)
					TotalPaidBack = atof(csvElement.c_str());
				if (i == 16)
					TotalInterestPaid = atof(csvElement.c_str());
				if (i == 17)
					NumPayments = atoi(csvElement.c_str());
				if (i == 18)
					LastPaid = csvElement;
				i++;
			}
			if (csvElement == Loan_No)
			{
				this->Loan_No = csvElement;
				i++;
			}
		}
	}
}

void Loan::ModifyToFile(string L_No)
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv", ios::in);
	myfile.open("Tmp.csv");
	if (!file.is_open())
	{
		cout << "File not found!\n";
		return;
	}
	// typedef to save typing for the following object
	typedef vector< vector<string> > csvVector;
	csvVector csvData;

	modifyCSV(file, csvData, L_No);
	// print out read data to prove reading worked
	for (csvVector::iterator i = csvData.begin(); i != csvData.end(); ++i)
	{
		for (vector<string>::iterator j = i->begin(); j != i->end(); ++j)
		{
			a = *j;
			myfile << a << ",";
		}
		myfile << "\n";
	}
	myfile.close();
	file.close();
	remove("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv");
	rename("Tmp.csv", "BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv");
}

/* Modify CSV File Function */
void Loan::modifyCSV(istream &input, vector< vector<string> > &output, string L_No)
{
	int i = 0;
	string csvLine;
	// read every line from the stream
	while (getline(input, csvLine))
	{
		istringstream csvStream(csvLine);
		vector<string> csvColumn;
		string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while (getline(csvStream, csvElement, ','))
		{
			if (i >= 1 && i <= 18)
			{
				if (i == 1)
					csvElement = Name;
				if (i == 2)
					csvElement = CNIC;
				if (i == 3)
					csvElement = Email;
				if (i == 4)
					csvElement = Contact;
				if (i == 5)
					csvElement = City;
				if (i == 6)
					csvElement = Monthly_Income;
				if (i == 7)
					csvElement = Company_Name;
				if (i == 8)
					csvElement = Segment;
				if (i == 9)
					csvElement = BestDayToContactYou;
				if (i == 10)
					csvElement = CreationDate;
				if (i == 11)
					csvElement = to_string(LoanAmount);
				if (i == 12)
					csvElement = to_string(AnnualInterestRate);
				if (i == 13)
					csvElement = to_string(MonthlyInterestRate);
				if (i == 14)
					csvElement = to_string(MonthlyPayment);
				if (i == 15)
					csvElement = to_string(TotalPaidBack);
				if (i == 16)
					csvElement = to_string(TotalInterestPaid);
				if (i == 17)
					csvElement = to_string(NumPayments);
				if (i == 18)
					csvElement = LastPaid;
				i++;
			}
			if (csvElement == L_No)
			{
				csvElement = this->Loan_No;
				i++;
			}
			csvColumn.push_back(csvElement);

		}
		output.push_back(csvColumn);
	}
}

void Loan::Loan_Registration()
{
	system("cls");
	string Str;
	Printing('-', '-');
	for (int i = 0; i < 15; i = i + 2)
	{
		if (i == 0)
			for (int j = 0; j < 79; j++)
			{
			gotoXY(j, 2);
			cout << '-';
			gotoXY(j, 22);
			cout << '-';
			}
		gotoXY(3, i + 4);
		cout << "|";
		gotoXY(32, i + 4);
		cout << "|";
	}
	this->Generate_Loan_No();
	gotoXY(30, 1);
	cout << "Loan Registration";
	gotoXY(7, 4);
	cout << "Name: ";
	gotoXY(7, 6);
	cout << "CNIC Number: ";
	gotoXY(7, 8);
	cout << "Email Address: ";
	gotoXY(7, 10);
	cout << "Contact No: ";
	gotoXY(7, 12);
	cout << "Monthly Income: ";
	gotoXY(7, 14);
	cout << "Company Name: ";
	gotoXY(7, 16);
	cout << "Segment: ";
	gotoXY(7, 18);
	cout << "Best Day to Contact You: ";
	gotoXY(3, 23);
	cout << "Status: Pending...";
	gotoXY(34, 4);
	fflush(stdin);
	getline(cin, Name);
	gotoXY(34, 6);
	fflush(stdin);
	getline(cin, CNIC);
	gotoXY(34, 8);
	fflush(stdin);
	getline(cin, Email);
	gotoXY(34, 10);
	fflush(stdin);
	getline(cin, Contact);
	gotoXY(34, 12);
	fflush(stdin);
	getline(cin, Monthly_Income);
	gotoXY(34, 14);
	fflush(stdin);
	getline(cin, Company_Name);
	gotoXY(34, 16);
	fflush(stdin);
	getline(cin, Segment);
	gotoXY(34, 18);
	fflush(stdin);
	getline(cin, BestDayToContactYou);
	gotoXY(11, 23);
	cout << "Successfully Done.";
	Sleep(1000);
	bool Flag = 0;
	if (atof(Monthly_Income.c_str()) > 25000)
	{
		gotoXY(11, 23);
		cout << "Your Loan Request Has Been Accepted.";
		Flag = 1;
	}
	else
	{
		gotoXY(11, 23);
		cout << "Your Loan Request Has Not Been Accepted.";
	}
	Sleep(1000);
	gotoXY(11, 23);
	cout << "Press Enter Key to Continue...       \b\b\b\b\b\b\b";
	gotoXY(79, 24);
	_getche();
	system("cls");
	srand(static_cast<unsigned int>(time(NULL)));
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	if (Flag == true)
	{
		gotoXY(19, 1);
		cout << "Home Loan EMI and Eligibility Calculations";
		gotoXY(4, 23);
		cout << "Status: Pending...";

		double LoanAmount, AnnualInterestRate, GrossAmount;
		int NumPayments;
		gotoXY(11, 7);
		cout << "-----------------------------------------------------------";
		gotoXY(13, 9);
		cout << "Enter Gross Monthly Income:    RS " << endl;
		gotoXY(13, 11);
		cout << "Enter the Amount of your Loan: RS " << endl;
		gotoXY(13, 13);
		cout << "Enter Your Annual Interest Rate: " << endl;
		gotoXY(13, 15);
		cout << "Enter the Number of Payments: " << endl;
		gotoXY(11, 17);
		cout << "-----------------------------------------------------------";
		gotoXY(47, 9);
		cin >> GrossAmount;
		gotoXY(47, 11);
		cin >> LoanAmount;
		gotoXY(47, 13);
		cin >> AnnualInterestRate;
		gotoXY(47, 15);
		cin >> NumPayments;
		Calculating_EMIs(LoanAmount, AnnualInterestRate, NumPayments);	// Calling Cal_EMIs
		Sleep(200);
		gotoXY(4, 23);
		cout << "Status: Press any Key to Continue...";
		_getch();
		EMIs_Display();
		{
			system("cls");
			Printing('-', '-');
			for (int j = 0; j < 79; j++)
			{
				gotoXY(j, 2);
				cout << '-';
				gotoXY(j, 22);
				cout << '-';
			}
			gotoXY(28, 1);
			cout << "Registration Successful";
			gotoXY(3, 23);
			cout << "Status: Pending...";
			gotoXY(5, 4);
			cout << "Congratulations your Loan registration has been successful.";
			gotoXY(5, 6);
			cout << "You can contact to any of the branch of bank soon...";
			gotoXY(5, 8);
			cout << "Kindly get your loan returened date in order to avoid any...";
			gotoXY(5, 10);
			cout << "...immediate circumstances.";
			this->Set_CreationDate();
			this->WriteToFile();
			gotoXY(3, 23);
			cout << "Status: Please Wait";
			for (int i = rand() % 3 + 3; i > 0; i--)
			{
				cout << '.';
				Sleep(700);
			}
		}
		this->Loan_Display();
	}
	else
	{
		gotoXY(27, 1);
		cout << "Registration Unsuccessful";
		gotoXY(3, 23);
		cout << "Status: Pending...";
		gotoXY(5, 4);
		cout << "Your Loan registration has not been successful...";
	}
	Sleep(1000);
	gotoXY(11, 23);
	cout << "Press Enter Key to Continue...";
	gotoXY(79, 24);
	_getche();
	gotoXY(79, 24);
}

char Loan::Loan_Options_Display()
{
	system("cls");
	Printing('*', ' ');
	gotoXY(32, 2);
	cout << "Loan Service" << endl;
	gotoXY(8, 5);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 7);
	cout << "Press \"1\" for Loan Status.";
	gotoXY(12, 9);
	cout << "Press \"2\" for Loan Installment.";
	gotoXY(12, 11);
	cout << "Press \"3\" for Home Loan (Registeration).";
	gotoXY(12, 13);
	cout << "Press \"4\" for Calculating EMIs";
	gotoXY(12, 15);
	cout << "Press \"5\" for Instructions.";
	gotoXY(12, 17);
	cout << "Press \"6\" for Main Menu.";
	gotoXY(8, 21);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 19);
	cout << "Enter Seletion: ";
	char CH;
	CH = _getche();
	Sleep(300);
	return CH;
}

void Loan::Loan_Display()
{
	for (int i = 9; i < 30; i++)
	{
		gotoXY(i * 2, 13);
		cout << '-';
		gotoXY(i * 2, 15);
		cout << '-';
		if (i < 18)
		{
			if (i != 17 && i != 16) {
				gotoXY(18, i + 5);
				cout << '-';
			}
			gotoXY(60, i + 4);
			cout << '-';
		}
		gotoXY(i * 2, 21);
		cout << '-';
	}
	gotoXY(29, 14);
	cout << "Loan No and Date/Time";
	gotoXY(24, 17);
	cout << "Loan ID:   " << Loan_No;
	gotoXY(24, 19);
	cout << "Date/Time: " << CreationDate;
	gotoXY(79, 24);
}

void Loan::Loan_Status()
{
	ofstream myfile;
	string a;
	fstream file("BANK MANAGEMENT SYSTEM (Copr. 2014 Project) - LOAN DATA.csv", ios::in);
	std::string line;
	int i = 0, j = 0;
	while (std::getline(file, line))
	{
		if (j == 12 || i == 0)
		{
			if (i != 0)
			{
				Sleep(1000);
				gotoXY(11, 23);
				cout << "Press Enter Key to Continue...";
				if (_getch() == ESC)
					break;
			}
			system("cls");
			Printing('-', '-');
			for (int j = 0; j < 79; j++)
			{
				gotoXY(j, 2);
				cout << '-';
				gotoXY(j, 22);
				cout << '-';
			}
			gotoXY(33, 1);
			cout << "Loan Status";
			gotoXY(3, 23);
			cout << "Status: Pending...";
		}
		const char *begin = line.c_str();

		// strip beyond first comma
		if (const char *end = strchr(begin, ','))
		{
			string column1(begin, end - begin);
			if (i > 1)
			{
				if (j == 12){
					j = 3;
				}
				gotoXY(4, (j) * 2);
				this->ReadToFile(column1);
				cout << "Loan Given To \"" << Name << "\", Last Paid: " << LastPaid;
				if (LastPaid != "Not Paid Yet.")
					cout << ".";
			}
			i++;
			j++;
		}
	}
}

void Loan::Status()
{
	if (Login() == true)
	{
		system("cls");
		Printing('-', '-');
		for (int j = 0; j < 79; j++)
		{
			gotoXY(j, 2);
			cout << '-';
			gotoXY(j, 22);
			cout << '-';
		}
		gotoXY(30, 1);
		cout << "Home Loan Status";
		gotoXY(4, 23);
		cout << "Status: Pending...";
		gotoXY(17, 5);
		cout << "----------------------------------------------";
		gotoXY(20, 7);
		cout << "Loan ID:         " << Loan_No;
		gotoXY(20, 9);
		cout << "Loan Amount:     " << LoanAmount;
		gotoXY(20, 11);
		cout << "Monthly Payment: " << MonthlyPayment << " Rupees";
		gotoXY(20, 13);
		cout << "Total Paid Back: " << TotalPaidBack << " Rupees";
		gotoXY(20, 15);
		cout << "Left Months:     " << NumPayments;
		gotoXY(20, 17);
		cout << "Last Paid:       " << LastPaid;
		gotoXY(17, 19);
		cout << "----------------------------------------------";

	}
	else
	{
		gotoXY(4, 23);
		cout << "Status: Loan ID Not Found...";
		Sleep(1000);

	}
	gotoXY(4, 23);
	cout << "Status: Press any Key to Continue...";
	_getch();
}

bool Loan::Login()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(28, 1);
	cout << "Login your Loan ID";
	gotoXY(4, 23);
	cout << "Status: Pending...";
	gotoXY(20, 9);
	cout << "--------------------------------------";
	gotoXY(23, 11);
	cout << "Enter Loan ID: ";
	gotoXY(20, 13);
	cout << "--------------------------------------";
	string ID;
	gotoXY(38, 11);
	cin >> ID;
	ReadToFile(ID);
	if (ID == Loan_No)
		return true;
	return false;
}

void Loan::Loan_Installment()
{
	if (Login() == true)
	{
		system("cls");
		Printing('-', '-');
		for (int j = 0; j < 79; j++)
		{
			gotoXY(j, 2);
			cout << '-';
			gotoXY(j, 22);
			cout << '-';
		}
		gotoXY(28, 1);
		cout << "Home Loan Installment";
		gotoXY(4, 23);
		cout << "Status: Pending...";
		string AC_ID, AC_Pass;
		gotoXY(17, 8);
		cout << "----------------------------------------------";
		gotoXY(20, 10);
		cout << "Loan ID:                " << Loan_No;
		gotoXY(20, 12);
		cout << "Enter Account ID:       " << AC_ID;
		gotoXY(20, 14);
		cout << "Enter Account Password: " << AC_Pass;
		gotoXY(17, 16);
		cout << "----------------------------------------------";
		gotoXY(44, 12);
		cin >> AC_ID;
		gotoXY(44, 14);
		cin >> AC_Pass;
		Account *NewAC;
		if (AC_ID[0] == 'C')
			NewAC = new Current_Account;
		else if (AC_ID[0] == 'S')
			NewAC = new Saving_Account;
		else
			goto Break;
		NewAC->ReadToFile(AC_ID);
		if (NewAC->Get_Balance() > this->MonthlyPayment)
		{
			if (NumPayments == 0)
			{
				gotoXY(4, 23);
				cout << "Status: Your Have No Installment...";
				goto Break_Yes;
			}
			NumPayments -= 1;
			LastPaid = Generate_DateandTime();
			NewAC->Set_Balance(NewAC->Get_Balance() - MonthlyPayment);
			gotoXY(4, 23);
			NewAC->ModifyToFile(AC_ID);
			this->ModifyToFile(Loan_No);
			cout << "Status: Successfully Installment...";
			delete NewAC;
			Sleep(1000);
		}
		else
		{
			Break:
			gotoXY(4, 23);
			cout << "Status: Unsuccessfully Installment...";
			Sleep(1000);
		}
	}
	else
	{
		gotoXY(4, 23);
		cout << "Status: Loan ID Not Found...";
		Break_Yes:
		Sleep(1000);
	}
	gotoXY(4, 23);
	cout << "Status: Press any Key to Continue...";
	_getch();
}

void Loan::Calculating_EMIs(double LoanAmount, double AnnualInterestRate, int NumPayments)
{
	this->LoanAmount = LoanAmount;
	this->AnnualInterestRate = AnnualInterestRate;
	this->NumPayments = NumPayments;

	MonthlyInterestRate = AnnualInterestRate / 12;

	MonthlyPayment = ((MonthlyInterestRate *
		pow(1.0 + MonthlyInterestRate, NumPayments)) /
		(pow(1.0 + MonthlyInterestRate, NumPayments)
		- 1)) * LoanAmount;

	TotalPaidBack = MonthlyPayment * NumPayments;

	TotalInterestPaid = TotalPaidBack - LoanAmount;
	return;
}

void Loan::EMIs_Display()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
	gotoXY(16, 1);
	cout << "Home Loan EMI and Eligibility Calculator Result";
	gotoXY(4, 23);
	cout << "Status: Pending...";
	gotoXY(8, 5);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 7);
	cout << fixed << setprecision(2) << showpoint;
	cout << setw(24) << left << "Loan Amount: ";
	cout << "Rs " << LoanAmount << endl;
	gotoXY(12, 9);
	cout << fixed << setprecision(5) << showpoint;
	cout << setw(24) << "Monthly Interest Rate: ";
	cout << MonthlyInterestRate * 100 << "%" << endl;
	gotoXY(12, 11);
	cout << setw(24) << "Number of Payments: ";
	if (NumPayments > 1)
		cout << NumPayments << " Months" << endl;
	else
		cout << NumPayments << " Month" << endl;
	gotoXY(12, 13);
	cout << fixed << setprecision(2) << showpoint;
	cout << setw(24) << "Monthly Payment: ";
	cout << "Rs " << MonthlyPayment << endl;
	gotoXY(12, 15);
	cout << setw(24) << "Amount Paid Back: ";
	cout << "Rs " << TotalPaidBack << endl;
	gotoXY(12, 17);
	cout << setw(24) << "Interest Paid: ";
	cout << "Rs " << TotalInterestPaid << endl;
	gotoXY(8, 19);
	cout << "----------------------------------------------------------------";
	gotoXY(4, 23);
	cout << "Status: Successfully Calculated...";
	Sleep(1500);
	gotoXY(4, 23);
	cout << "Status: Press any Key to Continue...";
	_getch();
}

void gotoXY(int x, int y)			// gotoXY Function 
{
	CursorPosition.X = x;			// Locates column
	CursorPosition.Y = y;			// Locates Row
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
} //end gotoXY Function

/* Printing Function */
void Printing(char Prt, char Spc)
{
	system("cls");
	for (int i = 0; i < 40; i++)
	{
		gotoXY(i * 2, 0);
		cout << Prt << Spc;
		if (i < 24)
		{
			gotoXY(0, i + 1);
			cout << Prt;
			gotoXY(79, i + 1);
			cout << Prt;
		}
		gotoXY(i * 2, 24);
		cout << Prt << Spc;
	}
	gotoXY(0, 0);
}

/* Main Display Function */
char Main_Display()
{
	system("cls");
	Printing('*', ' ');
	gotoXY(29, 02);
	cout << "Bank Management System" << endl;
	gotoXY(8, 5);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 7);
	cout << "Press \"1\" for Login your Account.";
	gotoXY(12, 9);
	cout << "Press \"2\" for Administrator Login.";
	gotoXY(12, 11);
	cout << "Press \"3\" for Registration your Account.";
	gotoXY(12, 13);
	cout << "Press \"4\" for Home Loan.";
	gotoXY(12, 15);
	cout << "Press \"5\" for Instructions(Login/Administrator/Loan).";
	gotoXY(12, 17);
	cout << "Press \"6\" for exit.";
	gotoXY(8, 21);
	cout << "----------------------------------------------------------------";
	gotoXY(12, 19);
	cout << "Enter Seletion: ";
	char CH;
	CH = _getche();
	Sleep(300);
	return CH;
} //end Main_Display Function

/* Welcome Function */
void Welcome()
{
	Printing('*', ' ');
	gotoXY(23, 10);
	cout << "WELCOME TO BANK MANAGEMENT SYSTEM" << endl;
	gotoXY(30, 12);
	cout << "Copr. Project 2014" << endl;
	gotoXY(79, 24);
	Sleep(1000);
} //end Welcome Function

/* Instruction Function */
void Instructions()
{
	system("cls");
	Printing('-', '-');
	for (int j = 0; j < 79; j++)
	{
		gotoXY(j, 2);
		cout << '-';
		gotoXY(j, 22);
		cout << '-';
	}
		gotoXY(27, 1);
		cout << "Important Instructions  \b\b";
		gotoXY(4, 5);
		cout << "In this programe, you can register new account/administrator.";
		gotoXY(4, 7);
		cout << "If you want to back any menu then you Press ESC (Press One/Two Times).";
		gotoXY(4, 9);
		cout << "If you have Saving Account your initial Account Id letter will be \"S\".";
		gotoXY(4, 11);
		cout << "If you have Current Account your initial Account Id letter will be \"C\".";
		gotoXY(4, 13);
		cout << "You can check your status in one click by prividing Account ID.";
		gotoXY(4, 15);
		cout << "After Registration, your Account ID and Password will be shown by Auto.";
		gotoXY(4, 17);
		cout << "If you want to close your account, So you have to Contact Administrator.";
}

/* Generate Date and Time Function */
string Generate_DateandTime()
{
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	strftime(buffer, 80, "%d-%m-%Y %I:%M:%S", timeinfo);
	string str(buffer);
	return str;
}

/* ESC Function */
void PRESS_ESC(char CH)
{
	if (CH == ESC)		// If Press ESC
		main();
	return;
}

/* MAIN FUNCTION */
int main()
{
	system("cls");
	system("color 77");
	static int Z = 0;
	if (Z == 0)
		Welcome();
	Z++;
	system("cls");
	srand(static_cast<unsigned int>(time(NULL)));
	Account *NewAccount;
	Administrator *Admin;
	Loan *L;
	do
	{
		switch (Main_Display())					// Main_Display Function
		{
		case '1':
		{
			system("cls");
			Printing('-', '-');
			for (int j = 0; j < 79; j++)
			{
				gotoXY(j, 2);
				cout << '-';
				gotoXY(j, 22);
				cout << '-';
			}
			gotoXY(30, 1);
			cout << "Login Your Account";
			gotoXY(24, 8);
			cout << "---------------------------------";
			gotoXY(30, 10);
			cout << "Account ID: ";
			gotoXY(30, 12);
			cout << "Password: ";
			gotoXY(24, 14);
			cout << "---------------------------------";
			gotoXY(42, 10);
		Again:
			gotoXY(3, 23);
			cout << "Status: Pending...";
			char ID[11];
			char Pass[11];
			for (int i = 0; i < 20; i++)
			{
				gotoXY(i + 41, 10);
				cout << ' ';
			}
			for (int i = 0; i < 50; i++)
			{
				gotoXY(i + 40, 12);
				cout << ' ';
			}
			fflush(stdin);
			gotoXY(40, 10);
			int i = -1;
			do
			{
				if (i == 10)
				{
					gotoXY(31, 17);
					gotoXY(11, 23);
					cout << "Invalid ID.";
					break;
				}
			BackSpac:
				int TMP = i;
				gotoXY(43 + i, 10);
				ID[++i] = _getch();
				PRESS_ESC(ID[i]);
				if (ID[i] == BS)
				{
					if (i != 0) {
						ID[i--] = '\0';
						cout << " \b";
						i--;
					}
					else
						i = TMP;
					goto BackSpac;
				}
				if (i == 0)
				{
					if (ID[0] == 'S')
					{
						NewAccount = new Saving_Account;
					}
					else if (ID[0] == 'C')
					{
						NewAccount = new Current_Account;
					}
					else
					{
						gotoXY(11, 23);
						cout << "Invalid Initial Letter.";
						Sleep(700);
						for (int i = 0; i < 30; i++)
						{
							gotoXY(11 + i, 23);
							cout << " ";
						}
						goto Again;
					}
				}
				if (ID[i] != '\r')
				{
					cout << ID[i];
				}
			} while (ID[i] != '\r');
			ID[i] = '\0';
			i = -1;
			do
			{
				if (i == 10)
				{
					gotoXY(31, 17);
					gotoXY(11, 23);
					cout << "Invalid Password.";
					break;
				}
			BackSpac1:
				int TMP = i;
				gotoXY(43 + i, 12);
				Pass[++i] = _getch();
				PRESS_ESC(ID[i]);
				if (Pass[i] == BS)
				{
					if (i != 0) {
						Pass[i--] = '\0';
						cout << " \b";
						i--;
					}
					else
						i = TMP;
					goto BackSpac1;
				}
				if (Pass[i] != '\r')
				{
					cout << "*";
				}
			} while (Pass[i] != '\r');
			Pass[i] = '\0';
			string Password(Pass);
			string AC_No(ID);
			gotoXY(11, 23);
			if (NewAccount->Login_Account(AC_No, Password) == 1)
			{
				NewAccount->ReadToFile(AC_No);
				cout << "Successfully Login.";
			Back_Menu:
				system("cls");
				Printing('*', ' ');
				switch (NewAccount->Account_Display())
				{
				case '1':
				{
					system("cls");
					cout << *NewAccount;
					break;
				} // end case 1
				case '2':
				{
					system("cls");
					// Transfer Money
					NewAccount->Transfer_Balance("", 0); // Assume 0
					break;
				}
				case '3':
				{
					system("cls");
					Printing('-', '-');
					for (int j = 0; j < 79; j++)
					{
						gotoXY(j, 2);
						cout << '-';
						gotoXY(j, 22);
						cout << '-';
					}
					gotoXY(30, 1);
					cout << "Enter Amount";
					gotoXY(3, 23);
					cout << "Status: Pending...";
					gotoXY(17, 10);
					cout << "==============================================";
					gotoXY(17, 14);
					cout << "==============================================";
					gotoXY(20, 12);
					double Amount;
					cout << "Enter Amount to Deposit: ";
					gotoXY(45, 12);
					cin >> Amount;
					system("cls");
					NewAccount->Deposit(Amount);
					NewAccount->ModifyToFile(AC_No);
					break;
				} // end case 2
				case '4':
				{
					system("cls");
					Printing('-', '-');
					for (int j = 0; j < 79; j++)
					{
						gotoXY(j, 2);
						cout << '-';
						gotoXY(j, 22);
						cout << '-';
					}
					gotoXY(30, 1);
					cout << "Enter Amount";
					gotoXY(3, 23);
					cout << "Status: Pending...";
					gotoXY(17, 10);
					cout << "==============================================";
					gotoXY(17, 14);
					cout << "==============================================";
					gotoXY(20, 12);
					double Amount;
					cout << "Enter Amount to Withdraw: ";
					gotoXY(46, 12);
					cin >> Amount;
					system("cls");
					NewAccount->Withdraw(Amount);
					NewAccount->ModifyToFile(AC_No);
					break;
				} // end case 3
				case '5':
				{
					system("cls");
					NewAccount->Change_Type(AC_No);
					AC_No = NewAccount->Get_Account_No();
					break;
				} // end case 4
				case '6':
				{
					system("cls");
					NewAccount->Change_Pass(AC_No);
					break;
				} // end case 5
				case '7':
				{
					main();
					break;
				} // end case 6
				default:
				{
					break;
				} //end defualt
				} // end switch-case
			}
			else
			{
				cout << "Account ID or Password You Entered is Incorret.";
				Sleep(1500);
				for (int i = 0; i < 50; i++)
				{
					gotoXY(i + 11, 23);
					cout << ' ';
				}
				goto Again;
			}
			Sleep(1500);
			for (int i = 0; i < 60; i++)
			{
				gotoXY(i + 11, 23);
				cout << ' ';
			}
			gotoXY(11, 23);
			cout << "Press Enter Key to Continue...";
			_getch();
			goto Back_Menu;
			break;
		} // end case
		case '2':
		{
			system("cls");
			Printing('-', '-');
			for (int j = 0; j < 79; j++)
			{
				gotoXY(j, 2);
				cout << '-';
				gotoXY(j, 22);
				cout << '-';
			}
			gotoXY(15, 1);
			cout << "Login Your Account (Only For Administrator)";
			gotoXY(24, 8);
			cout << "---------------------------------";
			gotoXY(30, 10);
			cout << "Admin ID: ";
			gotoXY(30, 12);
			cout << "Password: ";
			gotoXY(24, 14);
			cout << "---------------------------------";
			gotoXY(42, 10);
		Again_Adm:
			gotoXY(3, 23);
			cout << "Status: Pending...";
			char Adm[11];
			char Pass[11];
			for (int i = 0; i < 20; i++)
			{
				gotoXY(i + 40, 10);
				cout << ' ';
			}
			for (int i = 0; i < 50; i++)
			{
				gotoXY(i + 40, 12);
				cout << ' ';
			}
			fflush(stdin);
			gotoXY(40, 10);
			int i = -1;
			do
			{
				if (i == 10)
				{
					gotoXY(31, 17);
					gotoXY(11, 23);
					cout << "Invalid ID.";
					break;
				}
				gotoXY(41 + i, 10);
				Adm[++i] = _getch();
				PRESS_ESC(Adm[i]);
				if (Adm[i] != '\r')
				{
					cout << Adm[i];
				}
			} while (Adm[i] != '\r');
			Adm[i] = '\0';
			gotoXY(40, 12);
			i = -1;
			do
			{
				if (i == 10)
				{
					gotoXY(31, 17);
					gotoXY(11, 23);
					cout << "Invalid Password.";
					break;
				}
				gotoXY(41 + i, 12);
				Pass[++i] = _getch();
				PRESS_ESC(Pass[i]);
				if (Pass[i] != '\r')
				{
					cout << "*";
				}
			} while (Pass[i] != '\r');
			Pass[i] = '\0';
			Admin = new Administrator;
			string Password(Pass);
			string ADM_No(Adm);
			gotoXY(11, 23);
			if (Admin->Login_ADM(ADM_No, Password) == 1)
			{
			BACK_ADM:
				cout << "Successfully Login.";
			Back_Menu_ADM:
				Admin->ReadToFile_ADM(ADM_No);
				system("cls");
				Printing('*', ' ');
				switch (Admin->Administrator_Dispaly())
				{
				case '1':
				{
					system("cls");
					Printing('-', '-');
					for (int j = 0; j < 79; j++)
					{
						gotoXY(j, 2);
						cout << '-';
						gotoXY(j, 22);
						cout << '-';
					}
					gotoXY(31, 1);
					cout << "Enter Account ID";
					gotoXY(24, 8);
					cout << "---------------------------------";
					gotoXY(30, 10);
					cout << "Account ID: ";
					gotoXY(30, 12);
					cout << "*Password: ";
					gotoXY(24, 14);
					cout << "---------------------------------";
					gotoXY(42, 10);
				Again_1:
					gotoXY(3, 23);
					cout << "Status: Pending...";
					char ID[11];
					char Pass[11];
					for (int i = 0; i < 20; i++)
					{
						gotoXY(i + 41, 10);
						cout << ' ';
					}
					for (int i = 0; i < 50; i++)
					{
						gotoXY(i + 40, 12);
						cout << ' ';
					}
					fflush(stdin);
					gotoXY(40, 10);
					int i = -1;
					do
					{
						if (i == 10)
						{
							gotoXY(31, 17);
							gotoXY(11, 23);
							cout << "Invalid ID.";
							break;
						}
						gotoXY(43 + i, 10);
						ID[++i] = _getch();
						PRESS_ESC(ID[i]);
						if (i == 0)
						{
							if (ID[0] == 'S')
							{
								NewAccount = new Saving_Account;
							}
							else if (ID[0] == 'C')
							{
								NewAccount = new Current_Account;
							}
							else
							{
								gotoXY(11, 23);
								cout << "Invalid Initial Letter.";
								Sleep(700);
								for (int i = 0; i < 30; i++)
								{
									gotoXY(11 + i, 23);
									cout << " ";
								}
								goto Again_1;
							}
						}
						if (ID[i] != '\r')
						{
							cout << ID[i];
						}
					} while (ID[i] != '\r');
					ID[i] = '\0';
					i = -1;
					do
					{
						if (i == 10)
						{
							gotoXY(31, 17);
							gotoXY(11, 23);
							cout << "Invalid Password.";
							break;
						}
						gotoXY(43 + i, 12);
						Pass[++i] = _getch();
						PRESS_ESC(Pass[i]);
						if (Pass[i] != '\r')
						{
							cout << "*";
						}
					} while (Pass[i] != '\r');
					Pass[i] = '\0';
					string Password(Pass);
					string AC_No(ID);
					gotoXY(11, 23);
					NewAccount->ReadToFile(AC_No);
					if (NewAccount->Login_Account(AC_No, NewAccount->Get_Account_Password()) == 1)
					{
						cout << "Successfully Login.";
					Back_Menu_ADMIN:
						system("cls");
						Printing('*', ' ');
						Admin->ReadToFile(AC_No);
						switch (Admin->Manage_Accounts_Display())
						{
						case '1':
						{
							system("cls");
							cout << *NewAccount;
							break;
						} // end case 1
						case '2':
						{
							system("cls");
							Printing('-', '-');
							for (int j = 0; j < 79; j++)
							{
								gotoXY(j, 2);
								cout << '-';
								gotoXY(j, 22);
								cout << '-';
							}
							gotoXY(30, 1);
							cout << "Enter Amount";
							gotoXY(3, 23);
							cout << "Status: Pending...";
							gotoXY(14, 10);
							cout << "==================================================";
							gotoXY(14, 14);
							cout << "==================================================";
							gotoXY(16, 12);
							double Amount;
							cout << "Enter Amount to Deposit/Withdraw(+/-): ";
							gotoXY(55, 12);
							char CH = _getche();
							cin >> Amount;
							system("cls");
							NewAccount->Change_Balance(CH, Amount);
							NewAccount->ModifyToFile(AC_No);
							break;
						} // end case 2
						case '3':
						{
							system("cls");
							NewAccount->ReadToFile(AC_No);
							string Str;
							Printing('-', '-');
							for (int i = 0; i < 14; i = i + 2)
							{
								if (i == 0)
									for (int j = 0; j < 79; j++)
									{
									gotoXY(j, 2);
									cout << '-';
									gotoXY(j, 22);
									cout << '-';
									}
								gotoXY(3, i + 4);
								cout << "|";
								gotoXY(26, i + 4);
								cout << "|";
							}
							gotoXY(20, 1);
							cout << "Enter Account Type And Personal Detail";
							gotoXY(5, 4);
							cout << "Name: ";
							gotoXY(5, 6);
							cout << "Father/Husband Name: ";
							gotoXY(5, 8);
							cout << "Date of Birth: ";
							gotoXY(5, 10);
							cout << "Gender: ";
							gotoXY(5, 12);
							cout << "Occupation: ";
							gotoXY(5, 14);
							cout << "Qualification: ";
							gotoXY(5, 16);
							cout << "Phone Number: ";
							gotoXY(3, 23);
							cout << "Status: Pending...";
							gotoXY(28, 4);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Name(Str);
							gotoXY(28, 6);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Father_Husband_Name(Str);
							gotoXY(28, 8);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_DateofBirth(Str);
							gotoXY(28, 10);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Gender(Str);
							gotoXY(28, 12);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Occupation(Str);
							gotoXY(28, 14);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Education_Qualification(Str);
							gotoXY(28, 16);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Phone_No(Str);
							gotoXY(11, 23);
							cout << "Successfully Done.";
							Sleep(1000);
							gotoXY(11, 23);
							cout << "Press Enter Key to Continue...";
							_getch();
							system("cls");
							Printing('-', '-');
							for (int i = 0; i < 7; i = i + 2)
							{
								if (i == 0)
									for (int j = 0; j < 79; j++)
									{
									gotoXY(j, 2);
									cout << '-';
									gotoXY(j, 22);
									cout << '-';
									}
								gotoXY(3, i + 4);
								cout << "|";
								gotoXY(20, i + 4);
								cout << "|";
							}
							gotoXY(33, 1);
							cout << "Enter Address";
							gotoXY(5, 4);
							cout << "Address: ";
							gotoXY(5, 6);
							cout << "City: ";
							gotoXY(5, 8);
							cout << "State: ";
							gotoXY(5, 10);
							cout << "Postal Code: ";
							gotoXY(3, 23);
							cout << "Status: Pending...";
							gotoXY(22, 4);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_Address(Str);
							gotoXY(22, 6);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_City(Str);
							gotoXY(22, 8);
							fflush(stdin);
							getline(cin, Str);
							if (Str != "")
								NewAccount->Set_State(Str);
							gotoXY(22, 10);
							fflush(stdin);
							if (Str != "")
								getline(cin, Str);
							NewAccount->Set_Postal_Code(Str);
							NewAccount->ModifyToFile(AC_No);		// Write to File
							gotoXY(11, 23);
							cout << "Your Account Has Been Modified.";
							Sleep(1000);
							gotoXY(11, 23);
							cout << "Press Enter Key to Continue... \b";
							break;
						} // end case 3
						case '4':
						{
							system("cls");
							NewAccount->ReadToFile(AC_No);
							NewAccount->Generate_AC_Password();
							Printing('-', '-');
							for (int j = 0; j < 79; j++)
							{
								gotoXY(j, 2);
								cout << '-';
								gotoXY(j, 22);
								cout << '-';
							}
							gotoXY(28, 1);
							cout << "Password Reset Successful";
							gotoXY(3, 23);
							cout << "Status: Pending...\b\b\b\b\b\b\b\b\b\b          ";
							gotoXY(5, 4);
							cout << "Congratulations your account Password has been reset successful.";
							gotoXY(5, 6);
							cout << "Your access code will be appear on your screen in a short time.";
							gotoXY(5, 8);
							cout << "You can change or reset the password for your also account ID...";
							gotoXY(5, 10);
							cout << "...by providing some information.";
							gotoXY(3, 23);
							cout << "Status: Please Wait";
							for (int i = rand() % 3 + 3; i > 0; i--)
							{
								cout << '.';
								Sleep(700);
							}
							NewAccount->Password_Display();
							gotoXY(41, 17);
							cout << NewAccount->Get_Account_No();
							gotoXY(41, 19);
							cout << NewAccount->Get_Account_Password();
							NewAccount->ModifyToFile(AC_No);
							break;
						} // end case 4
						case '5':
						{
							system("cls");
							Printing('-', ' ');
							gotoXY(4, 2);
							cout << "Account \"" << NewAccount->Get_Account_No() << "\" has been Deleted Successfully.";
							NewAccount->deleteAccount(AC_No);
							Sleep(1500);
							main();
							break;
						} // end case 5
						case '6':
						{
							goto BACK_ADM;
							break;
						} // end case 6
						default:
						{
							break;
						} //end defualt
						} // end switch-case
					}
					else
					{
						cout << "Account ID or Password You Entered is Incorret.";
						Sleep(1500);
						for (int i = 0; i < 50; i++)
						{
							gotoXY(i + 11, 23);
							cout << ' ';
						}
						goto Again_1;
					}
					Sleep(1500);
					for (int i = 0; i < 50; i++)
					{
						gotoXY(i + 11, 23);
						cout << ' ';
					}
					gotoXY(11, 23);
					cout << "Press Enter Key to Continue...";
					_getch();
					goto Back_Menu_ADMIN;
					break;
				} // end case 1
				case '2':
				{
					system("cls");
					NewAccount->Accounts_Status();
					break;
				} // end case 2
				case '3':
				{
					system("cls");
					L = new Loan;
					L->Loan_Status();
					delete L;
					break;
				} // end case 3
				case '4':
				{
					system("cls");
					Admin = NULL;
					string Str;
					Printing('-', '-');
					for (int i = 0; i < 15; i = i + 2)
					{
						if (i == 0)
							for (int j = 0; j < 79; j++)
							{
							gotoXY(j, 2);
							cout << '-';
							gotoXY(j, 22);
							cout << '-';
							}
						gotoXY(3, i + 4);
						cout << "|";
						gotoXY(26, i + 4);
						cout << "|";
					}
					Admin = new Administrator;
					Admin->Generate_AC_No();
					Admin->Generate_AC_DT();
					gotoXY(21, 1);
					cout << "Enter Admin Type And Personal Detail";
					gotoXY(5, 4);
					cout << "Admin Type: ";
					gotoXY(5, 6);
					cout << "Name: ";
					gotoXY(5, 8);
					cout << "Father/Husband Name: ";
					gotoXY(5, 10);
					cout << "Date of Birth: ";
					gotoXY(5, 12);
					cout << "Gender: ";
					gotoXY(5, 14);
					cout << "Occupation: ";
					gotoXY(5, 16);
					cout << "Qualification: ";
					gotoXY(5, 18);
					cout << "Phone Number: ";
					gotoXY(3, 23);
					cout << "Status: Pending...";
					gotoXY(28, 4);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Type(Str);
				Back_Agian:
					gotoXY(28, 6);
					fflush(stdin);
					getline(cin, Str);
					if (Str != "")
					{
						Admin->Set_Name(Str);
						Admin->Set_Admin_Name(Str);
					}
					else
					{
						gotoXY(11, 23);
						cout << "Account Name must be Entered.";
						for (int i = 0; i < 30; i++)
						{
							gotoXY(i + 28, 6);
							cout << ' ';
						}
						goto Back_Agian;
					}
					for (int i = 0; i < 30; i++)
					{
						gotoXY(i + 10, 23);
						cout << ' ';
					}
					gotoXY(3, 23);
					cout << "Status: Pending...";
					gotoXY(28, 8);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Father_Husband_Name(Str);
					gotoXY(28, 10);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_DateofBirth(Str);
					gotoXY(28, 12);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Gender(Str);
					gotoXY(28, 14);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Occupation(Str);
					gotoXY(28, 16);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Education_Qualification(Str);
					gotoXY(28, 18);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Phone_No(Str);
					gotoXY(11, 23);
					cout << "Successfully Done.";
					Sleep(1000);
					gotoXY(11, 23);
					cout << "Press Enter Key to Continue...";
					_getch();
					system("cls");
					Printing('-', '-');
					for (int i = 0; i < 7; i = i + 2)
					{
						if (i == 0)
							for (int j = 0; j < 79; j++)
							{
							gotoXY(j, 2);
							cout << '-';
							gotoXY(j, 22);
							cout << '-';
							}
						gotoXY(3, i + 4);
						cout << "|";
						gotoXY(20, i + 4);
						cout << "|";
					}
					gotoXY(33, 1);
					cout << "Enter Address";
					gotoXY(5, 4);
					cout << "Address: ";
					gotoXY(5, 6);
					cout << "City: ";
					gotoXY(5, 8);
					cout << "State: ";
					gotoXY(5, 10);
					cout << "Postal Code: ";
					gotoXY(3, 23);
					cout << "Status: Pending...";
					gotoXY(22, 4);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Address(Str);
					gotoXY(22, 6);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_City(Str);
					gotoXY(22, 8);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_State(Str);
					gotoXY(22, 10);
					fflush(stdin);
					getline(cin, Str);
					Admin->Set_Postal_Code(Str);
					Admin->WriteToFile_ADM();		// Write to File
					gotoXY(11, 23);
					cout << "Your Admin AC Has Been Created.";
					Sleep(1000);
					gotoXY(11, 23);
					cout << "Press Enter Key to Continue... \b";
					_getche();
					{
						system("cls");
						srand(static_cast<unsigned int>(time(NULL)));
						Printing('-', '-');
						for (int j = 0; j < 79; j++)
						{
							gotoXY(j, 2);
							cout << '-';
							gotoXY(j, 22);
							cout << '-';
						}
						gotoXY(28, 1);
						cout << "Registration Successful";
						gotoXY(3, 23);
						cout << "Status: Pending...";
						gotoXY(5, 4);
						cout << "Congratulations your admin account registration has been successful.";
						gotoXY(5, 6);
						cout << "Your access code will be appear on your screen in a short time.";
						gotoXY(5, 8);
						cout << "You can change or reset the password for your account ID...";
						gotoXY(5, 10);
						cout << "...by providing some information.";
						gotoXY(3, 23);
						cout << "Status: Please Wait";
						for (int i = rand() % 3 + 3; i > 0; i--)
						{
							cout << '.';
							Sleep(700);
						}
						NewAccount->Password_Display();
						gotoXY(41, 17);
						cout << Admin->Get_Admin_Name();
						gotoXY(41, 19);
						cout << Admin->Get_Admin_Password();
					}
					Sleep(1000);
					gotoXY(11, 23);
					cout << "Press Enter Key to Go Main Menu...";
					_getch();
					main();
					break;
				} // end case 3
				case '5':
				{
					system("cls");
					Admin->Change_Name_ADM(ADM_No);
					ADM_No = Admin->Get_Admin_Name();
					break;
				} // end case 4
				case '6':
				{
					system("cls");
					Admin->Change_Pass_ADM(ADM_No);
					ADM_No = Admin->Get_Admin_Password();
					break;
				} // end case 5
				case '7':
				{
					main();
					break;
				} // end case 6
				default:
				{
					break;
				} //end defualt
				} // end switch-case
			}
			else
			{
				cout << "Admin ID or Password You Entered is Incorret.";
				Sleep(1500);
				for (int i = 0; i < 50; i++)
				{
					gotoXY(i + 11, 23);
					cout << ' ';
				}
				goto Again_Adm;
			}
			Sleep(1500);
			for (int i = 0; i < 50; i++)
			{
				gotoXY(i + 11, 23);
				cout << ' ';
			}
			gotoXY(11, 23);
			cout << "Press Enter Key to Continue...";
			_getch();
			goto Back_Menu_ADM;
			break;
		} // end case
		case '3':
		{
			system("cls");
			NewAccount = NULL;
			string AccountType, Str;
			Printing('-', '-');
			for (int i = 0; i < 15; i = i + 2)
			{
				if (i == 0)
					for (int j = 0; j < 79; j++)
					{
					gotoXY(j, 2);
					cout << '-';
					gotoXY(j, 22);
					cout << '-';
					}
				gotoXY(3, i + 4);
				cout << "|";
				gotoXY(26, i + 4);
				cout << "|";
			}
			gotoXY(20, 1);
			cout << "Enter Account Type And Personal Detail";
			gotoXY(5, 4);
			cout << "Account Type: ";
			gotoXY(5, 6);
			cout << "Name: ";
			gotoXY(5, 8);
			cout << "Father/Husband Name: ";
			gotoXY(5, 10);
			cout << "Date of Birth: ";
			gotoXY(5, 12);
			cout << "Gender: ";
			gotoXY(5, 14);
			cout << "Occupation: ";
			gotoXY(5, 16);
			cout << "Qualification: ";
			gotoXY(5, 18);
			cout << "Phone Number: ";
			gotoXY(3, 23);
			cout << "Status: Pending...";
		Back:
			gotoXY(28, 4);
			fflush(stdin);
			getline(cin, AccountType);
			if (AccountType == "Current" || AccountType == "current")
			{
				NewAccount = new Current_Account;
				NewAccount->Set_Type("Current");
			}
			else if (AccountType == "Saving" || AccountType == "saving")
			{
				NewAccount = new Saving_Account;
				NewAccount->Set_Type("Saving");
			}
			else
			{
				gotoXY(11, 23);
				cout << "Account Type is not Correct.";
				for (int i = 0; i < 20; i++)
				{
					gotoXY(i + 28, 4);
					cout << ' ';
				}
				goto Back;
			}
			NewAccount->Generate_AC_No();
			NewAccount->Generate_AC_Password();
			NewAccount->Generate_AC_DT();
			for (int i = 0; i < 30; i++)
			{
				gotoXY(i + 11, 23);
				cout << ' ';
			}
			gotoXY(11, 23);
			cout << "Pending...";
			gotoXY(5, 4);
			gotoXY(28, 6);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Name(Str);
			gotoXY(28, 8);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Father_Husband_Name(Str);
			gotoXY(28, 10);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_DateofBirth(Str);
			gotoXY(28, 12);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Gender(Str);
			gotoXY(28, 14);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Occupation(Str);
			gotoXY(28, 16);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Education_Qualification(Str);
			gotoXY(28, 18);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Phone_No(Str);
			gotoXY(11, 23);
			cout << "Successfully Done.";
			Sleep(1000);
			gotoXY(11, 23);
			cout << "Press Enter Key to Continue...";
			_getch();
			system("cls");
			Printing('-', '-');
			for (int i = 0; i < 7; i = i + 2)
			{
				if (i == 0)
					for (int j = 0; j < 79; j++)
					{
					gotoXY(j, 2);
					cout << '-';
					gotoXY(j, 22);
					cout << '-';
					}
				gotoXY(3, i + 4);
				cout << "|";
				gotoXY(20, i + 4);
				cout << "|";
			}
			gotoXY(33, 1);
			cout << "Enter Address";
			gotoXY(5, 4);
			cout << "Address: ";
			gotoXY(5, 6);
			cout << "City: ";
			gotoXY(5, 8);
			cout << "State: ";
			gotoXY(5, 10);
			cout << "Postal Code: ";
			gotoXY(3, 23);
			cout << "Status: Pending...";
			gotoXY(22, 4);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Address(Str);
			gotoXY(22, 6);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_City(Str);
			gotoXY(22, 8);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_State(Str);
			gotoXY(22, 10);
			fflush(stdin);
			getline(cin, Str);
			NewAccount->Set_Postal_Code(Str);
			NewAccount->WriteToFile();		// Write to File
			gotoXY(11, 23);
			cout << "Your Account Has Been Created.";
			Sleep(1000);
			gotoXY(11, 23);
			cout << "Press Enter Key to Continue...";
			_getche();
			{
				system("cls");
				srand(static_cast<unsigned int>(time(NULL)));
				Printing('-', '-');
				for (int j = 0; j < 79; j++)
				{
					gotoXY(j, 2);
					cout << '-';
					gotoXY(j, 22);
					cout << '-';
				}
				gotoXY(28, 1);
				cout << "Registration Successful";
				gotoXY(3, 23);
				cout << "Status: Pending...";
				gotoXY(5, 4);
				cout << "Congratulations your account registration has been successful.";
				gotoXY(5, 6);
				cout << "Your access code will be appear on your screen in a short time.";
				gotoXY(5, 8);
				cout << "You can change or reset the password for your account ID...";
				gotoXY(5, 10);
				cout << "...by providing some information.";
				gotoXY(3, 23);
				cout << "Status: Please Wait";
				for (int i = rand() % 3 + 3; i > 0; i--)
				{
					cout << '.';
					Sleep(700);
				}
				NewAccount->Password_Display();
				gotoXY(41, 17);
				cout << NewAccount->Get_Account_No();
				gotoXY(41, 19);
				cout << NewAccount->Get_Account_Password();
			}
			Sleep(1000);
			gotoXY(11, 23);
			cout << "Press Enter Key to Continue...";
			_getche();
			break;
		}
		case '4':
		{
			system("cls");
		BACK_LOAN_OPTIONS:
			L = NULL;
			L = new Loan;
			switch (L->Loan_Options_Display())
			{
			case '1':
			{
				L->Status();
				delete L;
				break;
			} //case 1
			case '2':
			{
				L->Loan_Installment();
				delete L;
				break;
			} //case 2
			case '3':
			{
				L->Loan_Instruction(true);
				L->Loan_Registration();
				delete L;
				break;
			} //case 3
			case '4':
			{
				system("cls");
				Printing('-', '-');
				for (int j = 0; j < 79; j++)
				{
				gotoXY(j, 2);
				cout << '-';
				gotoXY(j, 22);
				cout << '-';
				}
				gotoXY(20, 1);
				cout << "Home Loan EMI and Eligibility Calculator";
				gotoXY(4, 23);
				cout << "Status: Pending...";
				
				double LoanAmount, AnnualInterestRate;
				int NumPayments;
				gotoXY(11, 8);
				cout << "-----------------------------------------------------------";
				gotoXY(13, 10);
				cout << "Enter the Amount of your Loan: RS " << endl;
				gotoXY(13, 12);
				cout << "Enter Your Annual Interest Rate: " << endl;
				gotoXY(13, 14);
				cout << "Enter the Number of Payments: " << endl;
				gotoXY(11, 16);
				cout << "-----------------------------------------------------------";
				gotoXY(47, 10);
				cin >> LoanAmount;
				gotoXY(47, 12);
				cin >> AnnualInterestRate;
				gotoXY(47, 14);
				cin >> NumPayments;
				L->Calculating_EMIs(LoanAmount, AnnualInterestRate, NumPayments);	// Calling Cal_EMIs
				Sleep(200);
				gotoXY(4, 23);
				cout << "Status: Press any Key to Continue...";
				_getch();
				L->EMIs_Display();
				delete L;
				break;
			} //case 4
			case '5':
			{
				L->Loan_Instruction(false);
				_getch();
				break;
			} //case 5
			case '6':
			{
				main();
			} //case 6
			} // end switch-case
			goto BACK_LOAN_OPTIONS;
		}
		case '5':
		{
			int i = 0;
			do {
				system("cls");
				if (i == 0) {
					NewAccount->Account_Instructions();
				}
				if (i == 1) {
					Admin = new Administrator;
					Admin->Administator_Instructions();
					delete Admin;
				}
				if (i == 2) {
					NewAccount->Registration_Instructions();
				}
				if (i == 3) {
					L = new Loan;
					L->Loan_Instruction(false);
					delete L;
				}
				if (i == 4) {
					Instructions();
				}
				gotoXY(3, 23);
				cout << "Status: " << i + 1 << " of 5 Pages.";
				for (int j = 0; j < 20; j++)
					cout << " ";
				gotoXY(79, 24);
				Sleep(1000);
				gotoXY(3, 23);
				cout << "Status: ";
				system("pause");
			} while (i++ < 4);
			break;
		}
		case '6':
		{
			exit(1);
		}
		default:
		{
			system("cls");
			delete L;
			PRESS_ESC(27);
			break;
		}
		} //end Swtich
	} while (true);
	delete NewAccount;
	delete Admin;
	return 0;
} //end main

/*
	Project Completed (2014)
								*/