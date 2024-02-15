module;

export module model:relationship_impl;
export import :tags;

import std;
import util;

namespace model {

export class Relationship {
  std::shared_ptr<std::string> source_;
  std::shared_ptr<std::string> destination_;

  Relationship(tags::Source source, tags::Destination destination)
      : source_{std::make_shared<std::string>(source.release())},
        destination_{std::make_shared<std::string>(destination.release())} {}

public:
  Relationship() = delete;

  [[nodiscard]] static auto construct(tags::Source source,
                                      tags::Destination destination) noexcept
      -> result<std::shared_ptr<Relationship>> {
    try {
      return std::shared_ptr<Relationship>{
          new Relationship{std::move(source), std::move(destination)}};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto source() noexcept -> std::string_view { return *source_; }

  [[nodiscard]] auto destination() noexcept -> std::string_view {
    return *destination_;
  }

  [[nodiscard]] auto rename_source(std::string_view name) noexcept
      -> result<void> {
    try {
      source_ = std::make_shared<std::string>(name);
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }

  [[nodiscard]] auto rename_destination(std::string_view name) noexcept
      -> result<void> {
    try {
      destination_ = std::make_shared<std::string>(name);
      return {};
    } catch (std::exception const &e) {
      return error("runtime error: {}", e.what());
    }
  }
};

} // namespace model
