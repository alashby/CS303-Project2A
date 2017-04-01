#pragma once

using namespace std;

class Employee {
public:
	Employee() { ; }
	Employee(string new_emp) { name = new_emp; waitTime = retainTime = 0; }
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