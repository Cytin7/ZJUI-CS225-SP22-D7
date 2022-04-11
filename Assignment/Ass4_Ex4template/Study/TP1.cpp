#include<iostream>
#include "TemplateDemo.h"
using namespace std;
/*
template<class T> class A{
    public:
        T g(T a,T b);
        A();
};
*/
template<class T> A<T>::A(){}

template<class T> T A<T>::g(T a,T b){
    return a+b;
}

int *range(int start, int end){
    if(start > end){
        cout << "start should be smaller than end\n"<<
    }
    int length = end - start+1;
    int *array = new int[length];
    for (int i = 0; i < length; i++)
    {
        array[i] = i;
    }
    
    return array;
}


 
int main(){
    A<int> a;
    cout<<a.g(2,3.2)<<endl;
    int* list = range(1,5);
    for (int i = 0; i < 5; i++)
    {
        cout<< list[i];
    }
    
};