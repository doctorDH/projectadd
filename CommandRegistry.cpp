#include "CommandRegistry.h"
#include <iostream>
#include <sstream>

// 析构：遍历 map，逐一 delete handler 指针（裸指针所有权管理）
CommandRegistry::~CommandRegistry() {
    for (auto& pair : commands_) {
        delete pair.second;
    }
    commands_.clear();
}

void CommandRegistry::registerCommand(const std::string& name, CommandHandler* handler) {
    commands_[name] = handler;
}

// Task 3.1: 输入行解析 — 按空格拆分为 token 列表
std::vector<std::string> CommandRegistry::tokenize(const std::string& line) {
    std::vector<std::string> tokens;
    std::istringstream iss(line);
    std::string token;
    while (iss >> token) {
        tokens.push_back(token);
    }
    return tokens;
}

// Task 3.2: 命令分发执行 + 未知命令错误提示
void CommandRegistry::execute(const std::string& line) {
    std::vector<std::string> tokens = tokenize(line);
    if (tokens.empty()) return;

    const std::string& cmdName = tokens[0];
    std::vector<std::string> args(tokens.begin() + 1, tokens.end());

    auto it = commands_.find(cmdName);
    if (it != commands_.end()) {
        it->second->execute(args);
    } else {
        std::cout << "不支持的命令: " << cmdName << std::endl;
    }
}
