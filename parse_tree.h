// parse_tree.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef PARSE_TREE_H_
#define PARSE_TREE_H_

#include "./vector.h"
#include "./nodes/program_nodes.h"

class ParseTree {
 private:
  Vector<ProgramNode*> program_;

 public:
  ParseTree();
  void Execute();
  ~ParseTree();
};

#endif  // PARSE_TREE_H_
