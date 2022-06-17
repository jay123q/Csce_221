
#include <algorithm>
#include <chrono>
#include <iostream>
#include<vector>
#include <cmath>

#include <functional> 
using namespace std;

int main()
{
    int array[] = {1,2,3,4,5};
    int *ptr = array;
    int *ptr2 = array+4;
    cout << *(ptr +3)<<","<<endl;
    cout << ptr2-ptr << ","<<endl;
    cout << *ptr2-*ptr << endl;
    return 0;

}