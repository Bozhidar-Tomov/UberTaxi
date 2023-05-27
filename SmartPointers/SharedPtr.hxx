#pragma once
#include <stddef.h>

template <typename T>
class SharedPtr
{
    T *_data = nullptr;
    size_t *_refCount = 0;

public:
    explicit SharedPtr(T *data);

    SharedPtr(const SharedPtr<T> &);
    SharedPtr &operator=(const SharedPtr<T> &);

    ~SharedPtr() noexcept;

    T &operator*() const noexcept;
    T *operator->() const noexcept;

private:
    void copyFrom(const SharedPtr<T> &);
    void free() noexcept;
};

template <typename T>
inline SharedPtr<T>::SharedPtr(T *data)
    : _data(data), _refCount(new size_t(1)) {}

template <typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr &other)
{
    copyFrom(other);
}

template <typename T>
inline SharedPtr<T> &SharedPtr<T>::operator=(const SharedPtr<T> &other)
{
    if (this != &other)
    {
        free();
        copyFrom(other);
    }

    return *this;
}

template <typename T>
inline SharedPtr<T>::~SharedPtr() noexcept
{
    free();
}

template <typename T>
inline T &SharedPtr<T>::operator*() const noexcept
{
    return *_data;
}

template <typename T>
inline T *SharedPtr<T>::operator->() const noexcept
{
    return _data;
}

template <typename T>
inline void SharedPtr<T>::copyFrom(const SharedPtr &other)
{
    _data = other._data;
    _refCount = other._refCount;
    ++(*_refCount);
}

template <typename T>
inline void SharedPtr<T>::free() noexcept
{
    --(*_refCount);

    if (!(*_refCount))
    {
        delete _data;
        delete _refCount;
    }
}
