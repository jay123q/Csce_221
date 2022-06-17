#include <iostream>

#include <vector>
using namespace std;


template<typename T>
struct Node {
  Node<T> *left, *right;
  T obj;

  Node(T obj, Node<T> * left = nullptr, Node<T> * right = nullptr)
    : obj(obj), left(left), right(right)
  { }
};

template<typename T>
int count_filled_nodes(const Node<T> * node) {
	// code
    if(!node)
    {
      return 0;
    }

    return count_filled_nodes(node->right) + count_filled_nodes(node->left)+1;

}

int main()
{
   // Node <int> * head = new Node(0);
    Node <int> * head = new Node (12);
    head->left = new Node (5);
    head->left->left = new Node (4);
    head->left->right = new Node (11 );
    head->right = new Node (49 );
    head->right->left = new Node (30 );
    head->right->right = new Node (51 );




    int Count = count_filled_nodes(head);

    cout << " counting filled nodes " << Count <<  endl;
}