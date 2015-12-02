// expression_node.cpp
// Copyright (C) 2015 Sean Kirmani <sean@kirmani.io>
//
// Distributed under terms of the MIT license.

#include "expression_node.h"

#include "./arithmetic_nodes.h"
#include "./call_node.h"
#include "./var_node.h"
#include "../input.h"

ExpressionNode* NextExpressionNode() {
  Input::ReadToken();
  String token = Input::GetCurrentToken();

  if (Input::GetTokenType() == Input::TokenType::NUMBER) {
    return new NumNode(Input::GetTokenValue());
  } else if (token == String{"+"}) {
    return new AddNode();
  } else if (token == String{"-"}) {
    return new SubNode();
  } else if (token == String{"*"}) {
    return new MulNode();
  } else if (token == String{"/"}) {
    return new DivNode();
  } else if (token == String{"%"}) {
    return new ModNode();
  } else if (token == String{"&&"}) {
    return new AndNode();
  } else if (token == String{"||"}) {
    return new OrNode();
  } else if (token == String{"<"}) {
    return new LessNode();
  } else if (token == String{">"}) {
    return new GreaterNode();
  } else if (token == String{"=="}) {
    return new EquNode();
  } else if (token == String{"!="}) {
    return new NotEquNode();
  } else if (token == String{"<="}) {
    return new LEquNode();
  } else if (token == String{">="}) {
    return new GEquNode();
  } else if (token == String{"!"}) {
    return new NotNode();
  } else if (token == String{"~"}) {
    return new NegNode();
  } else if (token == String{"call"}) {
    return new CallNode();
  } else if (Input::GetTokenType() == Input::TokenType::NAME) {
    return new VarNode(token);
  }
  return new NumNode(0);
}
