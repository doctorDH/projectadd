#include "CatCommand.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>

void CatCommand::execute(const std::vector<std::string>& args) {
    // Scenario 1.5: 无参数
    if (args.empty()) {
        std::cout << "用法: cat <文件路径>" << std::endl;
        return;
    }

    std::filesystem::path filePath(args[0]);

    // Scenario 1.3: 文件不存在
    if (!std::filesystem::exists(filePath)) {
        std::cout << "cat: 文件不存在: " << args[0] << std::endl;
        return;
    }

    // Scenario 1.4: 目标是目录
    if (std::filesystem::is_directory(filePath)) {
        std::cout << "cat: 不是文件: " << args[0] << std::endl;
        return;
    }

    // Scenario 1.1 / 1.2: 逐行读取并输出
    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cout << "cat: 无法打开文件: " << args[0] << std::endl;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::cout << line << std::endl;
    }
}
