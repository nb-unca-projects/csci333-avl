#ifndef __BST_H__
#define __BST_H__

#include "Node.h"
#include <string>
#include <list>

template <typename T>
class BST {
 private:
  Node<T>* root;
  void traversalPrint(Node<T>* root);
  std::list<std::string>* createPrintQueue();
  int getDepth(Node<T>* root, int depth);
  std::string toString(T v);
  void rotate(int direction, Node<T>** cn);

 public:
  BST<T>();
  ~BST<T>();
  bool find(T v);
  void remove(T v);
  void insert(T v);
  void print();
};




#endif
