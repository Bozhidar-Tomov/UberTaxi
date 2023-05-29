#pragma once
#include <stddef.h>
#include "../MyVector/MyVector.h"

enum class PQueueType
{
    Ascending,
    Descending,
};

// TODO: Make priority value a template.
//  As in the STL implementation, we store a copy of the objects in a vector container.
template <typename T, PQueueType _T = PQueueType::Descending>
class PriorityQueue
{
private:
    // We do not make Element members const so that we can use std::move() on Element.
    struct Element
    {
        T _value;
        double _priority = 0;

        Element(const T &value, double priority) : _value(value), _priority(priority){};
        Element(T &&value, double priority) : _value(std::move(value)), _priority(priority){};
        Element(Element &&) noexcept = default;
        ~Element() noexcept = default;

        bool operator<(const Element &rhs) const { return _priority < rhs._priority; }
        bool operator==(const Element &rhs) const { return _priority == rhs._priority; }
        bool operator>(const Element &rhs) const { return _priority > rhs._priority; }
    };

private:
    MyVector<Element> _elements;
    const double _maxPriority = 0;
    const PQueueType _type = _T;

public:
    PriorityQueue(double maxPriority) : _maxPriority(maxPriority) {}

    void push(const T &elem, double priority);
    void push(T &&elem, double priority);
    void pop();
    const T &peek() const noexcept;

    bool empty() const noexcept;
    size_t size() const noexcept;

private:
    void pushOperation(Element &&);
    size_t binarySearch(const Element &) const noexcept;
};

#include "PriorityQueue.hxx"
