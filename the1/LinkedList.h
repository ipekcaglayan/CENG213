#ifndef LINKEDLIST_H
#define LINKEDLIST_H


#include <iostream>

#include "Node.h"

template<class T>
class LinkedList {
public: // DO NOT CHANGE THIS PART.
    LinkedList();
    LinkedList(const T arr[], int arrSize);
    LinkedList(const LinkedList<T> &obj);

    ~LinkedList();

    Node<T> *getFirstNode() const;
    Node<T> *getLastNode() const;
    Node<T> *getNode(const T &data) const;

    int getNumberOfNodes() const;
    bool isEmpty() const;
    bool contains(Node<T> *node) const;

    void insertAtTheHead(const T &data);
    void insertAtTheTail(const T &data);
    void insertSorted(const T &data);

    void removeNode(Node<T> *node);
    void removeNode(const T &data);
    void removeAllNodes();

    void print() const;

    T *toArray() const;

    LinkedList<T> &operator=(const LinkedList<T> &rhs);

private: // YOU MAY ADD YOUR OWN UTILITY MEMBER FUNCTIONS HERE.

private: // DO NOT CHANGE THIS PART.
    Node<T> *head;
    Node<T> *tail;
};

template<class T>
LinkedList<T>::LinkedList() {
    /* TODO */
}

template<class T>
LinkedList<T>::LinkedList(const T arr[], int arrSize) {
    /* TODO */
}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &obj) {
    /* TODO */
}

template<class T>
LinkedList<T>::~LinkedList() {
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getFirstNode() const {
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getLastNode() const {
    /* TODO */
}

template<class T>
Node<T> *LinkedList<T>::getNode(const T &data) const {
    /* TODO */
}

template<class T>
int LinkedList<T>::getNumberOfNodes() const {
    /* TODO */
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    /* TODO */
}

template<class T>
bool LinkedList<T>::contains(Node<T> *node) const {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheHead(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertAtTheTail(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::insertSorted(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(Node<T> *node) {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeNode(const T &data) {
    /* TODO */
}

template<class T>
void LinkedList<T>::removeAllNodes() {
    /* TODO */
}

template<class T>
void LinkedList<T>::print() const {
    std::cout << "Printing the linked list ..." << std::endl;

    if (this->isEmpty()) {
        std::cout << "empty" << std::endl;
        return;
    }

    Node<T> *node = this->head;

    while (node) {
        std::cout << *node << std::endl;
        node = node->next;
    }
}

template<class T>
T *LinkedList<T>::toArray() const {
    /* TODO */
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &rhs) {
    /* TODO */
}


#endif //LINKEDLIST_H
