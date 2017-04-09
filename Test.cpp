// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#include "Library.h"
#include "Date.h"
#include <iostream>

using namespace std;

void main() {

	cout << "-- Test 1 --" << endl << "Two Books Circulating at Different Dates (Given Example)" << endl << endl;
	Library library1;
	library1.addBook("Software Engineering");
	library1.addBook("Chemistry");

	library1.addEmployee("Adam");
	library1.addEmployee("Sam");
	library1.addEmployee("Ann");

	library1.circulateBook("Chemistry", Date(2015, 3, 1, DateFormat::US));
	library1.circulateBook("Software Engineering", Date(2015, 4, 1, DateFormat::US));
	library1.announceStatus();
	library1.passOn("Chemistry", Date(2015, 3, 5, DateFormat::US));
	library1.announceStatus();
	library1.passOn("Chemistry", Date(2015, 3, 7, DateFormat::US));
	library1.announceStatus();
	library1.passOn("Chemistry", Date(2015, 3, 15, DateFormat::US));
	library1.announceStatus();

	library1.passOn("Software Engineering", Date(2015, 4, 5, DateFormat::US));
	library1.announceStatus();
	library1.passOn("Software Engineering", Date(2015, 4, 10, DateFormat::US));
	library1.announceStatus();
	library1.passOn("Software Engineering", Date(2015, 4, 15, DateFormat::US));
	library1.announceStatus();


	cout << "-- Test 2 --" << endl << "Two Books Circulating In Tandem" << endl << endl;
	Library library2;
	library2.addBook("Software Engineering");
	library2.addBook("Chemistry");

	library2.addEmployee("Adam");
	library2.addEmployee("Sam");
	library2.addEmployee("Ann");

	library2.circulateBook("Chemistry", Date(2015, 3, 1, DateFormat::US));
	library2.circulateBook("Software Engineering", Date(2015, 3, 2, DateFormat::US));
	library2.passOn("Chemistry", Date(2015, 3, 5, DateFormat::US));
	library2.announceStatus();
	library2.passOn("Software Engineering", Date(2015, 3, 6, DateFormat::US));
	library2.announceStatus();
	library2.passOn("Chemistry", Date(2015, 3, 15, DateFormat::US));
	library2.announceStatus();
	library2.passOn("Software Engineering", Date(2015, 3, 16, DateFormat::US));
	library2.announceStatus();
	library2.passOn("Chemistry", Date(2015, 3, 17, DateFormat::US));
	library2.announceStatus();
	library2.passOn("Software Engineering", Date(2015, 3, 18, DateFormat::US));
	library2.announceStatus();

	cout << "-- Test 3 --" << endl << "Adding Employee Between Circulations" << endl << endl;
	Library library3;
	library3.addBook("Software Engineering");
	library3.addBook("Chemistry");

	library3.addEmployee("Adam");
	library3.addEmployee("Sam");
	library3.addEmployee("Ann");

	library3.circulateBook("Chemistry", Date(2015, 3, 1, DateFormat::US));
	library3.circulateBook("Software Engineering", Date(2015, 4, 1, DateFormat::US));
	library3.announceStatus();
	library3.passOn("Chemistry", Date(2015, 3, 5, DateFormat::US));
	library3.announceStatus();
	library3.passOn("Chemistry", Date(2015, 3, 7, DateFormat::US));
	library3.announceStatus();
	library3.passOn("Chemistry", Date(2015, 3, 15, DateFormat::US));
	library3.announceStatus();

	library3.addEmployee("Daniel");

	library3.passOn("Software Engineering", Date(2015, 4, 5, DateFormat::US));
	library3.announceStatus();
	library3.passOn("Software Engineering", Date(2015, 4, 10, DateFormat::US));
	library3.announceStatus();
	library3.passOn("Software Engineering", Date(2015, 4, 15, DateFormat::US));
	library3.announceStatus();

	system("pause");
}
