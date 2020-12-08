#include <cassert>
#include <iostream>
#include <string>
#include <utility>

template <typename T>
class Tree {
public:          
	Tree();
	~Tree();
	Tree(Tree const & other);
	template<typename U> friend void swap(Tree<U> & a, Tree<U> & b);
	Tree const & operator=(Tree other);
	void add(T value);
	int distinctValues() const;
	int totalValues() const;
	template<typename U> friend std::ostream & operator<<(
		std::ostream & out, Tree<U> const & tree
	);
private:
	struct Node {
		T value;
		size_t count;
		Node * left;
		Node * right;
	};
	static int countValues(Node const * root, bool distinct);
	Node * root = nullptr;
};

template<typename T>
Tree<T>::Tree() {}

template<typename T>
Tree<T>::~Tree() {
	auto const destroyTree = [](auto && self, Node * root) -> void {
		if (root) {
			self(self, root->left);
			self(self, root->right);
			delete root;
		}
	};
	destroyTree(destroyTree, this->root);
}

template<typename T>
Tree<T>::Tree(Tree const & other) {
	auto const copyTree = [](auto && self, Node const * root) -> Node * {
		if (root) {
			Node * newroot{new Node{*root}};
			newroot->left = self(self, root->left);
			newroot->right = self(self, root->right);
			return newroot;
		} else {
			return nullptr;
		}
	};
	this->root = copyTree(copyTree, other.root);
}

template <typename T>
void swap(Tree<T> & a, Tree<T> & b) {
	using std::swap;
	swap(a.root, b.root);
}

template <typename T>
Tree<T> const & Tree<T>::operator=(Tree other) {
	swap(*this, other);
	return *this;
}

template <typename T>
void Tree<T>::add(T value) {
	auto const addToTree = [](auto && self, Node * root, T value) -> Node * {
		if (root) {
			if (value < root->value) {
				root->left = self(self, root->left, value);
			} else if (value > root->value) {
				root->right = self(self, root->right, value);
			} else {
				++root->count;
			}
			return root;
		} else {
			return new Node{value, 1, nullptr, nullptr};
		}
	};
	this->root = addToTree(addToTree, this->root, value);
}

template <typename T>
int Tree<T>::countValues(Node const * root, bool distinct) {
	if (root) {
		return (
			(distinct ? 1 : root->count) +
			Tree::countValues(root->left, distinct) +
			Tree::countValues(root->right, distinct)
		);
	} else {
		return 0;
	}
}

template <typename T>
int Tree<T>::distinctValues() const {
	return Tree::countValues(this->root, true);
}

template <typename T>
int Tree<T>::totalValues() const {
	return Tree::countValues(this->root, false);
}

template <typename T>
std::ostream & operator<<(std::ostream & out, Tree<T> const & tree) {
	auto const printTree = [&out](
		auto && self,
		typename Tree<T>::Node const * root
	) -> void {
		if (root) {
			self(self, root->left);
			out << "[" << root->value << ", " << root->count << "] ";
			self(self, root->right);
		}
	};
	printTree(printTree, tree.root);
	out << std::endl;
	return out;
}

class WordTree : public Tree<std::string> {
public:
	int distinctWords() const { return this->distinctValues(); }
	int totalWords() const { return this->totalValues(); }
};

int main() {
	// Test WordTree::distinctWords and WordTree::totalWords.
	WordTree a;
	a.add("Skyler");
	a.add("Walter");
	a.add("Walter");
	a.add("Walter");
	assert(a.distinctWords() == 2);
	assert(a.totalWords() == 4);
	WordTree b;
	b.add("Skyler");
	b.add("Walter");
	b.add("Walter");
	b.add("Hank");
	b.add("Gus");
	b.add("Walter");
	b.add("Gus");
	assert(b.distinctWords() == 4);
	assert(b.totalWords() == 7);
	// Test copy constructor and copy assignment operator.
	std::cout << "a: " << a;
	std::cout << "b: "  << b;
	WordTree c{b};
	std::cout << "c (copy constructed from b): "  << c;
	c = a;
	std::cout << "c (copy assigned to from a): "  << c;
	// Test Tree<char>.
	Tree<char> d;
	d.add('u');
	d.add('w');
	d.add('u');
	d.add('o');
	d.add('w');
	d.add('o');
	std::cout << "d: "  << d;
}
