#ifndef ADMINISTRATOR_H
#define ADMINISTRATOR_H
using namespace std;
/* Administrator Class */
class Administrator : public Account
{
private:
	string Admin_Name;
	string Admin_Password;
	string Admin_Type;
public:
	Administrator();
	char Administrator_Dispaly();
	char Manage_Accounts_Display();
	void Administator_Instructions();

	/* Inline Functions */
	string Get_Admin_Name() { return Admin_Name; }
	string Get_Admin_Password() { return Admin_Password; }
	void Set_Admin_Name(string Name) { Admin_Name = Name; }
	void Set_Admin_Password(string Pass) { Admin_Password = Pass; }

	bool Login_ADM(string ADM_No, string ADM_Pass);
	void Change_Balance(double Amount);
	void WriteToFile_ADM();
	void ReadToFile_ADM(string ADM_No);
	void modifyCSV_ADM(istream &input, vector< vector<string> > &output, string ADM);
	void ModifyToFile_ADM(string ADM);
	void Change_Pass_ADM(string ADM);
	void Change_Name_ADM(string ADM);

	/* Virtual Functions */
	void Set_Type(string ADM) { Admin_Type = ADM; }
	string Get_Type() { return Admin_Type; }
	void Generate_AC_No();
}; // end Administrator Class
#endif