#pragma once
#include <stddef.h>

template <typename T>
class SharedPtr
{
    T *_ptr = nullptr;
    size_t *_refCount = nullptr;

public:
    SharedPtr() = default;
    explicit SharedPtr(T *ptr);

    SharedPtr(const SharedPtr<T> &);
    SharedPtr &operator=(const SharedPtr<T> &);

    SharedPtr(SharedPtr<T> &&) noexcept;
    SharedPtr &operator=(SharedPtr<T> &&) noexcept;

    ~SharedPtr() noexcept;

    T &operator*() const noexcept;
    T *operator->() const noexcept;

    size_t use_count() const noexcept;
    bool unique() const noexcept;
    explicit operator bool() const noexcept;

    void reset(T *ptr = nullptr) noexcept;
    void swap(SharedPtr<T> &) noexcept;

private:
    void copyFrom(const SharedPtr<T> &);
    void moveFrom(SharedPtr<T> &&) noexcept;
    void free() noexcept;
};

template <typename T>
inline SharedPtr<T>::SharedPtr(T *ptr)
    : _ptr(ptr), _refCount(new size_t(1)) {}

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
inline SharedPtr<T>::SharedPtr(SharedPtr<T> &&other) noexcept
{
    moveFrom(std::move(other));
}

template <typename T>
inline SharedPtr<T> &SharedPtr<T>::operator=(SharedPtr<T> &&other) noexcept
{
    if (this != &other)
    {
        free();
        moveFrom(std::move(other));
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
    return *_ptr;
}

template <typename T>
inline T *SharedPtr<T>::operator->() const noexcept
{
    return _ptr;
}

template <typename T>
inline size_t SharedPtr<T>::use_count() const noexcept
{
    return *_refCount;
}

template <typename T>
inline bool SharedPtr<T>::unique() const noexcept
{
    return *_refCount == 1;
}

template <typename T>
inline SharedPtr<T>::operator bool() const noexcept
{
    return (bool)(_ptr);
}

template <typename T>
inline void SharedPtr<T>::reset(T *ptr) noexcept
{
    SharedPtr(ptr).swap(*this);
}

template <typename T>
inline void SharedPtr<T>::swap(SharedPtr<T> &other) noexcept
{
    T *tempPtr = _ptr;
    size_t *tempRefCount = _refCount;

    _ptr = other._ptr;
    _refCount = other._refCount;

    other._ptr = tempPtr;
    other._refCount = tempRefCount;
}

template <typename T>
inline void SharedPtr<T>::copyFrom(const SharedPtr &other)
{
    _ptr = other._ptr;
    _refCount = other._refCount;
    ++(*_refCount);
}

template <typename T>
inline void SharedPtr<T>::moveFrom(SharedPtr<T> &&other) noexcept
{
    _ptr = other._ptr;
    other._ptr = nullptr;

    _refCount = other._refCount;
    other._refCount = nullptr;
}

template <typename T>
inline void SharedPtr<T>::free() noexcept
{
    if (!_refCount)
        return;

    if (--(*_refCount) == 0)
    {
        delete _ptr;
        delete _refCount;
    }
}
