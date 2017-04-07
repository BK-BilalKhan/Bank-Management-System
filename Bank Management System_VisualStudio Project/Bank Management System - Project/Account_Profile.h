#ifndef ACCOUNT_PROFILE_H
#define ACCOUNT_PROFILE_H
using namespace std;
/* Account_Profile Class */
class Account_Profile
{
	// For Access Private Member
	friend class Account;
	friend class Saving_Account;
	friend class Current_Account;
	friend class Administrator;
	// Private Class Member
private:
	string Name;
	string Father_Husband_Name;
	string DateofBirth;
	string Gender;
	string Occupation;
	string Education_Qualification;
	string Phone_No;
	string Address;
	string City;
	string State;
	string Postal_Code;
	string AC_Created_Date;
public:
	Account_Profile();
}; // end Account_Profile Class
#endif