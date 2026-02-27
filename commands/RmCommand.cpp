#include "RmCommand.h"
#include <iostream>
#include <filesystem>

void RmCommand::execute(const std::vector<std::string>& args) {
    // Scenario 4.4: 无参数
    if (args.empty()) {
        std::cout << "用法: rm <路径>" << std::endl;
        return;
    }

    std::filesystem::path target(args[0]);

    if (!std::filesystem::exists(target)) {
        // Scenario 4.3: 路径不存在
        std::cout << "rm: 路径不存在: " << args[0] << std::endl;
        return;
    }

    std::error_code ec;
    std::filesystem::remove(target, ec);

    if (ec) {
        std::cout << "rm: 删除失败: " << ec.message() << std::endl;
    } else {
        // Scenario 4.1 / 4.2: 删除成功
        std::cout << "已删除: " << args[0] << std::endl;
    }
}
