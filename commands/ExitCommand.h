#pragma once
#include "../Command.h"

// exit 命令：触发 Shell 正常退出（通过标志位协调，不直接调用 exit()）
// 注：exit/quit 退出控制由 Shell::run() 中的关键词检测统一处理，
//     此类保留为命令注册槽，execute() 实现为空（退出已在分发前拦截）
class ExitCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
