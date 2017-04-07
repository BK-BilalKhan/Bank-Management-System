#ifndef ACCOUNT_H
#define ACCOUNT_H
using namespace std;
/* Account Class */
class Account
{
protected:
	string Account_No;
	string Account_Type;
	double Balance;
	/* Objects */
	Account_Profile *Profile;			// Profile Class Object
	Authentication *Auth;				// Authentication Class Object
public:
	Account();
	virtual ~Account();
	char Account_Display();
	void Password_Display() { Auth->Password_Display(); }
	void Account_Instructions();
	
	/* Inline Functions */
	void Registration_Instructions();
	void Set_Account_No(string AC_No) { Account_No = AC_No; }
	void Set_Balance(double balance) { Balance = balance; }
	double Get_Balance() { return Balance; }
	void Set_Name(string name) { Profile->Name = name; }
	void Set_Father_Husband_Name(string f_h_name) { Profile->Father_Husband_Name = f_h_name; }
	void Set_DateofBirth(string dateofbirth) { Profile->DateofBirth = dateofbirth; }
	void Set_Gender(string gender) { Profile->Gender = gender; }
	void Set_Occupation(string occupation) { Profile->Occupation = occupation; }
	void Set_Education_Qualification(string qualification) { Profile->Education_Qualification = qualification; }
	void Set_Phone_No(string p_no) { Profile->Phone_No = p_no; }
	void Set_Address(string address) { Profile->Address = address; }
	void Set_City(string city) { Profile->City = city; }
	void Set_State(string state) { Profile->State = state; }
	void Set_Postal_Code(string postal_code) { Profile->Postal_Code = postal_code; }
	string Get_Account_No() { return Account_No; }
	string Get_Account_Password() { return Auth->Get_Password(); }
	void Generate_AC_Password() { Auth->Generate_AC_Password(Account_No); }
	
	void Generate_AC_DT();
	void WriteToFile();
	void ReadToFile(string AC_No);				// Prototype of ReadToFile Function
	void ModifyToFile(string AC_No);			// Prototype of ModifyToFile Function
	void modifyCSV(istream &input, vector< vector<string> > &output, string AC_No); // Prototype of Modify_CSV File Function
	void deleteCSV(istream &input, vector< vector<string> > &output, string AC_No);	// Prototype of Delete_CSV File Function
	void deleteAccount(string AC_No);
	bool Login_Account(string AC_N, string AC_Pas);
	void Deposit(double Amount);
	void Withdraw(double Amount);
	void Transfer_Balance(string AC_No, int Amount);
	void Change_Balance(char CH, double Amount);
	void Change_Pass(string AC_No);
	void Change_Type(string AC_No);
	void Accounts_Status();
	
	/* Virtual Functions */
	virtual void Set_Type(string accounttype) = 0;
	virtual string Get_Type() = 0;
	virtual void Generate_AC_No() = 0;
	
	/* Friend Functions */
	friend ostream& operator <<(ostream& out, Account& Obj);
}; // end Account Class
#endif