#pragma once
#include "CommandRegistry.h"

// Shell 主类：负责主循环、输入读取、编码初始化、命令注册
class Shell {
public:
    // 构造函数：初始化 UTF-8 编码输出，注册所有内置命令
    Shell();

    // 启动主循环：显示提示符 >> 等待输入，直到用户 exit/quit
    void run();

private:
    CommandRegistry registry_;
};
