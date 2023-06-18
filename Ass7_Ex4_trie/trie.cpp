//
//  trie.cpp
//  
//
//  Created by KD on 20.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.h"
using std::cout;
using std::cin;

template<class T> AList<T>::AList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &AList<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int AList<T>::getlength(void)
{
    return numitems;
}

template<class T> void AList<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template<class T> T AList<T>::getitem(int index)
{
    if ((index > 0) && (index <= numitems))
    {
        return reprarray[index - 1];
    }
    else
    {
        cout << "Index error: index out or range\n";
        exit(EXIT_FAILURE);
    }
}

template<class T> void AList<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void AList<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j+1] = reprarray[j];
        }
        reprarray[index] = value;
        ++numitems;
        return;
    }
    else
    {
        append(value);
        return;
    }
}

template<class T> void AList<T>::allocate(void)
{
    int newsize = 2 * maxsize;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

template<class T> void AList<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j-1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template<class T> void AList<T>::deallocate(void)
{
    int newsize = maxsize / 2;
    T *newarray = new T[newsize];
    for (int i = 0; i < numitems; ++i)
    {
        newarray[i] = reprarray[i];
    }
    delete[] reprarray;
    reprarray = newarray;
    maxsize = newsize;
    return;
}

/* the constructor creates a node with the given value and next and follow pointers */
template<class T> trienode<T>::trienode(T item, bool l, trienode<T> *pt_next, trienode<T> *pt_follow)
{
    data = item;
    last = l;
    next = pt_next;
    follow = pt_follow;
}

/* the get operations */
template<class T> T trienode<T>::getdata(void)
{
    return data;
}

template<class T> bool trienode<T>::getlast(void)
{
    return last;
}

template<class T> trienode<T> *trienode<T>::getnext(void)
{
    return next;
}

template<class T> trienode<T> *trienode<T>::getfollow(void)
{
    return follow;
}

/* the set operations */
template<class T> void trienode<T>::setdata(T item)
{
    data = item;
    return;
}

template<class T> void trienode<T>::setlast(bool l)
{
    last = l;
    return;
}

template<class T> void trienode<T>::setnext(trienode<T> *pt_next)
{
    next = pt_next;
    return;
}

template<class T> void trienode<T>::setfollow(trienode<T> *pt_follow)
{
    follow = pt_follow;
    return;
}

/* the constructor creates an empty trie containing just a null pointer at the start */
template<class T> trie<T>::trie(void)
{
    start = 0;
}

/* the insert and intrie functions are realised recursively starting from the start using the corresponding auxiliary functions */
template<class T> void trie<T>::insert(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    start = _insert(start, newlist);
    return;
}

template<class T> bool trie<T>::intrie(AList<T> list)
{
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++)
    {
        newlist.append(list[i]);
    }
    return contains(start, newlist);
}
/* auxiliary function for insertion */
template<class T> trienode<T> *trie<T>::_insert(trienode<T> *pt, AList<T> list)
{
    if (list.getlength() == 0)
        return 0;
    T key = list[1];  // take the first element of the new list
    if (pt == 0)  // case of null pointer: create a new trienode
    {
        list.remove(1);
        trienode<T> *newnode = new trienode<T>;
        (*newnode).setdata(key);  // set the value of the new trienode
        /* mark the trienode as final, if the inout list is used up */
        if (list.getlength() == 0)
            (*newnode).setlast(true);
        /* recursively proceed with the next element of the input list */
        (*newnode).setfollow(_insert((*newnode).getfollow(), list));
        return newnode;
    }
    if ((*pt).getdata() == key) // case of a prefix already in the trie
    {
        list.remove(1);
        if (list.getlength() == 0)
        {
            (*pt).setlast(true);
            return pt;
        }
        /* just skip over the prefix */
        (*pt).setfollow(_insert((*pt).getfollow(), list));
    }
    else
        /* otherwise follow the next pointer */
        (*pt).setnext(_insert((*pt).getnext(), list));
    return pt;
}

