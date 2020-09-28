#pragma once

#include <string_view>

namespace reference
{
    [[nodiscard]] constexpr int get_length_of_longest_common_sequence(std::string_view left, std::string_view right)
    {
        int result = 0;
        for (size_t i = 0; i < left.size(); ++i)
        {
            for (size_t length = 1; length <= left.size() - i; ++length)
            {
                auto substring = left.substr(i, length);
                if (right.find(substring) != std::string::npos && length > result)
                {
                    result = static_cast<int>(length);
                }
            }
        }
        return result;
    }
} // namespace reference