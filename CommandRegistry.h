#pragma once
#include <map>
#include <string>
#include <vector>
#include "Command.h"

// 命令注册表：负责命令的注册、输入行解析与分发执行
class CommandRegistry {
public:
    CommandRegistry() = default;

    // 析构时释放所有注册的 handler（Registry 拥有所有权）
    ~CommandRegistry();

    // 注册一条命令，Registry 接管 handler 的所有权
    void registerCommand(const std::string& name, CommandHandler* handler);

    // 解析整行输入并分发执行
    // - 以空格拆分 tokens[0] 为命令名，tokens[1..] 为参数
    // - 命令未注册时输出错误提示
    void execute(const std::string& line);

private:
    std::map<std::string, CommandHandler*> commands_;

    // 将输入行按空格拆分为 token 列表
    static std::vector<std::string> tokenize(const std::string& line);
};
