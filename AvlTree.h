#ifndef DSEX1_AVLTREE_H
#define DSEX1_AVLTREE_H


#include<iostream>
#include<cstdio>


//a generic avl node (in our case- data field will be of type Artist or Song)
template <class T>
class avl_node {
public:
    T* data;
    int height;
    avl_node* father;
    avl_node* left;
    avl_node* right;

    explicit avl_node(T* data);
    ~avl_node();
    avl_node(const avl_node& other);
    int getheight() { return this->height;}
    T* getdata() {return this->data;}
    int balanceFactor();
    avl_node<T>* findNode(const T*& to_find);
    void printtree();
    int calculateHeight();
    avl_node<T>* findNext();
};

template <class T>
class AVLTree {
    avl_node<T>* root;
public:
    int nodes_count;
    avl_node<T>* min_node;
    AVLTree() : root(nullptr) , nodes_count(0), min_node(nullptr) {};
    ~AVLTree();
    AVLTree(const AVLTree& other);
    avl_node<T>* getMin() { return this->min_node;}
    avl_node<T>* insert(T* to_insert);
    avl_node<T>* right_rotate(avl_node<T>*& node);
    avl_node<T>* left_rotate(avl_node<T>*& node);
    avl_node<T>* balance(avl_node<T>*& node);
    avl_node<T>* insertNode(T* to_insert, avl_node<T>*& node);
    avl_node<T>* remove(const T* to_delete);
    avl_node<T>* removeNode(avl_node<T>*& node);
    avl_node<T>* removeNodeRec(avl_node<T>*& node,const T* data);
    avl_node<T>* find(const T* to_find);
    void deleteTree();
    avl_node<T>* deleteTreeRec(avl_node<T>* node);
    void printtree();
    avl_node<T>* getRoot();
    void updateRoot();
    void updateMinNode(avl_node<T>* node);
};

#include "AVLTreeImp.h"


#endif //DSEX1_AVLTREE_H
