// arithmetic_nodes.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef NODES_ARITHMETIC_NODES_H_
#define NODES_ARITHMETIC_NODES_H_

#include "./binary_node.h"
#include "./unary_node.h"

class NumNode : public ExpressionNode {
 private:
  int value_;

 public:
  explicit NumNode(int value) {
    value_ = value;
  }

  int Compute() {
    return value_;
  }
};

class AddNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() + right_->Compute();
  }
};

class SubNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() - right_->Compute();
  }
};

class MulNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() * right_->Compute();
  }
};

class DivNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() / right_->Compute();
  }
};

class ModNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() % right_->Compute();
  }
};

class AndNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() && right_->Compute();
  }
};

class OrNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() || right_->Compute();
  }
};

class LessNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() < right_->Compute();
  }
};

class GreaterNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() > right_->Compute();
  }
};

class EquNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() == right_->Compute();
  }
};

class NotEquNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() != right_->Compute();
  }
};

class LEquNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() <= right_->Compute();
  }
};

class GEquNode : public BinaryNode {
 public:
  int Compute() {
    return left_->Compute() >= right_->Compute();
  }
};

class NotNode : public UnaryNode {
 public:
  int Compute() {
    return !child_->Compute();
  }
};

class NegNode : public UnaryNode {
 public:
  int Compute() {
    return -1 * child_->Compute();
  }
};

#endif  // NODES_ARITHMETIC_NODES_H_
