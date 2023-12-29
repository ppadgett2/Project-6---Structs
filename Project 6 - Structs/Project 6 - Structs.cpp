// Author: Parker Padgett
// Assignment: Project 6 - Structs
// Description: Use structs and get data about the user, and calculate overtime (if user has it),
//				tax rate based on deductions user claimed, gross, and net pay, and output to the screen. 
// Date: 3/8/2022


#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;

struct employee
{
	string fName, lName, title;
	int num, deductions;
	double hours, wage, oTimeHours, oTimeWage, oTimePay, grossPay, taxesWitheld, netPay, tax;
};

// Function Declaration
void getData(ifstream& inFile, employee info[10]);
void output(employee info[10]);

int main()
{
	// Open input file
	ifstream inFile;
	inFile.open("input.txt");

	employee info[10];

	// Get data from input file and assign values to other information
	getData(inFile, info);

	// Ouptput data to the screen
	output(info);

	// Close input file
	inFile.close();
	return 0;
}

void getData(ifstream& inFile, employee info[10])
{
	for (int a = 0; a <= 2; a++)
	{
		// Get data from input file
		inFile >> info[a].fName;
		inFile >> info[a].lName;
		inFile >> info[a].title;
		inFile >> info[a].num;
		inFile >> info[a].hours;
		inFile >> info[a].wage;
		inFile >> info[a].deductions;

		// if they have more than 40 hours, calculate overtime info and store into arrays
		if (info[a].hours > 40)
		{
			info[a].oTimeWage = 1.5 * info[a].wage;
			info[a].oTimeHours = info[a].hours - 40;
			info[a].oTimePay = info[a].oTimeWage * info[a].oTimeHours;

			info[a].grossPay = info[a].oTimePay + (40 * info[a].wage);
		}
		else // Else calculate gross pay normally and store into array
		{
			info[a].grossPay = info[a].wage * info[a].hours;
		}

		// Calculate tax based on deductions
		if (info[a].deductions <= 0)
			info[a].tax = .30;
		else if (info[a].deductions == 1)
			info[a].tax = .25;
		else if (info[a].deductions == 2)
			info[a].tax = .20;
		else if (info[a].deductions == 3)
			info[a].tax = .15;
		else
			info[a].tax = .10;

		// Calculate tax withheld and store into array
		info[a].tax = info[a].tax * info[a].grossPay;

		// Calculate net pay and store into array
		info[a].netPay = info[a].grossPay - info[a].tax;
	}
}

void output(employee info[10])
{
	// Output all information
	for (int a = 0; a <= 2; a++)
	{
		cout << "Name: " << info[a].fName << " " << info[a].lName << endl;
		cout << "Title: " << info[a].title << endl;
		cout << "Employee Number: " << info[a].num << endl;
		cout << "Worked Hours: " << info[a].hours << endl;
		cout << "Hourly Wage: $" << info[a].wage << endl;
		cout << "Number of Deductions: " << info[a].deductions << endl;

		// Checking to see if they got any overtime hours, if they didn't it doesn't output this
		if (info[a].hours > 40)
		{
			cout << "Overtime Wage: $" << info[a].oTimeWage << endl;
			cout << "Overtime Hours: " << info[a].oTimeHours << endl;
			cout << "Overtime Pay: $" << info[a].oTimePay << endl;
		}

		cout << "Gross Pay: $" << info[a].grossPay << endl;
		cout << "Taxes Withheld: $" << info[a].tax << endl;
		cout << "Net Pay: $" << info[a].netPay << endl;
		cout << endl;
	}
}