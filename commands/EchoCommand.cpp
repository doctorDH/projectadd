#include "EchoCommand.h"
#include <iostream>
#include <string>

void EchoCommand::execute(const std::vector<std::string>& args) {
    // Scenario 5.4: 无参数，输出空行
    if (args.empty()) {
        std::cout << std::endl;
        return;
    }

    // Scenario 5.1 / 5.2 / 5.3: 将所有参数用空格拼接后输出
    for (size_t i = 0; i < args.size(); ++i) {
        if (i > 0) std::cout << " ";
        std::cout << args[i];
    }
    std::cout << std::endl;
}
