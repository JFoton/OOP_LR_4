#pragma once
#include <iostream>

#ifndef CUSTOMVECTOR_H
#define CUSTOMVECTOR_H

template <typename T>
class MyVector {
private:
    T* data;
    int size_;
    int capacity_;

    void moveData(T* source, T* destination, int count);

public:
    MyVector();
    ~MyVector();
    explicit MyVector(int initialCapacity);
    MyVector(const MyVector& other);
    MyVector& operator=(const MyVector& other);

    MyVector(std::initializer_list<T> values) : size_(values.size()), capacity_(values.size()) {
        data = new T[capacity_];
        int i = 0;
        for (const T& value : values) {
            data[i++] = value;
        }
    }

    void push_back(const T& value);
    void pop_back();
    void clear();
    int size() const;
    int capacity() const;
    T& operator[](int index);
    const T& operator[](int index) const;
    void reserve(int newCapacity);
    void resize(int newSize, const T& value = T());
    bool empty() const;

    T* begin();
    const T* begin() const;

    T* end();
    const T* end() const;
};

template <typename T>
MyVector<T>::MyVector() : data(nullptr), size_(0), capacity_(0) {}

template <typename T>
MyVector<T>::MyVector(int initialCapacity) : size_(0), capacity_(initialCapacity) {
    data = new T[capacity];
}

template <typename T>
MyVector<T>::MyVector(const MyVector& other) : size_(other.size), capacity_(other.capacity) {
    data = new T[capacity_];
    moveData(other.data, data, size_);
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] data;
        size = other.size;
        capacity = other.capacity;
        data = new T[capacity];
        moveData(other.data, data, size);
    }
    return *this;
}

template <typename T>
MyVector<T>::~MyVector() {
    delete[] data;
}

template <typename T>
void MyVector<T>::moveData(T* source, T* destination, int count) {
    for (size_t i = 0; i < count; ++i) {
        destination[i] = source[i];
    }
}

template <typename T>
void MyVector<T>::push_back(const T& value) {
    if (size_ == capacity_) {
        reserve(capacity_ * 2 + 1);
    }
    data[size_++] = value;
}

template <typename T>
void MyVector<T>::pop_back() {
    if (size_ > 0) {
        --size_;
    }
}

template <typename T>
void MyVector<T>::clear() {
    size = 0;
}

template <typename T>
int MyVector<T>::size() const {
    return size_;
}

template <typename T>
int MyVector<T>::capacity() const {
    return capacity_;
}

template <typename T>
T& MyVector<T>::operator[](int index) {
    if (index < size_) {
        return data[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
const T& MyVector<T>::operator[](int index) const {
    if (index < size_) {
        return data[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

template <typename T>
void MyVector<T>::reserve(int newCapacity) {
    if (newCapacity > capacity_) {
        T* newData = new T[newCapacity];
        moveData(data, newData, size_);
        delete[] data;
        data = newData;
        capacity_ = newCapacity;
    }
}

template <typename T>
void MyVector<T>::resize(int newSize, const T& value) {
    if (newSize > size) {
        reserve(newSize);
        for (size_t i = size; i < newSize; ++i) {
            data[i] = value;
        }
    }
    size = newSize;
}

template <typename T>
bool MyVector<T>::empty() const {
    return size == 0;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const MyVector<T>& vec) {
    for (size_t i = 0; i < vec.size(); ++i) {
        os << vec[i];
    }
    return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, MyVector<T>& vec) {
    T value;
    vec.clear();

    while (is >> value) {
        vec.push_back(value);
    }

    return is;
}

template <typename T>
T* MyVector<T>::begin() {
    return data;
}

template <typename T>
const T* MyVector<T>::begin() const {
    return data;
}

template <typename T>
T* MyVector<T>::end() {
    return data + size_;
}

template <typename T>
const T* MyVector<T>::end() const {
    return data + size_;
}

#endif
