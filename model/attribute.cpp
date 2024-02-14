module;

export module model:attribute_impl;

import std;
import util;

namespace model {

export class Attribute {
  std::string name_;
  explicit Attribute(std::string_view name) : name_{name} {}

public:
  Attribute() = delete;
  constexpr Attribute(Attribute &&) noexcept = default;
  Attribute &operator=(Attribute &&) noexcept = default;
  constexpr Attribute(Attribute const &) noexcept = delete;
  constexpr Attribute &operator=(Attribute const &) noexcept = delete;

  static result<Attribute> construct(std::string_view name) noexcept {
    try {
      return Attribute{name};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto name() const noexcept -> std::string_view { return name_; }

  [[nodiscard]] auto
  rename(std::string_view new_name) noexcept -> result<void> {
    try {
      name_ = new_name;
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }
};

} // namespace model