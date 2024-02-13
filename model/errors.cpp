module;

export module model:errors;

import std;

namespace model {
export struct errors {
  constexpr static inline std::string_view does_not_exist{"does not exist"};
  constexpr static inline std::string_view already_exists{"already exists"};
}; // namespace errors

} // namespace model
