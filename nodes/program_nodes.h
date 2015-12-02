// program_nodes.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef PROGRAM_NODES_H
#define PROGRAM_NODES_H

#include "../expression_tree.h"
#include "../string.h"
#include "../vector.h"

struct ReturnValue {
 public:
  int value;
  bool returned;
};

class ProgramNode {
 public:
  virtual ReturnValue Execute() = 0;
  virtual ~ProgramNode() {}
};

class VarDefNode : public ProgramNode {
 private:
  ExpressionTree* e_;
  String name_;

 public:
  VarDefNode();
  ReturnValue Execute();
  ~VarDefNode();
};

class SetNode : public ProgramNode {
 private:
  ExpressionTree* e_;
  String name_;

 public:
  SetNode();
  ReturnValue Execute();
  ~SetNode();
};

class TextNode : public ProgramNode {
 private:
  String text_;

 public:
  TextNode();
  ReturnValue Execute();
  ~TextNode() {}
};

class OutputNode : public ProgramNode {
 private:
  ExpressionTree* e_;

 public:
  OutputNode();
  ReturnValue Execute();
  ~OutputNode();
};

class DoNode : public ProgramNode {
 private:
  ExpressionTree* condition_;
  Vector<ProgramNode*> body_;

 public:
  DoNode();
  ReturnValue Execute();
  ~DoNode();
};

class IfNode : public ProgramNode {
 private:
  ExpressionTree* condition_;
  Vector<ProgramNode*> body_;
  Vector<ProgramNode*> else_body_;
  bool is_else_;

 public:
  IfNode();
  ReturnValue Execute();
  ~IfNode();
};

class ReturnNode : public ProgramNode {
 private:
  ExpressionTree* e_;

 public:
  ReturnNode();
  ReturnValue Execute();
  ~ReturnNode();
};

class DefunNode : public ProgramNode {
 private:
  Vector<ProgramNode*> body_;
  Vector<String> param_names_;

 public:
  String name;

  DefunNode();
  ReturnValue Execute();
  int Call(const Vector<int>& args);
  ~DefunNode();
};

ProgramNode* NextProgramNode();

#endif  // PROGRAM_NODES_H
