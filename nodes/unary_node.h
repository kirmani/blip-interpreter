// unary_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef NODES_UNARY_NODE_H_
#define NODES_UNARY_NODE_H_

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

#endif  // NODES_UNARY_NODE_H_
