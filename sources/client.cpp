// Copyright 2020 Kochurin Nikita kochurin.nikita@gmail.com

#include "client.hpp"

client::client(int argc, char* argv[]) : argc_(argc), argv_(argv) {}

int client::run() {
  if (argc_ != 3) {
    std::cerr << "Usage: http-client-sync <url> "
                 "<request>\n"//

              << "Example:\n"
              << "    ./cmake-build-debug/tests  "
                 "http://localhost:8080/v1/api/suggest "
              << R"({\"input\":\"<user_input>\"})"
                 "\n";
    return EXIT_FAILURE;
  }

  try {
    prepare_comm_line();

    net::io_context ioc;
    tcp::resolver resolver{ioc};
    beast::tcp_stream stream(ioc);

    auto const results = resolver.resolve(parametrs.host, parametrs.port);
    stream.connect(results);
// Copyright 2020 Kavykin Andrey Kaviandr@yandex.ru

    http::string_body::value_type body = parametrs.request_body;

    http::request<http::string_body> req{http::verb::post, parametrs.target,
                                         parametrs.version};
    req.set(http::field::host, parametrs.host);
    req.body() = body;
    req.prepare_payload();
    req.set(http::field::content_type, "text/plain");

    http::write(stream, req);

    boost::beast::flat_buffer buffer;

    http::response<http::string_body> res;

    http::read(stream, buffer, res);
    std::cout << res.body() << std::endl;

    beast::error_code ec;
    stream.socket().shutdown(tcp::socket::shutdown_both, ec);

    if (ec && ec != beast::errc::not_connected) {
      throw beast::system_error{ec};
    }
  } catch (std::exception const& e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

void client::prepare_comm_line() {
  URL url(argv_[1]);
  parametrs.url = url.parse_url();
  parametrs.host = url.parse_url_to_host();
  parametrs.port = url.parse_url_to_port();
  parametrs.target = url.parse_url_to_target();
  parametrs.request_body = argv_[2];
  parametrs.version = 11;
}
