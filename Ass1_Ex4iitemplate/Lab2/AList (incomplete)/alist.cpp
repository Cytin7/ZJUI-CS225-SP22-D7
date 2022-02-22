//
//  alist.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 22.01.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "alist.h"
#include "time.h"
using std::cout;
using std::cin;

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
    /* to be done */
    if (index > numitems){
        cout<<"Wrong index."<<endl;
        return;
    }
    else if (index == numitems+1){
        append(value);
    }
    else{
        if (numitems == maxsize)
            allocate();
        for (int i = numitems + 1;i > index; i--){
            setitem(i,getitem(i-1));
        }
        setitem(index,value);
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
    /* to be done */
}

template<class T> void AList<T>::deallocate(void)
{
    /* to be done */
}

template<class T> void AList<T>::concat(AList<T> &list)
{
    /* to be done */
}

template<class T> bool AList<T>::member(T value)
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

template<class T> bool AList<T>::equal(AList<T> &list)
{
    /* to be done */
    for (int i = 0; i < list -> numitems; i++){
        if (reprarray)
    }
}

template<class T> bool AList<T>::sublist(AList<T> &list)
{
    /* to be done */
}
