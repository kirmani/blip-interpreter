// hash_map.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

#include "./vector.h"

const int kTableSize = 100;

template <typename K, typename V>
class HashNode {
 private:
  K key_;
  V value_;
  HashNode* next_;

 public:
  HashNode(const K& key, const V& value) {
    key_ = key;
    value_ = value;
    next_ = nullptr;
  }

  K GetKey() { return key_; }

  V GetValue() { return value_; }

  void SetValue(V value) { value_ = value; }

  HashNode* GetNext() { return next_; }

  void SetNext(HashNode* next) { next_ = next; }
};

template <class String>
struct StringHash {
  int operator()(const String& key) const {
    int hash_code = 11;
    for (int i = 0; i < key.Size(); i++) {
      hash_code *= const_cast<String&>(key)[i] * 33 + 7;
    }
    hash_code = hash_code % kTableSize;
    return hash_code ? hash_code > 0 : -hash_code;
  }
};

template <typename K>
struct KeyHash {
  int operator()(const K& key) const {
    return reinterpret_cast<int>(key) % kTableSize;
  }
};

template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
 public:
  HashMap() {
    // construct zero initialized has table of size
    table = new HashNode<K, V>* [kTableSize]();
  }

  ~HashMap() {
    // destory all buckets one by one
    for (int i = 0; i < kTableSize; i++) {
      HashNode<K, V>* entry = table[i];
      while (entry != NULL) {
        HashNode<K, V>* prev = entry;
        entry = entry->GetNext();
        delete prev;
      }
      table[i] = NULL;
    }
    // destroy the hash table
    delete[] table;
  }

  V Get(const K& key) {
    int hashValue = hashFunc(key);
    HashNode<K, V>* entry = table[hashValue];

    while (entry != NULL) {
      if (entry->GetKey() == key) {
        return entry->GetValue();
      }
      entry = entry->GetNext();
    }
    return NULL;
  }

  bool ContainsKey(const K& key) {
    int hashValue = hashFunc(key);
    HashNode<K, V>* entry = table[hashValue];

    while (entry != NULL) {
      if (entry->GetKey() == key) {
        return true;
      }
      entry = entry->GetNext();
    }
    return false;
  }

  void Put(const K& key, const V& value) {
    int hashValue = hashFunc(key);
    HashNode<K, V>* prev = NULL;
    HashNode<K, V>* entry = table[hashValue];

    while (entry != NULL && entry->GetKey() != key) {
      prev = entry;
      entry = entry->GetNext();
    }

    if (entry == NULL) {
      entry = new HashNode<K, V>(key, value);
      if (prev == NULL) {
        // insert as first bucket
        table[hashValue] = entry;
      } else {
        prev->SetNext(entry);
      }
    } else {
      // just update the value
      entry->SetValue(value);
    }
  }

  void Remove(const K& key) {
    int hashValue = hashFunc(key);
    HashNode<K, V>* prev = NULL;
    HashNode<K, V>* entry = table[hashValue];

    while (entry != NULL && entry->GetKey() != key) {
      prev = entry;
      entry = entry->GetNext();
    }

    if (entry == NULL) {
      // key not found
      return;
    } else {
      if (prev == NULL) {
        // remove first bucket of the list
        table[hashValue] = entry->GetNext();
      } else {
        prev->SetNext(entry->GetNext());
      }
      delete entry;
    }
  }

  Vector<K>* GetKeySet() {
    Vector<K>* key_set = new Vector<K>;
    for (int i = 0; i < kTableSize; i++) {
      HashNode<K, V>* entry = table[i];
      if (entry != NULL) {
        key_set->Append(entry->GetKey());
      }
    }
    return key_set;
  }

 private:
  // hash table
  HashNode<K, V>** table;
  F hashFunc;
};

#endif  // HASH_MAP_H_
