// Al Ashby
// CS303
// 4/9/2017
// Project 2A

#pragma once
#include <vector>
#include <string>
#include "Employee.h"

class Pqueue {
public:
	/*Pushes an employee to the back of the priority queue
	@param emp Employee to be pushed
	*/
	void push(const Employee& emp);

	/*Pops an the employee at the front of the priority queue*/
	void pop();

	/*States whether the priority queue is empty or not
	@return True if there are no items in the queue, false if otherwise*/
	bool empty() const { return data.empty(); }

	/*States how many objects are in the queue
	@return Number of objects in the queue*/
	size_t size() const { return data.size(); }

	/*Shows what employee is at the front of the queue and will be popped next
	@return The employee at the front of the queue*/
	Employee& top() { return data.front(); }

	/*Changes an employee's priority based on its current accumulated waiting and retaining times
	@param employee Name of the employee
	@param wait_time Accumulated waiting time of the employee in days
	@param retain_time Accumulated retaining time of the employee in days*/
	void update(string employee, int wait_time, int retain_time);
private:
	/*Raises an employee to a higher position in the queue based on its priority
	@param index Current index of the employee*/
	void raiseInQueue(int index);
	/*Lowers an employee to a higher position in the queue based on its priority
	@param index Current index of the employee*/
	void lowerInQueue(int index);

	//Data
	//Vector of employees in the queue organized to manipulate the queue
	vector<Employee> data;
};