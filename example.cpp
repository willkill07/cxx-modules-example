import std;
import model;
import util;

int main() try {
  std::println("Hello world!");

  result<model::Diagram> res = model::Diagram::construct();
  if (not res) {
    std::println("{}", res.error());
  }
  auto diagram = std::move(res.value());

  namespace tags = model::tags;

  std::println("Add A: {}", diagram.add_class("A").error_or(""));
  std::println("Add A: {}", diagram.add_class("A").error_or(""));
  std::println("Add B: {}", diagram.add_class("B").error_or(""));
  std::println("Add B: {}", diagram.add_class("B").error_or(""));
  
  std::println(
      "Add A->B: {}",
      diagram.add_relationship(tags::Source{"A"}, tags::Destination{"B"})
          .error_or(""));
  std::println(
      "Add A->B: {}",
      diagram.add_relationship(tags::Source{"A"}, tags::Destination{"B"})
          .error_or(""));

  std::println("Rename A->C: {}",
               diagram.rename_class(tags::OldName{"A"}, tags::NewName{"C"})
                   .error_or(""));
  std::println("Rename A->C: {}",
               diagram.rename_class(tags::OldName{"A"}, tags::NewName{"C"})
                   .error_or(""));

  return 0;
} catch (std::exception const& e) {
  return 1;
}
