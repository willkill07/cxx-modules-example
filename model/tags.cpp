module;

export module model:tags;

import std;

namespace model {

template <typename T, auto TagT = [] {}> class Tag {
  T value;

protected:
  static constexpr auto tag = TagT;

public:
  explicit Tag(std::convertible_to<T> auto &&value) noexcept : value{value} {}
  [[nodiscard]] T &&release() noexcept { return std::move(value); }
  [[nodiscard]] T get() const noexcept { return value; }
};

namespace tags {

/**
 * @brief 
 * 
 */
export class Source : public Tag<std::string_view> {
public:
  using Tag::Tag;
};

/**
 * @brief 
 * 
 */
export class Destination : public Tag<std::string_view> {
public:
  using Tag::Tag;
};

/**
 * @brief 
 * 
 */
export class OldName : public Tag<std::string_view> {
public:
  using Tag::Tag;
};

/**
 * @brief 
 * 
 */
export class NewName : public Tag<std::string_view> {
public:
  using Tag::Tag;
};

/**
 * @brief 
 * 
 */
export class Class : public Tag<std::string_view> {
public:
  using Tag::Tag;
};

/**
 * @brief 
 * 
 */
export class Attribute : public Tag<std::string_view> {
public:
  using Tag::Tag;
};

} // namespace tags

} // namespace model
