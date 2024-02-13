module;

export module model:class_impl;
export import :attribute_impl;
export import :tags;
export import :errors;

import std;
import util;

namespace model {

/**
 * @brief Represents a UML class object
 *
 */
export class Class {
  std::string name_;
  std::list<Attribute> attributes_;

public:
  explicit Class(std::string_view name);
  [[nodiscard]] std::string_view name() const noexcept;
  void rename(std::string_view new_name);
  [[nodiscard]] result<void> add_attribute(std::string_view name);
  [[nodiscard]] result<void> remove_attribute(std::string_view name);
  [[nodiscard]] result<void> rename_attribute(tags::OldName old_name,
                                              tags::NewName new_name);
};

Class::Class(std::string_view name) : name_{name} {}

std::string_view Class::name() const noexcept { return name_; }

void Class::rename(std::string_view new_name) { name_ = new_name; }

result<void> Class::add_attribute(std::string_view name) {
  if (std::ranges::find(attributes_, name, &Attribute::name) !=
      std::ranges::end(attributes_)) {
    return result<void>{std::unexpect, std::format("{} {}: {}", "attribute", errors::already_exists, name)};
  } else {
    attributes_.emplace_back(name);
    return result<void>{};
  }
}

result<void> Class::remove_attribute(std::string_view name) {
  if (auto iter = std::ranges::find(attributes_, name, &Attribute::name);
      iter == std::ranges::end(attributes_)) {
    return result<void>{std::unexpect, std::format("{} {}: {}", "attribute", errors::does_not_exist, name)};
  } else {
    attributes_.erase(iter);
    return result<void>{};
  }
}

result<void> Class::rename_attribute(tags::OldName old_name,
                                     tags::NewName new_name) {
  if (auto iter =
          std::ranges::find(attributes_, old_name.get(), &Attribute::name);
      iter == std::ranges::end(attributes_)) {
    return result<void>{std::unexpect, std::format("{} old name {}: {}", "attribute", errors::does_not_exist, old_name.get())};
  } else if (std::ranges::find(attributes_, new_name.get(), &Attribute::name) !=
             std::ranges::end(attributes_)) {
    return result<void>{std::unexpect, std::format("{} new name {}: {}", "attribute", errors::already_exists, old_name.get())};
  } else {
    iter->rename(new_name.get());
    return result<void>{};
  }
}

} // namespace model
