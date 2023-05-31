#pragma once
#include "MyVector.h"

namespace
{
    size_t closestPowerOfTwo(size_t n)
    {
        --n;
        n |= n >> 1;
        n |= n >> 2;
        n |= n >> 4;
        n |= n >> 8;
        n |= n >> 16;
        n |= n >> 32;
        return n + 1;
    }
}

template <typename T>
inline MyVector<T>::MyVector()
    : MyVector(VECTOR_DEFAULT_CAPACITY)
{
}

template <typename T>
inline MyVector<T>::MyVector(size_t capacity)
{
    _capacity = closestPowerOfTwo(capacity);
    _data = (T *)(operator new[](_capacity * sizeof(T)));
}

template <typename T>
inline MyVector<T>::MyVector(const MyVector &other)
{
    copyFrom(other);
}

template <typename T>
inline MyVector<T>::MyVector(MyVector &&other) noexcept
{
    moveFrom(std::move(other));
}

template <typename T>
inline MyVector<T> &MyVector<T>::operator=(const MyVector<T> &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

template <typename T>
inline MyVector<T> &MyVector<T>::operator=(MyVector<T> &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(other);
    }
    return *this;
}

template <typename T>
inline MyVector<T>::~MyVector() noexcept
{
    free();
}

template <typename T>
inline void MyVector<T>::push_back(const T &element)
{
    if (_size == _capacity)
        reserve();

    new (_data + _size) T(element);
    ++_size;
}

template <typename T>
inline void MyVector<T>::push_back(T &&element)
{
    if (_size == _capacity)
        reserve();

    new (_data + _size) T(std::move(element));
    ++_size;
}

template <typename T>
inline void MyVector<T>::push_at(const T &element, size_t idx)
{
    if (empty() || idx > _size - 1)
        throw std::invalid_argument("Invalid index.");

    if (_size == _capacity)
        reserve();

    for (size_t i = _size; i > idx; --i)
        new (_data + i) T(std::move(_data[i - 1]));

    new (_data + idx) T(element);
    ++_size;
}

template <typename T>
inline void MyVector<T>::push_at(T &&element, size_t idx)
{
    if (empty() || idx > _size - 1)
        throw std::invalid_argument("Invalid index.");

    if (_size == _capacity)
        reserve();

    for (size_t i = _size; i > idx; --i)
        new (_data + i) T(std::move(_data[i - 1]));

    new (_data + idx) T(std::move(element));
    ++_size;
}

template <typename T>
inline void MyVector<T>::pop_back()
{
    if (empty())
        throw std::range_error("Container is empty");

    --_size;
}

template <typename T>
inline void MyVector<T>::pop_at(size_t idx)
{
    if (empty() || idx > _size - 1)
        throw std::invalid_argument("Invalid index.");

    for (size_t i = idx; i < _size - 2; ++i)
        new (_data + i) T(std::move(_data[i + 1]));

    --_size;
}

template <typename T>
inline const T &MyVector<T>::back() const
{
    if (empty())
        throw std::range_error("Container is empty");
    return _data[_size - 1];
}

template <typename T>
inline T &MyVector<T>::back()
{
    if (empty())
        throw std::range_error("Container is empty");
    return _data[_size - 1];
}

template <typename T>
inline size_t MyVector<T>::size() const noexcept
{
    return _size;
}

template <typename T>
inline size_t MyVector<T>::capacity() const noexcept
{
    return _capacity;
}

template <typename T>
inline void MyVector<T>::resize(size_t newSize)
{
    if (newSize > _capacity)
        reserve(newSize);

    _size = newSize;
}

template <typename T>
inline bool MyVector<T>::empty() const noexcept
{
    return !_size;
}

template <typename T>
inline void MyVector<T>::clear() noexcept
{
    free();
    _size = 0;
    _capacity = VECTOR_DEFAULT_CAPACITY;
    _data = (T *)(operator new[](_capacity * sizeof(T)));
}

template <typename T>
inline void MyVector<T>::swap(size_t i, size_t j)
{
    T temp = at(i);
    at(i) = at(j);
    at(j) = temp;
}

template <typename T>
inline T &MyVector<T>::operator[](size_t n)
{
    return _data[n];
}

template <typename T>
inline const T &MyVector<T>::operator[](size_t n) const
{
    return _data[n];
}

template <typename T>
inline T &MyVector<T>::at(size_t n)
{
    if (n >= _size)
        throw std::out_of_range("Index out of range.");

    return _data[n];
}

template <typename T>
inline const T &MyVector<T>::at(size_t n) const
{
    if (n >= _size)
        throw std::out_of_range("Index out of range.");

    return _data[n];
}

template <typename T>
inline T *MyVector<T>::data() const noexcept
{
    return _data;
}

template <typename T>
inline T *MyVector<T>::operator*() const noexcept
{
    return _data;
}

template <typename T>
inline std::ostream &operator<<(std::ostream &out, const MyVector<T> &obj)
{
    out << '[';
    for (size_t i = 0; i < obj._size; ++i)
    {
        out << obj._data[i];
        if (i != obj._size - 1)
            out << ", ";
    }
    out << ']';
    return out;
}

template <typename T>
inline void MyVector<T>::free() noexcept
{
    for (size_t i = 0; i < _size; ++i)
        _data[i].~T();

    operator delete[](_data);
    _data = nullptr;
}

template <typename T>
inline void MyVector<T>::copyFrom(const MyVector &other)
{
    _data = (T *)(operator new[](other._capacity * sizeof(T)));
    for (size_t i = 0; i < other._size; ++i)
        new (_data + i) T(other._data[i]);

    _size = other._size;
    _capacity = other._capacity;
}

template <typename T>
inline void MyVector<T>::moveFrom(MyVector &&other) noexcept
{
    _data = other._data;
    other._data = nullptr;

    _size = other._size;
    other._size = 0;

    _capacity = other._capacity;
    other._capacity = 0;
}

template <typename T>
inline void MyVector<T>::reserve(size_t newCapacity)
{
    if (!newCapacity)
        _capacity *= 2;
    else
        closestPowerOfTwo(newCapacity);

    T *newData = (T *)(operator new[](_capacity * sizeof(T)));

    for (size_t i = 0; i < _size; ++i)
    {
        // move each object from the old array to the new one
        new (newData + i) T(std::move(_data[i]));

        // delete each object from the old array by calling the destructor in case of when T does not have move semantics
        _data[i].~T();
    }

    operator delete[](_data);
    _data = newData;
}