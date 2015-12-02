// input.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "./input.h"

#include <stdio.h>
#include <stdlib.h>

namespace Input {
  const int kBuffSize = 4096;
  const int kTokenMaxSize = 128;

  FILE* input_ = stdin;
  char buff_[kBuffSize];
  int cursor_ = 0;

  static char current_token_[kTokenMaxSize];
  static int current_token_value_ = 0;
  static TokenType current_token_type_ = TokenType::INVALID;
  static bool peeked_ = false;

  bool Initialize(char* filename) {
    FILE* p = fopen(filename, "r");
    if (!p) {
      fprintf(stderr, "sorry, I could't open the file %s for reading\n",
          filename);
      return false;
    }
    input_ = p;
    cursor_ = 0;
    buff_[0] = 0;
    return true;
  }

  void SkipLine() {
    cursor_ = 0;
    buff_[0] = 0;
  }

  static bool IsNumber(char c) {
    return c >= '0' && c <='9';
  }

  static bool IsLetter(char c) {
    return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
  }

  static bool IsSpace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
  }

  void ReadToken(void) {
    if (peeked_) {
      peeked_ = false;
      return;
    }

    int k = 0;
    do {
      if (buff_[cursor_] == 0) {
        cursor_ = 0;
        const char* res = fgets(buff_, kBuffSize, input_);
        if (res == 0) {
          *current_token_ = 0;
          current_token_type_ = END;
          return;
        }
      }
      bool is_quoted_string = false;
      while (buff_[cursor_] != 0) {
        if (IsSpace(buff_[cursor_]) && !is_quoted_string) {
          cursor_ += 1;
          break;
        }
        if (buff_[cursor_] == '\"') {  // a " character is next
          is_quoted_string = !is_quoted_string;
          cursor_ += 1;
        } else if (buff_[cursor_] == '\\') {  // a \ character is next
          switch (buff_[cursor_+1]) {
          case 'n':
            current_token_[k] = '\n'; k += 1;
            break;
          case 't':
            current_token_[k] = '\t'; k += 1;
            break;
          case '\\':
            current_token_[k] = '\\'; k += 1;
            break;
          default:
            break;
          }
          cursor_ += 2;
        } else {
          current_token_[k] = buff_[cursor_];
          k += 1;
          cursor_ += 1;
        }
      }
      current_token_[k] = 0;
    } while (k == 0);

    while (buff_[cursor_] != 0 && IsSpace(buff_[cursor_])) {
      cursor_ += 1;
    }

    // now, set the various parsing flags
    if (IsNumber(current_token_[0])) {
      current_token_type_ = NUMBER;
      current_token_value_ = atoi(current_token_);
    } else if (!IsLetter(current_token_[0])) {
      current_token_type_ = SYMBOL;
    } else {
      current_token_type_ = NAME;
    }
  }

  TokenType GetTokenType() {
    return current_token_type_;
  }

  String PeekToken() {
    ReadToken();
    peeked_ = true;
    return GetCurrentToken();
  }

  int GetTokenValue() {
    return current_token_value_;
  }

  String GetCurrentToken() {
    return String{current_token_};
  }
}  // namespace Input
