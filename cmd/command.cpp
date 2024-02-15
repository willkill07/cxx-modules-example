module;

export module cmd:command;
import std;
import util;

export namespace cmd {

class State {
public:
  [[nodiscard]] virtual auto clone() noexcept
      -> result<std::shared_ptr<State>> = 0;
};

class Command {
private:
  std::shared_ptr<State> state_;

protected:
  [[nodiscard]] virtual auto apply(std::shared_ptr<State> const &) noexcept
      -> result<void> = 0;

  [[nodiscard]] auto store(std::shared_ptr<State> const &state) noexcept
      -> result<void> {
    return state->clone().transform(
        [&](std::shared_ptr<State> &&copy) { state_ = std::move(copy); });
  }

public:
  [[nodiscard]] auto undo() noexcept -> std::shared_ptr<State> {
    return state_;
  }

  [[nodiscard]] auto execute(std::shared_ptr<State> const &state) noexcept
      -> result<void> {
    return store(state).and_then([&] { return apply(state); });
  }
};

} // namespace cmd