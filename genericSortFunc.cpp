#include <iostream>
using namespace std;

template <class X>
void bubble(X *items, int count) 
// number of items in array
// pointer to array to be sorted
{
    int a, b;
    X t;
    for (a = 0; a < count - 1; a++)
        for (b = 0; b < count - a - 1; b++)
            if (items[b] > items[b+1])
            {
                // exchange elements
                t = items[b];
                items[b] = items[b+1];
                items[b+1] = t;
            }
}

int main()
{
    int iarray[7] = {7, 5, 4, 3, 9, 8, 6};
    double darray[5] = {4.3, 2.5, -0.9, 100.2, 3.0};
    int i;
    cout << "Here is unsorted integer array: ";
    for (i = 0; i < 7; i++)
        cout << iarray[i] << ' ';
    cout << endl;
    cout << "Here is unsorted double array: ";
    for (i = 0; i < 5; i++)
        cout << darray[i] << ' ';
    cout << endl;
    bubble(iarray, 7);
    bubble(darray, 5);
    cout << "Here is sorted integer array: ";
    for (i = 0; i < 7; i++)
        cout << iarray[i] << ' ';
    cout << endl;
    cout << "Here is sorted double array: ";
    for (i = 0; i < 5; i++)
        cout << darray[i] << ' ';
    cout << endl;
    return 0;
}
