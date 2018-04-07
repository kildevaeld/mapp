#pragma once
#include "command.hpp"
#include <memory>
#include <uv.h>
#include <vector>

namespace args {
class ArgumentParser;
class Command;
} // namespace args

class Application {

public:
  Application(int argc, char **argv);
  Application(const Application &) = delete;
  ~Application();

  template <typename T, typename... Args> T *command(Args &&... args) {
    T *in = new T(this, std::forward<Args>(args)...);
    this->command(in);
    return in;
  }

  void command(const std::string &name, std::string &help,
               std::function<bool(args::Subparser &)> fn);

  void command(const std::string &name,
               std::function<bool(args::Subparser &)> fn);

  void command(Command *cmd);

  void exit(const std::string &msg);

  args::ArgumentParser &parser() { return *m_parser.get(); }

  int run();

private:
  static void run(uv_async_t *handle);

  char **m_argv;
  int m_argc;
  std::vector<Command *> m_cmds;
  std::vector<args::Command> m_cmds1;
  std::unique_ptr<args::ArgumentParser> m_parser;
};