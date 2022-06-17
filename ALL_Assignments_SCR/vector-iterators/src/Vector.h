#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm> // std::random_access_iterator_tag
#include <cstddef>   // size_t
#include <stdexcept> // std::range_error
#include <sstream>

template <class T>
class Vector
{
public:
    class iterator;

private:
    T *array;
    size_t _capacity, _size;

    // You may want to write a function that grows the vector
    void grow()
    {
        if (_capacity == 0)
        {
            _capacity = 1;
        }
        else
        {
            _capacity *= 2;
        }
        T *temp1243 = new T[_capacity];
        for (int i = 0; i < _size; ++i)
        {
            temp1243[i] = std::move(array[i]);
        }
        delete[] array;
        array = temp1243;
    }

public:
    Vector() noexcept : array(nullptr), _capacity(0), _size(0)
    {
    }

    Vector(size_t count, const T &value) : array(new T[count]), _capacity(count), _size(count)
    {
        for (size_t index = 0; index < _size; index++)
        {
            array[index] = value;
        }
    }

    explicit Vector(size_t count) : array(new T[count]), _capacity(count), _size(count)
    {
        for (size_t index = 0; index < count; index++)
        {
            // default constructor allows it to sens the class
            array[index] = T();
        }
    }

    Vector(const Vector &other) : array(new T[other._capacity]), _capacity(other._capacity), _size(other._size)
    {
        for (size_t index = 0; index < other._size; index++)
        {
            array[index] = other.array[index];
        }
    }

    Vector(Vector &&other) noexcept : array(nullptr), _size(other._size), _capacity(other._capacity)
    {

        array = other.array;
        // call it to be empty
        other.array = nullptr;
        other._capacity = 0;
        other._size = 0;
    }

    ~Vector()
    {
        delete[] array;
    }
    // this one is not the empty one

    Vector &operator=(const Vector &other)
    {
        if (_capacity != other._capacity)
        {
            if (array != nullptr)
            {
                delete[] array; // make sure there is nothing outside of forloop
            }

            array = new T[other._capacity];
        }

        for (int index = 0; index < other._size; index++)
        {
            array[index] = other[index];
        }
        _size = other._size;
        _capacity = other._capacity;
        return *this;
    }
    // move
    Vector &operator=(Vector &&other) noexcept
    {
        // this here is a reference to a vector on the lhs side of the equation
        _size = other._size;
        _capacity = other._capacity;
        if (array != other.array)
        {
            delete[] array;
            array = other.array;

            other._size = 0;
            other._capacity = 0;
            other.array = nullptr;
        }
        return *this;
    }

    iterator begin() noexcept
    {
        iterator Pain(array);
        return Pain;
    }
    iterator end() noexcept
    {
        iterator Pain(array + _size);
        return Pain;
    }

    [[nodiscard]] bool empty() const noexcept
    {
        // potential error here in the operator = and in the copy deconstructor you never set other's capactity/ size to 1/0 this could cause a error but likely wont
        return (_size == 0);
    }
    size_t size() const noexcept
    {
        return _size;
    }
    size_t capacity() const noexcept
    {
        return _capacity;
    }

    T &at(size_t pos)
    {
        if (pos >= _size)
        {
            std::stringstream s("");
            s << "Out of range position is, ";
            s << pos;
            s << " array is ";
            s << _size;
            s << " 165 T& ";

            throw std::out_of_range(s.str());
        }
        return array[pos];
    }
    const T &at(size_t pos) const
    {
        if (pos >= _size)
        {
            std::stringstream s("");
            s << "Out of range position is, ";
            s << pos;
            s << " array is ";
            s << _size;
            s << " 180 T& ";

            throw std::out_of_range(s.str());
        }
        return array[pos];
    }
    T &operator[](size_t pos) { return array[pos]; }

    const T &operator[](size_t pos) const { return array[pos]; }

    T &front()
    {
        return array[0];
    }
    const T &front() const
    {
        return array[0];
    }
    T &back()
    {
        return array[_size - 1];
    }
    const T &back() const
    {
        return array[_size - 1];
    }

    void push_back(const T &value)
    {
        while (_size >= _capacity)
        {
            grow();
        }
        array[_size] = value;
        _size++;
    }

    void push_back(T &&value)
    {
        while (_size >= _capacity)
        {
            grow();
        }
        array[_size] = std::move(value);
        _size++;
    }

    void pop_back()
    {
        _size--;
    }

