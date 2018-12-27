/*
Write a function, that is given a string and a length limit, splits provided string into sequence of string,
where length of each string is not more, than provided limit. If there are spaces under provided limit -
last space should be used to wrapp this line. If there are no spaces - wrapp it on provided length limit.

Example:
When pos is specified, the search only includes sequences of characters that begin at or before position pos,
ignoring any possible match beginning after pos

split(hee, 1) -> h, e, e
split(hee, 2) -> he, e
split("ha ha", 2|3|4) -> "ha", "ha"
split("h a", 1) -> "h", "a"

"When pos is specified, the",
"search only includes sequences",
"of characters that begin at or",
"before position pos, ignoring",
"any possible match beginning",
"after pos."
*/

#include <gtest/gtest.h>
#include <string>
#include <vector>

using StringContainer = std::vector<std::string>;
StringContainer SplitString(const std::string& string, size_t length)
{
    StringContainer result {{ string.substr(0, length) }};
    if (length < string.size()) {
        auto firstSpaceInSubstr = string.rfind(' ', length);
        std::string::size_type offset = length;
        if (firstSpaceInSubstr != std::string::npos)
        {
            result.clear();
            result.push_back(string.substr(0, firstSpaceInSubstr));
            result.push_back(string.substr(firstSpaceInSubstr + 1));
        }
        else
        {
            result.push_back(string.substr(offset));
        }
    }
    return result;
}

TEST(SplitString, OnePartForOneSymbol)
{
    StringContainer parts = {"a"};
    EXPECT_EQ(parts, SplitString("a", 1));
}

TEST(SplitString, AbFirstForAbbaAnd2)
{
    EXPECT_EQ("Ab", SplitString("Abba", 2).at(0));
}

TEST(SplitString, BaSecondForAbbba)
{
    EXPECT_EQ("ba", SplitString("Abba", 2).at(1));
}

TEST(SplitString, AbForAbAnd4)
{
    EXPECT_EQ("Ab", SplitString("Ab", 4).at(0));
}

TEST(SplitString, SplitAb_AbBeforeSpaceReturnsAbAndAb)
{
    StringContainer parts = {"Ab", "Ab"};
    EXPECT_EQ(parts, SplitString("Ab Ab", 2));
}

TEST(SplitString, SplitAb_AbAtSpaceReturnsAbAndAb)
{
    StringContainer parts = {"Ab", "Ab"};
    EXPECT_EQ(parts, SplitString("Ab Ab", 3));
}
