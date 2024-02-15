module;

export module model:class_impl;
export import :attribute_impl;
export import :tags;
export import :errors;

import std;
import util;

namespace model {

export class Class {
  std::shared_ptr<std::string> name_;
  std::list<std::shared_ptr<Attribute>> attributes_;

  explicit Class(std::string_view name)
      : name_{std::make_shared<std::string>(name)} {}

public:
  Class() = delete;

  [[nodiscard]] static auto construct(std::string_view name) noexcept
      -> result<std::shared_ptr<Class>> {
    try {
      return std::shared_ptr<Class>{new Class{name}};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] std::string_view name() const noexcept { return *name_; }

  [[nodiscard]] auto rename(std::string_view new_name) noexcept
      -> result<void> {
    try {
      name_ = std::make_shared<std::string>(new_name);
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto add_attribute(std::string_view name) noexcept
      -> result<void> {
    if (std::ranges::find(attributes_, name, &Attribute::name) !=
        std::ranges::end(attributes_)) {
      return error("{} {}: {}", "attribute", errors::already_exists, name);
    } else {
      return Attribute::construct(name).and_then(
          [&](std::shared_ptr<Attribute> &&attr) -> result<void> {
            try {
              attributes_.push_back(attr);
              return {};
            } catch (std::exception const &e) {
              return error("runtime error: {}", e.what());
            }
          });
    }
  }

  [[nodiscard]] auto remove_attribute(std::string_view name) noexcept
      -> result<void> {
    auto copy{attributes_};
    if (auto iter = std::ranges::find(attributes_, name, &Attribute::name);
        iter == std::ranges::end(attributes_)) {
      return error("{} {}: {}", "attribute", errors::does_not_exist, name);
    } else {
      attributes_.erase(iter);
      return result<void>{};
    }
  }

  [[nodiscard]] auto rename_attribute(tags::OldName old_name,
                                      tags::NewName new_name) noexcept
      -> result<void> {
    auto iter =
        std::ranges::find(attributes_, old_name.get(), &Attribute::name);
    if (iter == std::ranges::end(attributes_)) {
      return error("{} old name {}: {}", "attribute", errors::does_not_exist,
                   old_name.get());
    }
    if (std::ranges::find(attributes_, new_name.get(), &Attribute::name) !=
        std::ranges::end(attributes_)) {
      return error("{} new name {}: {}", "attribute", errors::already_exists,
                   old_name.get());
    }
    return (*iter)->rename(new_name.get());
  }
};

} // namespace model
