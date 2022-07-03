#include "rbtree.h"

RBTree::RBTree() {
  null_node_ = new RBNode(0);
  root_ = null_node_;
}

RBTree::~RBTree() {
  destroy_tree(root_);
  delete null_node_;
}

/*
  *	Calculate the height of the tree.

  * @params - void.
  * @return - height or 0 if tree is empty.
*/
int RBTree::height() {
  if (!root_) return 0;

  int tree_height = 0;
  std::vector<std::pair<RBNode*, int>> stack = {{root_, 0}};

  while (!stack.empty()) {
    std::pair<RBNode*, int> p = stack.back();
    stack.pop_back();

    if (p.first == null_node_) continue;
    tree_height = std::max(tree_height, p.second);

    if (p.first->left) stack.push_back({p.first->left, p.second + 1});

    if (p.first->right) stack.push_back({p.first->right, p.second + 1});
  }

  return tree_height;
}

// Find the smallest value in the tree.
RBNode* RBTree::minimum(RBNode* node) {
  RBNode* current = (!node) ? root_ : node;
  RBNode* min_node = current;
  while (current != null_node_) {
    min_node = current;
    current = current->left;
  }

  return min_node;
}

// Find the biggest value in the tree.
RBNode* RBTree::maximum(RBNode* node) {
  RBNode* current = (!node) ? root_ : node;
  RBNode* max_node = current;
  while (current != null_node_) {
    max_node = current;
    current = current->right;
  }

  return max_node;
}

/*
  *	Find node by data.

  * @params - int the type of the data stored in the node.
  * @return - RBNode* if node with given data exists else nullptr.
*/
RBNode* RBTree::find(int data) {
  RBNode* current = root_;
  while (current != nullptr) {
    if (data == current->data) return current;
    if (data > current->data)
      current = current->right;
    else
      current = current->left;
  }

  return nullptr;
}

/*
  *	Perform Tree Level Order Traversal.

  * @params - void.
  * @return - std::vector<std::vector<RBNode*>> where nodes are ordered by their
  levels.
*/
std::vector<std::vector<int>> RBTree::level_traversal() {
  std::vector<std::vector<int>> data;
  lot_helper(root_, data, 0);

  return data;
}

/*
  *	Insert a new node into the RBTree.

  * @params - int the type of the data stored in the node.
  * @return - void.
*/
void RBTree::insert(int data) {
  RBNode* new_node = new RBNode(data, null_node_);
  new_node->color = RED;

  RBNode* current = root_;
  RBNode* parent = nullptr;
  while (current != null_node_) {
    parent = current;
    if (current->data < new_node->data) {
      current = current->right;
    } else if (current->data > new_node->data) {
      current = current->left;
    } else {
      // Node with this value already exists.
      delete new_node;
      return;
    }
  }

  new_node->parent = parent;
  if (!parent)
    root_ = new_node;
  else if (parent->data < new_node->data)
    parent->right = new_node;
  else
    parent->left = new_node;

  if (!new_node->parent) {
    new_node->color = BLACK;
    return;
  }

  if (!new_node->parent->parent) return;

  fix_insert(new_node);
}

/*
  *	Fix new node insertion.

  * @params - RBNode* the type of the newly inserted node.
  * @return - void.
*/
void RBTree::fix_insert(RBNode* node) {
  while (node != root_ && node->parent->color == RED) {
    if (node->parent == node->parent->parent->left) {
      RBNode* uncle = node->parent->parent->right;

      if (uncle->color == RED) {
        node->parent->parent->left->color = BLACK;
        node->parent->parent->right->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->right) {
          node = node->parent;
          rotate_left(node);
        }

        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        rotate_right(node->parent->parent);
      }
    } else {
      RBNode* uncle = node->parent->parent->left;

      if (uncle->color == RED) {
        node->parent->parent->left->color = BLACK;
        node->parent->parent->right->color = BLACK;
        node->parent->parent->color = RED;
        node = node->parent->parent;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rotate_right(node);
        }

        node->parent->color = BLACK;
        node->parent->parent->color = RED;
        rotate_left(node->parent->parent);
      }
    }
  }

  root_->color = BLACK;
}

