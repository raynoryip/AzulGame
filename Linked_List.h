#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <iostream>
#include <string>
#include <vector>

class Linked_List{
    public:
        Linked_List();
        ~Linked_List();

        class Node{
            public:
                std::string data;
                char player;
                Node* next;
                Node* prev;
        };

        void addNodeAtTheBack(std::string data, char player);
        void addNodeAtTheFront(std::string data, char player);
        void printTheList();
        bool containsElement(std::string data, char player);
        int size();

    private:
        Node* headNode;
        Node* endNode;
        int listSize;
};
#endif // !LINKED_LIST_H