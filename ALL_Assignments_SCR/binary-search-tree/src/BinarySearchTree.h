#pragma once

#include <functional> // std::less
#include <iostream>
#include <queue> // std::queue
#include <utility> // std::pair

#include <cmath>

template <typename K, typename V, typename Comparator = std::less<K>>
class BinarySearchTree
{
  public:
    using key_type        = K;
    using value_type      = V;
    using key_compare     = Comparator;
    using pair            = std::pair<key_type, value_type>;
    using pointer         = pair*;
    using const_pointer   = const pair*;
    using reference       = pair&;
    using const_reference = const pair&;
    using difference_type = ptrdiff_t;
    using size_type       = size_t;

  private:
    struct BinaryNode
    {
        pair element;
        BinaryNode *left;
        BinaryNode *right;

        BinaryNode( const_reference theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ theElement }, left{ lt }, right{ rt } { }
        
        BinaryNode( pair && theElement, BinaryNode *lt, BinaryNode *rt )
          : element{ std::move( theElement ) }, left{ lt }, right{ rt } { }
    };

    using node           = BinaryNode;
    using node_ptr       = node*;
    using const_node_ptr = const node*;

    node_ptr _root;
    size_type _size;
    key_compare comp;
// your add
//Comparator isLessThan;

  public:
    BinarySearchTree(): _root(nullptr),_size(0),comp() {
        // TODO
    }
    BinarySearchTree( const BinarySearchTree & rhs ) : _root() , _size(rhs._size), comp()  {
        // TODO
        _root = clone(rhs._root);
    }
    BinarySearchTree( BinarySearchTree && rhs ) : _root() , _size(rhs._size), comp()  {
        // TODO
        // this could be rotation
        _root = std::move(rhs._root);
        _size = rhs._size;
        rhs._size = 0;
        rhs._root = nullptr;
    }
    ~BinarySearchTree() {
        // TODO
        clear();


    }

    const_reference min() const { return min( _root )->element; }
    const_reference max() const { return max( _root )->element; }
    const_reference root() const { 
        // TODO
        //BinaryNode x;
      //  this->_root->element;
        return this->_root->element;
    }
    bool contains( const key_type & x ) const { return contains( x, _root ); }
    value_type & find( const key_type & key ) { return find( key, _root )->element.second; }
    const value_type & find( const key_type & key ) const { return find( key, _root )->element.second; }
    bool empty() const {
        // TODO
        return (_size==0);
    }
    size_type size() const 
    {
        // TODO
        //return (_root == nullptr) ? 0 : _root->_size(_root);
        return _size;
    }

    void clear() {
        clear( _root );
        _size = 0;
    }
    void insert( const_reference x ) { insert( x, _root ); }
    void insert( pair && x ) { insert( std::move( x ), _root ); }
    void erase( const key_type & x ) { erase(x, _root); }

    BinarySearchTree & operator=( const BinarySearchTree & rhs ) {
        // TODO
        if(&rhs == this)
        {
            return *this;
        }
        else
        {
            clear();
            _root = clone(rhs._root);
            _size = rhs._size;
            

        }
        return *this;
    }
    BinarySearchTree & operator=( BinarySearchTree && rhs ) {
        // TODO
        if(&rhs != this)
        {
            clear();
            _root = std::move(rhs._root);
            _size = rhs._size;
            rhs._size = 0;
            rhs._root = nullptr;

        }
        return *this;
    }

  private:
    void insert( const_reference x, node_ptr & t ) {
        // TODO
        if (!t)
        {
            t = new BinaryNode{ x , nullptr , nullptr }; 
            _size++;
        }
        else if (comp(x.first,t->element.first))
        {
            insert(x , t->left);
        }
        else if (comp(t->element.first,x.first))
        {
            insert(x , t->right);
        }
       else
        {
            t->element = x;
        }

    }
    void insert( pair && x, node_ptr & t ) {
        // TODO
        if (!t)
        {
            t = new BinaryNode{ std::move(x) , nullptr , nullptr }; 
            _size++;
        }
        else if (comp(x.first,t->element.first))
        {
            insert(std::move(x) , t->left);
        }
        else if (comp(t->element.first,x.first))
        {
            insert(std::move(x) , t->right);
        }
        else
        {
            t->element = std::move(x);
        }
    }
    
