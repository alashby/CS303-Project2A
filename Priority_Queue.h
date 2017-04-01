#include <vector>
#include <functional>
#include "Date.h"

template < typename Item_Type, typename Compare = std::less<Item_Type> >

class priority_queue {
public:
	priority_queue() {}
	void push(const Item_Type& item);
	void pop();
	bool empty() const { return data.empty(); }
	size_t size() const { return data.size(); }
	const Item_Type& top() const { return data.front(); }

	//change priority based on index
	void change_priority(int index, Item_Type new_priority){
		data[index] = new_priority;
		//compare with parent
		int parent = (index - 1) / 2;
		int child = index;
		bool swap = false;

		while (parent >= 0
			&& comp(data[parent], data[child])) {
			std::swap(data[child], data[parent]);
			child = parent;
			parent = (child - 1) / 2;
			swap = true;
		}

		//if we made a swap we don't need to go down
		if (!swap){
			parent = index;
			
			while (true) {
				int left_child = 2 * parent + 1;
				if (left_child >= size()) break; // out of heap
				int right_child = left_child + 1;
				int max_child = left_child;
				if (right_child < size()
					&& comp(data[left_child], data[right_child]))
					max_child = right_child;
				if (comp(data[parent], data[max_child])) {
					std::swap(data[max_child], data[parent]);
					parent = max_child;
				}
				else break;
			}
}
	}



private:
	vector<Item_Type> data;
	Compare comp;
};

template<typename Item_Type, typename Compare> 
void priority_queue < Item_Type, Compare > ::push(const Item_Type& item) {
		data.push_back(item);
		int child = size() - 1;
		int parent = (child - 1) / 2;
		// Reheap
		while (parent >= 0
			&& comp(data[parent], data[child])) {
				std::swap(data[child], data[parent]);
				child = parent;
				parent = (child - 1) / 2;
		}
}

template<typename Item_Type, typename Compare>
void priority_queue<Item_Type,Compare>::pop() {
		if (size() == 1) { data.pop_back(); return; }
		std::swap(data[0], data[size() - 1]);
		data.pop_back();
		int parent = 0;
		while (true) {
			int left_child = 2 * parent + 1;
			if (left_child >= size()) break; // out of heap
			int right_child = left_child + 1;
			int max_child = left_child;
			if (right_child < size()
				&& comp(data[left_child], data[right_child]))
				max_child = right_child;
			if (comp(data[parent], data[max_child])) {
				std::swap(data[max_child], data[parent]);
				parent = max_child;
			}
			else break;
		}
}


