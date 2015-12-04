// hash_map.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef HASH_MAP_H_
#define HASH_MAP_H_

const int kTableSize = 100;

template <typename K, typename V>
class HashNode {
 private:
  K key;
  V value;
  HashNode* next;

 public:
  HashNode(const K& key, const V& value) : key(key), value(value), next(NULL) {}

  K GetKey() const { return key; }

  V GetValue() const { return value; }

  HashNode* GetNext() const { return next; }

  void setNext(HashNode* next) { HashNode::next = next; }
};

template <typename K>
struct KeyHash {
  unsigned long operator()(const K& key) const {
    return reinterpret_cast<unsigned long>(key) % kTableSize;
  }
};

template <typename K, typename V, typename F = KeyHash<K>>
class HashMap {
 public:
  HashMap() {
    // construct zero initialized has table of size
    table = new HashNode<K, V>*[kTableSize]();
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

  bool Get(const K& key, V& value) {
    unsigned long hashValue = hashFunc(key);
    HashNode<K, V>* entry = table[hashValue];

    while (entry != NULL) {
      if (entry->GetKey() == key) {
        value = entry->GetValue();
        return true;
      }
      entry = entry->GetNext();
    }
    return false;
  }

  void Put(const K& key, const V& value) {
    unsigned long hashValue = hashFunc(key);
    HashNode<K, V>* prev = NULL;
    HashNode<K, V>* entry = table[hashValue];

    while (entry != NULL && entry->getKey() != key) {
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
    unsigned long hashValue = hashFunc(key);
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

 private:
  // hash table
  HashNode<K, V>** table;
  F hashFunc;
};

#endif  // HASH_MAP_H_
