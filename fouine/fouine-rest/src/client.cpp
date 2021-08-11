#include "../inc/client.hpp"

#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>

#include <spdlog/spdlog.h>

namespace beast = boost::beast; // from <boost/beast.hpp>
namespace http = beast::http;   // from <boost/beast/http.hpp>
namespace net = boost::asio;    // from <boost/asio.hpp>
using tcp = net::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

namespace fouine::rest {

struct request_impl {
  std::string_view _addr;
  std::string _port;
  std::string_view _data;
  std::string_view _location;
};

request::request(std::string_view addr, uint16_t port,
                 std::string_view location, std::string_view data)
    : _impl(std::make_unique<request_impl>()) {
  _impl->_addr = addr;
  _impl->_port = std::to_string(port);
  _impl->_location = location;
  _impl->_data = data;
}

std::pair<std::string_view, std::string_view> request::connectInfo() const {
  return std::pair<std::string_view, std::string_view>(_impl->_addr,
                                                       _impl->_port);
}

std::string_view request::location() const { return _impl->_location; }
std::string_view request::data() const { return _impl->_data; }

request::~request() = default;

struct client_impl {
  client_impl() : _resolver(_ioctx), _stream(_ioctx) {}
  net::io_context _ioctx;
  tcp::resolver _resolver;
  beast::tcp_stream _stream;
};

client::client() : _impl(std::make_unique<client_impl>()) {}

tl::expected<response, std::string> client::get(request const &req) {
  auto connInfo = req.connectInfo();

  try {
    auto const results =
        _impl->_resolver.resolve(connInfo.first, connInfo.second);

    _impl->_stream.connect(results);
  } catch (boost::system::system_error const &error) {
    spdlog::error("exception caught {}", error.what());
    return tl::make_unexpected<std::string>(error.what());
  }

  http::request<http::string_body> get_req{http::verb::get,
                                           req.location().data(), 11};

  get_req.set(http::field::host, "fouine");
  get_req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  get_req.body().append(req.data());

  // Send the HTTP request to the remote host
  http::write(_impl->_stream, get_req);

  return response();
}

client::~client() = default;

} // namespace fouine::rest