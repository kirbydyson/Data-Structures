/* CSI 3334
 * Project 4 -- Balanced Tree-Based Encryption and Decryption
 * Filename: avl-tree-student-proj4.h
 * Student name: Kirby Dyson
 *
 * This file implements the functions from the templated AVLNode class
 */

#ifndef PROJECT4_BALANCEDTREEBASEDCRYPTION_AVL_TREE_STUDENT_PROJ4_H
#define PROJECT4_BALANCEDTREEBASEDCRYPTION_AVL_TREE_STUDENT_PROJ4_H

#include "avl-tree-prof-proj4.h"
#include <queue>

/* ~AVLNode
 *  parameters:
 *      none
 *  return value:
 *      none
 *
 *  This function is the destructor and deallocates its subtrees.
 */
template <class Base>
AVLNode<Base>::~AVLNode(){
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
void AVLNode<Base>::printPreorder(ostream &os, string indent) const{
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
const AVLNode<Base> *AVLNode<Base>::minNode() const{
    if(left){
        return this->left->minNode();
    }
    return this;
}

/* maxNode
 *  parameters:
 *      none
 *  return value:
 *      largest node in the tree
 *
 *  This function finds the rightmost node at or below the node they are
 *  called on.
 */
template <class Base>
const AVLNode<Base> *AVLNode<Base>::maxNode() const{
    if(right){
        return this->right->maxNode();
    }
    return this;
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
    const AVLNode<Base> *curr = this->root;
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
    const AVLNode<Base> *curr = this->root;

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

/* singleRotateLeft
 *  parameters:
 *      none
 *  return value:
 *      a pointer to the node after rotation
 *
 *  This function does a single left rotation.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateLeft(){
    AVLNode<Base> *rightChild = this->right;

    this->right = rightChild->left;
    rightChild->left = this;

    this->updateHeight();
    rightChild->updateHeight();

    return rightChild;
}

/* singleRotateRight
 *  parameters:
 *      none
 *  return value:
 *      a pointer to the node after rotation
 *
 *  This function does a single right rotation.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::singleRotateRight(){
    AVLNode<Base> *leftChild = this->left;

    this->left = leftChild->right;
    leftChild->right = this;

    this->updateHeight();
    leftChild->updateHeight();

    return leftChild;
}

/* doubleRotateLeftRight
 *  parameters:
 *      none
 *  return value:
 *      a pointer to the node after both rotations
 *
 *  This function does a double left-right rotation.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateLeftRight(){
    this->left = this->left->singleRotateLeft();
    return this->singleRotateRight();
}

/* doubleRotateRightLeft
 *  parameters:
 *      none
 *  return value:
 *      a pointer to the node after both rotations
 *
 *  This function does a double right-left rotation.
 */
template <class Base>
AVLNode<Base> *AVLNode<Base>::doubleRotateRightLeft(){
    this->right = this->right->singleRotateRight();
    return this->singleRotateLeft();
}

/* insert
 *  parameters:
 *      item -- given item to insert in the tree
 *  return value:
 *      none
 *
 *  This function inserts a given item into a tree, re-balancing as necessary.
 */
template <class Base>
void AVLTree<Base>::insert(const Base &item){
    vector<AVLNode<Base> *> path;
    AVLNode<Base> *node = new AVLNode<Base>(item);
    AVLNode<Base> *curr = this->root;
    AVLNode<Base> *prev = nullptr;

    if(!this->root){
        this->root = node;
        return;
    }
    while(curr){
        path.push_back(curr);
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

    this->rebalancePathToRoot(path);
}

/* rebalancePathToRoot
 *  parameters:
 *      path -- given vector of pointers to AVLNode objects
 *  return value:
 *      none
 *
 *  This function walks from the bottom of the path to the root, checking for
 *  imbalances, and correcting any it finds through rotations.
 */
template <class Base>
void AVLTree<Base>::rebalancePathToRoot(vector<AVLNode<Base> *> const &path){
    for(int i = path.size() - 1; i >= 0; i--){
        AVLNode<Base> *curr = path[i];
        AVLNode<Base> *parent = nullptr;

        if(i > 0) {
            parent = path[i - 1];
        }

        int diff = curr->getHeight(curr->left) - curr->getHeight(curr->right);

        if(diff > 1){
            if(curr->left->getHeight(curr->left->left) <
               curr->left->getHeight(curr->left->right)){
                if(!parent){
                    this->root = curr->doubleRotateLeftRight();
                }
                else if(parent->left == curr){
                    parent->left = curr->doubleRotateLeftRight();
                }
                else{
                    parent->right = curr->doubleRotateLeftRight();
                }
            }
            else{
                if(!parent){
                    this->root = curr->singleRotateRight();
                }
                else if(parent->left == curr){
                    parent->left = curr->singleRotateRight();
                }
                else{
                    parent->right = curr->singleRotateRight();
                }
            }
        }
        else if(diff < -1){
            if(curr->right->getHeight(curr->right->left) >
                curr->right->getHeight(curr->right->right)){
                if(!parent){
                    this->root = curr->doubleRotateRightLeft();
                }
                else if(parent->left == curr){
                    parent->left = curr->doubleRotateRightLeft();
                }
                else{
                    parent->right = curr->doubleRotateRightLeft();
                }
            }
            else{
                if(!parent){
                    this->root = curr->singleRotateLeft();
                }
                else if(parent->left == curr){
                    parent->left = curr->singleRotateLeft();
                }
                else{
                    parent->right = curr->singleRotateLeft();
                }
            }
        }
        curr->updateHeight();
    }
}

/* remove
 *  parameters:
 *      item -- given item to remove from the tree
 *  return value:
 *      none
 *
 *  This function removes the given item from the tree,
 *  re-balancing as necessary.
 */
template <class Base>
void AVLTree<Base>::remove(const Base &item){
    vector<AVLNode<Base> *> path;
    AVLNode<Base> *parent = nullptr;
    AVLNode<Base> *toRemove = this->root;
    bool flag = false;

    while(toRemove && !flag){
        path.push_back(toRemove);
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
        AVLNode<Base> *leftMost = toRemove->right;
        AVLNode<Base> *leftMostParent = toRemove;
        int ndx = path.size() - 1;

        if(leftMost->left){
            while(leftMost->left){
                path.push_back(leftMost);
                leftMostParent = leftMost;
                leftMost = leftMost->left;
            }
            leftMostParent->left = leftMost->right;
            leftMost->right = toRemove->right;
        }
        leftMost->left = toRemove->left;
        path.at(ndx) = leftMost;

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
        this->rebalancePathToRoot(path);
        delete toRemove;
    }
    else if(toRemove->left || toRemove->right){
        AVLNode<Base> *child = nullptr;

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
        this->rebalancePathToRoot(path);
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
        this->rebalancePathToRoot(path);
        delete toRemove;
    }
}


/* printLevelOrder
 *  parameters:
 *      os -- given stream to output data
 *  return value:
 *      none
 *
 *  This function prints all the nodes in the tree in the order of the
 *  root, the root's children, their children, etc.
 */
template <class Base>
void AVLTree<Base>::printLevelOrder(ostream &os) const{
    queue<AVLNode<Base>*> path;
    int nodes = 0;
    const int MAX = 20;

    path.push(this->root);
    if(!this->root) {
        os << "NULL" << endl;
        return;
    }

    while(!path.empty()){
        AVLNode<Base> *curr = path.front();
        nodes++;
        path.pop();

        if(curr){
            os << curr->data;
            path.push(curr->left);
            path.push(curr->right);
        }
        else {
            os << "NULL";
        }
        if(!path.empty()){
                if(nodes >= MAX){
                os << endl;
                nodes = 0;
            }
            else{
                os << " ";
            }
        }
    }
    os << endl;
}

#endif //PROJECT4_BALANCEDTREEBASEDCRYPTION_AVL_TREE_STUDENT_PROJ4_H
