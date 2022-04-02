//
//  hashset.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashset.h"
using std::cout;
using std::cin;
using std::hash;

/* This defines a constructor */
template<class T> hashset<T>::hashset(int size)
{
    maxsize = size;
    if (size < 20)
        maxsize = 20; // default size is 20; no smaller hashtables are considered
    numitems = 0; // initially, the hashtable is empty
    reprarray = new T*[maxsize];  // allocate space for the array of pointers
    // the for loop initialises all table entries to be undefined
    for (int i = 0; i < maxsize; i++)
    {
        reprarray[i] = 0;
    }
    T *pt0 = new T;  // This defines the fixed placeholder pointer
    *pt0 = 0;
    pt_nil = pt0;
}

// template<class T> hashset<T>::~hashset(void)
// {
//     delete[] reprarray;
// }

template<class T> T & hashset<T>::operator[](int index)
{
    if (index <= 0 || index > maxsize)
    {
        cout << "Index error: index out of range\n";
        exit(EXIT_FAILURE);
    }
    if (reprarray[index - 1] != 0 && reprarray[index - 1] != pt_nil)
        return *reprarray[index - 1];
    else
    {
        cout << "Index not used in hashtable";
        return 0;
    }
}

template<class T> void hashset<T>::add(T item)
{
    /* This function needs to be re-implemented by taking the Robin Hood method into account */
    //for the psl, if (the psl of the item which is needed to be added) is larger than (the psl of the item which is in the hash table),
    //we should swap them and try to add the swapped item into the hash table again.
    hash<T> hashfunction;         // use the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    int adder_psl = 0;            //initial pxl for the new item is 0(psl means probe sequence lengths)
    T adder_item = item;
    bool find_placeholder = false;//whether we have found a placeholder or not
    int placeholder_index;
    //TEST: cout << "yep\n";
    while (reprarray[index] != 0) //we stop when we have found a blank space
    {
        T inner_item = *reprarray[index];  //the item in the hash table at position index
        //1. before operation, we must confirm that we do not add a repeated value
        if (inner_item == item)
        {
            return;
        }
        //2. if we firstly find a placeholder for an added item, we remember the position of it and at last we add the item in this position
        if ((reprarray[index] == pt_nil) && (!find_placeholder))
        {
            placeholder_index = index;
            find_placeholder = true;
            index = (index + 1) % maxsize;//next index
            adder_psl++;
            continue;            //we skip this position
        }
        if (find_placeholder)    //if we have found a placeholder, we only need to judge the repeated condition and finally put it at placeholder
        {
            index = (index + 1) % maxsize;//next index
            continue;
        }
        //3. first we caculate the psl of the inner item
        int inner_psl;                    //the pxl of inner item
        if (index >= (hashfunction(inner_item) % maxsize))  //the index is behind the ideal position
        {
            inner_psl = index - (hashfunction(inner_item) % maxsize);
        }else
        {
            inner_psl = maxsize - (index - (hashfunction(inner_item) % maxsize));
        }
        //TEST: cout << inner_item << inner_psl << "\n";
        //TEST: cout << adder_item << adder_psl << "\n";
        //4. second we compare the psl value and do different operations
        if (inner_psl >= adder_psl)       //the inner psl is larger or equal, so we move to the next index
        {
            index = (index + 1) % maxsize;//next index
            adder_psl++;                  //we move the added item far from the ideal position, so we increment adder_pxl
        }else                             //the inner psl is smaller, so we swap the inner item and the added item;
        {
            T temp_item = inner_item;
            int temp_psl = inner_psl;
            reprarray[index] = new T;
            *reprarray[index] = adder_item;//put the added item into the hash table
            adder_item = temp_item;
            adder_psl = temp_psl;
            index = (index + 1) % maxsize;//next index
            adder_psl++;                  //move away
            find_placeholder = false;     //we should renew the placeholder because the added item is renewed
        }
    }
    //5. we have found a blank space and try to put the added value into the hash table
    if (find_placeholder)                 //we have found a placeholder, so we put the added item at this position
    {
        reprarray[placeholder_index] = new T;
        *reprarray[placeholder_index] = adder_item;
    }else{                                //we have not found a placeholder, so we put the added item at the blank space
        reprarray[index] = new T;
        *reprarray[index] = adder_item;
    }
    numitems++;
    //6. check whether we need to rehash or not
    int load = 100 * numitems / maxsize;
    //TEST: cout << load << "\n";
    if (load >= 75)
    {
        int newsize = maxsize * 2;   //double the size of the previous one
        if (newsize < 20)
        {
            newsize = 20;
        }
        rehash(newsize);
    }
    return;
    //TEST: this is the add function for normal linear probing
    /*hash<T> hashfunction;
    int index = hashfunction(item) % maxsize;
    //reprarray = new T*[maxsize];
    while (reprarray[index] != 0)
    {
        index = (index + 1) % maxsize;
    }
    reprarray[index] = new T;
    *reprarray[index] = item;
    numitems++;
    return;*/
    
    /*NOTE: some seemingly strange outcome(size 20)
    if we add 1,2,3,23,43 successively, outcome: 1 at entry 2 (1->2), 2->3, 3->4, 23->5, 43->6
    then we delete 3 (entry 4), outcome: 1->2, "2->3, 23->4, 43->5"
    why entry 4 is filled with 23? the entry 4 should have been free!
    the reason is that the hash table is rehashed, since the number of items(4) is so small*/
}

