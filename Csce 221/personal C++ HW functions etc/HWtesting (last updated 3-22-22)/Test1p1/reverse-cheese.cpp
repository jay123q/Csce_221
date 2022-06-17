#include <string>
using std::string;

struct Sandwich {
   string Bread;
   string Topping;
   string Cheese;
   string Protein;
};

// A is the array of sandwiches, n is the size of the array.
void reverseCheese(Sandwich *A, size_t n) {
   //... your code is here
   Sandwich * back = A+n -1 ; //  start at the back and the front stop running if they are the same
   for(Sandwich * front = A ; front != back ; front++)
   {
      swap(front->cheese, back->cheese)

      // back-- not here before
      back--;
   }
}

template <T> // this would be a template that causes me to ignore any disparitiies
void swap(T A, T B)
{
   string c = A;
   A = B;
   B = C;
}
int main()
{
   Sandwich a [3] = {{"bread1","Tom1","Prov","jerky1"},{"bread2","Tom2","Parm","jerky2"},{"bread3","Tom3","Chedder","jerky3"}};
   for (int i = 0 ;  i<3;i++)
   {
      cout << a[i];
   }
}