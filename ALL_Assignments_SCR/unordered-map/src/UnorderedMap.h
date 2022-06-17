#include <cstddef>    // size_t
#include <functional> // std::hash
#include <utility>    // std::pair
#include <iostream>

#include "primes.h"

template <typename Key, typename T, typename Hash = std::hash<Key>, typename Pred = std::equal_to<Key>>
class UnorderedMap
{
public:
    using key_type = Key;
    using mapped_type = T;
    using hasher = Hash;
    using key_equal = Pred;
    using value_type = std::pair<const key_type, mapped_type>;
    using reference = value_type &;
    using const_reference = const value_type &;
    using pointer = value_type *;
    using const_pointer = const value_type *;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

private:
    struct HashNode
    {
        HashNode *next;
        value_type val;

        HashNode(HashNode *next = nullptr) : next{next} {}
        HashNode(const value_type &val, HashNode *next = nullptr) : next{next}, val{val} {}
        HashNode(value_type &&val, HashNode *next = nullptr) : next{next}, val{std::move(val)} {}
    };

    HashNode **_buckets;
    size_type _size;
    size_type _bucket_count;

    HashNode _head;

    Hash _hash;
    key_equal _equal;

    static size_type _range_hash(size_type hash_code, size_type bucket_count)
    {
        return hash_code % bucket_count;
    }

public:
    class iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const key_type, mapped_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        HashNode *_node;

        explicit iterator(HashNode *ptr) noexcept : _node(ptr)
        { /* DOne */
        }

    public:
        iterator() : _node(nullptr){/* DOne */};
        iterator(const iterator &) = default;
        iterator(iterator &&) = default;
        ~iterator() = default;
        iterator &operator=(const iterator &) = default;
        iterator &operator=(iterator &&) = default;
        reference operator*() const { return this->_node->val; /* DOne */ }
        pointer operator->() const { return &this->_node->val; /* DOne */ }
        iterator &operator++()
        {
            /* DOne */
            _node = _node->next;
            return *this;
        }
        iterator operator++(int)
        {
            /* DOne */
            iterator old(*this);
            _node = _node->next;
            return old;
        }
        bool operator==(const iterator &other) const noexcept
        {
            /* DOne */
            return (this->_node == other._node);
        }
        bool operator!=(const iterator &other) const noexcept
        {
            /* DOne */
            return (this->_node != other._node);
        }
    };

    class local_iterator
    {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<const key_type, mapped_type>;
        using difference_type = ptrdiff_t;
        using pointer = value_type *;
        using reference = value_type &;

    private:
        friend class UnorderedMap<Key, T, Hash, key_equal>;
        using HashNode = typename UnorderedMap<Key, T, Hash, key_equal>::HashNode;

        UnorderedMap *_map;
        HashNode *_node;
        size_type _bucket;

        explicit local_iterator(UnorderedMap *map, HashNode *ptr, size_type bucket) noexcept
        { /* done */
            _map = map;
            _node = ptr;
            _bucket = bucket;
        }

    public:
        local_iterator() : _map(_map), _node(nullptr), _bucket(0){/* done */};
        local_iterator(const local_iterator &) = default;
        local_iterator(local_iterator &&) = default;
        ~local_iterator() = default;
        local_iterator &operator=(const local_iterator &) = default;
        local_iterator &operator=(local_iterator &&) = default;
        reference operator*() const { return this->_node->val; /* done */ }
        pointer operator->() const { return &this->_node->val; /* done */ }
        local_iterator &operator++()
        {
            // TODO
            if (!_node->next)
            {
                _node = nullptr;
            }
            else if (_map->bucket(_node->val.first) != _map->bucket(_node->next->val.first))
            {
                _node = nullptr;
            }
            else
            {
                _node = _node->next;
            }
            return *this;
        }
        local_iterator operator++(int)
        {
            // TODO

            local_iterator old(*this);
            ++(*this);
            return old;
        }
        bool operator==(const local_iterator &other) const noexcept
        {
            // TODO
            return (this->_node == other._node);
        }
        bool operator!=(const local_iterator &other) const noexcept
        {
            // TODO
            return (this->_node != other._node);
        }
    };

