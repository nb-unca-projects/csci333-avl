#include "BST.h"

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(10);
  bst->insert(1);
  bst->insert(2);
  bst->insert(3);
  bst->insert(4);
  bst->insert(12);

  //bst->remove(6);

  //bst->print();


}
