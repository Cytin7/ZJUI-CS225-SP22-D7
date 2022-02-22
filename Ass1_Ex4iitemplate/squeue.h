//
//  squeue.h
//
//  Created by KD on 18.02.22.
//

#ifndef squeue_h
#define squeue_h

template<class T> class stack
{
public:
    stack(int size = 10);
//    virtual ~stack();
    T &operator[](int index);
    int getheight(void);
    void push(T value);
    T pop(void);
    T top(void);
    bool isempty(void);
private:
    int maxsize, minsize;
    int numitems;
    T *reprarray;
    void allocate(void);
    void deallocate(void);
};

template<class T> class squeue
{
public:
    squeue(int size = 10);
    T &operator[](int index);
    int getlength(void);
    bool isempty(void);
    T front(void);
    void pushback(T value);
    T popfront(void);
private:
    stack<T> *stack1, *stack2;
};

#endif /* squeue_h */
