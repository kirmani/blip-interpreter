// expression_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef EXPRESSION_NODE_H
#define EXPRESSION_NODE_H

class ExpressionNode {
 public:
  virtual int Compute() = 0;
  virtual ~ExpressionNode() {}
};

ExpressionNode* NextExpressionNode();

#endif  // EXPRESSION_NODE_H
