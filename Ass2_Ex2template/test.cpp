//
//  test.cpp
//  
//
//  Created by KD on 09.05.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "blist.cpp"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

int main()
{
    BList<int> *mylist = new BList<int>();
    (*mylist).setmax(1000);
    (*mylist).setmin(-1000);
    srand(time(0));
    int j;
    for (int i = 0; i < 500; i++)
    {
        j = (rand() % 2000) - 1000;
        (*mylist).append(j);
    }
    (*mylist).prettyprint();
    AList<int> *mysortedlist;
    mysortedlist = (*mylist).bucketsort();
    (*mysortedlist).prettyprint();
}
