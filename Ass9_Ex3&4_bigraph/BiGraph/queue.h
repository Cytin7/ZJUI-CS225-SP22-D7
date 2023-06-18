//
// Created by 洪嘉栋 on 2022/5/2.
//

#ifndef BIGRAPH_QUEUE_H
#define BIGRAPH_QUEUE_H

template<class T>
class queue{
public:
    queue(int size = 20) {
        maxsize = size;
        if (size < 20)
            minsize = size;
        else
            minsize = 20;
        numitems = 0;
        reprarray = new T[maxsize];
    };

    void enqueue(T value){
        if (numitems == maxsize)
            allocate();
        reprarray[numitems] = value;
        numitems++;
        return;
    };

    T dequeue(){
        if ((numitems == maxsize / 4) && (maxsize > minsize))
            deallocate();
        if (numitems > 0){
            T temp = reprarray[0];
            numitems--;
            for (int i = 0; i < numitems; i++){
                reprarray[i] = reprarray[i+1];
            }
            return temp;
        }else{
            return 0;
        }
    };
    bool isEmpty(){
        if (numitems == 0){
            return true;
        }else{
            return false;
        }
    };

protected:
    int numitems;
    T* reprarray;
private:
    int maxsize, minsize;
    void allocate(){
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
    };

    void deallocate(){
        int newsize = maxsize/2;
        T *newarray = new T[newsize];
        for (int i = 0; i < numitems; ++i)
        {
            newarray[i] = reprarray[i];
        }
        delete[] reprarray;
        reprarray = newarray;
        maxsize = newsize;
        return;
    };
};


#endif //BIGRAPH_QUEUE_H
