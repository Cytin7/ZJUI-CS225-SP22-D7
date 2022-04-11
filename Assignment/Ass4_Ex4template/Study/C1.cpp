#include <iostream>
using namespace std;
/////////class Babe
class Babe
{
public:
    Babe()
    {
        cout << "Create a Babe to talk with me\" << endl;
    }
    ~Babe()
    {
        cout << "Babe don\'t go away,listen to me\" << endl;
    }
};
//////////main function
int main()
{
    Babe* pbabe = new Babe[3];
    delete pbabe;
    pbabe = new Babe[3];
    delete pbabe[];
    return 0;
}

