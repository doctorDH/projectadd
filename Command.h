#pragma once
#include <string>
#include <vector>

// 所有命令处理器的抽象基类
class CommandHandler {
public:
    // 执行命令，args 为命令后的参数列表（不含命令名本身）
    virtual void execute(const std::vector<std::string>& args) = 0;

    // 虚析构函数，防止派生类析构时发生切片问题
    virtual ~CommandHandler() = default;
};
