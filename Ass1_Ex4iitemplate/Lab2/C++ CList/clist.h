//
//  alist.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 22.01.21
//

#ifndef clist_h
#define clist_h

template<class T> class CList
{
public:
    CList(int size = 20);
//    virtual ~CList();
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    void setitem(int index, T value);
    T getitem(int index);
    void pushback(T value);
    T popback(void);
    void pushfront(T value);
    T popfront(void);
    T front(void);
    T back(void);
private:
    int numitems;
    T *reprarray;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> CList<T>::CList(int size)
{
    maxsize = size;
    if (size < 20)
        minsize = size;
    else
        minsize = 20;
    numitems = 0;
    reprarray = new T[maxsize];
}

//template<class T> CList<T>::~CList()
//{
//    delete[] reprarray;
//}

#endif /* clist_h */
