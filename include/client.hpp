// Copyright 2020 Kochurin Nikita kochurin.nikita@gmail.com

#ifndef INCLUDE_CLIENT_HPP_
#define INCLUDE_CLIENT_HPP_
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <iostream>
#include <string>

#include "URL.hpp"
#include "req_param.hpp"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

class client {
 public:
  client(int argc, char* argv[]);
  int run();

 private:
  void prepare_comm_line();
  int argc_;
  char** argv_;
  req_param parametrs;
};

#endif  // INCLUDE_CLIENT_HPP_
