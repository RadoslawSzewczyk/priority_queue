#include "queue.h"
# include <iostream>
# include <cassert>
# include <string>

void tests() {
	// Test push
	PriorityQueue<int> pq;
	PriorityQueue<int> pq2;
	const int testSize = 5;

	for (int i = 0; i < testSize; i++) 
	{
		pq.push(rand() % 100);
	}

	std::cout << pq.toString() << std::endl;

	//Test size
	assert(pq.size() == testSize);
	std::cout << "Size test" << std::endl;


	// Test pop
	for (int i = 0; i < testSize + 1; i++) 
	{
		try {
			pq.pop();
		}
		catch (const std::runtime_error& e) 
		{
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << pq.toString() << std::endl;
	}

	// Test copy constructor
	int value = 5;
	PriorityQueue<int>::Node node(value);

	assert(node.data == value);
	std::cout << "Copy constructor test" << std::endl;

	// Test move constructor
	PriorityQueue<int>::Node nodeMove(std::move(value));

	assert(nodeMove.data == 5);
	std::cout << "Move constructor test" << std::endl;

	//Test empty top
	try {
		int topElement = pq2.top();
		std::cout << "Exception was not thrown as expected." << std::endl;
	}
	catch (const std::runtime_error& e) {
		std::cout << "Caught expected exception: " << e.what() << std::endl;
	}

	for (int i = 0; i < testSize; i++)
	{
		pq.push(rand() % 100);
	}

	// Test copy operator
	pq2 = pq;
	assert(pq2.toString() == pq.toString());
	std::cout << "Copy operator test" << std::endl;

	std::cout << "Contents of pq: " << pq.toString() << std::endl;
	std::cout << "Contents of pq2: " << pq2.toString() << std::endl;

	//Test comparison operator
	assert(pq == pq2);
	std::cout << "Comparison operator test" << std::endl;

	//Test contains
	pq.push(5);
	assert(pq.contains(5));
	std::cout << "Contains test" << std::endl;


	// Test serialization
	std::string serialized = pq.serialize();
	std::cout << "Serialization test " << serialized<< std::endl;

	// Test deserialization

	auto pq3 = PriorityQueue<int>::deserialize(serialized);
	std::cout << "Deserialization test " << pq3->toString() << std::endl;

}
 
int main() {

	tests();
}