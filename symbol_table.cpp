// symbol_table.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "./symbol_table.h"

#include "./hash_map.h"
#include "./string.h"
#include "./vector.h"
#include "./nodes/program_nodes.h"

namespace SymbolTable {
static String current_table_;
static HashMap<String, HashMap<String, int, StringHash<String>>*,
               StringHash<String>>* symbol_table_;
static HashMap<String, DefunNode*, StringHash<String>>* function_list_;

void Initialize() {
  symbol_table_ = new HashMap<String, HashMap<String, int, StringHash<String>>*,
                              StringHash<String>>;
  symbol_table_->Put(String("main"),
                     new HashMap<String, int, StringHash<String>>);
  current_table_ = String{"main"};

  function_list_ = new HashMap<String, DefunNode*, StringHash<String>>;
}

void AddSymbol(String name, int value) {
  if (symbol_table_->Get(current_table_)->ContainsKey(name)) {
    printf("variable %s incorrectly re-initialiezd\n", name.c_str());
  }
  symbol_table_->Get(current_table_)->Put(name, value);
}

void SetSymbol(String name, int value) {
  if (!(symbol_table_->Get(current_table_)->ContainsKey(name))) {
    printf("variable %s not declared\n", name.c_str());
  }
  symbol_table_->Get(current_table_)->Put(name, value);
}

int GetSymbol(String name) {
  return symbol_table_->Get(current_table_)->Get(name);
}

void SwitchTable(String new_table) {
  if (!(symbol_table_->ContainsKey(new_table))) {
    symbol_table_->Put(new_table, new HashMap<String, int, StringHash<String>>);
  }
  current_table_ = new_table;
}

String GetCurrentTable() { return current_table_; }

void DeleteTable(String name) {
  delete symbol_table_->Get(name);
  symbol_table_->Remove(name);
}

void AddFunction(DefunNode* func) { function_list_->Put(func->name, func); }

int CallFunction(String name, const Vector<int>& args) {
  return function_list_->Get(name)->Call(args);
}

void Free() {
  Vector<String>* key_set = symbol_table_->GetKeySet();
  int key_set_size = key_set->Size();
  for (int i = 0; i < key_set_size; i++) {
    delete symbol_table_->Get((*key_set)[i]);
  }
  delete key_set;
  delete symbol_table_;
  delete function_list_;
}
}  // namespace SymbolTable