// Implemented By Hong Jiadong on April 14th 2022
template<class T> bool trie<T>::contains(trienode<T> *pt, AList<T> list)
{
    // consider the case that only the pt is not NULL,
    // then the search is reasonable.
    if (pt == 0){
        return false;
    }else{
        // successfully search.
        if (list[1] == pt->getdata()){
            list.remove(1);
            // the first element is correct,
            // so we should check
            // the search is end or not. <==> getlength() == 0.
            if (list.getlength() == 0){
                if (pt->last == true){
                    return true;
                }else{
                    return false;
                }
            }else{
                pt = pt->follow;
                return contains(pt,list);
            }
        }else{
            // node value != list[1].
            // to search through the linked list.
            pt = pt->next;
            return contains(pt,list);
        }
    }
}

template<class T> void trie<T>::display(void)
{
    AList<T> list;
    _display(start, list);
    cout << "\n";
}

template<class T> void trie<T>::_display(trienode<T> * pt, AList<T> list)
{
    if (pt != 0)
    {
        list.append((*pt).getdata());
        if ((*pt).getlast() == true)
        {
            cout << "Trie entry: ";
            for (int i = 1; i <= list.getlength(); i++)
            {
                cout << list[i];
                if (i != list.getlength())
                    cout << " , ";
                else
                    cout << "\n";
            }
            if ((*pt).getfollow() != 0)
                _display((*pt).getfollow(),list);
        }
        else
            _display((*pt).getfollow(), list);
        list.remove(list.getlength());
        if ((*pt).getnext() != 0)
            _display((*pt).getnext(), list);
    }
    return;
}

template<class T> void trie<T>::correct1(AList<T> list)
{
    // first deep copy the list.
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++){
        newlist.append(list[i]);
    }
    /*
     * This function needs to be implemented.
     * It should try to find the input word in the TRIE.
     * If unsuccessful,
     * it should output words from the dictionary
     * that extend the given word
     * (not found in the dictionary) by one symbol.
     */
    bool Figure = false;
    trienode<T>* pt = start;
    while (pt != 0){
        // successfully search.
        if (newlist[1] == pt->getdata()){
            newlist.remove(1);
            // the first element is correct,
            // so we should check
            // the search is end or not. <==> getlength() == 0.
            if (newlist.getlength() == 0){
                if (pt->last == true){
                    Figure = true;
                    break;
                }else{
                    break;
                }
            }else{
                pt = pt->follow;
                continue;
            }
        }else{
            // node value != list[1].
            // to search through the linked list.
            pt = pt->next;
            continue;
        }
    }
    if (Figure == true){
        cout << "\nExecuting the the testing program correct1.....\n"
             << "The input list can be found in the Tire Tree." <<std::endl;
        return;
    }else if (newlist.getlength() == 0){
        cout << "\nExecuting the the testing program correct1.....\n";
        AList<T> newlist_0;
        bool isTrue = false;
        for (int i = 1; i <= list.getlength(); i++){
            newlist_0.append(list[i]);
        }
        pt = start;
        while (newlist_0.getlength() != 0) {
            if (newlist_0[1] == pt->getdata()) {
                newlist_0.remove(1);
                pt = pt->follow;
                continue;
            } else {
                pt = pt->next;
                continue;
            }
        }
        do {
            if (pt->last == true){
                pt = pt->next;
                isTrue = true;
                break;
            }else{
                pt = pt->next;
                continue;
            }
        } while( pt->next != 0 );
        // set isTrue data to determine the list fits the condition or not.
        if (isTrue){
            AList<T> newlist_1;
            for (int i = 1; i <= list.getlength(); i++){
                newlist_1.append(list[i]);
            }
            // output program.
            cout << "Successfully executed! Here are the words....." <<std::endl;
            pt = start;
            while (newlist_1.getlength() != 0) {
                if (newlist_1[1] == pt->getdata()) {
                    cout << newlist_1[1];
                    newlist_1.remove(1);
                    pt = pt->follow;
                    continue;
                } else {
                    pt = pt->next;
                    continue;
                }
            }
            // print out te other left node's value.
            cout << pt->getdata();
            while (pt->next != 0){
                pt = pt->next;
                if (pt->last == true)
                    cout << "/" << pt->getdata();
            }
            cout << ".\n";
            // output example: final/s/d/f/q.\n
        }else{
            cout << "The list is not satisfying the condition that program use..... \n";
        }
    }else{
        cout << "\nExecuting the the testing program correct1.....\n";
        cout << "The list is not satisfying the condition that program use..... \n";
        return;
    }
}

