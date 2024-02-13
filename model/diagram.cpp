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
                                          std::string_view name) noexcept;

  [[nodiscard]] auto
  rel_iter_from_names(this auto &&self, tags::Source source,
                      tags::Destination destination) noexcept;

public:
  [[nodiscard]] result<void> add_class(std::string_view name);
  [[nodiscard]] result<void> remove_class(std::string_view name);
  [[nodiscard]] result<void> rename_class(tags::OldName old_class_name,
                                          tags::NewName new_class_name);
  [[nodiscard]] result<void> add_relationship(tags::Source source,
                                              tags::Destination destination);
  [[nodiscard]] result<void> remove_relationship(tags::Source source,
                                                 tags::Destination destination);
  [[nodiscard]] result<void> add_attribute(tags::Class class_name,
                                           tags::Attribute attr_name);
  [[nodiscard]] result<void> remove_attribute(tags::Class class_name,
                                              tags::Attribute attr_name);
  [[nodiscard]] result<void> rename_attribute(tags::Class class_name,
                                              tags::OldName old_attr_name,
                                              tags::NewName new_attr_name);
};

auto Diagram::class_iter_from_name(this auto &&self,
                                   std::string_view name) noexcept {
  return std::ranges::find(self.classes_, name, &Class::name);
}

auto Diagram::rel_iter_from_names(this auto &&self, tags::Source source,
                                  tags::Destination destination) noexcept {
  return std::ranges::find_if(self.relationships_, [=](auto &&rel) {
    return rel.source() == source.get() and
           rel.destination() == destination.get();
  });
}

result<void> Diagram::add_class(std::string_view name) {
  if (auto iter = class_iter_from_name(name);
      iter != std::ranges::end(classes_)) {
    return std::unexpected(std::format("{} {}: {}", "class", errors::already_exists, name));
  } else {
    classes_.emplace_back(name);
    return {};
  }
}

result<void> Diagram::remove_class(std::string_view name) {
  if (auto iter = class_iter_from_name(name);
      iter == std::ranges::end(classes_)) {
    return std::unexpected(std::format("{} {}: {}", "class", errors::does_not_exist, name));
  } else {
    classes_.erase(iter);
    return {};
  }
}

result<void> Diagram::rename_class(tags::OldName old_class_name,
                                   tags::NewName new_class_name) {
  if (auto old = class_iter_from_name(old_class_name.get());
      old == std::ranges::end(classes_)) {
    return std::unexpected(std::format("{} {}: {}", "class", errors::does_not_exist, old_class_name.get()));
  } else if (class_iter_from_name(new_class_name.get()) !=
             std::ranges::end(classes_)) {
    return std::unexpected(std::format("new {} name {}: {}", "class", errors::already_exists, new_class_name.get()));
  } else {
    old->rename(new_class_name.get());
    for (Relationship &rel : relationships_) {
      if (rel.source() == old_class_name.get()) {
        rel.rename_source(new_class_name.get());
      }
      if (rel.destination() == old_class_name.get()) {
        rel.rename_destination(new_class_name.get());
      }
    }
    return {};
  }
}

result<void> Diagram::add_relationship(tags::Source source,
                                       tags::Destination destination) {
  if (auto iter = rel_iter_from_names(source, destination);
      iter != std::ranges::end(relationships_)) {
    return std::unexpected(std::format("{} {}", "relationship", errors::already_exists));
  } else if (class_iter_from_name(source.get()) == std::ranges::end(classes_)) {
    return std::unexpected(std::format("source {} {}: {}", "class", errors::does_not_exist, source.get()));
  } else if (class_iter_from_name(destination.get()) ==
             std::ranges::end(classes_)) {
    return std::unexpected(std::format("destination {} {}: {}", "class", errors::does_not_exist, source.get()));
  } else {
    relationships_.emplace_back(source, destination);
    return {};
  }
}

result<void> Diagram::remove_relationship(tags::Source source,
                                          tags::Destination destination) {
  if (auto iter = rel_iter_from_names(source, destination);
      iter == std::ranges::end(relationships_)) {
    return std::unexpected(std::format("{} {}", "relationship", errors::does_not_exist));
  } else {
    relationships_.erase(iter);
    return {};
  }
}

result<void> Diagram::add_attribute(tags::Class class_name,
                                    tags::Attribute attr_name) {
  if (auto cls = class_iter_from_name(class_name.get());
      cls == std::ranges::end(classes_)) {
    return std::unexpected(std::format("{} {}: {}", "class", errors::already_exists, class_name.get()));
  } else {
    return cls->add_attribute(attr_name.get());
  }
}

result<void> Diagram::remove_attribute(tags::Class class_name,
                                       tags::Attribute attr_name) {
  if (auto cls = class_iter_from_name(class_name.get());
      cls == std::ranges::end(classes_)) {
    return std::unexpected(std::format("{} {}: {}", "class", errors::does_not_exist, class_name.get()));
  } else {
    return cls->remove_attribute(attr_name.get());
  }
}

result<void> Diagram::rename_attribute(tags::Class class_name,
                                       tags::OldName old_attr_name,
                                       tags::NewName new_attr_name) {
  if (auto cls = class_iter_from_name(class_name.get());
      cls == std::ranges::end(classes_)) {
    return std::unexpected(std::format("{} {}: {}", "class", errors::does_not_exist, class_name.get()));
  } else {
    return cls->rename_attribute(old_attr_name, new_attr_name);
  }
}

} // namespace model
