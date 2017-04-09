// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#pragma once

using namespace std;

class Employee {
public:
	// Constructors

	Employee() { ; }

	/*Book Constructor
	Creates brand new employee with no currently accumulated waiting or retaining time
	@param new_emp The name of the new employee
	*/
	Employee(string new_emp) { name = new_emp; waitTime = retainTime = 0; isRetaining = false; }

	/*Book Constructor
	Creates new object of employee class that already has a waiting and/or retaining time
	@param new_emp The name of the employee
	@param wait_time The current waiting time of the employee
	@param retain_time The current retaining time of the employee
	@param retaining If the employee is currently retaining a book or not
	*/
	Employee(string new_emp, int wait_time, int retain_time, bool retaining) { name = new_emp; waitTime = wait_time; retainTime = retain_time; isRetaining = retaining; }

	// Getters and Setters
	string getName() { return name; };

	int getWaitTime() { return waitTime; };
	void setWaitTime(int new_time) { waitTime = new_time; }

	int getRetainTime() { return retainTime; };
	void setRetainTime(int new_time) { retainTime = new_time; }

	// If the employee is currently retaining a book or not
	bool isRetaining;
private:
	// Data

	// Name of the employee
	string name;
	// Accumulated waiting time of the employee
	int waitTime;
	// Accumulated retaining time of the employee
	int retainTime;


};