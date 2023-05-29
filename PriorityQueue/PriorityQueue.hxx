#pragma once
#include "PriorityQueue.h"

template <typename T, PQueueType _T>
inline void PriorityQueue<T, _T>::push(const T &elem, double priority)
{
    if (priority > _maxPriority)
        throw std::invalid_argument("Invalid priority value passed.");

    pushOperation(Element(elem, priority));
}

template <typename T, PQueueType _T>
inline void PriorityQueue<T, _T>::push(T &&elem, double priority)
{
    if (priority > _maxPriority)
        throw std::invalid_argument("Invalid priority value passed.");

    pushOperation(Element(std::move(elem), priority));
}

template <typename T, PQueueType _T>
inline void PriorityQueue<T, _T>::pop()
{
    if (empty())
        throw std::domain_error("Priority queue is empty.");
    _elements.pop_back();
}

template <typename T, PQueueType _T>
inline const T &PriorityQueue<T, _T>::peek() const noexcept
{
    return _elements.back()._value;
}

template <typename T, PQueueType _T>
inline bool PriorityQueue<T, _T>::empty() const noexcept
{
    return _elements.empty();
}

template <typename T, PQueueType _T>
inline size_t PriorityQueue<T, _T>::size() const noexcept
{
    return _elements.size();
}

template <typename T, PQueueType _T>
inline void PriorityQueue<T, _T>::pushOperation(Element &&newElem)
{
    if (_elements.empty())
    {
        _elements.push_back(std::move(newElem));
        return;
    }

    size_t idx = binarySearch(newElem);

    if (idx == SIZE_MAX)
    {
        idx = 0;
        if (_type == PQueueType::Descending)
            while (idx < _elements.size() && _elements[idx] < newElem)
                ++idx;
        else
            while (idx < _elements.size() && _elements[idx] > newElem)
                ++idx;
    }

    _elements.push_at(std::move(newElem), idx);
}

template <typename T, PQueueType _T>
inline size_t PriorityQueue<T, _T>::binarySearch(const Element &element) const noexcept
{
    size_t low = 0;
    size_t high = _elements.size() - 1;

    while (low <= high)
    {
        size_t mid = low + (high - low) / 2;

        if (_elements[mid] == element)
        {
            while (mid != 0 && _elements[mid - 1] == element)
                --mid;

            return mid;
        }

        if (_elements[mid] < element)
            low = mid + 1;
        else
        {
            if (mid == 0)
                break;
            high = mid - 1;
        }
    }
    return SIZE_MAX;
}
