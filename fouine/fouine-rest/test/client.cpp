#include <gtest/gtest.h>
#include <iostream>

#include "../inc/client.hpp"

TEST(rest, badAddr) {
  fouine::rest::client cl;
  fouine::rest::request req("-dsadsdadsa-dsa845+66464", 80, "/",
                            "hello world\n");
  auto res = cl.get(req);

  ASSERT_FALSE(res);
  ASSERT_EQ(res.error(), "resolve: Host not found (authoritative)");
}

TEST(rest, client) {
  fouine::rest::client cl;
  fouine::rest::request req("127.0.0.1", 80, "/", "hello world\n");
  auto res = cl.get(req);

  ASSERT_FALSE(res);
  ASSERT_EQ(res.error(), "connect: Connection refused");
}
