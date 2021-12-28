#pragma once

#include <concepts>

template<typename T>
concept HasEquality = requires (T a, T b)
{
    {a == b} -> std::convertible_to<bool>;
};
