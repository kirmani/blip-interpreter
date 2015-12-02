// call_node.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef NODES_CALL_NODE_H_
#define NODES_CALL_NODE_H_

#include "./expression_node.h"
#include "../expression_tree.h"
#include "../string.h"
#include "../vector.h"

class CallNode : public ExpressionNode {
 private:
  String name_;
  Vector<ExpressionTree*> args_;

 public:
  CallNode();
  int Compute();
  ~CallNode();
};

#endif  // NODES_CALL_NODE_H_
