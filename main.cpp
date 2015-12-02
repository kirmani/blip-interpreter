// main.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include <stdio.h>

#include "./input.h"
#include "./parse_tree.h"
#include "./symbol_table.h"

int main(int argc, char* argv[]) {
  if (argc != 2) {
    printf("Incorrect number of arguments\n");
  }
  if (!Input::Initialize(argv[1])) {
    printf("Error opening %s\n", argv[1]);
    return 1;
  }

  SymbolTable::Initialize();

  ParseTree p;
  p.Execute();
}
