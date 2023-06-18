//
//  listext.cpp
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 02.03.22.
//

#include   <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listext.h"
using std::cout;
using std::cin;

template<class T> Listext<T>::Listext(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

template<class T> T &Listext<T>::operator[](int index)
{
    return reprarray[index - 1];
}

//The index of this method is from 1 to numitems
template<class T> int Listext<T>::getlength(void)
{
    return numitems;
}

//The index of this method is from 1 to numitems
template<class T> void Listext<T>::setitem(int index, T value)
{
    if ((index > 0) && (index <= numitems))
    {
        reprarray[index - 1] = value;
        return;
    }
    else
        cout << "Index error: index out or range\n";
}

//The index of this method is from 1 to numitems
template<class T> T Listext<T>::getitem(int index)
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

template<class T> void Listext<T>::append(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> void Listext<T>::insert(int index, T value)
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

template<class T> void Listext<T>::allocate(void)
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

template<class T> void Listext<T>::remove(int index)
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

template<class T> void Listext<T>::deallocate(void)
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

template<class T> void Listext<T>::concat(Listext<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
}

template<class T> bool Listext<T>::member(T value)
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

template<class T> bool Listext<T>::equal(Listext<T> &list)
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

template<class T> bool Listext<T>::sublist(Listext<T> &list)
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
        else
            if (j == numitems - 1)
            {
                result = false;
                break;
            }
            else
                --i;
    }
    return result;
}

template<class T> void Listext<T>::prettyprint(void)
{
    for (int i = 0; i < numitems; i++)
    {
        cout << i+1 << ":  " << reprarray[i];
        if (i != numitems - 1)
            cout << "; ";
        cout << "\n";
    }
}

/* for added member function for rotation and selection need to be implemented */

template<class T> void Listext<T>::rotate(int m)
{
    // first we should define a smaller of numitems and m
    // smaller could define which to devide.
    int smr;
    int bgr;
    if (m >= numitems){
        bgr = m;
        smr = numitems;
    }
    else{
        bgr = numitems;
        smr = m;
    }
    if (bgr % (smr-1) == 0){
        for (int i = 0; i < smr - 1; i++){
            T temp = reprarray[i];
            int index = i;
            int counter = 1;
            while (counter < numitems / (m-1) ){
                // design a loop that form a sequence.
                reprarray[index] = reprarray[(index + m - 1) % numitems];
                counter++;
                index = (index + m - 1) % numitems;
            }
            reprarray[index] = temp;
        }
    }
    else{
        T temp = reprarray[0];
        int index = 0;
        int counter = 1;
        while (counter < numitems){
            // design a loop that form a sequence.
            reprarray[index] = reprarray[(index + m - 1) % numitems];
            counter++;
            index = (index + m - 1) % numitems;
        }
        reprarray[index] = temp;
    }
}

template<class T> T Listext<T>::select(int k)
{
    // here is the logic to define that if the k is too large,
    // then the code will exit if k > numitems.
    if (k > numitems){
        cout << "Error: index out of range." << std::endl;
        exit(EXIT_FAILURE);
    }
    // the algorithm is select the first element as judge
    // split the list into another two lists
    // one is bigger than judge.
    // the other is smaller.
    // check if the list length is k-1.
    // if so, return the judge,
    // else, do a recurse on bigger and smaller list.
    Listext<T>* smrptr = new Listext<T>;
    Listext<T>* bgrptr = new Listext<T>;
    T temp = getitem(1);
    int counter = 0;
    //form two lists
    for (int i = 2; i <= getlength(); i++){
        T value = operator[](i);
        if (value >= temp){
            bgrptr->append(value);
        }
        else {
            smrptr->append(value);
            counter++;
        }
    }
    // check if the list length is k-1.
    // if so, return the judge
    if (counter+1 == k){
        delete smrptr;
        delete bgrptr;
        return temp;
    }
    // else, do a recurse on bigger and smaller list.
    else if(counter+1 > k){
        return smrptr->select(k);
    }
    else{
        return bgrptr->select(k-counter-1);
    }
}