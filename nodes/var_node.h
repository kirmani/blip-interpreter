// var_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef NODES_VAR_NODE_H_
#define NODES_VAR_NODE_H_

#include "../string.h"
#include "../symbol_table.h"
#include "./expression_node.h"

class VarNode : public ExpressionNode {
 private:
  String name_;

 public:
  explicit VarNode(String name) { name_ = name; }

  int Compute() { return SymbolTable::GetSymbol(name_); }
};

#endif  // NODES_VAR_NODE_H_
