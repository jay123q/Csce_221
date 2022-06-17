// sorting items from the heaviest to lightest
// by selecting the heaviest item at each time  

#include <iostream>
#include <vector>

using namespace std;

int comparisons = 0;

ostream& operator<<(ostream& out, vector<int>& v)
{
  // overload the output operator to display elements of v
  return out;
}

void sort_heaviest(vector<int>& v){
  
  //-1 since first for is index2+1
  for( size_t  index2 = 0 ; index2 < v.size()-1; index2 ++ )
  {
    int storeIndex = index2;
    for ( size_t index = index2+1; index < v.size() ; index++)
    {
      comparisons++;
      if(v.at(index) > v.at(storeIndex))
      {
        storeIndex = index;
      }
    }
      
      int temp = v.at(index2);
      v.at(index2) = storeIndex;
      v.at(storeIndex) = temp;
    
    
  }

  // implement the sorting algorithm based on video
 
}

int main()
{
 
  cout << "//////Test 2 for vector v ///////////////////////////////"<< endl;
  vector<int> v{16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1};

  cout << "initial vector v:\n";
  // use overloaded output operator to display vector's elements
  // use comma to separate the vector's elements
  cout << endl;
  // call the sorting function for vector v 
  sort_heaviest(v);
  cout << "# of comparisons to sort v: " << comparisons << endl << endl;
  cout << "vector v after sorting:\n";
  // use overloaded output operator to display elements of sorted vector
  // use comma to separate the vector's elements
  cout << endl;
  comparisons=0;
  
  cout << "//////Test 2 for vector v1 ///////////////////////////////"<< endl;
  sort_heaviest(v);

  vector<int> v1{1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  cout << "initial vector v1:\n";
    comparisons=0;

  // use overloaded output operator to display vector's elements
  // use comma to separate the vector's elements
  cout << endl;
   // call the sorting function for vector v2 
    sort_heaviest(v1);

  cout << "# of comparisons to sort v1: " << comparisons << endl << endl;
  cout << "vector v1 after sorting:\n";
    comparisons=0;

  // use overloaded output operator to display elements of sorted vector
  // use comma to separate the vector's elements
  cout << endl;
    
}
