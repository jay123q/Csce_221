#pragma once

#include <cstddef> // size_t
#include <iterator> // std::bidirectional_iterator_tag
#include <type_traits> // std::is_same, std::enable_if

template <class T>
class List {
    private:
    struct Node {
        Node *next, *prev;
        T data;
        explicit Node(Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev} {}
        explicit Node(const T& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{data} {}
        explicit Node(T&& data, Node* prev = nullptr, Node* next = nullptr)
        : next{next}, prev{prev}, data{std::move(data)} {}
    };

    template <typename pointer_type, typename reference_type>
    class basic_iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type        = T;
        using difference_type   = ptrdiff_t;
        using pointer           = pointer_type;
        using reference         = reference_type;
    private:
        friend class List<value_type>;
        using Node = typename List<value_type>::Node;

        Node* node;

        explicit basic_iterator(Node* ptr) noexcept : node{ptr} {}
        explicit basic_iterator(const Node* ptr) noexcept : node{const_cast<Node*>(ptr)} {}

    public:
        basic_iterator() {node = nullptr;}; // to do Node = nullptr
        basic_iterator(const basic_iterator&) = default;
        basic_iterator(basic_iterator&&) = default;
        ~basic_iterator() = default;
        basic_iterator& operator=(const basic_iterator&) = default;
        basic_iterator& operator=(basic_iterator&&) = default;

        reference operator*() const {
            // TODO
            return (this->node->data);
        }
        pointer operator->() const {
            // TODO
            return (&(this->node->data));
        }

        // Prefix Increment: ++
        basic_iterator& operator++() {
            // TODO
            node = node->next;
            return *this;
        }
        // Postfix Increment: a++
        basic_iterator operator++(int) {
            // TODO
            basic_iterator old(node);
            node = node->next; // TODO: what if we go beyond the vector?
            return old;
            
        }
        // Prefix Decrement: --a
        basic_iterator& operator--() {
            // TODO
            node = node->prev;
            return *this;
        }
        // Postfix Decrement: a--
        basic_iterator operator--(int) {
            // TODO
            basic_iterator old(node);
            node = node->prev; // TODO: what if we go beyond the vector?
            return old;
        }

        bool operator==(const basic_iterator& other) const noexcept {
            return(this->node == other.node);
            // TODO
        }
        bool operator!=(const basic_iterator& other) const noexcept {
            // TODO
            return (this->node != other.node);
        }
    };

public:
    using value_type      = T;
    using size_type       = size_t;
    using difference_type = ptrdiff_t;
    using reference       = value_type&;
    using const_reference = const value_type&;
    using pointer         = value_type*;
    using const_pointer   = const value_type*;
    using iterator        = basic_iterator<pointer, reference>;
    using const_iterator  = basic_iterator<const_pointer, const_reference>;

private:
    Node head, tail;
    size_type _size;

public:
    List() : head(), tail(), _size(0)
    //head(T(),nullptr,&tail),  tail(T(),&head, nullptr), _size(0) {
    {
        head.next = &tail;
        tail.prev = &head;
        // TODO - Don't forget the list initializer
    } 
    List( size_type count, const T& value ) : head(),tail(),_size(0){ //  call pushback in here
        // TODO - Don't forget the list initializer
        head.next = &tail;
        tail.prev = &head;
        for(int i = 0 ; i < count ; i++)
        {
           push_back(value);
        }
        
    } 
    explicit List( size_type count ):head(),tail(),_size(0) {
        // TODO - Don't forget the list initializer
        head.next = &tail;
        tail.prev = &head;
        for(int i = 0 ; i < count ; i++)
        {
           push_back(T());
        }
        _size = count;
    }
    List( const List& other ) : head(),tail(),_size(0) {
        // TODO - Don't forget the list initializer
        head.next = &tail;
        tail.prev = &head;
        
        for(auto & i : other)
        {
            
            push_back(i);
        }
    }
    List( List&& other ) : head(), tail() , _size(other._size) {
        // TODO - Don't forget the list initializer
        // two cases 
        // a 3 steper
        // change 6 pointers
        // new head and new tailer point to same that the old head and old trailer point too

        if(other.empty())
        {
            head.next = &tail;
            tail.prev = &head;
        }
        else
        {

            //step 1
            head.next = other.head.next;
            tail.prev = other.tail.prev;
            // step 2
            tail.prev->next = &tail;
            head.next->prev = &head;
            // step 3
            other.head.next = &other.tail;
            other.tail.prev  = &other.head;
            other._size = 0;
        }
    }
    ~List() {
        // TODO
        clear();
        head.next = nullptr;
        tail.prev= nullptr;
    }
    List& operator=( const List& other ) {
        // TODO
      //  clear()
      // check if we are trying to copy a value that already exits
            if(this == &other)
            {
                return *this;
            }
            else
            {
                clear();
                head.next = &tail;
                tail.prev = &head;
                
                for(auto & i : other)
                {
                    push_back(i);
                }
            }
            return *this;
        // List copy = other;
        // std::swap(*this,copy);
        // return *this;
    }
    List& operator=( List&& other ) noexcept {
        // TODO
        // hi you can use the text book here page 118 of http://www.uoitc.edu.iq/images/documents/informatics-institute/Competitive_exam/DataStructures.pdf
       // other.head = Node(other.head);
        //swap(_size, other._size);
        if(this!=&other)
        {
            clear();
            if(other.empty())
            {
                head.next = &tail;
                tail.prev = &head;
                
                
            }
            else
            {
                head.next = other.head.next;
                tail.prev = other.tail.prev;
                // step 2
                tail.prev->next = &tail;
                head.next->prev = &head;
                // step 3
                other.head.next = &other.tail;
                other.tail.prev  = &other.head;
                _size = other._size;
                other._size = 0;
            }
        }
        return *this;

    }

