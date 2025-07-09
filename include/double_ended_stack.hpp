#pragma once

#include <cstring>
#include <cmath>
#include <stdexcept>

template<typename T>
class DoubleEndedStack {
    static constexpr double GROW_FACTOR{1.3};

public:
    DoubleEndedStack();
    ~DoubleEndedStack();

    DoubleEndedStack(const DoubleEndedStack &other)
        : capacity_(other.capacity_), front_(other.front_), back_(other.back_) {
        data_ = static_cast<T *>(malloc(sizeof(T) * other.capacity_));
        std::memcpy(data_, other.data_, other.capacity_ * sizeof(T));
    }

    DoubleEndedStack(DoubleEndedStack &&other) noexcept
        : capacity_(other.capacity_), data_(other.data_), front_(other.front_), back_(other.back_) {
        other.data_ = nullptr;
    }

    DoubleEndedStack &operator=(const DoubleEndedStack &other) {
        if (this == &other) return *this;
        capacity_ = other.capacity_;
        data_ = static_cast<T *>(malloc(sizeof(T) * other.capacity_));
        std::memcpy(data_, other.data_, other.capacity_ * sizeof(T));
        front_ = other.front_;
        back_ = other.back_;
        return *this;
    }
    DoubleEndedStack &operator=(DoubleEndedStack &&other) noexcept {
        if (this == &other) return *this;
        capacity_ = other.capacity_;
        data_ = other.data_;
        other.data_ = nullptr;
        front_ = other.front_;
        back_ = other.back_;
        return *this;
    }

    bool empty() const;
    std::size_t size() const;
    void clear();

    void push_back(T v);
    T pop_back();

    T &back();
    const T &back() const;

    void push_front(T v);
    T pop_front();

    T &front();
    const T &front() const;

    T &operator[](std::size_t idx);
    const T &operator[](std::size_t idx) const;

private:
    std::size_t capacity_;
    T *data_;
    std::size_t front_;
    std::size_t back_;
};

template<typename T>
DoubleEndedStack<T>::DoubleEndedStack()
    : capacity_(1), data_(static_cast<T *>(std::malloc(sizeof(T)))), front_(0), back_(0) {}

template<typename T>
DoubleEndedStack<T>::~DoubleEndedStack() {
    free(data_);
    data_ = nullptr;
}

template<typename T>
bool DoubleEndedStack<T>::empty() const {
    return front_ == back_;
}

template<typename T>
std::size_t DoubleEndedStack<T>::size() const {
    return back_ - front_;
}

template<typename T>
void DoubleEndedStack<T>::clear() {
    front_ = back_ = 0;
}

template<typename T>
void DoubleEndedStack<T>::push_back(T v) {
    if (back_ == capacity_) {
        T *tmp = data_;
        std::size_t new_capacity = std::floor(capacity_ * GROW_FACTOR);
        if (new_capacity == capacity_) new_capacity = capacity_ * 2;

        data_ = static_cast<T *>(std::malloc(sizeof(T) * new_capacity));
        std::memmove(data_, tmp, sizeof(T) * capacity_);
        std::free(tmp);

        capacity_ = new_capacity;
    }

    data_[back_++] = v;
}

template<typename T>
T DoubleEndedStack<T>::pop_back() {
    if (front_ == back_) throw std::runtime_error("stack is empty");
    return data_[--back_];
}

template<typename T>
T &DoubleEndedStack<T>::back() {
    return data_[back_ - 1];
}

template<typename T>
const T &DoubleEndedStack<T>::back() const {
    return data_[back_ - 1];
}

template<typename T>
void DoubleEndedStack<T>::push_front(T v) {
    if (front_ == 0) {
        T *tmp = data_;
        std::size_t new_capacity = std::floor(capacity_ * GROW_FACTOR);
        if (new_capacity == capacity_) new_capacity = capacity_ * 2;
        const std::size_t offset = new_capacity - capacity_;

        data_ = static_cast<T *>(std::malloc(sizeof(T) * new_capacity));
        std::memmove(data_ + offset, tmp, sizeof(T) * capacity_);
        std::free(tmp);

        capacity_ = new_capacity;
        front_ += offset;
        back_ += offset;
    }

    data_[--front_] = v;
}

template<typename T>
T DoubleEndedStack<T>::pop_front() {
    if (front_ == back_) throw std::runtime_error("stack is empty");
    return data_[front_++];
}

template<typename T>
T &DoubleEndedStack<T>::front() {
    if (front_ == 0) return data_[front_];
    return data_[front_ + 1];
}

template<typename T>
const T &DoubleEndedStack<T>::front() const {
    if (front_ == 0) return data_[front_];
    return data_[front_ + 1];
}

template<typename T>
T &DoubleEndedStack<T>::operator[](std::size_t idx) {
    if (front_ == 0) return data_[idx];
    return data_[idx + 1];
}

template<typename T>
const T &DoubleEndedStack<T>::operator[](std::size_t idx) const {
    if (front_ == 0) return data_[idx];
    return data_[idx + 1];
}
