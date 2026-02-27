#include "MvCommand.h"
#include <iostream>
#include <filesystem>

void MvCommand::execute(const std::vector<std::string>& args) {
    // Scenario 3.5: 参数不足
    if (args.size() < 2) {
        std::cout << "用法: mv <源路径> <目标路径>" << std::endl;
        return;
    }

    std::filesystem::path src(args[0]);
    std::filesystem::path dst(args[1]);

    // Scenario 3.4: 源路径不存在
    if (!std::filesystem::exists(src)) {
        std::cout << "mv: 源路径不存在: " << args[0] << std::endl;
        return;
    }

    // Scenario 3.2: 目标是已存在的目录，则将源移入该目录下（保持原文件名）
    if (std::filesystem::is_directory(dst)) {
        dst = dst / src.filename();
    }

    std::error_code ec;
    // Scenario 3.1 / 3.2 / 3.3: 移动/重命名
    std::filesystem::rename(src, dst, ec);

    if (ec) {
        std::cout << "mv: 移动失败: " << ec.message() << std::endl;
    } else {
        std::cout << "已移动: " << args[0] << " -> " << dst.string() << std::endl;
    }
}