template<class T> void trie<T>::correct2(AList<T> list)
{
    // first deep copy the list.
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++){
        newlist.append(list[i]);
    }
    /* This function needs to be implemented.
     * It should try to find the input word in the TRIE.
     * If unsuccessful,
     * it should output words from the dictionary
     * that are prefixes of the given word (not found in the dictionary)
     * with one or two symbols less. */
    bool Figure = false;
    trienode<T>* pt = start;
    while (pt != 0){
        // successfully search.
        if (newlist[1] == pt->getdata()){
            newlist.remove(1);
            // the first element is correct,
            // so we should check
            // the search is end or not. <==> getlength() == 0.
            if (newlist.getlength() == 0){
                if (pt->last == true){
                    Figure = true;
                    break;
                }else{
                    break;
                }
            }else{
                pt = pt->follow;
                continue;
            }
        }else{
            // node value != list[1].
            // to search through the linked list.
            pt = pt->next;
            continue;
        }
    }
    if ( Figure == true ){
        cout << "\nExecuting the the testing program correct2.....\n"
             << "The input list can be found in the Tire Tree." <<std::endl;
        return;
    }else if (newlist.getlength() == 1 || newlist.getlength() == 2){
        cout << "\nExecuting the the testing program correct2.....\n";
        AList<T> newlist_0;
        bool isTrue = false;
        for (int i = 1; i <= list.getlength(); i++){
            newlist_0.append(list[i]);
        }
        pt = start;
        int length = newlist.getlength();
        // to test the input list satisfying the condition or not.
        while (newlist_0.getlength() != length) {
            if (newlist_0[1] == pt->getdata()) {
                newlist_0.remove(1);
                if (newlist_0.getlength() != length){
                    pt = pt->follow;
                    continue;
                }else{
                    if (pt->last == true){
                        isTrue = true;
                    }else{
                        isTrue = false;
                    }
                    continue;
                }
            }else{
                pt = pt->next;
                continue;
            }
        }
        if (isTrue){
            AList<T> newlist_1;
            for (int i = 1; i <= list.getlength(); i++){
                newlist_1.append(list[i]);
            }
            // output program.
            cout << "Successfully executed! Here are the words....." <<std::endl;
            pt = start;
            while (newlist_1.getlength() != length) {
                if (newlist_1[1] == pt->getdata()) {
                    cout << newlist_1[1];
                    newlist_1.remove(1);
                    pt = pt->follow;
                    continue;
                } else {
                    pt = pt->next;
                    continue;
                }
            }
            cout << "." << std::endl;
        }else{
            cout << "The list is not satisfying the condition that program use..... \n";
        }
        return;
    }else{
        cout << "\nExecuting the the testing program correct2.....\n";
        cout << "The list is not satisfying the condition that program use..... \n";
        return;
    }
}

template<class T> void trie<T>::correct3(AList<T> list)
{
    /* This function needs to be implemented.
     * It should try to find the input word in the TRIE.
     * If unsuccessful,
     * it should output words from the dictionary
     * that differ from the given word (not found in the dictionary)
     * by exactly one symbol. */
    // first deep copy the list.
    AList<T> newlist;
    for (int i = 1; i <= list.getlength(); i++){
        newlist.append(list[i]);
    }
    if ( contains(start, newlist) == true ){
        cout << "\nExecuting the the testing program correct3.....\n"
             << "The input list can be found in the Tire Tree." <<std::endl;
        return;
    }else{
        cout << "\nExecuting the the testing program correct3.....\n";
        // we use a detecting number method.
        // if the detector detected two differences...
        // execute false
        AList<T> tmp;
        AList<T>* newlist_1 = &tmp;
        // used for out put.
        int detector = 0;
        bool isTrue = this->trie<T>::_connect3(start,list,detector,newlist_1);
        if (isTrue){
            cout << "Detecting Successfully! Here are the words:\n";
            for (int i = 1; i <= newlist_1->getlength(); i++){
                cout << newlist_1->getitem(i);
            }
            cout << ".\n";
        }else{
            cout << "The list is not satisfying the condition that program use..... \n";
        }
        return;
    }
}