    reference front() {
        // TODO
        return *begin();

    }
    const_reference front() const {
        // TODO
        return *begin();
    }
	
    reference back() {
        // TODO
        return (*--end());
    }
    const_reference back() const {
        // TODO
        return (*--end());

    }
	
    iterator begin() noexcept {
        return iterator(head.next);
        // TODO
    }
    const_iterator begin() const noexcept {
        // TODO
        return const_iterator(head.next);
    }
    const_iterator cbegin() const noexcept {
        // TODO
        return const_iterator(head.next);
// fix cbegin and cend
    }

    iterator end() noexcept {
        // TODO
        return iterator(&tail);
    }
    const_iterator end() const noexcept {
        // TODO
        return const_iterator(&tail);

    }
    const_iterator cend() const noexcept {
        // TODO
        return const_iterator(&tail);

    }
    //insert(pos,value)
    bool empty() const noexcept {
        // TODO
        return size()==0;
    }

    size_type size() const noexcept 
    {
        // TODO
        return _size;
    }

    void clear() noexcept {
        // TODO
        while(!empty())
        {
            pop_back();
        }

    }

    iterator insert( const_iterator pos, const T& value ) 
    {
        Node * walkthrough = new Node(value, pos.node->prev, pos.node);
        // taking a copy of po
        pos.node->prev->next = walkthrough; // pos back to front
        pos.node->prev = walkthrough; // pos next is our pervious
        _size++;
        return iterator(pos.node->prev);

        // TODO
    }

    // insert  before
    iterator insert( const_iterator pos, T&& value ) {
        // TODO
        // Node *p = pos.node;
        // _size++;
        // return { p->prev = p->prev->next = new Node{ std::move(value) , p->prev, p } };
        Node * walkthrough = new Node(std::move(value), pos.node->prev, pos.node);
        // taking a copy of po
        pos.node->prev->next = walkthrough; // pos back to front
        pos.node->prev = walkthrough; // pos next is our pervious
        _size++;
        return iterator(pos.node->prev);
    }

    iterator erase( const_iterator pos ) 
    {
        Node *walkThrough = pos.node;
        iterator CopyOfReturnedValue{ walkThrough->next };
        walkThrough->prev->next = walkThrough->next;
        walkThrough->next->prev = walkThrough->prev;
        delete walkThrough;
        _size--;

        return CopyOfReturnedValue;
        // TODO
        // iterator walk = iterator(pos.node);
        // pos.node->prev->next = pos.node->next;
        // pos.node->next->prev = pos.node->prev; 
        // delete pos.node;
        // _size--;
        // return walk;
    }

    void push_back( const T& value ) {
        // TODO
        insert(cend(),value);
    }
    void push_back( T&& value ) {
        // TODO
        insert(cend(),std::move(value));

    }

    void pop_back() {
        // TODO
        // tail.prev
        iterator ooga {tail.prev};
        erase(ooga);
    }
	
    void push_front( const T& value ) {
        // TODO
        iterator awooga {head.next};
        insert(awooga,value);
    }
	void push_front( T&& value ) {
        // TODO
        iterator chacka {head.next};
        insert(chacka,std::move(value));
    
    }

    void pop_front() {
        // TODO
        iterator hooka {head.next};
        erase(hooka);
    }

    void swap(Node &a , Node &b)
    {
        Node c = std::move(b);
        b = a;
        a = c;
    }

    /*
      You do not need to modify these methods!
      
      These method provide the non-const complement 
      for the const_iterator methods provided above.
    */
    iterator insert( iterator pos, const T & value) { 
        return insert((const_iterator &) (pos), value);
    }

    iterator insert( iterator pos, T && value ) {
        return insert((const_iterator &) (pos), std::move(value));
    }

    iterator erase( iterator pos ) {
        return erase((const_iterator&)(pos));
    }
};


/*
    You do not need to modify these methods!

    These method provide a overload to compare const and 
    non-const iterators safely.
*/
 
namespace {
    template<typename Iter, typename ConstIter, typename T>
    using enable_for_list_iters = typename std::enable_if<
        std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::iterator, 
            Iter
        >{} && std::is_same<
            typename List<typename std::iterator_traits<Iter>::value_type>::const_iterator,
            ConstIter
        >{}, T>::type;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) == rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator==(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) == lhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const Iterator & lhs, const ConstIter & rhs) {
    return (const ConstIter &)(lhs) != rhs;
}

template<typename Iterator, typename ConstIter>
enable_for_list_iters<Iterator, ConstIter, bool> operator!=(const ConstIter & lhs, const Iterator & rhs) {
    return (const ConstIter &)(rhs) != lhs;
}