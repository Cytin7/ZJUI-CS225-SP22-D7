//
//  squeue.cpp
//  
//
//  Created by KD on 17.01.21.
//  Extended on 17.02.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "squeue.h"
using std::cout;
using std::cin;

template<class T> stack<T>::stack(int size)
{
    maxsize = size;
    if (size < 10)
        minsize = size;
    else
        minsize = 10;
    numitems = 0;
    reprarray = new T[maxsize];
}

//template<class T> stack<T>::~stack()
//{
//    delete[] reprarray;
//}

template<class T> T &stack<T>::operator[](int index)
{
    return reprarray[index - 1];
}

template<class T> int stack<T>::getheight(void)
{
    return numitems;
}

template<class T> void stack<T>::push(T value)
{
    if (numitems == maxsize)
        allocate();
    reprarray[numitems] = value;
    ++numitems;
    return;
}

template<class T> T stack<T>::pop(void)
{
    if (numitems > 0)
    {
        T result = reprarray[numitems - 1];
        if ((numitems <= maxsize / 4) && (maxsize >= 2 * minsize))
            deallocate();
        --numitems;
        return result;
    }
    else
    {
        cout << "The stack is empty.";
        exit(EXIT_FAILURE);
    }
}

template<class T> T stack<T>::top(void)
{
    if (numitems > 0)
        return reprarray[numitems - 1];
    else
    {
        cout << "The stack is empty.";
        exit(EXIT_FAILURE);
    }
}

template<class T> bool stack<T>::isempty(void)
{
    if (numitems > 0)
        return false;
    else
        return true;
}

template<class T> void stack<T>::allocate(void)
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

template<class T> void stack<T>::deallocate(void)
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


template<class T> squeue<T>::squeue(int size)
{
    stack1 = new stack<T>(size);
    stack2 = new stack<T>(size);
}

template<class T> T &squeue<T>::operator[](int index)
{
    if ((1 <= index) && (index <= (*stack1).getheight()))
        return (*stack1)[index];
    else
        if (((*stack1).getheight() < index) && (index <= (*stack1).getheight() + (*stack2).getheight()))
        {
            index -= (*stack1).getheight();
            return (*stack2)[index];
        }
        else
        {
            cout << "Error: index " << index << " out of range.\n";
            exit(EXIT_FAILURE);
        }
}

template<class T> int squeue<T>::getlength(void)
{
    return (*stack1).getheight() + (*stack2).getheight();
}

template<class T> bool squeue<T>::isempty(void)
{
    if (((*stack1).getheight() + (*stack2).getheight()) == 0)
        return true;
    else
        return false;
}

template<class T> T squeue<T>::front(void)
{
    // this member function needs to be implemented
}

template<class T> void squeue<T>::pushback(T value)
{
    // this member function needs to be implemented
}

template<class T> T squeue<T>::popfront(void)
{
    // this member function needs to be implemented
}