template<class T> bool trie<T>::_connect3(trienode<T>* node, AList<T> list, int detector, AList<T>* list_1){
    if (detector <= 1 && list.getlength() > 0){
        trienode<T>* pt = node;
        cout << "executing the node with char " << node->data << " and the current comparing node is "
             << list[1] << "." << std::endl;
        if (pt->data == list[1]){
            T temp = list.getitem(1);
            // append into the queue.
            list_1->append(pt->data);
            list.remove(1);
            // 1. list == none but Tries longer one element.
            // 2. Tries == none but list longer one element.
            if (detector == 0){
                if ((list.getlength() == 0 && pt->follow->last == true)
                    || (list.getlength() == 1 && pt->last == true )){
                    if (list.getlength() == 0 && pt->follow->last == true){
                        list_1->append(pt->follow->data);
                    }
                    return true;
                }
                // considering the case
                // that the sibling of one of the pt->follow node can be last.
                if (list.getlength() == 0 && pt->follow->last == false ){
                    trienode<T>* ptr = pt->follow;
                    while (ptr->next != 0){
                        if (ptr->last == true){
                            list_1->append(pt->data);
                            return true;
                        }
                        ptr = ptr->next;
                    }
                    // delete the element in the queue.
                    list.insert(0,temp);
                    list_1->remove(list_1->getlength());
                    return false;
                }
            }else if(list.getlength() == 0 && detector != 0){
                // detecting that abcd->abdd.
                if (list.getlength() == 0 && pt->last == true){
                    return true;
                }else{
                    // delete the element in the queue.
                    list.insert(0,temp);
                    list_1->remove(list_1->getlength());
                    return false;
                }
            }
            if (pt->follow != 0){
                pt = pt->follow;
                if ( _connect3(pt,list,detector,list_1) == false){
                    if (pt->next != 0){
                        if (_connect3(pt->next, list, detector, list_1)== false){
                            // delete the element in the queue.
                            list.insert(0,temp);
                            list_1->remove(list_1->getlength());
                            return false;
                        }else{
                            return true;
                        }
                    }else{
                        // delete the element in the queue.
                        list.insert(0,temp);
                        list_1->remove(list_1->getlength());
                        return false;
                    }
                }else{
                    return true;
                }
            }else{
                // delete the element in the queue.
                list.insert(0,temp);
                list_1->remove(list_1->getlength());
                return false;
            }
        }else{
            // Here is the failure to fit in the character.
            detector++;
            T temp = list.getitem(1);
            list_1->append(pt->data);
            list.remove(1);
            if (detector > 1){
                // delete the element in the queue.
                list.insert(0,temp);
                list_1->remove(list_1->getlength());
                if (pt->next != 0)
                    return _connect3(pt->next,list,detector-1,list_1);
                else
                    return false;
            }else{
                if (list.getlength() == 0){
                    if (pt->last == true){
                        return true;
                    }else{
                        // considering that we should search
                        // until finding there is a word that has a "last marked."
                        // or we should return false.
                        if (pt->next != 0){
                            list.append(temp);
                            list_1->remove(list_1->getlength());
                            if (_connect3(pt->next, list, detector - 1, list_1) == false){
                                // delete the element in the queue.
                                list.insert(0,temp);
                                list_1->remove(list_1->getlength());
                                return false;
                            }else{
                                return true;
                            }
                        }else{
                            // delete the element in the queue.
                            list.insert(0,temp);
                            list_1->remove(list_1->getlength());
                            return false;
                        }
                    }
                }else{
                    if (pt->follow != 0){
                        if (_connect3(pt->follow, list, detector, list_1) == false){
                            if (pt->next != 0){
                                list.insert(0,temp);
                                list_1->remove(list_1->getlength());
                                if (_connect3(pt->next, list, detector - 1, list_1) == false){
                                    // delete the element in the queue.
                                    list.insert(0,temp);
                                    list_1->remove(list_1->getlength());
                                    return false;
                                }else{
                                    return true;
                                }
                            }else{
                                // come back until to the last absolutely right node.
                                // and we can figure out that will move on to the next sub tree.
                                // delete the element in the queue.
                                list.insert(0,temp);
                                list_1->remove(list_1->getlength());
                                return false;
                            }
                        }else{
                            return true;
                        }
                    }else{
                        // here, pt is leaf node...
                        // only when the list.getlength is 0, the condition can return true.
                        // delete the element in the queue.
                        list.insert(0,temp);
                        list_1->remove(list_1->getlength());
                        return false;
                    }
                }
            }
        }
    }
}
