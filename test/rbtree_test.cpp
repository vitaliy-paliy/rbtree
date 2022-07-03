#include<cassert>
#include "../rbtree.h"

void test_insert(RBTree& tree) {
	std::vector<int> tests = {4, 2, 1, 7, 5, 6};
	for (auto t: tests)
		tree.insert(t);

	std::vector<std::vector<int>> correct_order = {{2}, {1, 5}, {4, 7}, {6}};
	assert(tree.level_traversal() == correct_order);
	assert(tree.height() == correct_order.size()-1);
}

void test_remove(RBTree& tree) {
	tree.remove(6);
	std::vector<std::vector<int>> correct_order = {{2}, {1, 5}, {4, 7}};
	assert(tree.level_traversal() == correct_order);
	assert(tree.height() == correct_order.size()-1);

	tree.remove(5);
	correct_order = {{2}, {1, 7}, {4}};
	assert(tree.level_traversal() == correct_order);

	tree.remove(2);
	correct_order = {{4}, {1, 7}};
	assert(tree.level_traversal() == correct_order);
	
	assert(tree.height() == correct_order.size()-1);
}

void test_find(RBTree& tree) {
	assert(tree.find(5) != nullptr);	
	assert(tree.find(10) == nullptr);	
	assert(tree.find(6) != nullptr);	
}

int main() {
	RBTree tree = RBTree();

	test_insert(tree);
	test_find(tree);
	test_remove(tree);

	return 0;
}
