/*
Given a phrase, count the occurrences of each word in that phrase. Ignore whitespaces and punctual symbols
For example for the input "olly olly in come free please please let it be in such manner olly"
olly: 3
in: 2
come: 1
free: 1
please: 2
let: 1
it: 1
be: 1
manner: 1
such: 1
*/

#include <gtest/gtest.h>
#include <string>
#include <map>

std::map<std::string, int> CountWords(const std::string& sentence)
{
    return {{sentence, 1}};
}

TEST(CountWords, OneWordForSingleSymbol)
{
    EXPECT_EQ(1, CountWords("a").size());
}

TEST(CountWords, SameValueForSingleWord)
{
    std::map<std::string, int> expectedWords = {{"hello", 1}};
    EXPECT_EQ(expectedWords, CountWords("hello"));
}

TEST(SplitWords, OneWordFromSentence)
{
    std::map<std::string, int> expectedWords = {{"hello", 1}};
    EXPECT_EQ("a", Split("a b c"));
}