/*
  *	Delete a node from the tree.

  * @params - int the type of the data stored in the node.
  * @return - void.
*/
void RBTree::remove(int data) {
  RBNode* node = find(data);
  if (node == nullptr) return;
  RBNode *current = node, *replacing_node;

  char color = current->color;
  if (node->left == null_node_) {
    replacing_node = node->right;
    replace(node, node->right);
  } else if (node->right == null_node_) {
    replacing_node = node->left;
    replace(node, node->left);
  } else {
    current = minimum(node->right);
    color = current->color;
    replacing_node = current->right;

    if (current->parent == node) {
      replacing_node->parent = current;
    } else {
      replace(current, current->right);
      current->right = node->right;
      current->right->parent = current;
    }

    replace(node, current);
    current->left = node->left;
    current->left->parent = current;
    current->color = node->color;
  }

  delete node;
  if (color == BLACK) fix_remove(replacing_node);
}

/*
  *	Fix deletion.

  * @params - RBNode* the type of the deleted node.
  * @return - void.
*/
void RBTree::fix_remove(RBNode* node) {
  while (node != root_ && node->color == BLACK) {
    if (node == node->parent->left) {
      RBNode* sibling = node->parent->right;
      if (sibling->color == RED) {
        sibling->color = BLACK;
        node->parent->color = RED;
        rotate_left(node->parent);
        sibling = node->parent->right;
      }

      if (sibling->left->color == BLACK && sibling->right->color == BLACK) {
        sibling->color = RED;
        node = node->parent;
      } else {
        if (sibling->right->color == BLACK) {
          sibling->left->color = BLACK;
          sibling->color = RED;
          rotate_right(sibling);
          sibling = node->parent->right;
        }

        sibling->color = node->parent->color;
        node->parent->color = BLACK;
        sibling->right->color = BLACK;
        rotate_left(node->parent);
        node = root_;
      }
    } else {
      RBNode* sibling = node->parent->left;
      if (sibling->color == RED) {
        sibling->color = BLACK;
        node->parent->color = RED;
        rotate_right(node->parent);
        sibling = node->parent->left;
      }

      if (sibling->right->color == BLACK && sibling->left->color == BLACK) {
        sibling->color = RED;
        node = node->parent;
      } else {
        if (sibling->left->color == BLACK) {
          sibling->right->color = BLACK;
          sibling->color = RED;
          rotate_left(sibling);
          sibling = node->parent->left;
        }

        sibling->color = node->parent->color;
        node->parent->color = BLACK;
        sibling->left->color = BLACK;
        rotate_right(node->parent);
        node = root_;
      }
    }
  }

  node->color = BLACK;
}

// -*- Helper functions -*-

void RBTree::lot_helper(RBNode* node, std::vector<std::vector<int>>& data,
                        int level) {
  if (!node || node == null_node_) return;

  if (data.size() == level) data.push_back({});
  data[level].push_back(node->data);

  level++;
  lot_helper(node->left, data, level);
  lot_helper(node->right, data, level);
}

void RBTree::replace(RBNode* node, RBNode* replacing_node) {
  if (node->parent == nullptr)
    root_ = replacing_node;
  else if (node == node->parent->left)
    node->parent->left = replacing_node;
  else
    node->parent->right = replacing_node;

  replacing_node->parent = node->parent;
}

void RBTree::rotate_left(RBNode* node) {
  RBNode* y = node->right;
  node->right = y->left;
  if (y->left != null_node_) y->left->parent = node;

  y->parent = node->parent;
  if (node->parent == nullptr) {
    root_ = y;
  } else if (node == node->parent->left) {
    node->parent->left = y;
  } else {
    node->parent->right = y;
  }

  y->left = node;
  node->parent = y;
}

void RBTree::rotate_right(RBNode* node) {
  RBNode* y = node->left;
  node->left = y->right;
  if (y->right != null_node_) y->right->parent = node;

  y->parent = node->parent;
  if (node->parent == nullptr)
    root_ = y;
  else if (node == node->parent->right)
    node->parent->right = y;
  else
    node->parent->left = y;

  y->right = node;
  node->parent = y;
}

void RBTree::destroy_tree(RBNode* node) {
  if (node == null_node_) return;

  destroy_tree(node->left);
  destroy_tree(node->right);
  delete node;
}
