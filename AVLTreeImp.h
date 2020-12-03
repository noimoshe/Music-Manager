#ifndef DSEX1_AVLTREEIMP_H
#define DSEX1_AVLTREEIMP_H

#include<iostream>
#include<cstdio>

using std::max;

template <class T>
avl_node<T>::avl_node(T* data) {
    this->data = data;
    this->left = nullptr;
    this->right = nullptr;
    this->height = 1;
    this->father = nullptr;
}

template <class T>
avl_node<T>::avl_node(const avl_node &other) {
    this->data = other.data;
    this->height = other.height;
    this->father = other.father;
    this->right = other.right;
    this->left = other.left;
}

template <class T>
avl_node<T>::~avl_node() {
   if(this->data) delete this->data;
}

template <class T>
int avl_node<T>::balanceFactor() {
        int left_height;
        if(this->left == nullptr)
            left_height = 0;
        else
            left_height = this->left->getheight();
        int right_height;
        if(this->right == nullptr)
            right_height = 0;
        else
            right_height= this->right->getheight();
        int bf = left_height - right_height;
        return bf;
}

template <class T>
avl_node<T>* AVLTree<T>::right_rotate(avl_node<T>*& node) {
    avl_node<T>* left_son = node->left;
    avl_node<T>* left_son_right_son = left_son->right;
    left_son->right = node;
    node->left = left_son_right_son;
    if(left_son_right_son)
        left_son_right_son->father = node;
    left_son->father = node->father;
    node->father = left_son;
    node->calculateHeight();
    left_son->calculateHeight();
    if(node == root)
        root = left_son;
    return left_son;
}

template <class T>
avl_node<T>* AVLTree<T>::left_rotate(avl_node<T>*& node) {
    avl_node<T>* right_son = node->right;
    avl_node<T>* right_son_left_son = right_son->left;
    right_son->left = node;
    node->right = right_son_left_son;
    if(right_son_left_son)
        right_son_left_son->father = node;
    right_son->father = node->father;
    node->father = right_son;
    node->calculateHeight();
    right_son->calculateHeight();
    if(node == root)
        root = right_son;
    return right_son;
}

template <class T>
int avl_node<T>::calculateHeight() {
    if(this == nullptr) return 0;
    if(this->left != nullptr && this->right != nullptr)
        this->height = max(this->left->getheight(), this->right->getheight()) + 1;
    //one child
    if((this->left == nullptr && this->right != nullptr) || (this->left !=
                                                             nullptr && this->right == nullptr))
        this->height = 2;
    //no child
    if(this->left == nullptr && this->right == nullptr)
        this->height = 1;
    return this->height;
}

template <class T>
avl_node<T>* AVLTree<T>::balance(avl_node<T>*& node) {
    node->calculateHeight();
    int bf = node->balanceFactor();
    if (bf > 1) {
        //ll rotate
        if (node->left->balanceFactor() != -1) {
            return right_rotate(node);
        }
        //lr rotate
        else {
            node->left = left_rotate(node->left);
            return right_rotate(node);
        }
    } else if (bf < -1) {
        //rl rotate
        if (node->right->balanceFactor() == 1) {
            node->right = right_rotate(node->right);
            return left_rotate(node);
        }
        else { //rr rotate
            return left_rotate(node);
        }
    }
    return node;
}

template<class T>
avl_node<T>* avl_node<T>::findNext() {
    if(this->right == nullptr) return this->father;
    avl_node<T>* next = this->right;
    while(this->right->left != nullptr)
        next = this->right->left;
    return next;
}

template <class T>
avl_node<T>* AVLTree<T>::insertNode(T *to_insert, avl_node<T>*& node) {
    if (*(node->data) > *to_insert) {
        if(node->left == nullptr) {
            node->left = new avl_node<T>(to_insert);
            node->left->father = node;
            return balance(node);
        }
        else{
            node->left = insertNode(to_insert, node->left);
            return balance(node);
        }
    } else if (*(node->data) < *to_insert) {
        if (node->right == nullptr) {
            node->right = new avl_node<T>(to_insert);
            node->right->father = node;
            return balance(node);
        } else {
            node->right = insertNode(to_insert, node->right);
            return balance(node);
        }
    }
    else {
        return node;
    }
}

