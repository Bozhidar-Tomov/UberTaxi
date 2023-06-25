#pragma once
#include <iostream>
#include <exception>
template <typename T>
class Optional
{
    // TBI move and operator*
    T *data; // DYN MEM

    void copyFrom(const Optional<T> &other);
    void free();

public:
    Optional();
    Optional(const T &obj);

    Optional(const Optional<T> &other);
    Optional<T> &operator=(const Optional<T> &other);

    explicit operator bool() const noexcept;

    bool containsData() const;
    const T &getData() const;
    void setData(const T &el);
    void clear();
};

#include "Optional.hxx"