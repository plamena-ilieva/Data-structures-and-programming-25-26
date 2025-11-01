#pragma once
#include <stdexcept>
#include <utility>

namespace Constants
{
    constexpr unsigned GROWTH_FACTOR = 2;
}

template <class T>
class Vector
{
public:
    Vector() = default;
    explicit Vector(size_t count);
    Vector(size_t count, const T& initial);

    Vector(const Vector& other);
    Vector& operator=(const Vector& other);

    Vector(Vector&& other) noexcept;
    Vector& operator=(Vector&& other) noexcept;

    void push_back(const T& element);
    void push_back(T&& element);
    void pop_back();

    void clear();
    void resize(size_t n);
    void reserve(size_t n);
    void shrink_to_fit();

    T& operator[](size_t idx);
    const T& operator[](size_t idx) const;

    size_t size() const;
    size_t capacity() const;
    bool empty() const;

    T& back();
    const T& back() const;
    T& front();
    const T& front() const;

    ~Vector();

private:
    void copy(const Vector& other);
    void move(Vector&& other) noexcept;
    void free();
    size_t calculate_capacity() const;

    T* _data = nullptr;
    size_t _size = 0;
    size_t _capacity = 0;
};

// Constructors
template <class T>
Vector<T>::Vector(size_t count)
    : _data(new T[count]()), _size(count), _capacity(count)
{
}

template <class T>
Vector<T>::Vector(size_t count, const T& initial)
    : _data(new T[count]), _size(count), _capacity(count)
{
    for (size_t i = 0; i < _size; i++)
        _data[i] = initial;
}

// Copy and move
template <class T>
Vector<T>::Vector(const Vector& other)
{
    copy(other);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }
    return *this;
}

template <class T>
Vector<T>::Vector(Vector&& other) noexcept
{
    move(std::move(other));
}

template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept
{
    if (this != &other)
    {
        free();
        move(std::move(other));
    }
    return *this;
}

template <class T>
Vector<T>::~Vector()
{
    free();
}

template <class T>
void Vector<T>::copy(const Vector& other)
{
    _data = new T[other._capacity];
    for (size_t i = 0; i < other._size; i++)
        _data[i] = other._data[i];
    _size = other._size;
    _capacity = other._capacity;
}

template <class T>
void Vector<T>::move(Vector&& other) noexcept
{
    _data = other._data;
    _size = other._size;
    _capacity = other._capacity;

    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template <class T>
void Vector<T>::free()
{
    delete[] _data;
    _data = nullptr;
    _size = 0;
    _capacity = 0;
}

template <class T>
size_t Vector<T>::calculate_capacity() const
{
    return _capacity == 0 ? 1 : _capacity * Constants::GROWTH_FACTOR;
}

template <class T>
void Vector<T>::push_back(const T& element)
{
    if (_size == _capacity)
        reserve(calculate_capacity());
    _data[_size++] = element;
}

template <class T>
void Vector<T>::push_back(T&& element)
{
    if (_size == _capacity)
        reserve(calculate_capacity());
    _data[_size++] = std::move(element);
}

template <class T>
void Vector<T>::pop_back()
{
    if (!empty())
        --_size;
}

template <class T>
void Vector<T>::clear()
{
    _size = 0;
}

template <class T>
void Vector<T>::resize(size_t n)
{
    if (n > capacity) {
        reserve(n);
    }
    
    _size = n;
}

template <class T>
void Vector<T>::reserve(size_t n)
{
    if (n <= _capacity)
        return;

    T* new_data = new T[n];
    for (size_t i = 0; i < _size; i++)
        new_data[i] = std::move(_data[i]);

    delete[] _data;
    _data = new_data;
    _capacity = n;
}

template <class T>
void Vector<T>::shrink_to_fit()
{
    if (_capacity == _size)
        return;

    T* new_data = new T[_size];
    for (size_t i = 0; i < _size; i++)
        new_data[i] = std::move(_data[i]);

    delete[] _data;
    _data = new_data;
    _capacity = _size;
}

template <class T>
T& Vector<T>::operator[](size_t idx)
{
    return _data[idx];
}

template <class T>
const T& Vector<T>::operator[](size_t idx) const
{
    return _data[idx];
}

template <class T>
T& Vector<T>::back()
{
    return _data[_size - 1];
}

template <class T>
const T& Vector<T>::back() const
{
    return _data[_size - 1];
}

template <class T>
T& Vector<T>::front()
{
    return _data[0];
}

template <class T>
const T& Vector<T>::front() const
{
    return _data[0];
}

template <class T>
size_t Vector<T>::size() const
{
    return _size;
}

template <class T>
size_t Vector<T>::capacity() const
{
    return _capacity;
}

template <class T>
bool Vector<T>::empty() const
{
    return _size == 0;
}
