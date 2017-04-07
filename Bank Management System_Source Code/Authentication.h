#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H
using namespace std;
/* Authentication Class */
class Authentication
{
private:
	string AC_Password;
public:
	Authentication();
	void Password_Display();
	void Generate_AC_Password(string Account_No);
	void Change_Password();
	bool Login(string AC_No, string AC_Pass);

	/* Inline Functions */
	void Set_Password(string Password) { AC_Password = Password; }
	string Get_Password() { return AC_Password; }
}; // end Authentication Class
#endif