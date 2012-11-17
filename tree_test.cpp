#include "BST.h"

int main() {
  BST<int>* bst = new BST<int>();

  bst->insert(5);
  bst->insert(3);
  bst->insert(4);
  
  for (int i=6; i<50; ++i){
    bst->insert(i);
  }
  for (int j=25; j<40; ++j) {
    bst->remove(j);
  }
  
  bst->print();


}
