//
//  listext.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 02.03.22
//

#ifndef listext_h
#define listext_h

template<class T> class Listext
{
public:
    Listext(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(Listext<T> &list);
    bool member(T value);
    bool equal(Listext<T> &list);
    bool sublist(Listext<T> &list);
    void prettyprint(void);
    void rotate(int m);
    T select(int k);
private:
    int numitems;
    T *reprarray;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

#endif /* listext_h */
