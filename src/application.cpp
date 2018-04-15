#include <args.hxx>
#include <iostream>
#include <mapp/application.hpp>
#include <uv.h>

using commandtype = std::function<void(
    const std::string &, std::vector<std::string>::const_iterator,
    std::vector<std::string>::const_iterator)>;

Application::Application(int argc, char **argv)
    : m_argc(argc), m_argv(argv), m_parser(new args::ArgumentParser("")) {
  uv_setup_args(argc, argv);
}

Application::~Application() {
  for (auto a : m_cmds) {
    delete a;
  }
}

void Application::command(Command *cmd) {
  m_cmds.push_back(cmd);
  cmd->init();
}

void Application::command(const std::string &name, std::string &help,
                          std::function<bool(args::Subparser &)> fn) {
  command(new SimpleCommand(this, name, help, fn));
}

void Application::command(const std::string &name,
                          std::function<bool(args::Subparser &)> fn) {
  command(new SimpleCommand(this, name, "", fn));
}

void Application::exit(const std::string &msg) {
  std::cerr << "exit " << msg << std::endl;
  std::exit(1);
}

void Application::run(uv_async_t *handle) {
  Application *app = static_cast<Application *>(handle->data);
  uv_close((uv_handle_t *)handle, NULL);
  args::HelpFlag h(*app->m_parser, "help", "help", {'h', "help"});

  try {
    bool ret = app->m_parser->ParseCLI(app->m_argc, app->m_argv);

  } catch (args::Help) {
    std::cout << *app->m_parser << std::endl;

  } catch (const args::ParseError &e) {
    std::cerr << e.what() << "\n" << *app->m_parser << std::endl;

  } catch (const args::RequiredError &e) {
    std::cerr << e.what() << "\n" << *app->m_parser << std::endl;
  } catch (const args::ValidationError &e) {
    std::cerr << e.what() << "\n" << *app->m_parser << std::endl;
  } /*catch (...) {
    std::cout << "Heller ikk" << std::endl;
  }*/

  /// uv_close((uv_handle_t *)handle, NULL);
}

int Application::run() {

  uv_async_t async;
  async.data = this;
  uv_async_init(uv_default_loop(), &async, Application::run);
  uv_async_send(&async);
  return uv_run(uv_default_loop(), UV_RUN_DEFAULT);
}

void Application::initialized() {}