#pragma once

static const size_t DEFAULT_CAPACITY_VECTOR = 8;

template <typename Type>
class MyVector
{
    Type *_data = nullptr;
    size_t _size = 0;
    size_t _capacity = DEFAULT_CAPACITY_VECTOR;

public:
    MyVector();
    MyVector(size_t);

    MyVector(const MyVector &);
    MyVector(MyVector &&) noexcept;

    MyVector &operator=(const MyVector &);
    MyVector &operator=(MyVector &&) noexcept;

    ~MyVector() noexcept;

public:
    void push_back(const Type &);
    void pop_back();

    size_t size() const noexcept;
    size_t capacity() const noexcept;
    bool empty() const noexcept;

    // Element access:
    Type &operator[](size_t);
    const Type &operator[](size_t) const;

    Type &at(size_t);
    const Type &at(size_t) const;

private:
    void free() noexcept;
    void copyFrom(const MyVector &);
    void copyData(const Type *);
    void moveFrom(MyVector &&) noexcept;

    void resize();
};

#include "MyVector.hxx"