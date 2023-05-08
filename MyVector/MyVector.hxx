#pragma once

static size_t closestPowerOfAwo(size_t n)
{
    n--;
    n |= n >> 1;
    n |= n >> 2;
    n |= n >> 4;
    n |= n >> 8;
    n |= n >> 16;
    n |= n >> 32;
    return n + 1;
}

template <typename Type>
MyVector<Type>::MyVector() : MyVector(DEFAULT_CAPACITY_VECTOR)
{
}

template <typename Type>
MyVector<Type>::MyVector(size_t capacity)
{
    _capacity = closestPowerOfAwo(capacity);
    _data = new Type[_capacity];
}

template <typename Type>
MyVector<Type>::MyVector(const MyVector &other)
{
    copyFrom(other);
}

template <typename Type>
MyVector<Type>::MyVector(MyVector &&other) noexcept
{
    moveFrom(std::move(other));
}

template <typename Type>
MyVector<Type> &MyVector<Type>::operator=(const MyVector<Type> &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename Type>
MyVector<Type> &MyVector<Type>::operator=(MyVector<Type> &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

template <typename Type>
MyVector<Type>::~MyVector() noexcept
{
    free();
}

template <typename Type>
void MyVector<Type>::push_back(const Type &element)
{
    if (_size >= _capacity)
    {
        _capacity <<= 1;
        resize();
    }

    _data[_size++] = element;
}

template <typename Type>
void MyVector<Type>::pop_back()
{
    if (_size)
    {
        _data[--_size].~Type();
    }
}

template <typename Type>
size_t MyVector<Type>::size() const noexcept
{
    return _size;
}

template <typename Type>
size_t MyVector<Type>::capacity() const noexcept
{
    return _capacity;
}

template <typename Type>
bool MyVector<Type>::empty() const noexcept
{
    return !_size;
}

// Element access:
template <typename Type>
Type &MyVector<Type>::operator[](size_t n)
{
    return _data[n];
}

template <typename Type>
const Type &MyVector<Type>::operator[](size_t n) const
{
    return _data[n];
}

template <typename Type>
Type &MyVector<Type>::at(size_t n)
{
    if (n >= _size)
        throw std::out_of_range("Index out of range.");

    return _data[n];
}

template <typename Type>
const Type &MyVector<Type>::at(size_t n) const
{
    if (n >= _size)
        throw std::out_of_range("Index out of range.");

    return _data[n];
}

template <typename Type>
void MyVector<Type>::free() noexcept
{
    delete[] _data;
}

template <typename Type>
void MyVector<Type>::copyFrom(const MyVector &other)
{
    copyData(other._data);
    _size = other._size;
    _capacity = other._capacity;
}

template <typename Type>
void MyVector<Type>::copyData(const Type *otherData)
{
    if (!_data || !otherData)
        return;

    _data = new Type[_capacity];

    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = otherData[i];
    }
}

template <typename Type>
void MyVector<Type>::moveFrom(MyVector &&other) noexcept
{
    _data = other._data;
    other._data = nullptr;

    _size = other._size;
    other._size = 0;

    _capacity = other._capacity;
    other._capacity = 0;
}

template <typename Type>
void MyVector<Type>::resize()
{
    Type *temp = _data;

    _data = new Type[_capacity];

    for (size_t i = 0; i < _size; ++i)
        _data[i] = temp[i];

    delete[] temp;
}
