// parse_tree.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "./parse_tree.h"
#include "./nodes/program_nodes.h"

ParseTree::ParseTree() {
  while (true) {
    ProgramNode* p = NextProgramNode();
    if (p != nullptr) {
      program_.Append(p);
    } else {
      break;
    }
  }
}

void ParseTree::Execute() {
  for (int i = 0; i < program_.Size(); i++) {
    program_[i]->Execute();
  }
}

ParseTree::~ParseTree() {
  for (int i = 0; i < program_.Size(); i++) {
    delete program_[i];
  }
}
