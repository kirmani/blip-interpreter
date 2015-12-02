/*
 * Vector.h
 * Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef VECTOR_H_
#define VECTOR_H_

#include <assert.h>
#include <stdlib.h>
#include <iostream>

const double kResizeCapacity = 0.7;

template <typename T>
class Vector {
 private:
    T* data_;
    int length_;
    int capacity_;

    void ResizeArray() {
      int new_capacity_ = 2 * this->capacity_ + 1;
      T* new_data = new T[new_capacity_];
      for (int index = 0; index < this->length_; index++)
        new_data[index] = this->data_[index];
      delete[] this->data_;
      this->data_ = new_data;
      this->capacity_ = new_capacity_;
    }

 public:
    explicit Vector(int initial_capacity = 10) {
      this->capacity_ = initial_capacity;
      this->length_ = 0;
      this->data_ = new T[initial_capacity];
    }

    ~Vector() {
      delete[] this->data_;
    }

    void Append(T val) {
      int length = this->length_;
      if (length > this->capacity_ * kResizeCapacity)
        ResizeArray();
      this->data_[length] = val;
      this->length_++;
    }

    void Remove(int index) {
      assert(index > 0 && index < this->length - 1);
      for (int i = this->length_ - 1; i > index; i--) {
        this->data[i - 1] = this->data_[i];
      }
      this->length--;
    }

    T& operator[](int index) {
      assert(index < this->length_);
      return this->data_[index];
    }

    int Size() {
      return this->length_;
    }

    friend std::ostream& operator<<(std::ostream& out, const Vector& v) {
      out << "[";
      int last_index = v.length_ - 1;
      for (int index = 0; index < last_index; index++)
        out << v.data_[index] << ", ";
      out << v.data_[last_index] << "]";
      return out;
    }
};

#endif  // VECTOR_H_
