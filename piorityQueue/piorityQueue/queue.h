#include <iostream>
#include <memory>
#include <vector>
#include <sstream>
#include <cassert>

template<typename T>
class PriorityQueue
{
	size_t count = 0;
public:
	struct Node
	{
		T data;
		std::unique_ptr<Node> next;

		Node(const T& data) : data(data), next(nullptr) {}
		Node(T&& data) : data(std::move(data)), next(nullptr) {}
	};

	std::unique_ptr<Node> head;

	PriorityQueue() : head(nullptr) {}

	void push(const T& data)
	{
		if (!head)
		{
			head = std::make_unique<Node>(data);
			count++;
			return;
		}

		if (head->data > data)
		{
			auto temp = std::make_unique<Node>(data);
			temp->next = std::move(head);
			head = std::move(temp);
			count++;
			return;
		}

		auto current = head.get();
		while (current->next && current->next->data < data)
		{
			current = current->next.get();
		}

		auto temp = std::make_unique<Node>(data);
		temp->next = std::move(current->next);
		current->next = std::move(temp);

		count++;
	}

	void pop()
	{
		if (!head)
		{
			throw std::runtime_error("Attempted to pop from an empty queue");
		}

		head = std::move(head->next);
		count--;
	}

	const T& top() const
	{
		if (!head)
		{
			throw std::runtime_error("Attempted to access top element of an empty queue");
		}
		return head->data;
	}

	bool empty() const
	{
		return !head;
	}

	std::string toString() const
	{
		std::stringstream ss;
		ss << "[";
		auto current = head.get();
		while (current) {
			ss << current->data;
			if (current->next)
			{
				ss << ", ";
			}
			current = current->next.get();
		}
		ss << "]";
		return ss.str();
	}

	PriorityQueue& operator=(const PriorityQueue& other)
	{
		if (this == &other)
		{
			return *this;
		}

		// Clear the current contents
		clear();

		// Copy the elements from the other queue
		Node* currentOther = other.head.get();
		Node* lastCopiedNode = nullptr;
		while (currentOther != nullptr)
		{
			// Create a new node with the data from the other queue
			auto newNode = std::make_unique<Node>(currentOther->data);

			if (lastCopiedNode == nullptr)
			{
				// This is the first node being copied
				head = std::move(newNode);
			}
			else {
				// Append to the last copied node
				lastCopiedNode->next = std::move(newNode);
			}

			// Move to the next node in both queues
			lastCopiedNode = lastCopiedNode ? lastCopiedNode->next.get() : head.get();
			currentOther = currentOther->next.get();
		}
		count = other.count;
		return *this;
	}

	bool operator==(const PriorityQueue& other) const
	{

		if (count != other.count) {
			return false;
		}

		Node* current = head.get();
		Node* currentOther = other.head.get();

		while (current != nullptr && currentOther != nullptr) {
			if (current->data != currentOther->data) {
				return false;
			}
			current = current->next.get();
			currentOther = currentOther->next.get();
		}

		return true;
	}

	// Helper function to clear the queue
	void clear()
	{
		while (head != nullptr)
		{
			head = std::move(head->next);
		}
	}

	size_t size() const
	{
		return count;
	}

	bool contains(const T& value) const {
		Node* current = head.get();
		while (current != nullptr) {
			if (current->data == value) {
				return true;
			}
			current = current->next.get();
		}
		return false;
	}

	std::string serialize() const {
		std::stringstream ss;
		for (auto current = head.get(); current != nullptr; current = current->next.get()) {
			ss << current->data;
			if (current->next) {
				ss << ",";
			}
		}
		return ss.str();
	}

	static std::unique_ptr<PriorityQueue> deserialize(const std::string& data) {
		auto queue = std::make_unique<PriorityQueue>();
		std::stringstream ss(data);
		T value;
		while (ss >> value) {
			queue->push(value);
			if (ss.peek() == ',') ss.ignore();
		}
		return queue;
	}

};
