// Copyright 2020 Kochurin Nikita kochurin.nikita@gmail.com

#ifndef INCLUDE_REQ_PARAM_HPP_
#define INCLUDE_REQ_PARAM_HPP_
#include <string>
struct req_param {
  std::string url;
  std::string host;
  std::string port;
  std::string target;
  std::string request_body;
  int version;
};
#endif  // INCLUDE_REQ_PARAM_HPP_
