#pragma once
#include <ostream>
#include <stddef.h>  // including std::size_t
#include <utility>   // including std::move
#include <stdexcept> // including std::excepton

namespace
{
    const size_t VECTOR_DEFAULT_CAPACITY = 8;
}

/*
This implementation of this template class container 'MyVector' uses placement new.
Aka. 'operator new[]()' and 'operator delete[]()'
*/
template <typename T>
class MyVector
{
    T *_data = nullptr;
    size_t _size = 0;
    size_t _capacity = VECTOR_DEFAULT_CAPACITY;

public:
    MyVector();
    MyVector(size_t);

    MyVector(const MyVector &);
    MyVector(MyVector &&) noexcept;

    MyVector &operator=(const MyVector &);
    MyVector &operator=(MyVector &&) noexcept;

    ~MyVector() noexcept;

public:
    void push_back(const T &);
    void push_back(T &&);

    void push_at(const T &, size_t);
    void push_at(T &&, size_t);

    void pop_back();
    void pop_at(size_t);
    const T &back() const;
    T &back();

    // Capacity:
    size_t size() const noexcept;
    size_t capacity() const noexcept;
    void resize(size_t);
    bool empty() const noexcept;
    void clear() noexcept;
    void swap(size_t, size_t);

    // Element access:
    T &operator[](size_t);
    const T &operator[](size_t) const;

    T &at(size_t);
    const T &at(size_t) const;

    T *data() const noexcept;
    T *operator*() const noexcept;

    size_t find(const T &) const noexcept;

    template <typename U>
    friend std::ostream &operator<<(std::ostream &, const MyVector<U> &);

private:
    void free() noexcept;
    void copyFrom(const MyVector &);
    void moveFrom(MyVector &&) noexcept;

    void reserve(size_t = 0);
};

#include "MyVector.hxx"
