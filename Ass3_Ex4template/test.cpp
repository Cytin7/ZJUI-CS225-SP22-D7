//
//  test.cpp
//  
//
//  Created by KD on 09.05.21.
//  Modified by HJD on 10.3.22
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listext.cpp"
#include "time.h"
using std::cout;
using std::cin;
using std::rand;
using std::srand;

int main()
{
    for (int i = 0; i < 1; i++)
    {
        Listext<int> *mylist = new Listext<int>();
        //srand(time(0));
        int j;
        for (int i = 0; i < 500; i++)
        {
            j = (rand() % 2000) - 1000;
            (*mylist).append(j);
        }
        mylist->prettyprint();
        int result;
        for (int k = 1; k < 20; k++) {
            result = mylist->select(k);
            cout << k << "'th element: " << result << "\n";
        }
        (*mylist).rotate(7);
        cout << "Rotation by " << 7 << " positions:\n";
        mylist->prettyprint();
        return 0;
    }
}
