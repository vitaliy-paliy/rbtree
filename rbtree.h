#ifndef RBTREE_
#define RBTREE_

#include <vector>

enum RBColor { BLACK, RED };

struct RBNode {
  int data;
  int color;
  RBNode *parent, *left, *right;
  RBNode(int d, RBNode* ptr = nullptr)
      : data(d), color(BLACK), parent(ptr), left(ptr), right(ptr) {}
};

class RBTree {
  RBNode* root_;
  RBNode* null_node_;

 private:
  void fix_insert(RBNode* node);
  void fix_remove(RBNode* node);
  void replace(RBNode* node, RBNode* replacing_node);
  void rotate_left(RBNode* node);
  void rotate_right(RBNode* node);
  void lot_helper(RBNode* node, std::vector<std::vector<int>>& data, int level);
  void destroy_tree(RBNode* node);
  int height_helper(RBNode* node);

 public:
  RBTree();
  ~RBTree();
  int height();
  RBNode* minimum(RBNode* node = nullptr);
  RBNode* maximum(RBNode* node = nullptr);
  std::vector<std::vector<int>> level_traversal();
  void insert(int data);
  void remove(int data);
  RBNode* find(int data);
};

#endif
