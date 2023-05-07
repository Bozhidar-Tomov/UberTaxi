#include "VectorString.h"

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

VectorString::VectorString() : VectorString(DEFAULT_CAPACITY)
{
}

VectorString::VectorString(size_t capacity)
{
    _capacity = closestPowerOfAwo(capacity);
    _data = new MyString[_capacity];
}

VectorString::VectorString(const VectorString &other)
{
    copyFrom(other);
}

VectorString::VectorString(VectorString &&other) noexcept
{
    moveFrom(std::move(other));
}

VectorString &VectorString::operator=(const VectorString &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }
    return *this;
}

VectorString &VectorString::operator=(VectorString &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
    }
    return *this;
}

void VectorString::push_back(const MyString &element)
{
    if (_size >= _capacity)
    {
        _capacity <<= 1;
        resize();
    }

    _data[_size++] = element;
}

void VectorString::pop_back()
{
    if (_size)
    {
        _data[--_size].~MyString();
    }
}

bool VectorString::empty() const noexcept
{
    return !_size;
}

MyString &VectorString::operator[](size_t n)
{
    return _data[n];
}

const MyString &VectorString::operator[](size_t n) const
{
    return _data[n];
}

MyString &VectorString::at(size_t n)
{
    if (n >= _size)
        throw std::out_of_range("Index out of range.");

    return _data[n];
}

const MyString &VectorString::at(size_t n) const
{
    if (n >= _size)
        throw std::out_of_range("Index out of range.");

    return _data[n];
}

void VectorString::free() noexcept
{
    delete[] _data;
}

void VectorString::copyFrom(const VectorString &other)
{
    copyData(other._data);
    _size = other._size;
    _capacity = other._capacity;
}

void VectorString::copyData(const MyString *otherData)
{
    if (!_data || !otherData)
        return;

    _data = new MyString[_capacity];

    for (size_t i = 0; i < _size; ++i)
    {
        _data[i] = otherData[i];
    }
}

void VectorString::moveFrom(VectorString &&other) noexcept
{
    _data = other._data;
    other._data = nullptr;

    _size = other._size;
    other._size = 0;

    _capacity = other._capacity;
    other._capacity = 0;
}

VectorString::~VectorString() noexcept
{
    free();
}

void VectorString::resize()
{
    MyString *temp = _data;

    _data = new MyString[_capacity];

    for (size_t i = 0; i < _size; ++i)
        _data[i] = temp[i];

    delete[] temp;
}
