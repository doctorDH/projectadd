#include "Shell.h"
#include "commands/LsCommand.h"
#include "commands/ExitCommand.h"
#include "commands/PwdCommand.h"
#include "commands/CdCommand.h"
#include "commands/MkdirCommand.h"
#include "commands/RmCommand.h"
#include "commands/EchoCommand.h"
#include "commands/CatCommand.h"
#include "commands/CpCommand.h"
#include "commands/MvCommand.h"
#include <iostream>
#include <string>
#include <windows.h>   // Task 4.1: SetConsoleOutputCP

// Task 4.1: 构造函数 — UTF-8 编码初始化 + 命令注册
Shell::Shell() {
    // 同时设置输入和输出代码页为 UTF-8
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);

    // 强制控制台使用 UTF-8 模式（解决 VS 调试控制台乱码）
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);

    // 注册内置命令（Registry 接管所有权，析构时自动 delete）
    registry_.registerCommand("ls",    new LsCommand());
    registry_.registerCommand("exit",  new ExitCommand());
    registry_.registerCommand("quit",  new ExitCommand());
    registry_.registerCommand("pwd",   new PwdCommand());
    registry_.registerCommand("cd",    new CdCommand());
    registry_.registerCommand("mkdir", new MkdirCommand());
    registry_.registerCommand("rm",    new RmCommand());
    registry_.registerCommand("echo",  new EchoCommand());
    registry_.registerCommand("cat",   new CatCommand());
    registry_.registerCommand("cp",    new CpCommand());
    registry_.registerCommand("mv",    new MvCommand());
}

// Task 3.3 + 3.4 + 3.5: 主循环实现
void Shell::run() {
    std::string line;

    while (true) {
        // 显示提示符（持续命令循环 Scenario: 正常启动循环）
        std::cout << ">>" << std::flush;

        // Task 3.3: 整行读取（getline 替代 cin >>，保留全部参数）
        if (!std::getline(std::cin, line)) {
            break;  // EOF（管道结束或重定向结束）
        }

        // Task 3.4: 空行处理 — 直接 continue，不分发
        if (line.empty()) {
            continue;
        }

        // Task 3.5: 退出控制 — 在分发前拦截 exit/quit
        if (line == "exit" || line == "quit") {
            break;
        }

        // 分发执行（命令分发 + 未知命令错误提示 均在 Registry 中处理）
        registry_.execute(line);
    }
}
