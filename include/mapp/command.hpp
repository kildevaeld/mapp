#pragma once
#include <memory>
#include <string>
#include <vector>

namespace args {
class ArgumentParser;
class Subparser;
class Command;
} // namespace args

class Application;

class Command {

public:
  Command(Application *app);
  virtual ~Command();

  virtual bool execute(args::Subparser &) = 0;

  virtual std::string name() const = 0;
  virtual std::string help() const = 0;

  Application *app() const { return m_app; }

protected:
  void command(args::ArgumentParser &, const std::string &name,
               const std::string &help = std::string(""));
  void exit(const std::string &message);
  args::Command &command();

private:
  void init();

private:
  friend class Application;
  std::unique_ptr<args::Command> m_command;
  Application *m_app;
};

class SimpleCommand : public Command {
public:
  SimpleCommand(Application *app, const std::string &name,
                const std::string &help,
                std::function<bool(args::Subparser &)> fn);
  virtual ~SimpleCommand();

  virtual bool execute(args::Subparser &);

  virtual std::string name() const;
  virtual std::string help() const;

private:
  std::string m_name;
  std::string m_help;
  std::function<bool(args::Subparser &)> m_fn;
};