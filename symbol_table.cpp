// symbol_table.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "./symbol_table.h"

#include <map>

#include "./nodes/program_nodes.h"
#include "./string.h"

namespace SymbolTable {
static String current_table_;
static std::map<String, std::map<String, int>*>* symbol_table_;
static std::map<String, DefunNode*>* function_list_;

void Initialize() {
  symbol_table_ = new std::map<String, std::map<String, int>*>;
  (*symbol_table_)[String("main")] = new std::map<String, int>;
  current_table_ = String{"main"};

  function_list_ = new std::map<String, DefunNode*>;
}

void AddSymbol(String name, int value) {
  if ((*symbol_table_)[current_table_]->count(name) > 0) {
    printf("variable %s incorrectly re-initialiezd\n", name.c_str());
  }
  (*(*symbol_table_)[current_table_])[name] = value;
}

void SetSymbol(String name, int value) {
  if ((*symbol_table_)[current_table_]->count(name) == 0) {
    printf("variable %s not declared\n", name.c_str());
  }
  (*(*symbol_table_)[current_table_])[name] = value;
}

int GetSymbol(String name) { return (*(*symbol_table_)[current_table_])[name]; }

void SwitchTable(String new_table) {
  if (symbol_table_->find(new_table) == symbol_table_->end()) {
    (*symbol_table_)[new_table] = new std::map<String, int>;
  }
  current_table_ = new_table;
}

String GetCurrentTable() { return current_table_; }

void DeleteTable(String name) {
  delete (*symbol_table_)[name];
  symbol_table_->erase(name);
}

void AddFunction(DefunNode* func) { (*function_list_)[func->name] = func; }

int CallFunction(String name, const Vector<int>& args) {
  return (*function_list_)[name]->Call(args);
}

void Free() {
  for (auto iterator = symbol_table_->begin(); iterator != symbol_table_->end();
       iterator++) {
    delete iterator->second;
  }
  delete symbol_table_;
  delete function_list_;
}
}  // namespace SymbolTable
