module;

export module model:diagram_impl;
export import :class_impl;
export import :relationship_impl;
export import :tags;

import std;
import util;

namespace model {

export class Diagram {
  std::list<Class> classes_;
  std::list<Relationship> relationships_;

  [[nodiscard]] auto class_iter_from_name(this auto &&self,
                                          std::string_view name) noexcept {
    return std::ranges::find(self.classes_, name, &Class::name);
  }

  [[nodiscard]] auto
  rel_iter_from_names(this auto &&self, tags::Source source,
                      tags::Destination destination) noexcept {
    return std::ranges::find_if(self.relationships_, [=](auto &&rel) {
      return rel.source() == source.get() and
             rel.destination() == destination.get();
    });
  }

  Diagram() = default;
public:
  Diagram(Diagram &&) noexcept = default;
  Diagram &operator=(Diagram &&) noexcept = default;
  constexpr Diagram(Diagram const &) noexcept = delete;
  constexpr Diagram &operator=(Diagram const &) noexcept = delete;

  [[nodiscard]] static auto construct() noexcept -> result<Diagram> {
    try {
      return Diagram{};
    } catch (std::exception const& e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto add_class(std::string_view name) noexcept -> result<void> {
    if (auto iter = class_iter_from_name(name);
        iter != std::ranges::end(classes_)) {
      return error("{} {}: {}", "class", errors::already_exists, name);
    } else {
      return Class::construct(name).and_then([&](Class &&cls) -> result<void> {
        try {
          classes_.push_back(std::move(cls));
          return {};
        } catch (std::exception const &e) {
          return error("runtime error: {}", e.what());
        }
      });
    }
  }

  [[nodiscard]] auto
  remove_class(std::string_view name) noexcept -> result<void> {
    if (auto iter = class_iter_from_name(name);
        iter == std::ranges::end(classes_)) {
      return error("{} {}: {}", "class", errors::does_not_exist, name);
    } else {
      classes_.erase(iter);
      return {};
    }
  }

  [[nodiscard]] auto
  rename_class(tags::OldName old_class_name,
               tags::NewName new_class_name) noexcept -> result<void> {
    if (auto old = class_iter_from_name(old_class_name.get());
        old == std::ranges::end(classes_)) {
      return error("{} {}: {}", "class", errors::does_not_exist,
                   old_class_name.get());
    } else if (class_iter_from_name(new_class_name.get()) !=
               std::ranges::end(classes_)) {
      return error("new {} name {}: {}", "class", errors::already_exists,
                   new_class_name.get());
    } else {
      if (auto res = old->rename(new_class_name.get()); not res) {
        return res;
      }
      for (Relationship &rel : relationships_) {
        if (rel.source() == old_class_name.get()) {
          if (auto res = rel.rename_source(new_class_name.get()); not res) {
            return res;
          }
        }
        if (rel.destination() == old_class_name.get()) {
          if (auto res = rel.rename_destination(new_class_name.get());
              not res) {
            return res;
          }
        }
      }
      return {};
    }
  }

  [[nodiscard]] auto
  add_relationship(tags::Source source,
                   tags::Destination destination) noexcept -> result<void> {
    if (auto iter = rel_iter_from_names(source, destination);
        iter != std::ranges::end(relationships_)) {
      return error("{} {}", "relationship", errors::already_exists);
    } else if (class_iter_from_name(source.get()) ==
               std::ranges::end(classes_)) {
      return error("source {} {}: {}", "class", errors::does_not_exist,
                   source.get());
    } else if (class_iter_from_name(destination.get()) ==
               std::ranges::end(classes_)) {
      return error("destination {} {}: {}", "class", errors::does_not_exist,
                   source.get());
    } else {
      return Relationship::construct(std::move(source), std::move(destination))
          .and_then([&](Relationship &&rel) -> result<void> {
            try {
              relationships_.push_back(std::move(rel));
              return {};
            } catch (std::exception const &e) {
              return error("runtime error; {}", e.what());
            }
          });
    }
  }

  [[nodiscard]] auto
  remove_relationship(tags::Source source,
                      tags::Destination destination) noexcept -> result<void> {
    if (auto iter = rel_iter_from_names(source, destination);
        iter == std::ranges::end(relationships_)) {
      return error("{} {}", "relationship", errors::does_not_exist);
    } else {
      relationships_.erase(iter);
      return {};
    }
  }

  [[nodiscard]] auto
  add_attribute(tags::Class class_name,
                tags::Attribute attr_name) noexcept -> result<void> {
    if (auto cls = class_iter_from_name(class_name.get());
        cls == std::ranges::end(classes_)) {
      return error("{} {}: {}", "class", errors::already_exists,
                   class_name.get());
    } else {
      return cls->add_attribute(attr_name.get());
    }
  }

  [[nodiscard]] auto
  remove_attribute(tags::Class class_name,
                   tags::Attribute attr_name) noexcept -> result<void> {
    if (auto cls = class_iter_from_name(class_name.get());
        cls == std::ranges::end(classes_)) {
      return error("{} {}: {}", "class", errors::does_not_exist,
                   class_name.get());
    } else {
      return cls->remove_attribute(attr_name.get());
    }
  }

  [[nodiscard]] auto
  rename_attribute(tags::Class class_name, tags::OldName old_attr_name,
                   tags::NewName new_attr_name) noexcept -> result<void> {
    if (auto cls = class_iter_from_name(class_name.get());
        cls == std::ranges::end(classes_)) {
      return error("{} {}: {}", "class", errors::does_not_exist,
                   class_name.get());
    } else {
      return cls->rename_attribute(old_attr_name, new_attr_name);
    }
  }
};

} // namespace model
