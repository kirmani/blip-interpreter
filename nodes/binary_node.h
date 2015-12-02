// binary_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef BINARY_NODE_H
#define BINARY_NODE_H

#include "./expression_node.h"

class BinaryNode : public ExpressionNode {
 protected:
  ExpressionNode* left_;
  ExpressionNode* right_;

 public:
  BinaryNode() {
    left_ = NextExpressionNode();
    right_ = NextExpressionNode();
  }

  ~BinaryNode() {
    delete left_;
    delete right_;
  }
};

#endif  // BINARY_NODE_H
