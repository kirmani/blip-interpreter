// symbol_table.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef SYMBOL_TABLE_H_
#define SYMBOL_TABLE_H_

#include "./expression_tree.h"
#include "./string.h"
#include "./vector.h"
#include "./nodes/program_nodes.h"

namespace SymbolTable {
void Initialize();
void Free();

void AddSymbol(String name, int value);
void SetSymbol(String name, int value);
int GetSymbol(String name);

void SwitchTable(String new_table);
String GetCurrentTable();
void DeleteTable(String name);

void AddFunction(DefunNode* func);
int CallFunction(String name, const Vector<int>& args);
}  // namespace SymbolTable

#endif  // SYMBOL_TABLE_H_
