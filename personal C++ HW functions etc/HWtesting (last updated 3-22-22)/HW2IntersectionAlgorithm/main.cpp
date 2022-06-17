#include <vector>
#include <iostream>
#include <list>
using namespace std;

void print(const std::list<int> printList)
{
    for (const auto & i : printList)
    {
        cout << i;
    }
    cout << endl;
}
// template<typename T>
// bool operator==()(T a, T b){
//     return(a.node == other.node);
//     // TODO
// }

std::list<int> intersection(const std::list<int> & l1, const std::list<int> & l2) {
  list <int> CombinedList;
  if(!l1.size() || !l2.size())
  {
      cout  << " no intersection one of the lists has size 0 " << endl;
      return CombinedList;
  }

auto IterInFor = l1.begin();
auto IterInIf=l2.begin();
auto IterEndFor = l1.end();
auto IterEndIf= l2.end();
if(l1.size()>l2.size())
    {
         IterEndFor=l1.end();
         IterEndFor=l2.end();
         IterInFor = l1.begin();
         IterInIf = l2.begin();
    }
else{
     IterEndFor=l2.end();
     IterEndIf=l1.end();
     IterInFor = l2.begin();
     IterInIf=l1.begin();
    }

for( ;IterInFor != IterEndFor; std::advance(IterInFor,1) )
    {
 //       cout << "Iterator in For "<< *IterInFor<< " Iter in if " <<  *IterInIf << endl;
        if(*IterInFor==*IterInIf) 
        {

            CombinedList.push_back(*IterInFor);
            std::advance(IterInIf,1);
            if(IterInIf ==IterEndIf )
            {
                break;
            }

        }
    
    }

    return CombinedList;
}

int maxValue(vector <int> & searchVector, int index, int TheMadMax){
// {   if(searchVector.size() == 1){return index;}
    if(index == -1){return TheMadMax;} // one comparision
    int compareValue = searchVector.at(index); // one assignment
    cout << " compare " <<  compareValue << " with max " << TheMadMax << endl; // one operation
    

    if(compareValue > TheMadMax) // one comparision
    {
        return maxValue(searchVector,index-1,compareValue);
    }
    else
    {
        return maxValue(searchVector,index-1,TheMadMax);
    }
}



int main()
{
    std::list<int> list1;
    for ( int i = 0 ; i  < 16 ; i ++ )
    {
        list1.push_front(i);
    }

    std::list<int> list2;
    for ( int i = 0 ; i  < 4 ; i ++ )
    {
       // cout << " i is " << i << endl;
        list2.push_front(i);
    }
    
    list1.sort();
    list2.sort();
    print(list2);
    print(list1);
 //  cout << " ye " << endl;
   list<int> newList = intersection(list1,list2);

    cout <<  " lists compared new list made # of elements is " << endl;
    print(newList);











    // cout << " Max Value of vector test 1 " << endl;
    // vector <int> p = {1,2,33,3,4,10};
    // int storage = maxValue(p,p.size()-1,0);
    // cout << " max value is " << storage << endl;
    // cout << " Max Value of vector test 2 " << endl;
    // p = {10};
    // storage = maxValue(p,p.size()-1,0);
    // cout << " max value is " << storage << endl;
    // cout << " Max Value of vector test 3 " << endl;
    // p = {10,0,0,0,1};
    // storage = maxValue(p,p.size()-1,0);
    // cout << " max value is " << storage << endl;




}