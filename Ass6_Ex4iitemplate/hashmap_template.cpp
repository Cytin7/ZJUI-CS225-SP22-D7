//
//  hashmap.cpp
//  
//
//  Created by KD on 6.03.21.
//  Modified on 22.03.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.h"
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class K, class T> hashmap<K,T>::hashmap(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashmaps are considered
    numitems = 0; // initially, the hashmap is empty
    keyarray = new K*[maxsize];  // allocate space for the array of pointers
    reprarray = new T[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        keyarray[i] = 0;
    }
    K *pt0 = new K;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

template<class K, class T> T & hashmap<K,T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    // H. J.: I consider that pt_nil is a place holder for deletion.
    if (keyarray[index - 1] != 0 && keyarray[index - 1] != pt_nil)
        return reprarray[index - 1];
        // so we can figure out
        // that reprarray stores the value.
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class K, class T> void hashmap<K,T>::add(K key, T item)
{
    cout<<"executing add function, detecting the key...\n";
    if (member(key,item)){
        cout << "Add error: the element has already in the map." << std::endl;
        return;
    }else{
        if(numitems > 0){
            T value = retrieve(key);
            if(retrieve(key) != item){
                cout << "Add error: this key has a different value in the hashmap.\n";
                return;
            }
        }
        // First to define index.
        hash <T> hashfunction;
        int index = hashfunction(key) % this->maxsize;
        // Then to define a definitely correct condition.
        // if the entry is empty
        // or the element in the entry has been deleted.
        if (keyarray[index] == 0 || keyarray[index] == pt_nil) {
            // set a pointer to keyarray
            K* key1 = new K;
            *key1 = key;
            keyarray[index] = key1;
            reprarray[index] = item;
            this->numitems++;
        } else {
            while (keyarray[index] != 0 && keyarray[index] != pt_nil) {
                index = (index + 1) % this->maxsize;
                // linear probing method in hashing.
            }
            keyarray[index] = &key;
            reprarray[index] = item;
            this->numitems++;
        }
        // considering the fill factor will be too large.
        // so we should set a way to rehash.
        float fill_factor = numitems / maxsize;
        if (fill_factor >= 0.75) {
            rehash(maxsize * 2);
            return;
        } else {
            return;
        }
    }
}

template<class K, class T> void hashmap<K,T>::remove(K key)
{
    // as a hash function,
    // we should firstly define the index
    // using the hash function.
    hash<T> hashfunction;
    int index = hashfunction(key) % this->maxsize;
    // but we should check if the index stores
    // truly the key we put in.
    // the standard is that we fetch the key value,
    // if not same, then find the "next" position
    while (*keyarray[index] != key){
        index = (index + 1) % this->maxsize;
        // linear probing method in hashing.
    }
    // as the logic to check the element is:
    // keyarray[index-1] != pt_nil,
    // so just let the keyarray[index-1] = pt_nil.
    this->keyarray[index] = pt_nil;
    float fill_factor = numitems/maxsize;
    if (fill_factor <= 0.25){
        rehash(maxsize/2);
        return;
    }else{
        return;
    }
}

template<class K, class T> T hashmap<K,T>::retrieve(K key)
{
    // as a hash function,
    // we should firstly define the index
    // using the hash function.
    hash<T> hashfunction;
    int index = hashfunction(key) % this->maxsize;
    // but we should check if the index stores
    // truly the key we put in.
    // the standard is that we fetch the key value,
    // if not same, then find the "next" position
    int times = 0;
    while (*keyarray[index] != key && times < maxsize){
        index = (index + 1) % this->maxsize;
        // linear probing method in hashing.
        times ++;
    }
    // ACTUALLY as we cannot define
    // that if there is truly a key the same as input
    // so, we define a method to check if we loop through every entry.
    if (times == maxsize && *keyarray[index] != key){
        cout << "there is no such a value in this hashmap.\n";
        exit(0);
    }else{
        return reprarray[index];
    }
}

template<class K, class T> bool hashmap<K,T>::member(K key, T item)
{
    // as a hash function,
    // we should firstly define the index
    // using the hash function.
    hash<T> hashfunction;
    int index = hashfunction(key) % this->maxsize;
    // but we should check if the index stores
    // truly the key we put in.
    // the standard is that we fetch the key value,
    // if not same, then find the "next" position
    if (numitems == 0){ return false; }
    int times = 0;
    while (*keyarray[index] != key && times < maxsize){
        index = (index + 1) % this->maxsize;
        // linear probing method in hashing.
        times ++;
    }
    // ACTUALLY as we cannot define
    // that if there is truly a key the same as input
    // so, we define a method to check if we loop through every entry.
    if (times == maxsize && *keyarray[index] != key){
        return false;
    }else{
        if (reprarray[index] == item){
            return true;
        }else{
            return false;
        }
    }
}

template<class K, class T> void hashmap<K,T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    K **newkeyarray = new K*[newsize];
    T *newarray = new T[newsize];
    // allocate space for a new hashmap of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newkeyarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (keyarray[i] != 0 && keyarray[i] != pt_nil)
        {
            K item = *keyarray[i];
            T value = reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
            // recompute the new hash value
            while (newkeyarray[index] != 0)
                // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newkeyarray[index] = keyarray[i];  // do the actual copying
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    keyarray = newkeyarray;   // make the new hashmap
    reprarray = newarray;
    maxsize = newsize;   // update the size
}

template<class K, class T> void hashmap<K,T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (keyarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (keyarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " has the key " << *keyarray[i] << " and the value " << reprarray[i]<< " .\n";
    }
    return;
}