template<class T> void hashset<T>::remove(T item)
{
    hash<T> hashfunction;  // use again the predefined hashfunction
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0)  // same as for add we search for item in the hashtable; the search starts at the designated hash value, and stops when we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
                    // item found
        {
            int nextindex = (index + 1) % maxsize;
            /* check the next entry, if it is a null pointer; if yes, we can overwrite item by a null pointer; otherwise we use a placeholder, i.e. the pointer pt_nil */
            if (reprarray[nextindex] == 0)
                reprarray[index] = 0;
            else
                reprarray[index] = pt_nil;
            --numitems;
            int load = 100 * numitems / maxsize;
            if (load <= 25)
                // if the min load factor is undershot, we shrink the hashtable, but the size shall always be >= 20
            {
                int newsize = numitems;
                if (newsize < 20)
                    newsize = 20;
                rehash(newsize);
            }
            return;
        }
        index = (index + 1) % maxsize;
    }
    cout << item << " is not in the hashtable.\n";
    return;
}

template<class T> bool hashset<T>::member(T item)
{
    hash<T> hashfunction;  // use the "key" function for the type T (if defined)
    int index;
    index = hashfunction(item) % maxsize;
    while (reprarray[index] != 0) // again we search for item starting from the index position until we find a null pointer
    {
        if (reprarray[index] != pt_nil && *reprarray[index] == item)
            return true;  // item was found
        index = (index + 1) % maxsize;
    }
    return false;  // a null pointer was found, so item is not in the hashtable
}

template<class T> void hashset<T>::rehash(int newsize)
{
    if (newsize < 20)
        newsize = 20;
    int newnum = 0;
    T **newarray = new T*[newsize];   // allocate space for a new hashtable of the given new size
    for (int i = 0; i < newsize; i++)
    {
        newarray[i] = 0;   // initialise the new hashtable with only null pointers
    }
    for (int i = 0; i < maxsize; i++)  // we need to copy all existing entries to the new hash table
    {
        if (reprarray[i] != 0 && reprarray[i] != pt_nil)
        {
            T item = *reprarray[i];
            hash<T> hashfunction;
            int index = hashfunction(item) % newsize;
                // recompute the new hash value
            while (newarray[index] != 0)  // find the first free place, where the entry can be stored in the new hashtable
            {
                index = (index + 1) % newsize;
            }
            newarray[index] = reprarray[i];  // do the actual copying
            ++ newnum;
        }
    }
    numitems = newnum;   // change the number of stored elements
    reprarray = newarray;   // make the new hashtable the one of the hashset object
    maxsize = newsize;   // update the size
}

template<class T> void hashset<T>::display(void) // only for test purposes
{
    cout << "The size of the hashtable is: " << maxsize << "\n";
    cout << "The number of elements in the hashtable is: " << numitems << "\n";
    for (int i = 0; i < maxsize; ++i)
    {
        if (reprarray[i] == 0)
            cout << "The entry " << i + 1 << " is undefined.\n";
        else if (reprarray[i] == pt_nil)
            cout << "The entry " << i + 1 << " is free.\n";
        else
            cout << "The entry " << i + 1 << " is " << *reprarray[i] << " .\n";
    }
    return;
}
