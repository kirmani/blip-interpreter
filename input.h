// input.h
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#ifndef INPUT_H
#define INPUT_H

#include "./string.h"

namespace Input {
  enum TokenType {
    NUMBER,
    SYMBOL,
    NAME,
    END,
    INVALID
  };

  bool Initialize(char* filename);

  void SkipLine();
  void ReadToken();
  TokenType GetTokenType();
  String PeekToken();
  String GetCurrentToken();
  int GetTokenValue();
}

#endif  // INPUT_H
