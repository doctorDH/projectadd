#include "CpCommand.h"
#include <iostream>
#include <filesystem>

void CpCommand::execute(const std::vector<std::string>& args) {
    // Scenario 2.4: 参数不足
    if (args.size() < 2) {
        std::cout << "用法: cp <源路径> <目标路径>" << std::endl;
        return;
    }

    std::filesystem::path src(args[0]);
    std::filesystem::path dst(args[1]);

    // Scenario 2.3: 源文件不存在
    if (!std::filesystem::exists(src)) {
        std::cout << "cp: 源文件不存在: " << args[0] << std::endl;
        return;
    }

    std::error_code ec;
    // Scenario 2.1 / 2.2: 复制（overwrite_existing 覆盖已存在目标）
    std::filesystem::copy_file(src, dst,
        std::filesystem::copy_options::overwrite_existing, ec);

    if (ec) {
        std::cout << "cp: 复制失败: " << ec.message() << std::endl;
    } else {
        std::cout << "已复制: " << args[0] << " -> " << args[1] << std::endl;
    }
}
