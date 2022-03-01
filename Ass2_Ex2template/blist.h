//
//  blist.h
//  
//
//  Created by KD on 14.01.21.
//  Modified by KD on 09.05.21
//

#ifndef blist_h
#define blist_h

template<class T> class AList
{
public:
    AList(int size = 20);
    T &operator[](int index);
    int getlength(void);
    void setitem(int index, T value);
    void setmin(T minimum);
    void setmax(T maximum);
    T getmin(void);
    T getmax(void);
    T getitem(int index);
    void append(T value);
    void insert(int index, T value);
    void remove(int index);
    void concat(AList<T> &list);
    bool member(T value);
    bool equal(AList<T> &list);
    bool sublist(AList<T> &list);
    void prettyprint(void);
protected:
    int numitems;
    T *reprarray;
    T min, max;
private:
    int maxsize, minsize;
    void allocate(void);
    void deallocate(void);
};

template<class T> class BList : public AList<T>
{
public:
    BList(int size = 20) : AList<T>(size){};
    AList<T> *bucketsort(void);
};

#endif /* blist_h */
