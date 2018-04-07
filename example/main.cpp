#include <iostream>
#include <mapp/application.hpp>

class TestCommand : public Command {
public:
  TestCommand(Application *app) : Command(app) {}

  std::string name() const { return "test"; }
  std::string help() const { return ""; }

  virtual bool execute(args::Subparser &) {
    std::cout << "Hello," << std::endl;
    return true;
  }
};

int main(int argc, char **argv) {

  Application app(argc, argv);

  app.command<TestCommand>();

  app.command("list", [](args::Subparser &p) {
    std::cout << "list" << std::endl;
    return true;
  });

  return app.run();
}