    // my function
    BinaryNode * findMin( BinaryNode *t ) const
    {
        if( t == nullptr )
        {return nullptr;}
        if( t->left == nullptr )
        {return t;}
        return findMin( t->left );
    }

    void erase( const key_type & x, node_ptr & t ) {
        // TODO -- Bonus
        if( t == nullptr )
            return; // Item not found; do nothing
        if( comp( x,t->element.first ))
            {erase( x, t->left );}
        else if( comp(t->element.first,x ))
            {erase( x, t->right );}
        else if( t->left != nullptr && t->right != nullptr ) // Two children
        {
            t->element = findMin( t->right )->element;
            erase( t->element.first, t->right );
        }
        else
        {
            BinaryNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
            _size--;
        }
    }

    const_node_ptr min( const_node_ptr t ) const {
        // TODO
        if(!t)
        {
            return nullptr;
        }
        if(!(t->left)) 
        {
            return t;
        }
        return min(t->left);

    }
    const_node_ptr max( const_node_ptr t ) const {
        // TODO
        if(t)
        {
            while( t-> right != nullptr)
            {
                t = t->right;
            }
        }
        return t;
    }

    bool contains( const key_type & x, const_node_ptr t ) const {
        // TODO
        if(!t)
        {return false;}
        else if ( x < t->element.first)
        {
            return contains(x , t->left);
        }
        else if ( x > t->element.first)
        {
            return contains(x, t->right);
        }
        else
        {return true;}


    }
    node_ptr find( const key_type & key, node_ptr t ) {
        // TODO
        if(t == nullptr)
        {
            return nullptr;
        }
        else if (comp(key,t->element.first))
        {
            t = t->left;
            return find(key,t);
        }
        else if ( comp( t->element.first, key))
        {
            t = t -> right;
            return find(key,t);
        }
        else
        {
            return t;
        }
    }
    const_node_ptr find( const key_type & key, const_node_ptr t ) const {
        // TODO
        if(t == nullptr)
        {
            return nullptr;
        }
        else if (comp(key,t->element.first))
        {
            t = t->left;
            return find(key,t);
        }
        else if ( comp( t->element.first, key))
        {
            t = t -> right;
            return find(key,t);
        }
        else
        {
            return t;
        }
    }

    void clear( node_ptr & t ) {
        // TODO
        if(t != nullptr)
        {
            clear(t->right);
            clear(t->left);
            delete t;
        }
        // t->left = nullptr;
        // t->right = nullptr;
        // t->element = nullptr
        t = nullptr;
        _size = 0;
    }
    
    node_ptr clone ( const_node_ptr t ) const {
        // TODO
        if (t == nullptr)
        {
            return nullptr;
        }
        else
            return new BinaryNode{ t->element , clone(t->left) , clone( t->right) };
    }

    int Height( node_ptr t) const
    {
        if(t == nullptr) {return 0;}
        else
        {
            int max;
            int left_height = Height(t->left);
          //  std::cout << left_height << " left height " << std::endl;
            int right_height = Height(t->right);
          //  std::cout << right_height << " right height " << std::endl;
            if(left_height > right_height)
            {
                max = left_height;
            }
            else
            {
                max =  right_height;
            }
            return max+1;
        }

    }

  public:
    template <typename KK, typename VV, typename CC>
    friend void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend std::ostream& printNode(std::ostream& o, const typename BinarySearchTree<KK, VV, CC>::node& bn);

    template <typename KK, typename VV, typename CC>
    friend void printTree( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out );

    template <typename KK, typename VV, typename CC>
    friend void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
        std::ostream & out,
        typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev
    );

    template <typename KK, typename VV, typename CC>
    friend void vizTree(
        const BinarySearchTree<KK, VV, CC> & bst, 
        std::ostream & out
    );
};

