#include "MkdirCommand.h"
#include <iostream>
#include <filesystem>

void MkdirCommand::execute(const std::vector<std::string>& args) {
    // Scenario 3.3: 无参数
    if (args.empty()) {
        std::cout << "用法: mkdir <目录名>" << std::endl;
        return;
    }

    std::filesystem::path dirPath(args[0]);

    if (std::filesystem::exists(dirPath)) {
        // Scenario 3.2: 目录已存在
        std::cout << "mkdir: 目录已存在: " << args[0] << std::endl;
        return;
    }

    std::error_code ec;
    std::filesystem::create_directory(dirPath, ec);

    if (ec) {
        std::cout << "mkdir: 创建失败: " << ec.message() << std::endl;
    } else {
        // Scenario 3.1: 创建成功
        std::cout << "已创建目录: " << args[0] << std::endl;
    }
}
