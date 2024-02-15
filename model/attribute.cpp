module;

export module model:attribute_impl;

import std;
import util;

namespace model {

export class Attribute {
  std::shared_ptr<std::string> name_;
  explicit Attribute(std::string_view name)
      : name_{std::make_shared<std::string>(name)} {}

public:
  Attribute() = delete;

  [[nodiscard]] static auto construct(std::string_view name) noexcept
      -> result<std::shared_ptr<Attribute>> {
    try {
      return std::shared_ptr<Attribute>(new Attribute{name});
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto name() const noexcept -> std::string_view {
    return *name_;
  }

  [[nodiscard]] auto rename(std::string_view new_name) noexcept
      -> result<void> {
    try {
      name_ = std::make_shared<std::string>(new_name);
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }
};

} // namespace model
