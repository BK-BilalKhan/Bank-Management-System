#ifndef SAVING_ACCOUNT_H
#define SAVING_ACCOUNT_H
using namespace std;
/* Saving_Account Class*/
class Saving_Account : public Account
{
public:
	Saving_Account();
	void Generate_AC_No();

	/* Inline Functions */
	double Check_Balance() { return Balance; }
	string Get_Type() { return Account_Type; }
	void Set_Type(string accounttype) { Account_Type = accounttype; }
}; // end Saving_Account Class
#endif