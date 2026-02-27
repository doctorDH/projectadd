#include "LsCommand.h"
#include <cstdlib>
#include <string>

void LsCommand::execute(const std::vector<std::string>& args) {
    std::string cmd = "dir";
    for (const auto& arg : args) {
        cmd += " " + arg;
    }
    system(cmd.c_str());
}
