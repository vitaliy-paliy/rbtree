# C++ Implementation of Red-black tree

A `Red-black tree` is a kind of [binary search tree](https://en.wikipedia.org/wiki/Binary_search_tree). The main aspect of the Red-black tree is its self-balancing feature.
In order for this data structure to function, these four properties should always be satisfied:
- The root node of the tree is always `black`.
- Each node should be colored either red `or` black.
- Two red nodes `cannot` be adjacent.
- Every path from the root node to any leaf node must have the same number of `black` nodes.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/1/10/Red-black_tree_example_nN.svg/800px-Red-black_tree_example_nN.svg.png)

## Example
```cpp
#include "rbtree.h"

void example() {
  RBTree tree = RBTree();
  tree.insert(5);
  tree.insert(6);
  tree.insert(2);
  tree.insert(4);
  
  tree.level_traversal(); // returns [[5], [2, 6], [4]].
  tree.height(); // returns 2.
  tree.find(2); // returns RBNode*(2);
  tree.find(1); // returns nullptr.
}

```

### Credits:
[Red Black-Tree Image](https://en.wikipedia.org/wiki/File:Red-black_tree_example_nN.svg)
