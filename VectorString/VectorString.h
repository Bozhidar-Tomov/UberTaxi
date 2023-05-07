#include "../MyString/MyString.h"

static const size_t DEFAULT_CAPACITY_VECTOR = 8;

class VectorString
{
    MyString *_data = nullptr;
    size_t _size = 0;
    size_t _capacity = DEFAULT_CAPACITY_VECTOR;

public:
    VectorString();
    VectorString(size_t);

    VectorString(const VectorString &);
    VectorString(VectorString &&) noexcept;

    VectorString &operator=(const VectorString &);
    VectorString &operator=(VectorString &&) noexcept;

    ~VectorString() noexcept;

public:
    void push_back(const MyString &);
    void pop_back();

    bool empty() const noexcept;

    // Element access:
    MyString &operator[](size_t);
    const MyString &operator[](size_t) const;

    MyString &at(size_t);
    const MyString &at(size_t) const;

private:
    void free() noexcept;
    void copyFrom(const VectorString &);
    void copyData(const MyString *);
    void moveFrom(VectorString &&) noexcept;

    void resize();
};