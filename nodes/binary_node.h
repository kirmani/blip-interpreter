// binary_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef NODES_BINARY_NODE_H_
#define NODES_BINARY_NODE_H_

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

#endif  // NODES_BINARY_NODE_H_
