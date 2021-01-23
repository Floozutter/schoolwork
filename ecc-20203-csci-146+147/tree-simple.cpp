#include <cassert>
#include <iostream>
#include <string>
#include <utility>

using Word = std::string;

class WordTree {
public:
	WordTree();
	~WordTree();
	WordTree(WordTree const & other);
	friend void swap(WordTree & a, WordTree & b);
	WordTree const & operator=(WordTree other);
	void add(Word const & word);
	int distinctWords() const;
	int totalWords() const;
	friend std::ostream & operator<<(std::ostream & out, WordTree const & wt);
private:
	struct Node {
		Word word;
		size_t count;
		Node * left;
		Node * right;
	};
	static void destroyTree(Node * root);
	static Node * copyTree(Node const * root);
	static Node * addToTree(Node * root, Word const & word);
	static int countWords(Node const * root, bool distinct);
	static void printTree(Node const * root, std::ostream & out);
	Node * root = nullptr;
};

WordTree::WordTree() {}

void WordTree::destroyTree(Node * root) {
	if (root) {
		WordTree::destroyTree(root->left);
		WordTree::destroyTree(root->right);
		delete root;
	}
}
WordTree::~WordTree() {
	WordTree::destroyTree(this->root);
}

WordTree::Node * WordTree::copyTree(Node const * root) {
	if (root) {
		return new Node{
			root->word,
			root->count,
			WordTree::copyTree(root->left),
			WordTree::copyTree(root->right)
		};
	} else {
		return nullptr;
	}
}
WordTree::WordTree(WordTree const & other) {
	this->root = WordTree::copyTree(other.root);
}

void swap(WordTree & a, WordTree & b) {
	using std::swap;
	swap(a.root, b.root);
}

WordTree const & WordTree::operator=(WordTree other) {
	swap(*this, other);
	return *this;
}

WordTree::Node * WordTree::addToTree(Node * root, Word const & word) {
	if (root) {
		if (word < root->word) {
			root->left = WordTree::addToTree(root->left, word);
		} else if (word > root->word) {
			root->right = WordTree::addToTree(root->right, word);
		} else {
			++root->count;
		}
		return root;
	} else {
		return new Node{word, 1, nullptr, nullptr};
	}
}
void WordTree::add(Word const & word) {
	this->root = WordTree::addToTree(this->root, word);
}

int WordTree::countWords(Node const * root, bool distinct) {
	if (root) {
		return (
			(distinct ? 1 : root->count) +
			WordTree::countWords(root->left, distinct) +
			WordTree::countWords(root->right, distinct)
		);
	} else {
		return 0;
	}
}
int WordTree::distinctWords() const {
	return WordTree::countWords(this->root, true);
}
int WordTree::totalWords() const {
	return WordTree::countWords(this->root, false);
}

void WordTree::printTree(Node const * root, std::ostream & out) {
	if (root) {
		WordTree::printTree(root->left, out);
		out << "[" << root->word << ", " << root->count << "] ";
		WordTree::printTree(root->right, out);
	}
}
std::ostream & operator<<(std::ostream & out, WordTree const & wt) {
	WordTree::printTree(wt.root, out);
	out << std::endl;
	return out;
}

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
}
