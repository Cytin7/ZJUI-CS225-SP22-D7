//
//  hashmap.h
//  
//
//  Created by KD on 6.03.21.
//  Modified on 22.03.22
//

#ifndef hashmap_h
#define hashmap_h

template<class K, class T> class hashmap
{
public:
    hashmap(int size = 5);
    T &operator[](int index);
// The operation add inserts
// an element into the hashmap,
// remove deletes an
// element and member checks,
// if the element is in the hashmap
    void add(K key, T item);
    void remove(K key);
    T retrieve(K key);
    bool member(K key, T item);
// The function display is only used
// for testing purposes.
// It shows the size of
// the hashmap, the number of elements,
// and displays all entries
    void display(void);
public:
    int numitems;
private:
    // contains the number of elements in the hashmap
    K **keyarray;
    T *reprarray;
/* keyarray defines a pointer to (an array of)
 * pointers to key values of type K.
 * reprarray defines an array of
 * corresponding values of type T.
 * We will use a null pointer,
 * if an entry is undefined,
 * and a fixed pointer as placeholder
 * for free entries (after remove) */
    K *pt_nil;
    // used as placeholder
    int maxsize;
    // defines the size of the hashmap
    void rehash(int newsize);
// rehash is an internal function
// to enlarge or shrink the hashtable,
// if the fill factors 0.75 or 0.25
// are exceeded or undershot, resp.
};

#include <stdio.h>
#include <iostream>
#include <cstdlib>
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class K, class T> hashmap<K,T>::hashmap(int size)
{
    maxsize = size;
    if (size < 5)
        maxsize = 5; // default size is 20; no smaller hashmaps are considered
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
    if (member(key,item)){
        cout << "Add error: the element has already in the map." << std::endl;
        return;
    }else{
        // First to define index.
        hash <K> hashfunction;
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
            K* key1 = new K;
            *key1 = key;
            keyarray[index] = key1;
            reprarray[index] = item;
            this->numitems++;
        }
        // considering the fill factor will be too large.
        // so we should set a way to rehash.
        if (numitems >= 0.75 * maxsize) {
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
        cout << "Remove error: There is no such a key.\n";
        return;
    }else{
        this->keyarray[index] = pt_nil;
        float fill_factor = numitems/maxsize;
        if (fill_factor <= 0.25){
            rehash(maxsize/2);
            return;
        }else{
            return;
        }
    }
    // as the logic to check the element is:
    // keyarray[index-1] != pt_nil,
    // so just let the keyarray[index-1] = pt_nil.
}

template<class K, class T> T hashmap<K,T>::retrieve(K key)
{
    // as a hash function,
    // we should firstly define the index
    // using the hash function.
    hash<K> hashfunction;
    int index = hashfunction(key) % this->maxsize;
    // but we should check if the index stores
    // truly the key we put in.
    // the standard is that we fetch the key value,
    // if not same, then find the "next" position
    if (numitems == 0){
        cout << "there is no such a value in this hashmap.\n";
        exit(0);
    }
    int times = 0;
    if (keyarray[index] == nullptr){
        return nullptr;
    }
    while (*keyarray[index] != key && times < maxsize){
        index = (index + 1) % this->maxsize;
        // linear probing method in hashing.
        times ++;
        if (keyarray[index] == nullptr){
            break;
        }
    }
    if (keyarray[index] == nullptr){
        return nullptr;
    }
    // ACTUALLY as we cannot define
    // that if there is truly a key the same as input
    // so, we define a method to check if we loop through every entry.
    if (times == maxsize && *keyarray[index] != key){
        cout << "there is no such a value in this hashmap.\n";
        return NULL;
    }else{
        return reprarray[index];
    }
}

template<class K, class T> bool hashmap<K,T>::member(K key, T item)
{
    // as a hash function,
    // we should firstly define the index
    // using the hash function.
    hash<K> hashfunction;
    int index = hashfunction(key) % this->maxsize;
    // but we should check if the index stores
    // truly the key we put in.
    // the standard is that we fetch the key value,
    // if not same, then find the "next" position
    if (numitems == 0){ return false; }
    int times = 0;
    if (keyarray[index] == nullptr){
        return false;
    }
    while (*keyarray[index] != key && times < maxsize){
        index = (index + 1) % this->maxsize;
        if (keyarray[index] == nullptr){
            return false;
        }
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
            hash<K> hashfunction;
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
    return;
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
        else{
            cout << "The entry " << i + 1 << " has the key " << *keyarray[i] << " and the value " << reprarray[i]<< " .\n";
        }
    }
    return;
}
#endif /* hashmap_h */
