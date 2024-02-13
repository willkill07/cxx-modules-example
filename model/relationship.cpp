module;

export module model:relationship_impl;
export import :tags;

import std;
import util;

namespace model {

/**
 * @brief
 *
 */
export class Relationship {
  std::string source_;
  std::string destination_;

public:
  Relationship(tags::Source source, tags::Destination destination);
  [[nodiscard]] std::string_view source() noexcept;
  [[nodiscard]] std::string_view destination() noexcept;
  void rename_source(std::string_view name);
  void rename_destination(std::string_view name);
};

Relationship::Relationship(tags::Source source, tags::Destination destination)
    : source_{source.release()}, destination_{destination.release()} {}

[[nodiscard]] std::string_view Relationship::source() noexcept {
  return source_;
}

[[nodiscard]] std::string_view Relationship::destination() noexcept {
  return destination_;
}

void Relationship::rename_source(std::string_view name) { source_ = name; }

void Relationship::rename_destination(std::string_view name) {
  destination_ = name;
}

} // namespace model