template <typename KK, typename VV, typename CC>
std::ostream& printNode(std::ostream & o, const typename BinarySearchTree<KK, VV, CC>::node & bn) {
    return o << '(' << bn.element.first << ", " << bn.element.second << ')';
}

template <typename KK, typename VV, typename CC>
void printLevelByLevel( const BinarySearchTree<KK, VV, CC>& bst, std::ostream & out = std::cout ) {
    using node = typename BinarySearchTree<KK, VV, CC>::node;
    using node_ptr = typename BinarySearchTree<KK, VV, CC>::node_ptr;
    using const_node_ptr = typename BinarySearchTree<KK, VV, CC>::const_node_ptr;
    
    
    // TODO -- Guide in Instructions
  //  out << printNode(out,bst) << std::endl;
 // int counter = 0;
        int countallNodes = 0;
        if(bst._root  == nullptr){ return;}
        std::queue <node_ptr> q;
        node_ptr Node;
        q.push(bst._root);
        int heightOfTree = bst.Height(bst._root);
    //    std::cout << heightOfTree <<  " height" << std::endl;
        int countLinesTillSkip = 0;
        int lineSkipper = 1;
        int breakCondition = 0;

        while(!q.empty())
        {

            Node = q.front();
            if(Node)
            {
                if(Node->left)
                {
                    q.push(Node->left);
                }
                else
                {
                    q.push(nullptr);
                   // out << "null";
                }
                if(Node->right)
                {
                    q.push(Node->right);
                }
                else
                {
                    q.push(nullptr);
                //    out << "null";
                }
                printNode<KK,VV,CC>(out,*Node);

            }
            else{
                q.push(nullptr);
                q.push(nullptr);
                out << "null";
            }
            q.pop();
            
            countLinesTillSkip++;
            countallNodes++;
            if(lineSkipper == countLinesTillSkip)
            {
                
                breakCondition = log2(countallNodes+1);
            //    std::cout << " break me " <<  breakCondition;
                lineSkipper*=2;
                countLinesTillSkip = 0;
                out << std::endl;
            }
            if(breakCondition == heightOfTree  )
            {break;}

        }

    

}

template <typename KK, typename VV, typename CC>
void printTree( const BinarySearchTree<KK, VV, CC> & bst, std::ostream & out = std::cout ) { printTree<KK, VV, CC>(bst._root, out ); }

template <typename KK, typename VV, typename CC>
void printTree(typename BinarySearchTree<KK, VV, CC>::const_node_ptr t, std::ostream & out, unsigned depth = 0 ) {
    if (t != nullptr) {
        printTree<KK, VV, CC>(t->right, out, depth + 1);
        for (unsigned i = 0; i < depth; ++i)
            out << '\t';
        printNode<KK, VV, CC>(out, *t) << '\n';
        printTree<KK, VV, CC>(t->left, out, depth + 1);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr node, 
    std::ostream & out,
    typename BinarySearchTree<KK, VV, CC>::const_node_ptr prev = nullptr
) {
    if(node) {
        std::hash<KK> khash{};

        out << "\t" "node_" << (uint32_t) khash(node->element.first)
            << "[label=\"" << node->element.first 
            << " [" << node->element.second << "]\"];" << std::endl;
        
        if(prev)
            out << "\tnode_" << (uint32_t) khash(prev->element.first) <<  " -> ";
        else
            out << "\t";
        
        out << "node_" << (uint32_t) khash(node->element.first) << ";" << std::endl;
    
        vizTree<KK, VV, CC>(node->left, out, node);
        vizTree<KK, VV, CC>(node->right, out, node);
    }
}

template <typename KK, typename VV, typename CC>
void vizTree(
    const BinarySearchTree<KK, VV, CC> & bst, 
    std::ostream & out = std::cout
) {
    out << "digraph Tree {" << std::endl;
    vizTree<KK, VV, CC>(bst._root, out);
    out << "}" << std::endl;
}
