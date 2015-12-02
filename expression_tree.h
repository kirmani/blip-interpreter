// expression_tree.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef EXPRESSION_TREE_H_
#define EXPRESSION_TREE_H_

#include "./input.h"
#include "./string.h"
#include "./nodes/expression_node.h"

class ExpressionTree {
 private:
  ExpressionNode* root_;

 public:
  ExpressionTree() { root_ = NextExpressionNode(); }

  int Compute() { return root_->Compute(); }

  ~ExpressionTree() { delete root_; }
};

#endif  // EXPRESSION_TREE_H_