template<class T>
avl_node<T>* AVLTree<T>::removeNodeRec(avl_node<T> *&node, const T* data) {
    if (node == nullptr) return nullptr;
    if (*(node->data) < *data) //go right
        node->right = removeNodeRec(node->right, data);
    else if (*(node->data) > *data) //go left
        node->left = removeNodeRec(node->left, data);
    else if (*(node->data) == *data) {
        //remove node
        removeNode(node);
    }
    if (node == nullptr)
        return node;
    node->calculateHeight();
    return balance(node);
}

template <class T>
avl_node<T>* AVLTree<T>::removeNode(avl_node<T> *&node) {
    if((node->left== nullptr) && (node->right==nullptr)){ //no sons
        avl_node<T>* temp = node;
        if(node == root){
            root = root->right;
        }
        node = nullptr;
        delete temp;
    }
    else if(node->left == nullptr) { //only right son
        T* temp = node->getdata();
        node->data = node->right->getdata();
        node->right->data = temp;
        delete node->right;
        node->right = nullptr;
    }
    else if(node->right == nullptr) { //only left son
        T* temp = node->data;
        node->data = node->left->data;
        node->left->data = temp;
        delete node->left;
        node->left = nullptr;
    }
    else { // got left and right son
        avl_node<T>* minkey = node->right;
        while (minkey->left != nullptr){
            minkey=minkey->left;
        }
        T* temp = node->data;
        node->data=minkey->data;
        minkey->data= temp;
        node->right = removeNodeRec(node->right,(minkey->data));
    }
    return nullptr;
}

template<class T>
avl_node<T>* avl_node<T>::findNode(const T*& to_find) {
    if(this == nullptr) return nullptr;
    if(*this->data > *to_find){
        return this->left->findNode(to_find);
    }
    else if(*this->data < *to_find ){
        return this->right->findNode(to_find);
    }
    else if (*this->data == *to_find){
        return this;
    }
    return nullptr;
}

template <class T>
AVLTree<T>::~AVLTree() {
   deleteTree();
}

template <class T>
AVLTree<T>::AVLTree(const AVLTree &other) {
    this->root = other.root;
    this->min_node = other.min_node;
    this->nodes_count = other.nodes_count;
}

template<class T>
avl_node<T>* AVLTree<T>::insert(T* to_insert) {
    if(to_insert == nullptr) return nullptr;
    if (root == nullptr) {
        root = new avl_node<T>(to_insert);
        nodes_count++;
        min_node = root;
    } else {
        root = insertNode(to_insert, root);
        nodes_count++;
        updateMinNode(root);
    }
    updateRoot();
    return nullptr;
    //return find(to_insert);
}

template<class T>
avl_node<T>* AVLTree<T>::remove(const T* to_delete) {
    if(root == nullptr) return root;
    avl_node<T>* intree = find(to_delete);
    if(!intree) return nullptr;
    if(intree == min_node)
        min_node = nullptr;
    avl_node<T>* to_return = removeNodeRec(this->root, to_delete);
    nodes_count--;
    updateRoot();
    updateMinNode(root);
    return to_return;
}

template<class T>
avl_node<T>* AVLTree<T>::find(const T* to_find) {
    return root->findNode(to_find);
}

template<class T>
void AVLTree<T>::deleteTree() {
    root = deleteTreeRec(root);
    nodes_count = 0;
}

template <class T>
void avl_node<T>::printtree() {
    if (this == nullptr) return;
    this->left->printtree();
    std::cout << *this->data << " ";
    std::cout << "BF:" << this->balanceFactor() << " ";
    std::cout << "Height:" << this->getheight() -1 << " ";
    std::cout << '\n';
    this->right->printtree();
}

template<class T>
avl_node<T>* AVLTree<T>::deleteTreeRec(avl_node<T> *node) {
    if(node == nullptr) return nullptr;
    if(node->left) node->left = deleteTreeRec(node->left);
    if(node->right) node->right = deleteTreeRec(node->right);
    return removeNode(node);
}


template <class T>
void AVLTree<T>::printtree() {
    this->root->printtree();
}

template <class T>
avl_node<T>* AVLTree<T>::getRoot() {
    return this->root;
}

template <class T>
void AVLTree<T>::updateRoot() {
    if(this->root == nullptr) return;
    while(this->root->father != nullptr){
        this->root = this->root->father;
    }
}

template <class T>
void AVLTree<T>::updateMinNode(avl_node<T>* node){
    if(node == nullptr) return;
    min_node = node;
    node = node->left;
    while(node != nullptr){
        min_node = node;
        node = node->left;
    }
}
#endif //DSEX1_AVLTREEIMP_H
