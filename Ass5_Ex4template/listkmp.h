//
//  listkmp.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 12.03.22
//

#ifndef listkmp_h
#define listkmp_h

template<class T> class KMPlist
{
public:
    KMPlist(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(KMPlist<T> &list);
    bool member(T value);
    bool equal(KMPlist<T> &list);
    bool sublist(KMPlist<T> &list);
    void prettyprint(void);
    void rotate(int m);
    T select(int k);
    void create_next(void);
    int kmp(KMPlist<T> *target);
private:
    int numitems;
    T *reprarray;
    int * nextlist;
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

#endif /* listkmp_h */
