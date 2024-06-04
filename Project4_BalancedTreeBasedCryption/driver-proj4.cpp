/* CSI 3334
 * Project 4 -- Balanced Tree-Based Encryption and Decryption
 * Filename: driver-proj4.cpp
 * Student name: Kirby Dyson
 *
 * This file contains a program which implements encryption and decryption
 * using a balanced tree.
 */

#include <iostream>
#include "avl-tree-student-proj4.h"

using namespace std;

/* main
 *  parameters:
 *      none
 *  return value:
 *      0 (indicating a successful run)
 *
 *  This function reads through a list of commands to encrypt or decrypt an
 *  AVL-balanced binary search tree by building a codebook. The command will
 *  either insert or remove a word, encrypt or decrypt a message, or print the
 *  codebook in preorder format. The program will quit once 'q' is read.
 */
int main(){
    EncryptionTree<string> tree;
    char c;
    string item;
    int ndx;
    size_t len;

    cin >> c;

    while(c != 'q'){
        switch(c){
            case 'i':
                cin >> item;
                tree.insert(item);
                break;
            case 'r':
                cin >> item;
                tree.remove(item);
                break;
            case 'e':
                getline(cin, item, '\'');
                getline(cin, item, '\'');
                cin.ignore();
                ndx = 0;
                len = item.length();
                for(int i = 0; i < len; i++){
                    if(item[i] == ' '){
                        cout << tree.encrypt(item.substr(ndx, i - ndx)) << " ";
                        ndx = i + 1;
                    }
                }
                cout << tree.encrypt(item.substr(ndx, item.length() - ndx)) << endl;
                break;
            case 'd':
                getline(cin, item, '\'');
                getline(cin, item, '\'');
                cin.ignore();
                ndx = 0;
                const string *msg;
                len = item.length();
                for(int i = 0; i < len; i++){
                    if(item[i] == ' '){
                        msg = tree.decrypt(item.substr(ndx, i - ndx));
                        ndx = i + 1;
                        cout << (msg ? *msg : "?") << " ";
                    }
                }
                msg = tree.decrypt(item.substr(ndx, item.length() - ndx));
                cout << (msg ? *msg : "?") << endl;
                break;
            case 'p':
                tree.printPreorder();
                break;
            case 'l':
                tree.printLevelOrder();
            default:
                c = 'q';
                break;
        }
        cin >> c;
    }

    return 0;
}