#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "heap.h"
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
    if (index < numitems)
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

template<class T> void AList<T>::concat(AList<T> &list)
{
    int length = list.getlength();
    for (int i = 1; i <= length; ++i)
    {
        append(list[i]);
    }
    return;
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

template<class T> bool AList<T>::sublist(AList<T> &list)
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
                ++j;
    }
    return result;
}

//build the max heap using elements in the input array.
template<class T> void MaxHeap<T>::build_heap(AList<T> &array){
    //put your code below
    AList<T>::concat(array);
    for (int idx = (AList<T>::getlength())/2;
             idx >= 1;
             idx --){
        sift_down(idx,AList<T>::getlength());
    }
    return;
}

//sift down the element with index i within the first num_elements elements.
template<class T> void MaxHeap<T>::sift_down(int idx, int num_elements){
    //put your code below
    if (idx >= 1 && (idx <= num_elements / 2)){
        T parent = AList<T>::getitem(idx);
        T child;
        int idx2;
        if ((2*idx+1) <= num_elements) {
            if (AList<T>::getitem(idx * 2) >= AList<T>::getitem(idx * 2 + 1)) {
                child = AList<T>::getitem(idx * 2);
                idx2 = idx * 2;
            }else{
                child = AList<T>::getitem(idx * 2 + 1);
                idx2 = idx * 2 + 1;
            }
        }else{
            child = AList<T>::getitem(idx * 2);
            idx2 = idx * 2;
        }
        if (child > parent){
            swap(idx,idx2);
            sift_down(idx2,num_elements);
            return;
        }else{
            return;
        }
    }else{
        return;
    }
}

//sort the input array using max heap.
template<class T> void MaxHeap<T>::heap_sort(AList<T> &array){
    //put your code below
    build_heap(array);
    print_elements();
    cout<<"\n";
    for (int i = 1; i < array.getlength(); i++){
        swap(1,AList<T>::getlength()+1-i);
        cout<<"fuck you!1\n";
        print_elements();
        cout<<"\n";
        sift_down(1,(AList<T>::getlength()-i));
        cout<<"fuck you!2\n";
        print_elements();
        cout<<"\n";
    }
    return;
}

//swap elements with indices i and j.
template<class T> void MaxHeap<T>::swap(int i, int j){
    //the index of this array is begin by 1;
    T temp = AList<T>::getitem(i);
    AList<T>::setitem(i,AList<T>::getitem(j));
    AList<T>::setitem(j,temp);
    return;
}

//return the root element. 
template<class T> T MaxHeap<T>::max(){
    //as heap->array[0] is a dector element, so return the array[1]
    return AList<T>::getitem(1);
}

//print all elements in the heap in sequential order.
template<class T> void MaxHeap<T>::print_elements(){
    int n = this->getlength();
    for (int i=1; i<=n; i++){
        cout << this->getitem(i) << "\n";
    }
    return;
}


int main(){
    /*
    cout << "\npart1 test\n";
    //please feel free to add more test cases
    int input_list[10] = {5, 3, 9, 46, 15, 22, 91, 8, 29, 77};
    AList<int> input_array;
    for (int i=0; i<10; i++){
        input_array.append(input_list[i]);
    }
    MaxHeap<int> max_heap;
    max_heap.build_heap(input_array);
    cout<< max_heap.max() << "\n\n";
    max_heap.print_elements();
    cout << "\npart2 test\n";
    */
    //please feel free to add more test cases
    int input_list_2[15] = {55, 32, 9, 46, 15, 22, 91, 18, 29, 77, 32, 16, 791, 45, 32};
    AList<int> input_array_2;
    for (int i=0; i<15; i++){
        input_array_2.append(input_list_2[i]);
    }
    MaxHeap<int> max_heap_2;
    max_heap_2.heap_sort(input_array_2);
    max_heap_2.print_elements();
    return 0;
}
