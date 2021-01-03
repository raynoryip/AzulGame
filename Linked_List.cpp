#include "Linked_List.h"

Linked_List::Linked_List(){
    this->headNode = NULL;
    this->endNode = NULL;
}

Linked_List::~Linked_List(){
    Node* tempNode;
    while(headNode!=NULL){
        tempNode = headNode->next;
        delete headNode;
        headNode = tempNode;
    }
}

void Linked_List::addNodeAtTheBack(std::string data, char player){
    //create a new node
    Node* currentNode = new Node();
    this->listSize += 1;

    currentNode->data = data;
    currentNode->player = player;
    currentNode->next = NULL;

    //if the list is empty
    if(this->headNode==NULL){
        this->headNode = currentNode;
        this->endNode = currentNode;
        currentNode->prev = NULL;
    }
    else{
        currentNode->prev = this->endNode;
        this->endNode->next = currentNode;
        this->endNode = currentNode;
    }
}

void Linked_List::addNodeAtTheFront(std::string data, char player){
    Node* currentNode = new Node();
    this->listSize += 1;
    
    currentNode->data = data;
    currentNode->player = player;
    currentNode->prev = NULL;
    //if the list is empty
    if(this->headNode==NULL){
        this->headNode = currentNode;
        this->endNode = currentNode;
        currentNode->next = NULL;
    }else{
        this->headNode->prev = currentNode;
        currentNode->next = this->headNode;
        this->headNode = currentNode;
    }
}

void Linked_List::printTheList(){
    Node *currentNode = this->headNode; 
    while(currentNode!=NULL){
        std::cout << "Player " << currentNode->player << " > " << currentNode->data << '\n';
        currentNode = currentNode->next;
    }
}

bool Linked_List::containsElement(std::string data, char player){
    Node *currentNode = this->headNode; 
    while(currentNode!=NULL){
        if(currentNode->data==data && currentNode->player==player){
            return true;
        }
        currentNode = currentNode->next;
    }
    return false;
}

int Linked_List::size(){
    return this->listSize;
}