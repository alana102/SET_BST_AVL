// Alana Maria Sousa Augusto - 564976
#ifndef NODE_HPP
#define NODE_HPP
#include<iostream>
using namespace std;

struct Node{

    int key;
    Node *right;
    Node *left;
    int height;

    Node(int k, Node *r, Node *l){
        key = k;
        right = r;
        left = l;
        height = 1;
    }


};

#endif