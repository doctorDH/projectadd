#include "ExitCommand.h"

// exit/quit 退出已由 Shell::run() 在分发前拦截处理，
// 此处 execute() 作为兜底（正常情况不会被调用）
void ExitCommand::execute(const std::vector<std::string>& /*args*/) {
    // 退出由 Shell::run() 中的 isRunning_ 标志控制，无需在此处理
}
