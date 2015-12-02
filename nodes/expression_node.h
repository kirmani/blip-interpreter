// expression_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef NODES_EXPRESSION_NODE_H_
#define NODES_EXPRESSION_NODE_H_

class ExpressionNode {
 public:
  virtual int Compute() = 0;
  virtual ~ExpressionNode() {}
};

ExpressionNode* NextExpressionNode();

#endif  // NODES_EXPRESSION_NODE_H_
