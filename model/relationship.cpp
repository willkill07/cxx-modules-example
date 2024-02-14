module;

export module model:relationship_impl;
export import :tags;

import std;
import util;

namespace model {

export class Relationship {
  std::string source_;
  std::string destination_;

  Relationship(tags::Source source, tags::Destination destination)
      : source_{source.release()}, destination_{destination.release()} {}

public:
  Relationship() = delete;
  constexpr Relationship(Relationship &&) noexcept = default;
  Relationship &operator=(Relationship &&) noexcept = default;
  constexpr Relationship(Relationship const &) noexcept = delete;
  Relationship &operator=(Relationship const &) noexcept = delete;

  [[nodiscard]] static auto
  construct(tags::Source source,
            tags::Destination destination) noexcept -> result<Relationship> {
    try {
      return Relationship{std::move(source), std::move(destination)};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto source() noexcept -> std::string_view { return source_; }

  [[nodiscard]] auto destination() noexcept -> std::string_view {
    return destination_;
  }

  [[nodiscard]] auto
  rename_source(std::string_view name) noexcept -> result<void> {
    try {
      source_ = name;
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto
  rename_destination(std::string_view name) noexcept -> result<void> {
    try {
      destination_ = name;
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }
};

} // namespace model
