module;

export module cmd:types;
import std;
import util;

export namespace cmd::types {

enum class CommandType : int {
  add_class,
  remove_class,
  rename_class,
  add_attribute,
  remove_attribute,
  rename_attribute,
  add_relationship,
  remove_relationship,
  save,
  load,
  exit
};

[[nodiscard]] auto command_type_from_string(std::string_view str) noexcept
    -> result<CommandType> {
  const static auto map = [] {
    std::unordered_map<std::string_view, CommandType> m;
    m.reserve(11);
    m["add_class"] = CommandType::add_class;
    m["remove_class"] = CommandType::remove_class;
    m["rename_class"] = CommandType::rename_class;
    m["add_attribute"] = CommandType::add_attribute;
    m["remove_attribute"] = CommandType::remove_attribute;
    m["rename_attribute"] = CommandType::rename_attribute;
    m["add_relationship"] = CommandType::add_relationship;
    m["remove_relationship"] = CommandType::remove_relationship;
    m["save"] = CommandType::save;
    m["load"] = CommandType::load;
    m["exit"] = CommandType::exit;
    return m;
  }();
  if (auto iter = map.find(str); iter == map.end()) {
    return error("invalid command specified: {}", str);
  } else {
    return iter->second;
  }
}

} // namespace cmd::types
