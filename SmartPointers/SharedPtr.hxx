#pragma once
#include <stddef.h>
#include <stdexcept>

template <typename T>
class SharedPtr
{
private:
    struct Counter
    {
        size_t useCount = 0;
        size_t weakCount = 0;
        Counter() : useCount(0), weakCount(0){};
        Counter(const Counter &) = delete;
        Counter &operator=(const Counter &) = delete;

        void removeSharedPtr()
        {
            --useCount;
            if (useCount == 0)
                --weakCount;
        }
        void removeWeakPtr()
        {
            --weakCount;
        }

        void addSharedPtr()
        {
            ++useCount;
            if (useCount == 1)
                ++weakCount;
        }

        void addWeakPtr()
        {
            ++weakCount;
        }
    };

private:
    T *_ptr = nullptr;
    Counter *counter = nullptr;

public:
    SharedPtr();
    explicit SharedPtr(T *ptr);

    SharedPtr(const SharedPtr<T> &);
    SharedPtr &operator=(const SharedPtr<T> &);

    SharedPtr(SharedPtr<T> &&) noexcept;
    SharedPtr &operator=(SharedPtr<T> &&) noexcept;

    ~SharedPtr() noexcept;

    T &operator*();
    const T &operator*() const;
    T *operator->() const noexcept;
    T *get() const noexcept;

    size_t use_count() const noexcept;
    bool unique() const noexcept;
    explicit operator bool() const noexcept;

    void reset() noexcept;
    void reset(T *ptr);
    void swap(SharedPtr<T> &) noexcept;

private:
    void copyFrom(const SharedPtr<T> &);
    void moveFrom(SharedPtr<T> &&) noexcept;
    void free() noexcept;
};

template <typename T>
SharedPtr<T>::SharedPtr() : _ptr(nullptr), counter(nullptr) {}

template <typename T>
inline SharedPtr<T>::SharedPtr(T *ptr)
{
    _ptr = ptr;
    if (_ptr)
    {
        counter = new Counter();
        counter->addSharedPtr();
    }
}

template <typename T>
inline SharedPtr<T>::SharedPtr(const SharedPtr<T> &other)
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
inline T &SharedPtr<T>::operator*()
{
    if (!_ptr)
        throw std::runtime_error("Pointer not set");
    return *_ptr;
}

template <typename T>
inline const T &SharedPtr<T>::operator*() const
{
    if (!_ptr)
        throw std::runtime_error("Pointer not set");
    return *_ptr;
}

template <typename T>
inline T *SharedPtr<T>::operator->() const noexcept
{
    return _ptr;
}

template <typename T>
inline T *SharedPtr<T>::get() const noexcept
{
    return _ptr;
}

template <typename T>
inline size_t SharedPtr<T>::use_count() const noexcept
{
    if (_ptr)
        return counter->useCount;
    return 0;
}

template <typename T>
inline bool SharedPtr<T>::unique() const noexcept
{
    return use_count() == 1;
}

template <typename T>
inline SharedPtr<T>::operator bool() const noexcept
{
    return (bool)(_ptr);
}

template <typename T>
inline void SharedPtr<T>::reset() noexcept
{
    SharedPtr<T>().swap(*this);
}

template <typename T>
inline void SharedPtr<T>::reset(T *ptr)
{
    SharedPtr<T>(ptr).swap(*this);
}

template <typename T>
inline void SharedPtr<T>::swap(SharedPtr<T> &other) noexcept
{
    T *tempPtr = _ptr;
    Counter *tempCounter = counter;

    _ptr = other._ptr;
    counter = other.counter;

    other._ptr = tempPtr;
    other.counter = tempCounter;
}

template <typename T>
inline void SharedPtr<T>::copyFrom(const SharedPtr &other)
{
    _ptr = other._ptr;
    counter = other.counter;
    if (counter)
        counter->addSharedPtr();
}

template <typename T>
inline void SharedPtr<T>::moveFrom(SharedPtr<T> &&other) noexcept
{
    _ptr = other._ptr;
    other._ptr = nullptr;

    counter = other.counter;
    other.counter = nullptr;
}

template <typename T>
inline void SharedPtr<T>::free() noexcept
{
    if (_ptr == nullptr && counter == nullptr)
        return;

    counter->removeSharedPtr();

    if (counter->useCount == 0)
        delete _ptr;

    if (counter->weakCount == 0)
        delete counter;
}
