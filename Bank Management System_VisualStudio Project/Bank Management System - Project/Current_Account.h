#ifndef CURRENT_ACCOUNT_H
#define CURRENT_ACCOUNT_H
using namespace std;
/* Current_Account Class Functions */
class Current_Account : public Account
{
public:
	Current_Account();
	void Generate_AC_No();

	/* Inline Functions */
	double Check_Balance() { return Balance; }
	string Get_Type() { return Account_Type; }
	void Set_Type(string accounttype) { Account_Type = accounttype; }
}; // end Current_Account Class
#endif