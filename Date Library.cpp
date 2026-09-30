#include <iostream>
#include "clsDate.h"

using namespace std;

int main()
{

    clsDate Date1(15, 8, 2025);
    clsDate Date2("20/9/2025");

    cout << "Date1: ";
    Date1.Print();

    cout << "Date2: ";
    Date2.Print();

    cout << "\nDate1 Information:\n";

    cout << "Day: " << Date1.Day << endl;
    cout << "Month: " << Date1.Month << endl;
    cout << "Year: " << Date1.Year << endl;

    cout << "Days in Year: " << clsDate::NumberOfDaysInYear(Date1.Year) << endl;

    cout << "Days in Month: " << clsDate::NumberOfDaysInMonth(Date1.Year, Date1.Month) << endl;
    cout << "Hours in Year: " << clsDate::NumberOfHoursInYear(Date1.Year) << endl;


    clsDate Today = clsDate::GetSystemDate();

    Today.Print();



    return 0;
}