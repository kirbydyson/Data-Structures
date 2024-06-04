/* CSI 3334
 * Project 3 -- Tree Based Encryption
 * Filename: bst-student-proj3.h
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the templated BSTNode class
 */

#ifndef PROJECT3_TREEBASEDENCRYPTION_BST_STUDENT_PROJ3_H
#define PROJECT3_TREEBASEDENCRYPTION_BST_STUDENT_PROJ3_H

#include "bst-prof-proj3.h"

/* ~BSTNode
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor and deallocates its subtrees.
 */
template <class Base>
BSTNode<Base>::~BSTNode(){
    delete this->left;
    delete this->right;
}

/* printPreorder
 *  parameters:
 *      os -- given stream to output data
 *      indent -- indentation level based on the node
 *  return value:
 *      none
 *
 *  This function traverses this node and its children recursively in
 *  pre-order and prints each node it visits to a given ostream.
 */
template <class Base>
void BSTNode<Base>::printPreorder(ostream &os, string indent) const{
    os << indent << this->data << endl;
    if(left){
        this->left->printPreorder(os, indent + "  ");
    }
    else{
        os << indent + "  NULL" << endl;
    }
    if(right){
        this->right->printPreorder(os, indent + "  ");
    }
    else{
        os << indent + "  NULL" << endl;
    }
}

/* minNode
 *  parameters:
 *      none
 *  return value:
 *      smallest node in the tree
 *
 *  This function finds the leftmost node at or below the node they are
 *  called on.
 */
template <class Base>
const BSTNode<Base> *BSTNode<Base>::minNode() const{
    if(left){
        return this->left->minNode();
    }
    return this;
}

/* minNode
 *  parameters:
 *      none
 *  return value:
 *      largest node in the tree
 *
 *  This function finds the rightmost node at or below the node they are
 *  called on.
 */
template <class Base>
const BSTNode<Base> *BSTNode<Base>::maxNode() const{
    if(right){
        return this->right->maxNode();
    }
    return this;
}

/* insert
 *  parameters:
 *      item -- given item to insert in the tree
 *  return value:
 *      none
 *
 *  This function inserts a given item into a tree, unless the item is already
 *  in the tree.
 */
template <class Base>
void BST<Base>::insert(const Base &item){
    BSTNode<Base> *node = new BSTNode<Base>(item);
    BSTNode<Base> *curr = this->root;
    BSTNode<Base> *prev = nullptr;

    if(!this->root){
        this->root = node;
        return;
    }
    while(curr){
        prev = curr;
        if(item < curr->data){
            curr = curr->left;
        }
        else if(curr->data < item){
            curr = curr->right;
        }
        else{
            delete node;
            return;
        }
    }

    if(item < prev->data){
        prev->left = node;
    }
    else{
        prev->right = node;
    }
}

/* encrypt
 *  parameters:
 *      item -- given object to be encrypted
 *  return value:
 *      string of paths taken
 *
 *  This function encrypts a path to an object in a tree.
 */
template <class Base>
string EncryptionTree<Base>::encrypt(const Base &item) const{
    const BSTNode<Base> *curr = this->root;
    string path = "r";
    bool flag = false;

    while(curr){
        if(item < curr->getData()){
            path += "0";
            curr = curr->getLeft();
        }
        else if(curr->getData() < item){
            path += "1";
            curr = curr->getRight();
        }
        else{
            curr = nullptr;
            flag = true;
        }
    }
    if(!flag){
        path = "?";
    }
    return path;
}

/* decrypt
 *  parameters:
 *      path -- given encrypted string
 *  return value:
 *      a pointer to the associated string for the given path,
 *      or NULL if the path is invalid
 *
 *  This function decrypts a path into the object it leads to.
 */
template <class Base>
const Base *EncryptionTree<Base>::decrypt(const string &path) const{
    const BSTNode<Base> *curr = this->root;

    for(int i = 0; i < path.length() && curr; i++){
        if(path[i] == '0'){
            curr = curr->getLeft();
        }
        else if(path[i] == '1'){
            curr = curr->getRight();
        }
    }
    if(!curr){
        return nullptr;
    }

    return &curr->getData();
}

/* remove
 *  parameters:
 *      item -- given item to remove from the tree
 *  return value:
 *      none
 *
 *  This function removes the given item from the tree,
 *  if it is in the tree.
 */
template <class Base>
void BST<Base>::remove(const Base &item){
    BSTNode<Base> *parent = nullptr;
    BSTNode<Base> *toRemove = this->root;
    bool flag = false;

    while(toRemove && !flag){
        if(item < toRemove->data){
            parent = toRemove;
            toRemove = toRemove->left;
        }
        else if(toRemove->data < item){
            parent = toRemove;
            toRemove = toRemove->right;
        }
        else{
            flag = true;
        }
    }
    if(!flag){
        return;
    }

    if(toRemove->left && toRemove->right){
        BSTNode<Base> *leftMost = toRemove->right;
        BSTNode<Base> *leftMostParent = toRemove;

        if(leftMost->left){
            while(leftMost->left){
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }
        leftMost->left = toRemove->left;

        if(parent){
            if(parent->left == toRemove){
                parent->left = leftMost;
            }
            else{
                parent->right = leftMost;
            }
        }
        else{
            this->root = leftMost;
        }
        leftMostParent = nullptr;
        toRemove->left = toRemove->right = nullptr;
        delete toRemove;
    }
    else if(toRemove->left || toRemove->right){
        BSTNode<Base> *child = nullptr;

        if(toRemove->left){
            child = toRemove->left;
            toRemove->left = nullptr;
        }
        else{
            child = toRemove->right;
            toRemove->right = nullptr;
        }
        if(parent){
            if(parent->left == toRemove){
                parent->left = child;
            }
            else{
                parent->right = child;
            }
        }
        else{
            this->root = child;
        }
        delete toRemove;
    }
    else{
        if(parent){
            if(parent->left == toRemove) {
                parent->left = nullptr;
            }
            else{
                parent->right = nullptr;
            }
        }
        if(!parent){
            this->root = nullptr;
        }
        delete toRemove;
    }
}

#endif //PROJECT3_TREEBASEDENCRYPTION_BST_STUDENT_PROJ3_H
