// unary_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef UNARY_NODE_H
#define UNARY_NODE_H

class UnaryNode : public ExpressionNode {
 protected:
  ExpressionNode* child_;

 public:
  UnaryNode() {
    child_ = NextExpressionNode();
  }

  ~UnaryNode() {
    delete child_;
  }
};

#endif  // UNARY_NODE_H
