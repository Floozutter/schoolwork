#include <iostream>
#include <string>

using ItemType = std::string;

struct Node {
	ItemType value;
	Node *next;
};

class LinkedList {
	public:
		// Default constructor.
		LinkedList() : head(nullptr) {}
		
		// Copy constructor.
		LinkedList(const LinkedList& rhs);
		
		// Destructor. (Frees its dynamically allocated resources.)
		~LinkedList();
		
		// Copy assignment operator.
		const LinkedList& operator=(const LinkedList& rhs);
		
		// Inserts val at the front of the list.
		void insertToFront(const ItemType &val);
		
		// Prints the LinkedList.
		void printList() const;
		
		// Sets item to the value at index i. Returns false if invalid index.
		bool get(int i, ItemType& item) const;
		
		// Reverses the LinkedList.
		void reverseList();
		
		// Prints the LinkedList in reverse order.
		void printReverse() const;
		
		// Appends the values of other onto the end of this LinkedList.
		void append(const LinkedList &other);
		
		// Exchange the contents of this LinkedList with the other one.
		void swap(LinkedList &other);
		
		// Returns the number of items in the Linked List.
		int size() const;
	private:
		Node *head;
};
