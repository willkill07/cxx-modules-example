module;

export module model:attribute_impl;

import std;

namespace model {

export class Attribute {
  std::string name_;
public:
  explicit Attribute(std::string_view name);
  [[nodiscard]] std::string_view name() const noexcept;
  void rename(std::string_view new_name);
};


Attribute::Attribute(std::string_view name) : name_{name} {}

[[nodiscard]] std::string_view Attribute::name() const noexcept { return name_; }

void Attribute::rename(std::string_view new_name) { name_ = new_name; }

}