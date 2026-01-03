#pragma once

#include <iostream>
#include <stdexcept>

namespace mtm {

    template <typename T>
    class SortedList {
        struct Node{
        Node *next, *prev;
        T data;
        explicit Node(const T& data): next(nullptr), prev(nullptr), data(data){
        }
    };
        Node *head;
    public:
    class ConstIterator;
    SortedList(){
        head = nullptr;
    }

    ~SortedList(){
        Node *currentNode = this->head;
        while(currentNode != nullptr){
            Node *nextNode = currentNode->next;
            delete currentNode;
            currentNode = nextNode;
        }
    }

    SortedList(const SortedList& list){
        Node *prev = nullptr;
        this->head = nullptr;
        for(SortedList<T>::ConstIterator it = list.begin(); it != list.end(); ++it){
            Node *node = new Node(*it);
            if(prev != nullptr){
                prev->next = node;
                node->prev = prev;
            }else{
                head = node;
            }
            prev = node;
        }
    }

    SortedList& operator=(const SortedList& list){
        if(this == &list){
            return *this;
        }
        Node* current = head;
        while (current != nullptr){
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
        head = nullptr;
        Node *prev = nullptr;
        for(SortedList<T>::ConstIterator it = list.begin(); it != list.end(); ++it){
            Node *node = new Node(*it);
            if(prev != nullptr){
                prev->next = node;
                node->prev = prev;
            }else{
                head = node;
            }
            prev = node;
        }
        return *this;
    }

    SortedList<T>::ConstIterator begin() const{
        return SortedList<T>::ConstIterator(head);
    }

    SortedList<T>::ConstIterator end() const{
        return SortedList<T>::ConstIterator(nullptr);
    }

    void insert(T element){
        Node *newNode = new Node(element);
        if(head == nullptr){
            head = newNode;
        }else{
            SortedList<T>::ConstIterator it = this->begin();
            for(;it != this->end() && !(element > *it); ++it){
            }
            if(it.index == nullptr){
                SortedList<T>::ConstIterator tail = this->begin();
                for(;tail.index->next != nullptr; ++tail){
                }
                newNode->prev = tail.index;
                tail.index->next = newNode;
            }else if(it.index == head){
                newNode->next = head;
                head = newNode;
                it.index->prev = newNode;
                newNode->prev = nullptr;
            }else{
            newNode->prev = it.index->prev;
            it.index->prev->next = newNode;
            it.index->prev = newNode;
            newNode->next = it.index;
            }
        }
    }

    void remove(const SortedList<T>::ConstIterator it){
        if(!it.index){
            return;
        }
        if(it.index == head){
            head = it.index->next;
            if(head != nullptr){
                head->prev = nullptr;
            }
        }else if(it.index->next == nullptr){
            it.index->prev->next = nullptr;
        }else{
            it.index->prev->next = it.index->next;
            it.index->next->prev = it.index->prev;
        }
        delete it.index;
    }

    int length() const{
        int length = 0;
        for(SortedList<T>::ConstIterator it = this->begin(); it != this->end(); ++it, length++){
        }
        return length;
    }

    template <typename Predicate>
    SortedList<T> filter(Predicate predicate) const{
        SortedList<T> list;
        for(SortedList<T>::ConstIterator it = this->begin(); it != this->end(); ++it){
            if(predicate(*it)){
                list.insert(*it);
            }
        }
        return list;
    }

    template <typename Function>
    SortedList<T> apply(Function function) const{
        SortedList<T> list;
        for(SortedList<T>::ConstIterator it = begin(); it != end(); ++it){
            list.insert(function(*it));
        }
        return list;
    }

        /**
         *
         * the class should support the following public interface:
         * if needed, use =defualt / =delete
         *
         * constructors and destructor:
         * 1. SortedList() - creates an empty list.
         * 2. copy constructor
         * 3. operator= - assignment operator
         * 4. ~SortedList() - destructor
         *
         * iterator:
         * 5. class ConstIterator;
         * 6. begin method
         * 7. end method
         *
         * functions:
         * 8. insert - inserts a new element to the list
         * 9. remove - removes an element from the list
         * 10. length - returns the number of elements in the list
         * 11. filter - returns a new list with elements that satisfy a given condition
         * 12. apply - returns a new list with elements that were modified by an operation
         */

    };

    template <class T>
    class SortedList<T>::ConstIterator {
        Node *index;
        ConstIterator(Node *index) : index(index){
        }

        public:

        ~ConstIterator() = default;

        ConstIterator(const ConstIterator& it){
            index = it.index;
        }

        ConstIterator& operator=(const ConstIterator& it){
            index = it.index;
            return *this;
        }

        const T& operator*() const{
            return index->data;
        }

        ConstIterator& operator++(){
            if(index == nullptr){
            throw std::out_of_range("End of List");
            }
            index = index->next;
            return *this;
        }

        bool operator!=(const ConstIterator& it) const{
            return !(index == it.index);
        }
        friend class SortedList;
    /**
     * the class should support the following public interface:
     * if needed, use =defualt / =delete
     *
     * constructors and destructor:
     * 1. a ctor(or ctors) your implementation needs
     * 2. copy constructor
     * 3. operator= - assignment operator
     * 4. ~ConstIterator() - destructor
     *
     * operators:
     * 5. operator* - returns the element the iterator points to
     * 6. operator++ - advances the iterator to the next element
     * 7. operator!= - returns true if the iterator points to a different element
     *
     */
    };
};

