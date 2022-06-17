#include <iostream>
using namespace std;

void Recur_fun(int n)
{
    if(n>0)
    {
        Recur_fun(n-1);
        cout << n << endl;
        Recur_fun(n-1);
    }
}


// int sum(int n) 
// { 
//    if (n == 0) return 0; 
//    return (n - 1) + sum(n); 
// }

int main()
{
    cout << " CHANGE 3" << endl;
    Recur_fun(3);
    cout << " CHANGE 4" << endl;
    Recur_fun(4);
    cout << "CHANGE  5" << endl;
    Recur_fun(5);
    sum(3);
    // cout << "n in input 3" << x <<  endl;
    // cout << "n in input 4" << Recur_fun(4) <<  endl;
    // cout << "n in input 5" << Recur_fun(5) <<  endl;

}