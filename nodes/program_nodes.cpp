// program_nodes.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "./program_nodes.h"

#include <sstream>

#include "../expression_tree.h"
#include "../input.h"
#include "../string.h"
#include "../symbol_table.h"

ProgramNode* NextProgramNode() {
  Input::ReadToken();
  String token = Input::GetCurrentToken();

  if (Input::GetTokenType() == Input::TokenType::END) {
    return nullptr;
  } else if (token[0] == '/' && token[1] == '/') {
    Input::SkipLine();
    return NextProgramNode();
  } else if (token == String{"var"}) {
    return new VarDefNode();
  } else if (token == String{"set"}) {
    return new SetNode();
  } else if (token == String{"output"}) {
    return new OutputNode();
  } else if (token == String{"text"}) {
    return new TextNode();
  } else if (token == String{"if"}) {
    return new IfNode();
  } else if (token == String{"do"}) {
    return new DoNode();
  } else if (token == String{"defun"}) {
    return new DefunNode();
  } else if (token == String{"return"}) {
    return new ReturnNode();
  }
  return nullptr;
}

// The default is to not return a value
ReturnValue base_execute() {
  ReturnValue r = {0, false};
  return r;
}

// VarDef
VarDefNode::VarDefNode() {
  Input::ReadToken();
  name_ = Input::GetCurrentToken();
  e_ = new ExpressionTree();
}

ReturnValue VarDefNode::Execute() {
  SymbolTable::AddSymbol(name_, e_->Compute());
  return base_execute();
}

VarDefNode::~VarDefNode() { delete e_; }

// Set
SetNode::SetNode() {
  Input::ReadToken();
  name_ = Input::GetCurrentToken();
  e_ = new ExpressionTree();
}

ReturnValue SetNode::Execute() {
  SymbolTable::SetSymbol(name_, e_->Compute());
  return base_execute();
}

SetNode::~SetNode() { delete e_; }

// Text
TextNode::TextNode() {
  Input::ReadToken();
  text_ = Input::GetCurrentToken();
}

ReturnValue TextNode::Execute() {
  printf("%s", text_.c_str());
  return base_execute();
}

// Output
OutputNode::OutputNode() { e_ = new ExpressionTree(); }

ReturnValue OutputNode::Execute() {
  printf("%d", e_->Compute());
  return base_execute();
}

OutputNode::~OutputNode() { delete e_; }

// Do
DoNode::DoNode() {
  condition_ = new ExpressionTree();
  while (true) {
    ProgramNode* p = NextProgramNode();
    if (p != nullptr) {
      body_.Append(p);
    } else {
      break;
    }
  }
}

ReturnValue DoNode::Execute() {
  while (condition_->Compute()) {
    for (int i = 0; i < body_.Size(); i++) {
      ReturnValue r = body_[i]->Execute();
      if (r.returned) {
        return r;
      }
    }
  }
  return base_execute();
}

DoNode::~DoNode() {
  delete condition_;
  for (int i = 0; i < body_.Size(); i++) {
    delete body_[i];
  }
}

// If
IfNode::IfNode() {
  is_else_ = false;
  condition_ = new ExpressionTree();
  while (true) {
    ProgramNode* p = NextProgramNode();
    if (p == 0) {
      if (Input::GetCurrentToken() == String{"fi"}) {
        break;
      } else {
        is_else_ = true;
        continue;
      }
    }
    if (!is_else_) {
      body_.Append(p);
    } else {
      else_body_.Append(p);
    }
  }
}

ReturnValue IfNode::Execute() {
  if (condition_->Compute()) {
    for (int i = 0; i < body_.Size(); i++) {
      ReturnValue r = body_[i]->Execute();
      if (r.returned) {
        return r;
      }
    }
  } else {
    for (int i = 0; i < else_body_.Size(); i++) {
      ReturnValue r = else_body_[i]->Execute();
      if (r.returned) {
        return r;
      }
    }
  }
  return base_execute();
}

IfNode::~IfNode() {
  delete condition_;
  for (int i = 0; i < body_.Size(); i++) {
    delete body_[i];
  }
  for (int i = 0; i < else_body_.Size(); i++) {
    delete else_body_[i];
  }
}

// Return
ReturnNode::ReturnNode() { e_ = new ExpressionTree(); }

ReturnValue ReturnNode::Execute() {
  ReturnValue r = {e_->Compute(), true};
  return r;
}

ReturnNode::~ReturnNode() { delete e_; }

// Defun
DefunNode::DefunNode() {
  Input::ReadToken();
  name = Input::GetCurrentToken();

  Input::ReadToken();
  while (Input::PeekToken() != String{"smarap"}) {
    Input::ReadToken();
    param_names_.Append(Input::GetCurrentToken());
  }
  Input::ReadToken();

  while (true) {
    ProgramNode* p = NextProgramNode();
    if (p != nullptr) {
      body_.Append(p);
    } else {
      break;
    }
  }
}

ReturnValue DefunNode::Execute() {
  SymbolTable::AddFunction(this);
  return base_execute();
}

int DefunNode::Call(const Vector<int>& args) {
  static int recurse = 0;

  String new_table = name + String{recurse};
  recurse += 1;

  String old_table = SymbolTable::GetCurrentTable();
  SymbolTable::SwitchTable(new_table);

  for (int i = 0; i < param_names_.Size(); i++) {
    SymbolTable::AddSymbol(param_names_[i], const_cast<Vector<int>&>(args)[i]);
  }

  int value = 0;
  for (int i = 0; i < body_.Size(); i++) {
    ReturnValue r = body_[i]->Execute();
    if (r.returned) {
      value = r.value;
      break;
    }
  }

  SymbolTable::DeleteTable(new_table);
  SymbolTable::SwitchTable(old_table);
  return value;
}

DefunNode::~DefunNode() {
  for (int i = 0; i < body_.Size(); i++) {
    delete body_[i];
  }
}
