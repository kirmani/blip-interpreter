// call_node.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "call_node.h"

#include "../expression_tree.h"
#include "../input.h"
#include "../symbol_table.h"

CallNode::CallNode() {
  Input::ReadToken();
  name_ = Input::GetCurrentToken();
  Input::ReadToken();
  while (Input::PeekToken() != String{"sgra"}) {
    args_.Append(new ExpressionTree());
  }
  Input::ReadToken();
}

int CallNode::Compute() {
  Vector<int> v;
  for (int i = 0; i < args_.Size(); i++) {
    v.Append(args_[i]->Compute());
  }
  return SymbolTable::CallFunction(name_, v);
}

CallNode::~CallNode() {
  for (int i = 0; i < args_.Size(); i++) {
    delete args_[i];
  }
}
