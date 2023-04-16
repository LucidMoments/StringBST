

#include <iostream>
#include <fstream>


using namespace std;


int main()
{
    ifstream input("from.txt", ios::in);
    ofstream output("ready.txt", ios::out);

    int size, time;
    while (!input.eof())
    {
        input >> size >> time;

        output << time << endl;
    }
    

    return 0;
}