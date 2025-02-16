#include "hello.hpp"

#include <userver/utest/utest.hpp>

UTEST(SayHelloTo, Basic) {
  EXPECT_EQ(userver_project::SayHelloTo("Developer"), "Hello, Developer!\n");
  EXPECT_EQ(userver_project::SayHelloTo({}), "Hello, unknown user!\n");
}
