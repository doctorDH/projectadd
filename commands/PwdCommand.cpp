#include "PwdCommand.h"
#include <iostream>
#include <filesystem>

void PwdCommand::execute(const std::vector<std::string>& args) {
    // 忽略多余参数（Scenario 1.3），直接输出当前路径
    std::cout << std::filesystem::current_path().string() << std::endl;
}
