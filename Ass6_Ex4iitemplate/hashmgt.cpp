//
//  hashmgt.cpp
//  
//
//  Created by KD on 6.03.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "hashmap.h"
#include "hashmap_template.cpp"
using std::cout;
using std::cin;
using std::hash;

int main()
{
    // testing add && retrieve && member.
    hashmap<int,char> hashmap;
    hashmap.add(1,'h');
    hashmap.display();
    hashmap.member(1,'j');
    cout << hashmap.retrieve(1)<<std::endl;
    hashmap.add(1,'j');
    return 0;
}
