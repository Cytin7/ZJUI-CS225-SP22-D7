//
//  test.cpp
//  
//
//  Created by KD on 09.05.21.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "listkmp.cpp"
using std::cout;
using std::cin;

int main()
{
    KMP<char> *plist = new KMPlist<char>();
    (*plist).append('a');
    (*plist).append('b');
    (*plist).append('c');
    (*plist).append('a');
    (*plist).append('b');
    (*plist).append('c');
    (*plist).append('a');
    (*plist).append('c');
    (*plist).append('a');
    (*plist).append('b');
    (*plist).create_next();
    /* You should create more target lists */
    KMP<char> *slist = new KMPlist<char>();
    (*slist).append('b');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('b');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('c');
    (*slist).append('a');
    (*slist).append('b');
    (*slist).append('c');
    int position = (*plist).kmp(slist);
    if (position >= 0)
        cout << "The pattern list appears in the target list\n" << "at position " << position << ".\n";
    else
        cout << "The pattern list does not appear in the target list.\n";
    return 0;
}
