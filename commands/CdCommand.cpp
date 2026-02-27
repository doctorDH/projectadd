#include "CdCommand.h"
#include <iostream>
#include <filesystem>

void CdCommand::execute(const std::vector<std::string>& args) {
    // Scenario 2.4: 无参数
    if (args.empty()) {
        std::cout << "用法: cd <目录>" << std::endl;
        return;
    }

    std::filesystem::path newPath(args[0]);
    std::error_code ec;
    std::filesystem::current_path(newPath, ec);

    if (ec) {
        // Scenario 2.3: 目标目录不存在或无权限
        std::cout << "cd: 目录不存在: " << args[0] << std::endl;
    }
    // Scenario 2.1 / 2.2: 切换成功，无需输出
}
