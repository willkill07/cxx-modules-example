#include <cstdlib>
import std;
import model;

int main() try {
  std::println("Hello world!");

  model::Diagram diagram;

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

  return EXIT_SUCCESS;
} catch (std::exception const &e) {
  std::println("An unknown exception was encountered during runtime: {}",
               e.what());
}
