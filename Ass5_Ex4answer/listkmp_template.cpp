//
//  listkmp.cpp
//
//
//  Created by KD on 14.01.21.
//  Modified by KD on 12.03.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listkmp.h"
using std::cin;
using std::cout;

template <class T>
KMPlist<T>::KMPlist(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
    nextlist = 0;
}

/* Most of the member functions are the same as for AList */

template <class T>
T &KMPlist<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template <class T>
int KMPlist<T>::getlength(void)
{
    return numitems;
}

template <class T>
void KMPlist<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

template <class T>
T KMPlist<T>::getitem(int index)
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

template <class T>
void KMPlist<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template <class T>
void KMPlist<T>::insert(int index, T value)
{
    if (numitems == maxsize)
        allocate();
    if (index < numitems)
    {
        for (int j = numitems - 1; j >= index; --j)
        {
            reprarray[j + 1] = reprarray[j];
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

template <class T>
void KMPlist<T>::allocate(void)
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

template <class T>
void KMPlist<T>::remove(int index)
{
    if ((numitems == maxsize / 4) && (maxsize > minsize))
        deallocate();
    if (index <= numitems)
    {
        for (int j = index; j < numitems; ++j)
        {
            reprarray[j - 1] = reprarray[j];
        }
        --numitems;
        return;
    }
    else
        cout << "Index error: list index out of range\n";
}

template <class T>
void KMPlist<T>::deallocate(void)
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

template <class T>
void KMPlist<T>::concat(KMPlist<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template <class T>
bool KMPlist<T>::member(T value)
{
    bool result = false;
    for (int i = 0; i < numitems; ++i)
    {
        if (reprarray[i] == value)
        {
            result = true;
            break;
        }
    }
    return result;
}

template <class T>
bool KMPlist<T>::equal(KMPlist<T> &list)
{
    bool result = true;
    if (numitems == list.getlength())
    {
        for (int i = 0; i < numitems; ++i)
        {
            if (reprarray[i] == list[i + 1])
                continue;
            else
            {
                result = false;
                break;
            }
        }
    }
    else
        result = false;
    return result;
}

template <class T>
bool KMPlist<T>::sublist(KMPlist<T> &list)
{
    int length = list.getlength();
    bool result = true;
    for (int i = 1, j = 0; (i <= length) && (j < numitems); ++i, ++j)
    {
        if (list[i] == reprarray[j])
        {
            if ((j == numitems - 1) && (i < length))
            {
                result = false;
                break;
            }
        }
        else if (j == numitems - 1)
        {
            result = false;
            break;
        }
        else
            --i;
    }
    return result;
}

template <class T>
void KMPlist<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i + 1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* the added member functions create_next and kmp need to be implemented */

template <class T>
void KMPlist<T>::create_next(int *next)
{
    /* This member function needs to be implemented. It pre-computes the NEXT values used in the KMP algorithm */
    //Initially, we have the prefix of Plist and the suffix of Plist. Prefix is equal to suffix. The length of 
    //such prefix or suffix plus 1 is the next value.
    next[1] = 0;  //initialization
    next[2] = 1;
    int i = 2;
    int j = 1;
    while (i < numitems)
    {
        if (j == 0 || reprarray[i - 1] == reprarray[j - 1])
        {//if the char at position i is equal to the char at position j
            i++;
            j++;
            if (reprarray[i - 1] != reprarray[j - 1])
            {
                next[i] = j;//the next value at position i+1 is the length of prefix or suffix plus 1
            }
            else//Plist[j]=Plist[NEXT[j]], in this situation, Plist[NEXT[j]] cannot be euqal to Slist[i] since Plist[j] != Slist[i]
            {   //so we recurse one more time, NEXT[j]=NEXT[NEXT[j]], in another word, NEXT[i]=NEXT[j]
                next[i] = next[j];
            }
        }
        else
        {//if the char at position i is not equal to the char at position j, we need to relocate j
            j = next[j];
        }
    }
    //TEST CODE: print NEXT for test
    //for (int x = 0; x < numitems; x++)
    //{
    //    cout << next[x + 1] << "\n";
    //}
}

template <class T>
int KMPlist<T>::kmp(KMPlist<T> *target)
{
    /* This member function needs to be implemented. It implements the KMP algorithm with this list as pattern list and an arbitrary target list given as input */
    int *next = new int[numitems];
    create_next(next);
    int i = 1;
    int j = 1;
    while (i <= target->numitems && j <= numitems)
    {
        if (j == 0 || target->reprarray[i - 1] == reprarray[j - 1])//the corresponding characters are the same, so we test subsequent positions.
        {
            i++;
            j++;
        }
        else//the corresponding characters are different, so we utilize NEXT array to align
        {
            j = next[j];
        }
    }
    if (j > numitems)//if TRUE, it means we have matched every char in Plist, so we successfully find a matching.
    {
        return i - numitems;
    }
    return -1;//not match
}
