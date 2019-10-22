// Copyright 2018 Apex.AI, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <stdio.h>
#include <gtest/gtest.h>

#include "osrf_testing_tools_cpp/scope_exit.hpp"

#include "rcl_yaml_param_parser/parser.h"

#include "rcutils/allocator.h"
#include "rcutils/error_handling.h"
#include "rcutils/filesystem.h"

static char cur_dir[1024];

TEST(test_parser, correct_syntax) {
  rcutils_reset_error();
  // EXPECT_TRUE(rcutils_get_cwd(cur_dir, 1024)) << rcutils_get_error_string().str;
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  // char * test_path = rcutils_join_path(cur_dir, "test", allocator);
  // ASSERT_TRUE(NULL != test_path) << rcutils_get_error_string().str;
  // OSRF_TESTING_TOOLS_CPP_SCOPE_EXIT({
  //   allocator.deallocate(test_path, allocator.state);
  // });
  char * test_path = "/home/brian/ros2_ws/src/ros2/rcl/rcl_yaml_param_parser/test/";
  char * path = rcutils_join_path(test_path, "parameter_descriptors.yaml", allocator);
  ASSERT_TRUE(NULL != path) << rcutils_get_error_string().str;
  OSRF_TESTING_TOOLS_CPP_SCOPE_EXIT({
    allocator.deallocate(path, allocator.state);
  });
  ASSERT_TRUE(rcutils_exists(path)) << "No test YAML file found at " << path;
  rcl_params_t * params_hdl = rcl_yaml_node_struct_init(allocator);
  ASSERT_TRUE(NULL != params_hdl) << rcutils_get_error_string().str;
  OSRF_TESTING_TOOLS_CPP_SCOPE_EXIT({
    rcl_yaml_node_struct_fini(params_hdl);
  });
  bool res = rcl_parse_yaml_file(path, params_hdl);
  ASSERT_TRUE(res) << rcutils_get_error_string().str;

  rcl_yaml_node_struct_print(params_hdl);
}


int32_t main(int32_t argc, char ** argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
