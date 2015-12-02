// string.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef STRING_H_
#define STRING_H_

#include <stdio.h>

class String {
 private:
  char* ptr_;
  int len_;

  char* integer_to_ascii(int x) {
    int num_digits = 0;
    int temp = x;
    while (temp != 0) {
      num_digits++;
      temp /= 10;
    }
    char* digits = new char[num_digits + 1];
    int index = 0;
    while (x != 0) {
      digits[index++] = '0' + (x % 10);
      x /= 10;
    }
    digits[index] = '\0';
    return digits;
  }

 public:
  explicit String(const char* src) {
    Construct(src);
  }

  explicit String(int num) {
    Construct(integer_to_ascii(num));
  }

  String(void) {
    Construct("");
  }

  String(const String& that) {
    Copy(that);
  }

  ~String(void) {
    Destroy();
  }

  String& operator=(const String& that) {
    if (this != &that) {
      Destroy();
      Copy(that);
    }
    return *this;
  }

  friend String operator+(const String& str1, const String& str2) {
    int str1_size = str1.Size();
    int str2_size = str2.Size();
    char* ptr = new char[str1_size + str2_size + 1];
    for (int i = 0; i < str1_size; i++) {
      ptr[i] = const_cast<String&>(str1)[i];
    }
    for (int i = 0; i < str2_size; i++) {
      ptr[str1_size + i] = const_cast<String&>(str2)[i];
    }
    ptr[str1_size + str2_size] = '\0';
    return String{ptr};
  }

  char operator[](int index) {
    return this->ptr_[index];
  }

  String& operator=(const char* src) {
    Destroy();
    Construct(src);
    return *this;
  }

  const char* c_str(void) const {
    return ptr_;
  }

  int Size(void) const {
    return len_;
  }

  bool operator==(String s2) const {
    const String& s1 = *this;
    if (s1.Size() != s2.Size())
      return false;
    int size = s1.Size();
    for (int index = 0; index < size; index++)
      if (s1.ptr_[index] != s2.ptr_[index])
        return false;
    return true;
  }

  bool operator<(String s2) const {
    const String& s1 = *this;
    int k = 0;
    while (s1.ptr_[k] == s2.ptr_[k]) {
      if (s1.ptr_[k] == 0)
        return false;
      k += 1;
    }
    return s1.ptr_[k] < s2.ptr_[k];
  }


  bool operator!=(String s2) const {
    const String& s1 = *this; return !(s1 == s2);
  }

  bool operator>(String s2) const {
    const String& s1 = *this;
    return s2 < s1;
  }

  bool operator<=(String s2) const {
    const String& s1 = *this;
    return !(s2 < s1);
  }

  bool operator>=(String s2) const {
    const String& s1 = *this;
    return !(s1 < s2);
  }

 private:
  void Construct(const char* src) {
    len_ = 0;
    while (src[len_])
      len_++;
    ptr_ = new char[len_ + 1];
    Copy(src);
  }

  void Copy(const char* src) {
    int k = len_;
    while (k >= 0) {
      ptr_[k] = src[k];
      k -= 1;
    }
  }

  void Copy(const String& that) {
    len_ = that.len_;
    ptr_ = new char[len_ + 1];
    Copy(that.ptr_);
  }

  void Destroy(void) {
    delete[] ptr_;
  }
};

#endif  // STRING_H_