    iterator insert(iterator pos, const T &value)
    {

        ptrdiff_t index = (pos - this->begin()); // / sizeof(T);

        if (_size+1 >= _capacity)
        {
            grow();
        }

        for (ptrdiff_t i = _size; i != index; i--)
        {
            array[i] = std::move(array[i - 1]);
        }

        array[index] = value;
        _size++;
        return begin() + index;
    }
    iterator insert(iterator pos, T &&value)
    {
        ptrdiff_t index = (pos - this->begin()); // / sizeof(T);
        std::cout<<_size << std::endl;
        std::cout<<_capacity << std::endl;
        if (_size+1 >= _capacity)
        {
            grow();
        }

        for (ptrdiff_t i = static_cast<ptrdiff_t>(_size); i != index; i--)
        {
            array[i] = std::move(array[i - 1]);
        }

        array[index] = std::move(value);
        _size++;
        return begin() + index;
    }
    iterator insert(iterator pos, size_t count, const T &value)
    {
     //   using namespace std;
     //   cout << "before insert:\n";
        // for (auto i = 0; i < this->_capacity; i++)
        //     cout << "i: " << i << ", arr[i]:" << array[i] << endl;

        ptrdiff_t index = (pos - this->begin()); // / sizeof(T);

        //    std::cout <<"array " << array << endl;

        while (_size + count > _capacity)
        {
            grow();
        }

        for (ptrdiff_t i = _size + count-1; i > index+count-1; i--)
        {
            array[i] = std::move(array[i - count]);

        }
        //      cout << "running " << endl;

        for (size_t i = 0; i < count; i++)
        {

            array[i + index] = value;
 
        }

        _size += count;

        return begin() + index;
    }
    iterator erase(iterator pos)
    {
        ptrdiff_t index = (pos - this->begin()); // / sizeof(T);
        iterator copy(pos);
        for (ptrdiff_t i = index; i != _size - 1; i++)
        {
            array[i] = std::move(array[i + 1]);
        }
        _size--;

        return copy;
    }
    iterator erase(iterator first, iterator last)
    {
        size_t SizeChange = last - first;
        ptrdiff_t index = (first - this->begin()); // / sizeof(T);
        ptrdiff_t indexEND = (last - this->begin());
        std::cout  << _size <<std::endl;

    //    std::cout  << _capacity <<std::endl;


        for (ptrdiff_t i = index; i != _size - SizeChange; i++)
        {
            array[i] = std::move(array[indexEND]);
            indexEND++;
        }

        _size -= SizeChange;
        return first;
    }

    class iterator
    {
    public:
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using difference_type = ptrdiff_t;
        using pointer = T *;
        using reference = T &;

    private:
        // Add your own data members here
        // HINT: For random_access_iterator, the data member is a pointer 99.9% of the time
        T *ptr;

    public:
        // iterator(const iterator &constructme) = default;
        // Add any constructors that you may need
        iterator() : ptr(nullptr)
        {
        }
        iterator(T *ptr) : ptr(ptr)
        {
        }
        T *point() { return ptr; }
        // This assignment operator is done for you, please do not add more
        iterator &operator=(const iterator &) noexcept = default;

        [[nodiscard]] reference operator*() const noexcept
        {
            return *(this->ptr);
        }
        [[nodiscard]] pointer operator->() const noexcept
        {
            return (this->ptr);
        }

        // Prefix Increment: ++a
        iterator &operator++() noexcept
        {
            ptr++; // TODO: what if we go beyond the vector?
            return *this;
        }
        // Postfix Increment: a++
        iterator operator++(int) noexcept
        {
            iterator old(ptr);
            ptr++; // TODO: what if we go beyond the vector?
            return old;
        }
        // Prefix Decrement: --a
        iterator &operator--() noexcept
        {
            ptr--; // TODO: what if we go beyond the vector
            return *this;
        }
        // Postfix Decrement: a--
        iterator operator--(int) noexcept
        {
            iterator old(ptr);
            ptr--; // TODO: what if we go beyond the vector?
            return old;
        }
        iterator &operator+=(difference_type offset) noexcept
        {
            this->ptr = this->ptr + offset;
            return *(this);
        }
        [[nodiscard]] iterator operator+(difference_type offset) const noexcept
        {
            iterator temp(this->ptr);
            temp.ptr = (temp.ptr) + offset;
            // esentiallialy I make a copy of the position the  define temp to be teh cahnge in positions of offset.
            return temp;
        }
        iterator &operator-=(difference_type offset) noexcept
        {
            this->ptr = this->ptr - offset;
            return *(this);
        }
        [[nodiscard]] iterator operator-(difference_type offset) const noexcept
        {
            iterator temp(this->ptr);
            temp.ptr = temp.ptr - offset;
            // esentiallialy I make a copy of the position the  define temp to be teh cahnge in positions of offset.
            return temp;
        }
        [[nodiscard]] difference_type operator-(const iterator &rhs) const noexcept
        {
            return (this->ptr - (rhs.ptr));
        }

        [[nodiscard]] reference operator[](difference_type offset) const noexcept
        {
            // return this as a unpacked box
            return *(this->ptr + offset);
        }

        [[nodiscard]] bool operator==(const iterator &rhs) const noexcept
        { // this is suspisous
            // check this
            // is the memory address the same NT is the value the same
            if ((this->ptr) == (rhs.ptr))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        [[nodiscard]] bool operator!=(const iterator &rhs) const noexcept
        {
            if ((this->ptr) == (rhs.ptr))
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        [[nodiscard]] bool operator<(const iterator &rhs) const noexcept
        {
            if ((this->ptr) < (rhs.ptr))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        [[nodiscard]] bool operator>(const iterator &rhs) const noexcept
        {
            if ((this->ptr) > (rhs.ptr))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        [[nodiscard]] bool operator<=(const iterator &rhs) const noexcept
        {
            if ((this->ptr) <= (rhs.ptr))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        [[nodiscard]] bool operator>=(const iterator &rhs) const noexcept
        {
            if ((this->ptr) >= (rhs.ptr))
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    };

    void clear() noexcept
    {
        _size = 0;
        T *array = new T[_capacity];
    }
};

template <class T>
[[nodiscard]] typename Vector<T>::iterator operator+(typename Vector<T>::iterator::difference_type offset, typename Vector<T>::iterator iterator) noexcept
{
    return offset + iterator;
}

#endif
