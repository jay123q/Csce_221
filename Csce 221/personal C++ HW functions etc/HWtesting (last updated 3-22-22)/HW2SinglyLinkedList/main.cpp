using namespace std;
#include <iostream>
template<typename T>
struct Node {
  Node * next;
  T obj;

  Node(T obj, Node * next = nullptr)
    : obj(obj), next(next)
  { }
};

template<typename T> 
int count_nodes(T* currNode)  
	{if(!currNode){return 0;} 
	else     
	{return 1+count_nodes( currNode->next);}
}



int main()
{
 
  Node <int> * head = new Node <int> {11,nullptr};

  for(int i = 0 ; i < 10 ; i++)
  {
 //   cout << i <<  endl;
    head = new Node <int> {i,head};

  }
  //head = new Node <int> {box+1,nullptr};
  

  int Count = count_nodes(head);
  cout << " number of nodes " <<  Count << endl;

//   Node <int> * head1 = nullptr;
//    int CountNull = count_nodes(head1);
//  cout << " number of nodes " <<  CountNull << endl;


  while (head != nullptr)
  {
    Node <int> * temp;
    temp = head->next;
    delete  head;
    head = temp;
  }
  
  head = nullptr;




  delete head;


}