private:
    size_type _bucket(size_t code) const
    {
        return _range_hash(code, this->_bucket_count);
        /* done */ }
        size_type _bucket(const Key &key) const
        { /* done */
            return _bucket(_hash(key));
        }

        void _insert_before(size_type index, HashNode *node)
        {
            /* done */
            // potentially call begin
            HashNode *&currentHead = _buckets[index];
            _size++;
            if (currentHead)
            {
                node->next = currentHead->next;
                currentHead->next = node;
            }
            else
            {
                node->next = _head.next;
                if (_head.next)
                {
                    size_t UpdateOldNode = bucket(_head.next->val.first);
                    _buckets[UpdateOldNode] = node;
                }
                // if the head does not exist
                _head.next = node;
                currentHead = &_head;
                // size_t UpdateOldNode = bucket(_head.next->val.first);
                // _buckets[UpdateOldNode] = &_head;

                // hash(RehashMe);
            }
        }

        HashNode *&_bucket_begin(size_type bucket)
        {
            /* done */
            if(_buckets[bucket])
            {
                return _buckets[bucket]->next;
            }
            return _buckets[bucket];
        }

        HashNode *_find_prev(size_type code, size_type bucket, const Key &key)
        {
            /* done */
            // size_t index = _bucket(bucket);
            if (!_buckets[bucket] || !_buckets[bucket]->next)
            {
                return nullptr;
            }
            HashNode *walkThrough = _buckets[bucket]->next;
            HashNode *oldNode = _buckets[bucket];

            while (walkThrough != nullptr)
            {
                bool checkKey = _equal(walkThrough->val.first, key);
                // if(bucket != _bucket(key)){ return; }
                if (checkKey)
                {
                    return oldNode;
                }
                walkThrough = walkThrough->next;
                oldNode = oldNode->next;
            }

            return nullptr;
        }

        HashNode *_find_prev(const Key &key)
        {
            size_t code = _hash(key);
            size_t bucketIndex = _bucket(_hash(key));
            return _find_prev(code, bucketIndex, key);
        }

        void _erase_after(HashNode *prev)
        {
            /* TODO */
            size_t indexNext = _bucket_count;
            auto index = _bucket(prev->next->val.first);
            auto temp = prev->next;
            prev->next = prev->next->next;
            delete temp;
            _size--;
            if(prev->next)
            {
                
                indexNext = _bucket(prev->next->val.first);
                if(temp == _buckets[indexNext])
                {
                    _buckets[indexNext] = prev;
                }
            }
            if( index != indexNext && _buckets[index] == prev )
            { // _buuckets[index] == prev
                    _buckets[index] = nullptr;
            }

            // if( prev->next->next)
            // {
            //     size_t indexPrev = _bucket(prev->next->next->val.first);
            //     if(prev->next == _buckets[indexPrev])
            //     {
            //         _buckets[indexPrev] = prev;
            //     }
            //     if(_bucket(prev->next->val.first)!= _bucket(prev->next->next->val.first))
            //     {
            //         _buckets[_bucket(prev->next->val.first)] = nullptr;
            //         //   _bucket_count--;
            //     }

            // }
            // else
            // {
            //     size_t indexPrev = _bucket(prev->next->val.first);
            //     // check if its a head node
            //     if(prev == _buckets[indexPrev])
            //     {
            //         _buckets[indexPrev] = nullptr;
            //         //  _bucket_count--;
            //     }
            // }

            // decrement bucket count?



        }

    public:
        explicit UnorderedMap(size_type bucket_count, const Hash &hash = Hash{},
                              const key_equal &equal = key_equal{}) : _size(0), _hash(hash), _equal(equal), _head()
        {
            /* done */
            //  std::cout << bucket_count << std::endl;
            _bucket_count = next_greater_prime(bucket_count);
            _buckets = new HashNode *[_bucket_count]();
        }

        ~UnorderedMap()
        {
            /* done */
            clear();
            delete [] _buckets;
        }

        UnorderedMap(const UnorderedMap &other) : _size(0), _hash(other._hash), _equal(other._equal), _head()
        {
            /* TODO */
            // read notations
            // pass copy, pass number of buckets, size, etc?
            _bucket_count = other._bucket_count;

            _buckets = new HashNode *[_bucket_count]();
            auto walk = other._head.next;
            while(walk)
            {
                insert(walk->val);
                walk = walk->next;
            }
        }

        UnorderedMap(UnorderedMap &&other) : _size(0), _hash(other._hash), _equal(other._equal), _head()
        {
            /* TODO */
                _bucket_count = other._bucket_count;
             //   _buckets = new HashNode *[_bucket_count](); // reassign pointers
                _size = other._size;
                _head.next = other._head.next;
                _buckets = other._buckets; 
                if(other._head.next)
                {
                    // take the other head pointer and point it to our head
                    // take position that points to the head of the hashnode and saying its the addy of head
                    _buckets[_bucket(_head.next->val.first)] = &_head;
                }
                other._buckets = new HashNode *[other._bucket_count](); // calls default
                other._size = 0;
                other._head.next = nullptr;
                other._hash = Hash{};
                other._equal = key_equal{};


        }

        UnorderedMap &operator=(const UnorderedMap &other)
        {
            // /*  */
            if(this == &other)
            {
                return *this;
            }
            else{
                if(this != nullptr)
                {
                    clear();
                    delete [] _buckets;

                }
                _bucket_count = other._bucket_count;
                _size = 0;
                _buckets = new HashNode *[_bucket_count]();
                auto walk = other._head.next;
                while(walk)
                {
                    insert(walk->val);
                    walk = walk->next;
                }
             //   _head = other._head;
                // for loop
            }
        }

        UnorderedMap &operator=(UnorderedMap &&other)
        {
            /* TODO */
            if( this != &other)
            {
                clear();
                delete [] _buckets;
                _bucket_count = other._bucket_count;
                _buckets = new HashNode *[_bucket_count]();
             //   _buckets = new HashNode *[_bucket_count](); // reassign pointers
                _size = other._size;
                _head.next = other._head.next;
                _buckets = other._buckets; 
                if(other._head.next)
                {
                    // take the other head pointer and point it to our head
                    // take position that points to the head of the hashnode and saying its the addy of head
                    _buckets[_bucket(_head.next->val.first)] = &_head;
                }
                other._buckets = new HashNode *[other._bucket_count](); // calls default
                other._size = 0;
                other._head.next = nullptr;
                other._hash = Hash{};
                other._equal = key_equal{};
             }
             return *this;

             }

        void clear() noexcept
        {
            iterator begin = this->begin();
            while(_size > 0) 
            {
                erase(begin);
                begin++;
            }
        }

        size_type size() const noexcept
        {
            return this->_size; /* done */
        }

        bool empty() const noexcept { return (this->_size == 0); /* TODO */ }

        size_type bucket_count() const noexcept
        { /* Done */
            return _bucket_count;
        }

        iterator begin()
        {
            // explicit iterator(HashNode *ptr) noexcept : _node(ptr)
            return iterator(_head.next);
            /* done */
        }

        iterator end()
        {
            return iterator(nullptr);

         /* done */ }

        local_iterator begin(size_type n)
        {
    
            local_iterator box(this,this->_bucket_begin(n), n);
            return box;

            /* done */
        }

        local_iterator end(size_type n)
        { /* done */
            local_iterator box(this, nullptr, n);
            return box;
        }

        size_type bucket_size(size_type n)
        {   /* done */
            // requires insert to test
            auto walk = begin(n);
            size_t count = 0;
            while ( walk != end(n) )
            {
                count++;
                walk++;
            }
            return count;
        }

        float load_factor() const
        {
            return (float) this->_size / this->_bucket_count;
        }

        size_type bucket(const Key &key) const
        { /* done */
            return _hash(key) % _bucket_count;
        }

        std::pair<iterator, bool> insert(const value_type &value)
        {
            /* TODO */
            std::pair<iterator, bool> insertPair;
            // we hope this gets the keyValue out of the _hash()
            // size_t key = bucket (value.first);
            size_t index = _bucket(_hash(value.first));
            HashNode *findPrev = _find_prev(value.first);

            if (findPrev != nullptr)
            {
                insertPair.second = false;
                insertPair.first = iterator(findPrev->next);
            }
            else
            {
                HashNode *NewNode = new HashNode{value};
                _insert_before(index, NewNode);
                insertPair.second = true;
                insertPair.first = iterator(NewNode);
            }
            return insertPair;


        }

        std::pair<iterator, bool> insert(value_type &&value)
        {
            /* TODO */
            std::pair<iterator, bool> insertPair;
            // we hope this gets the keyValue out of the _hash()
            // size_t key = bucket (value.first);
            size_t index = std::move(_bucket(_hash(value.first)));
            HashNode *findPrev = _find_prev(value.first);

            if (findPrev != nullptr)
            {
                insertPair.second = false;
                insertPair.first = iterator(findPrev->next);
            }
            else
            {
                HashNode *NewNode = new HashNode{std::move(value)};
                _insert_before(index, NewNode);
                insertPair.second = true;
                insertPair.first = iterator(NewNode);
            }
            return insertPair;
        }

        iterator find(const Key &key)
        {
            /* TODO */
            iterator walk = begin();

            while (walk != end())
            {
                bool equalsKey = _equal(walk._node->val.first,key);
                if (equalsKey)
                {
                    return walk;
                }
                walk++;
            }
            return end();
        }

        T &operator[](const Key &key)
        {
            /* TODO */
            auto checkExist = _find_prev(key);
            if (checkExist == nullptr)
            { 
                auto box = std::make_pair(key, mapped_type{});
                iterator temp = insert(box).first;

                return temp->second;
            }
            else
            {
                return checkExist->next->val.second;
            }

        }

        iterator erase(iterator pos)
        {
            /* TODO */
        if(pos != end())
            {
            iterator posReturn = pos;
            posReturn++;
            HashNode* prev =  _find_prev(pos._node->val.first);
            _erase_after(prev);
            return posReturn;
            }
        else{
            return pos;
            }
        }

        size_type erase(const Key &key)
        {
            /* TODO */
            iterator ComeToDaddy = find(key);
            if(ComeToDaddy != end())
            {
                erase(ComeToDaddy);
                return 1;
            }
            else
            {
                return 0;
            }

        }

        template <typename KK, typename VV>
        friend void print_map(const UnorderedMap<KK, VV> &map, std::ostream &os);
};

template <typename K, typename V>
void print_map(const UnorderedMap<K, V> &map, std::ostream &os = std::cout)
{
    using size_type = typename UnorderedMap<K, V>::size_type;
    using HashNode = typename UnorderedMap<K, V>::HashNode;

    HashNode const *node = map._head.next;
    os << "List: ";
    do
    {
        if (node)
        {
            os << "(" << node->val.first << ", " << node->val.second << ") ";
        }
        else
        {
            os << "(nullptr)";
            break;
        }

        node = node->next;
    } while (true);
    os << std::endl;

    for (size_type bucket = 0; bucket < map.bucket_count(); bucket++)
    {
        os << bucket << ": ";

        HashNode const *node = map._buckets[bucket];

        if (!node)
        {
            os << "(nullptr)";
        }
        else
        {
            while ((node = node->next) && map.bucket(node->val.first) == bucket)
            {
                os << "(" << node->val.first << ", " << node->val.second << ") ";
            }
        }
        os << std::endl;
    }
}