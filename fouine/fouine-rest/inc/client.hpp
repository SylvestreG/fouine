
#ifndef FOUINE_CLIENT_HPP
#define FOUINE_CLIENT_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <string_view>

#include <tl/expected.hpp>

namespace fouine::rest {

struct request_impl;
struct client_impl;

class request {
public:
  request() = delete;
  request(std::string_view addr, uint16_t port, std::string_view location,
          std::string_view data);
  ~request();

  std::pair<std::string_view, std::string_view> connectInfo() const;
  std::string_view location() const;
  std::string_view data() const;

private:
  std::unique_ptr<request_impl> _impl;
};

class response {
public:
private:
};

class client {
public:
  client(client const &) = delete;
  client &operator=(client const &) = delete;

  client();
  ~client();

  tl::expected<response, std::string> get(request const &req);

private:
  std::unique_ptr<client_impl> _impl;
};

} // namespace fouine::rest

#endif // FOUINE_CLIENT_HPP
