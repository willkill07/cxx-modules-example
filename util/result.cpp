module;

export module util:result;

import std;

export template <typename T> using result = std::expected<T, std::string>;
