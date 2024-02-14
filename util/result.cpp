module;

export module util:result;

import std;

export template <typename T> using result = std::expected<T, std::string>;

export template <typename... Args>
auto error(std::string_view fmt, Args... args) noexcept {
  try {
    return std::unexpected(std::vformat(fmt, std::make_format_args(args...)));
  } catch (std::exception const &e) {
    return std::unexpected(std::format("internal format error: {}", e.what()));
  }
}