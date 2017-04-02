#pragma once

using namespace std;

class Employee {
public:
	Employee() { ; }
	Employee(string new_emp) { name = new_emp; waitTime = retainTime = 0; }
	Employee(string new_emp, int wait_time, int retain_time) { name = new_emp; waitTime = wait_time; retainTime = retain_time; }
	string getName() { return name; };
	int getWaitTime() { return waitTime; };
	int getRetainTime() { return retainTime; };
	void setWaitTime(int new_time) { waitTime = new_time; }
	void setRetainTime(int new_time) { retainTime = new_time; }
private:
	string name;
	int waitTime;
	int retainTime;


};