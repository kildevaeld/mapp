#include <args.hxx>
#include <iostream>
#include <mapp/application.hpp>
#include <mapp/command.hpp>

Command::Command(Application *app) : m_app(app) {}

Command::~Command() {}

void Command::command(args::ArgumentParser &parser, const std::string &name,
                      const std::string &help) {
  m_command = std::unique_ptr<args::Command>(
      new args::Command(parser, name, help,
                        [this](args::Subparser &sub) { this->execute(sub); }));
}

args::Command &Command::command() { return *m_command; }

void Command::exit(const std::string &msg) {
  std::cerr << "exit " << msg << std::endl;
  std::exit(1);
}

void Command::init() {
  m_command = std::unique_ptr<args::Command>(
      new args::Command(m_app->parser(), name(), help(),
                        [this](args::Subparser &sub) { this->execute(sub); }));
}

SimpleCommand::SimpleCommand(Application *app, const std::string &name,
                             const std::string &help,
                             std::function<bool(args::Subparser &)> fn)
    : Command(app), m_name(name), m_help(help), m_fn(fn) {}

SimpleCommand::~SimpleCommand() {}

bool SimpleCommand::execute(args::Subparser &a) { return m_fn(a); }

std::string SimpleCommand::name() const { return m_name; }
std::string SimpleCommand::help() const { return m_help; }