// var_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef VAR_NODE_H
#define VAR_NODE_H

#include "../string.h"
#include "../symbol_table.h"
#include "./expression_node.h"

class VarNode : public ExpressionNode {
 private:
  String name_;

 public:
  VarNode(String name) {
    name_ = name;
  }

  int Compute() {
    return SymbolTable::GetSymbol(name_);
  }
};

#endif  // VAR_NODE_H
