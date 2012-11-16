#include "BST.h"
#include <iostream>
#include <sstream>
#include <list>

using std::string;

template <typename T>
BST<T>::BST() {
  root = 0;
}

template <typename T>
BST<T>::~BST() {
  
}

template <typename T>
bool BST<T>::find(T v) {
  Node<T>* temp = new Node<T>(v);
  root = temp;  
  return true;
}

template <typename T>
void BST<T>::rotate(int direction, Node<T>** cn) {
  if(cn == 0)
    cn = &root;
  if (direction == -1) {
    //rotate left
    Node<T>* temp = *cn;
    Node<T>* child = ((*cn)->getRightChild())->getLeftChild();
    *cn = temp->getRightChild();
    (*cn)->setLeftChild(*temp);
    temp->setRightChild(*child); 
  }
  else {
    //rotate right
    Node<T>* temp = *cn;
    Node<T>* child = ((*cn)->getLeftChild())->getRightChild();
    *cn = temp->getLeftChild();
    (*cn)->setRightChild(*temp);
    temp->setLeftChild(*child);
  }
}

template <typename T>
void BST<T>::insert(T v) {
    Node<T>* newNode = new Node<T>(v);
  Node<T>** P = &root;
  Node<T>** A;
  bool CritNodeFound = false;
  while (*P != 0 && (*P)->getValue() != v) {
    if ((*P)->getBalance() != 0) {
      A = P;
      CritNodeFound = true;      
    }
    if ((*P)->getValue() > v) {
      P = &((*P)->getLeftChild());
    } else {
      P = &((*P)->getRightChild());
    }
  }
  //Node with value v already exists
  if (*P != 0)
    return;
  *P = newNode;
  Node<T>* R = 0;
  Node<T>** C = 0;
  Node<T>** B = 0;
  int d1;
  int d2;
  int d3;
  if (!CritNodeFound)
    R = root;
  else {
      if (v == (*A)->getValue()){
        C = A;
        d1 = 0;
      } else if (v < (*A)->getValue()) {
        C = &((*A)->getLeftChild());
        d1 = -1;
      } else {
        C = &((*A)->getRightChild());
        d1 = 1;
      }
    if ((*A)->getBalance() != d1) {
      (*A)->setBalance(0);
      R = *C;
    }
    else {
  	if (v == (*C)->getValue()){
    	  B = C;
    	  d2 = 0;
  	} else if (v < (*C)->getValue()) {
    	  B = &((*C)->getLeftChild());
    	  d2 = -1;
  	} else {
    	  B = &((*C)->getRightChild());
    	  d2 = 1;
  	}
      if (d2 == d1) {
        (*A)->setBalance(0);
        R = *B;
	rotate(-d1, A);
      }
      else {
       
  	if (v == (*B)->getValue()){
          R = *B;
    	  d3 = 0;
  	} else if (v < (*B)->getValue()) {
   	  R = ((*B)->getLeftChild());
  	  d3 = -1;
 	} else {
   	  R = ((*B)->getRightChild());
    	  d3 = 1;
  	}
	if (d3 == d2) {
	  (*A)->setBalance(0);
	  (*C)->setBalance(d1);
	}
	else if (d3 == -d2)
	  (*A)->setBalance(d2);
	else {
	  rotate(-d2, C);
	  rotate(-d1, A);
	}
      }
    }
  }
  while (R->getValue() != v) {
    if (v < R->getValue()) {
      R->setBalance(-1);
      R = R->getLeftChild();
    }
    else {
      R->setBalance(1);
      R = R->getRightChild();
    }
  }
}

template <typename T>
void BST<T>::remove(T v) {
  Node<T>** curr = &root;
  while (*curr != 0 && (*curr)->getValue() != v) {
    if ((*curr)->getValue() > v)
      curr = &((*curr)->getLeftChild());
    else if ((*curr)->getValue() < v)
      curr = &((*curr)->getRightChild());
  }
  //if node doesn't exist
  if (*curr == 0) {
    std::cout << "Value not found in tree" << std::endl;
  } else {

  Node<T>* temp = *curr;
  if ((*curr)->getLeftChild() == 0 && (*curr)->getRightChild() == 0) {
    *curr = 0;
    delete temp;
  }else if ((*curr)->getLeftChild() == 0) {
    *curr = (*curr)->getRightChild();
    delete temp;
  }else if ((*curr)->getRightChild() == 0) {
    *curr = (*curr)->getLeftChild();
    delete temp;
  }else {
    //find inorder successor (ios)
    Node<T>* ios = (*curr)->getRightChild();
    while (ios->getLeftChild() != 0) {
      ios = ios->getLeftChild();
    }
    ios->setLeftChild(*((*curr)->getLeftChild()));
    *curr = ios;
    delete temp;
  }
 }
}

template <typename T>
void BST<T>::print() {
  traversalPrint(root);
}

template <typename T>
std::list<string>* BST<T>::createPrintQueue() {
  std::list<string>* printQ = new std::list<string>();
  std::list< Node<T>* >* q = new std::list< Node<T>* >();
  
  Node<T>* curr = root;
  printQ->push_back(toString(curr->getValue()));
  q->push_back(curr);
  while (!q->empty()) {
    curr = q->front();
    
    if (curr->getLeftChild() != 0) {
      printQ->push_back(toString(curr->getLeftChild()->getValue()));
      q->push_back(curr->getLeftChild());
    }else {
      printQ->push_back("-");
    }
    if (curr->getRightChild() != 0) {
      printQ->push_back(toString(curr->getRightChild()->getValue()));
      q->push_back(curr->getRightChild());
    }else {
      printQ->push_back("-");
    }
    q->pop_front();
    //printQ->push_back(toString(curr->getValue()));
  }
  delete q;
  return printQ;  
}

template <typename T>
int BST<T>::getDepth(Node<T>* root, int depth) {
  if(root != 0 && (root->getLeftChild() !=0 || root->getRightChild())) {
    int leftDepth = getDepth(root->getLeftChild(), depth+1);
    int rightDepth = getDepth(root->getRightChild(), depth+1);
    if(leftDepth>rightDepth)
      return leftDepth;
    else
      return rightDepth;
  }
  else
    return depth;
}

template <typename T>
string BST<T>::toString(T v) {
  std::stringstream s;
  s << v;
  return s.str();
}

template <typename T>
void BST<T>::traversalPrint(Node<T>* root) {
  if(root != 0) {
    traversalPrint(root->getLeftChild());
    std::cout << root->getValue() << std::endl;
    traversalPrint(root->getRightChild());
    //std::cout << root->getValue() << std::endl;
  }
}


template class BST<int>;
template class BST<double>;
template class BST<std::string>;
