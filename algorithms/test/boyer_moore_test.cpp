#pragma once

#include <gtest\gtest.h>
#include "..\src\boyer_moore.h"

struct _BoyerMooreTestCases {
#define CASE std::tuple<std::string, std::string, bool>
  const std::vector<CASE> simple = {
    CASE("i really enjoy watching pandas eat bamboo", "p", true),
    CASE("i really enjoy watching pandas eat bamboo", "g pandas ea", true),
    CASE("which finally halts.  at that point", "at that", true),
    CASE("anananananbananab", "ananab", true),
    CASE("bnanabnanabnanabnanabnanabnanabnanabnanabananab", "ananab", true),
    CASE("bnanabnanabnanabnanabnanabnanabnanabnanabananab", "cananab", false),
    CASE("what would a woodchuck chuck if a woodchuck could chuck wood?", "chuck chuck", true)
  };
#undef CASE

#define CASE std::tuple<std::string, std::string, std::vector<size_t>>
  const std::vector<CASE> multi = {
    CASE("bananana", "an", {1, 3, 5}),
    CASE("aaaaa", "aa", {0, 1, 2, 3}),
    CASE("what would a woodchuck chuck if a woodchuck could chuck wood?", "wo", {5, 13, 34, 56}),
    CASE("what would a woodchuck chuck if a woodchuck could chuck wood?", "chuck", {17, 23, 38, 50})
  };
#undef CASE

} BoyerMooreTestCases;


class BoyerMooreTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, bool>> {};

TEST_P(BoyerMooreTest, SimpleTest) {
  auto text = std::get<0>(GetParam());
  auto pattern = std::get<1>(GetParam());
  auto expect_success = std::get<2>(GetParam());

  auto index = algorithm::search(text, pattern);
  if (expect_success) {
    EXPECT_GT(index, -1);
    EXPECT_STREQ(pattern.c_str(), text.substr(index, pattern.size()).c_str());
  }
  else {
    EXPECT_EQ(-1, index);
  }
}

INSTANTIATE_TEST_CASE_P(Simple, BoyerMooreTest, ::testing::ValuesIn(BoyerMooreTestCases.simple));


class MultiBoyerMooreTest : public ::testing::TestWithParam<std::tuple<std::string, std::string, std::vector<size_t>>> {};

TEST_P(MultiBoyerMooreTest, MultiTest) {
  auto text = std::get<0>(GetParam());
  auto pattern = std::get<1>(GetParam());
  auto expected_indices = std::get<2>(GetParam());

  auto indices = algorithm::search_all(text, pattern);

  EXPECT_EQ(expected_indices, indices);
  for (auto& index : indices)
  EXPECT_STREQ(pattern.c_str(), text.substr(index, pattern.size()).c_str());
}

INSTANTIATE_TEST_CASE_P(Simple, MultiBoyerMooreTest, ::testing::ValuesIn(BoyerMooreTestCases.multi));

