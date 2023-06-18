//
//  trietest.cpp
//  
//
//  Created by KD on 20.03.21.
//  Modified on 04.04.22.
//

#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include "trie.cpp"
using std::cout;
using std::cin;

int main()
{
    trie<char> mytrie = trie<char>();
    AList<char> mylist1 = AList<char>(10);
    AList<char> mylist2 = AList<char>(10);
    AList<char> mylist3 = AList<char>(10);
    AList<char> mylist4 = AList<char>(10);
    AList<char> mylist5 = AList<char>(10);
    AList<char> mylist6 = AList<char>(10);
    AList<char> mylist7 = AList<char>(10);
    AList<char> mylist8 = AList<char>(10);
    AList<char> mylist9 = AList<char>(10);
    AList<char> mylist10 = AList<char>(10);
    AList<char> mylist11 = AList<char>(10);
    // Enter your dictionary words
    mylist1.append('e');
    mylist1.append('n');
    mylist1.append('t');
    mylist1.append('e');
    mylist1.append('r');
    mylist2.append('y');
    mylist2.append('o');
    mylist2.append('u');
    mylist2.append('r');
    mylist3.append('d');
    mylist3.append('i');
    mylist3.append('c');
    mylist3.append('t');
    mylist3.append('i');
    mylist3.append('o');
    mylist3.append('n');
    mylist3.append('a');
    mylist3.append('r');
    mylist3.append('y');
    mylist5.append('w');
    mylist5.append('o');
    mylist5.append('r');
    mylist5.append('d');
    mylist5.append('s');
    mytrie.insert(mylist1);
    mylist11.append('w');
    mylist11.append('o');
    mylist11.append('r');
    mylist11.append('d');
    mylist11.append('g');
    mytrie.insert(mylist11);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist1) << "\n";
    cout << mytrie.intrie(mylist2) << "\n\n";
    mytrie.insert(mylist2);
    mytrie.display();
    mytrie.insert(mylist3);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist5) << "\n";
    cout << mytrie.intrie(mylist3) << "\n\n";
    mytrie.insert(mylist5);
    mytrie.display();
    cout << "\n" << mytrie.intrie(mylist5) << "\n";
    // Now test the correction functions

    /*
     *
     * Testing for correct1.
     *
     */

    mylist6.append('w');
    mylist6.append('o');
    mylist6.append('r');
    mylist6.append('d');
    mytrie.correct1(mylist6);

    /*
     *
     * Testing for correct2.
     *
     */

    mylist4.append('e');
    mylist4.append('n');
    mylist4.append('t');
    mylist4.append('e');
    mylist4.append('r');
    mylist4.append('e');
    mylist4.append('d');
    mytrie.correct2(mylist4);

    /*
     *
     * Testing for correct3.
     *
     */

    mylist7.append('w');
    mylist7.append('o');
    mylist7.append('r');
    mylist7.append('m');
    mylist7.append('s');
    mylist8.append('l');
    mylist8.append('o');
    mylist8.append('r');
    mylist8.append('d');
    mylist8.append('s');

    // testing the subs middle condition.
    mytrie.correct3(mylist7);

    // testing the subs heading condition.
    mytrie.correct3(mylist8);

    // testing the non end condition.
    mytrie.correct3(mylist6);

    // testing the subs end condition.
    mylist9.append('w');
    mylist9.append('o');
    mylist9.append('r');
    mylist9.append('d');
    mylist9.append('e');
    mytrie.correct3(mylist9);

    // testing the additional end condition.
    mylist10.append('w');
    mylist10.append('o');
    mylist10.append('r');
    mylist10.append('d');
    mylist10.append('s');
    mylist10.append('f');
    mytrie.correct3(mylist10);

    return 0;
}
