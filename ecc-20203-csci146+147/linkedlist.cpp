#include <cassert>
#include <iostream>
#include <string>


using ItemType = std::string;

struct Node {
	ItemType value;
	Node * next;
};

class LinkedList {
	public:
		// Default constructor.
		LinkedList() = default;
		
		// Copy constructor.
		LinkedList(LinkedList const & other) {
			this->append(other);
		}
		
		// Destructor. (Frees its dynamically allocated resources.)
		~LinkedList() {
			Node const * ptr{this->head};
			while (ptr) {
				Node const * next{ptr->next};
				delete ptr;
				ptr = next;
			}
		}
		
		// Copy assignment operator.
		LinkedList const & operator=(const LinkedList& other) {
			LinkedList copy{other};
			this->swap(copy);
			return *this;
		}

		// Exchange the contents of this LinkedList with the other one.
		void swap(LinkedList & other) {
			Node * const temp{this->head};
			this->head = other.head;
			other.head = temp;
		}
		
		// Inserts value at the front of the list.
		void insertToFront(ItemType const & value) {
			this->head = new Node{value, this->head};
		}
		
		// Appends the values of other onto the end of this LinkedList.
		void append(LinkedList const & other) {
			// Copy Nodes from the other LinkedList.
			Node * const copied_head{[other_head = other.head]{
				if (!other_head) {
					return static_cast<Node *>(nullptr);
				} else {
					Node * const first{new Node{other_head->value, nullptr}};
					Node * ptr{first};
					for (Node * qtr{other_head->next}; qtr; qtr = qtr->next) {
						ptr->next = new Node{qtr->value, nullptr};
						ptr = ptr->next;
					}
					return first;
				}
			}()};
			// Append the copied Nodes to this LinkedList.
			if (!this->head) {
				// Replace the head with copied_head.
				this->head = copied_head;
			} else {
				// Replace the tail's next with copied_head.
				Node * const tail{[head = this->head]{
					Node * ptr{head};
					for (; ptr->next; ptr = ptr->next) {}
					return ptr;
				}()};  // The tail is the final Node of this LinkedList.
				tail->next = copied_head;
			}
		}
		
		// Reverses the LinkedList.
		void reverseList() {
			auto reverse = [this](auto && self, Node * ptr) -> Node * {
				if (!ptr) {
					return nullptr;
				} else if (!ptr->next) {
					this->head = ptr;
					return ptr;
				} else {
					Node * const prev{self(self, ptr->next)};
					prev->next = ptr;
					ptr->next = nullptr;
					return ptr;
				}
			};
			reverse(reverse, this->head);
		}

		// Returns the number of items in the Linked List.
		int size() const {
			int s{0};
			for (Node const * ptr{this->head}; ptr; ptr = ptr->next) {
				++s;
			}
			return s;
		}

		// Sets item to the value at index i. Returns false if invalid index.
		bool get(int i, ItemType & item) const {
			int index{0};
			for (Node const * ptr{this->head}; ptr; ptr = ptr->next) {
				if (index == i) {
					item = ptr->value;
					return true;
				}
				++index;
			}
			return false;
		}
		
		// Prints the LinkedList.
		void printList() const {
			for (Node const * ptr{this->head}; ptr; ptr = ptr->next) {
				std::cout << ptr->value << " ";
			}
			std::cout << std::endl;
		}
		
		// Prints the LinkedList in reverse order.
		void printReverse() const {
			auto printNextFirst = [](auto && self, Node const * ptr) -> void {
				if (ptr) {
					self(self, ptr->next);
					std::cout << ptr->value << " ";
				}
			};
			printNextFirst(printNextFirst, this->head);
			std::cout << std::endl;
		}
	private:
		Node * head{nullptr};
};


void testA() {
	LinkedList ls;
	ls.insertToFront("Jack");
	ls.insertToFront("Germaine");
	ls.insertToFront("Agatha");
	ls.insertToFront("Agnes");
	for (int k = 0; k < ls.size(); ++k) {
		std::string x;
		ls.get(k, x);
		std::cout << x << std::endl;
	}
}

void testB() {
	LinkedList ls;
	ls.insertToFront("George");
	ls.insertToFront("Louise");
	ls.insertToFront("Lionel");
	ls.insertToFront("Helen");
	ls.printList();
	ls.printReverse();
}

void testC() {
	LinkedList e1;
	e1.insertToFront("bell");
	e1.insertToFront("biv");
	e1.insertToFront("devoe");
	LinkedList e2;
	e2.insertToFront("Andre");
	e2.insertToFront("Big Boi");
	e1.append(e2);  // Adds the contents of e2 to the end of e1.
	std::string s;
	assert(e1.size() == 5 && e1.get(3, s) && s == "Big Boi");
	assert(e2.size() == 2 && e2.get(1, s) && s == "Andre");
	LinkedList e3;
	e3.insertToFront("Rare Essence");
	e3.insertToFront("JunkYard");
	e3.insertToFront("Chuck Brown");
	e3.append(e3);
	assert(e3.size() == 6 && e3.get(3, s) && s == "Chuck Brown");
}

void testD() {
    LinkedList e1;
    e1.insertToFront("Sam");
    e1.insertToFront("Carla");
    e1.insertToFront("Cliff");
    e1.insertToFront("Norm");
    e1.reverseList();  // Reverses the contents of e1.
    std::string s;
    assert(e1.size() == 4 && e1.get(0, s) && s == "Sam");
}

void testE() {
	LinkedList e1;
	e1.insertToFront("A");
	e1.insertToFront("B");
	e1.insertToFront("C");
	e1.insertToFront("D");
	LinkedList e2;
	e2.insertToFront("X");
	e2.insertToFront("Y");
	e2.insertToFront("Z");
	e1.swap(e2);  // Exchange the contents of e1 and e2.
	std::string s;
	assert(e1.size() == 3 && e1.get(0, s) && s == "Z");
	assert(e2.size() == 4 && e2.get(2, s) && s == "B");
}


int main() {
	std::cout << "Test A: (Prints for insertToFront, get.)" << std::endl;
	testA();
	std::cout << "Test B: (Prints for printList, printReverse.)" << std::endl;
	testB();
	std::cout << "Test C: (Asserts for append.)" << std::endl;
	testC();
	std::cout << "Test D: (Asserts for reverseList.)" << std::endl;
	testD();
	std::cout << "Test E: (Asserts for swap.)" << std::endl;
	testE();
	return 0;
}
