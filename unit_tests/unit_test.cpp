#include "gtest/gtest.h"

#include "single_command_test.hpp"
#include "or_test.hpp"
#include "and_test.hpp"
#include "semicolon_test.hpp"
#include "container_test.hpp"
#include "exit_command_test.hpp"
#include "test_command_test.hpp"
#include "input_redir.hpp"
#include "output_redir.hpp"
#include "pipe_redir.hpp"

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
