#pragma once

template <typename T>
class UniquePtr
{
    T *_ptr = nullptr;

public:
    explicit UniquePtr(T *ptr) noexcept;

    UniquePtr(const UniquePtr &) = delete;
    UniquePtr &operator=(const UniquePtr &) = delete;

    UniquePtr(UniquePtr &&) noexcept;
    UniquePtr &operator=(UniquePtr &&) noexcept;

    ~UniquePtr() noexcept;

    T *release() noexcept;
    void reset(T *ptr = nullptr) noexcept;

    explicit operator bool();
    T &operator*() const noexcept;
    T *operator->() const noexcept;
    T *get() const noexcept;
};

template <typename T>
inline UniquePtr<T>::UniquePtr(T *ptr) noexcept : _ptr(ptr) {}

template <typename T>
inline UniquePtr<T>::UniquePtr(UniquePtr<T> &&other) noexcept
    : _ptr(other.release()) {}

template <typename T>
inline UniquePtr<T> &UniquePtr<T>::operator=(UniquePtr<T> &&other) noexcept
{
    if (this != &other)
        reset(other.release());

    return *this;
}

template <typename T>
inline UniquePtr<T>::~UniquePtr() noexcept
{
    delete _ptr;
}

// Transfers ownership.
// UniquePtr is no longer responsible for memory management of the object
template <typename T>
inline T *UniquePtr<T>::release() noexcept
{
    T *temp = _ptr;
    _ptr = nullptr;
    return temp;
}

template <typename T>
inline void UniquePtr<T>::reset(T *ptr) noexcept
{
    delete _ptr;
    _ptr = ptr;
}

template <typename T>
inline UniquePtr<T>::operator bool()
{
    return (bool)(_ptr);
}

template <typename T>
inline T &UniquePtr<T>::operator*() const noexcept
{
    return *_ptr;
}

template <typename T>
inline T *UniquePtr<T>::operator->() const noexcept
{
    return _ptr;
}

template <typename T>
inline T *UniquePtr<T>::get() const noexcept
{
    return _ptr;
}
