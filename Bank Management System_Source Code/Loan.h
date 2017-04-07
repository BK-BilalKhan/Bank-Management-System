#ifndef LOAN_H
#define LOAN_H
using namespace std;
/* Loan Class */
class Loan
{
	/* Loan Data Members */
private:
	double LoanAmount,
		AnnualInterestRate,
		MonthlyInterestRate,
		MonthlyPayment,
		TotalPaidBack,
		TotalInterestPaid;
	int NumPayments;
	/* Details */
private:
	string Loan_No;
	string Name;
	string CNIC;
	string Email;
	string Contact;
	string City;
	string Monthly_Income;
	string Company_Name;
	string Segment;
	string BestDayToContactYou;
	string CreationDate;
	string LastPaid;	// Date
public:
	Loan();
	void Loan_Instruction(bool T);
	char Loan_Options_Display();
	void Loan_Registration();
	void Generate_Loan_No();
	void Loan_Display();
	void WriteToFile();
	void ReadToFile(string Loan_No);
	void ModifyToFile(string L_No);
	void modifyCSV(istream &input, vector< vector<string> > &output, string L_No);
	void Loan_Status();
	void Set_CreationDate();
	void Calculating_EMIs(double LoanAmount, double AnnualInterestRate, int NumPayments);
	void EMIs_Display();
	void Status();
	bool Login();
	void Loan_Installment();

	/* Inline Function */
	string Get_CreationDate() { return CreationDate; }
};
#endif