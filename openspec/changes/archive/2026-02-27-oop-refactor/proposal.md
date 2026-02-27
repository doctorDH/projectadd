## Why

当前实现将所有逻辑集中在 main() 函数的 if-else 链中，导致每新增一条命令都需要修改核心逻辑，无法扩展。重构为 OOP 架构以支持后续持续添加 Unix 命令。

## What Changes

- **BREAKING**: main.cpp 从单文件重构为多文件项目结构
- 引入 Shell 类，负责主循环与输入读取
- 引入抽象基类 CommandHandler，定义命令接口
- 引入 CommandRegistry，负责命令注册与分发
- 将 ls、exit 迁移为独立的 Command 类
- 修复命令行参数解析（整行读取替代单词读取）
- 修复中文错误信息乱码问题

## Capabilities

### New Capabilities
- `shell-core`: Shell 主循环行为，包括输入读取、提示符显示、退出控制
- `command-system`: 命令注册、分发与错误处理行为

### Modified Capabilities

（无，这是首次建立规格基线）

## Impact

- 影响文件：main.cpp（拆分重构）
- 新增文件：Shell.h/cpp、Command.h、CommandRegistry.h/cpp、commands/LsCommand.h/cpp、commands/ExitCommand.h/cpp
- 无外部依赖变更
