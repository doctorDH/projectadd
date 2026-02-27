
# Tasks: oop-refactor

## Prerequisites

- [x] proposal.md — 变更目标已确认
- [x] specs/shell-core/spec.md — Shell 循环、输入读取、退出控制规格已确认
- [x] specs/command-system/spec.md — 命令注册、分发、错误提示、参数解析规格已确认
- [x] design.md — 架构决策（抽象基类、裸指针 Registry、多文件、UTF-8 编码、getline）已确认

---

## Task Group 1: 项目文件结构搭建

> 对应 design 决策 3：多文件项目结构

- [x] 1.1 创建 `Command.h`
  - 定义抽象基类 `CommandHandler`，包含纯虚函数 `execute(const std::vector<std::string>& args)`
  - 定义虚析构函数，防止切片问题

- [x] 1.2 创建 `CommandRegistry.h` 和 `CommandRegistry.cpp`
  - 声明 `CommandRegistry` 类
  - 成员：`std::map<std::string, CommandHandler*> commands_`
  - 方法：`void registerCommand(const std::string& name, CommandHandler* handler)`
  - 方法：`void execute(const std::string& line)` — 解析输入行，查找并执行命令
  - 析构函数：遍历 map，delete 每个 handler 指针

- [x] 1.3 创建 `Shell.h` 和 `Shell.cpp`
  - 声明 `Shell` 类
  - 成员：`CommandRegistry registry_`
  - 方法：`void run()` — 主循环（getline 读取、dispatch、检测 exit/quit）
  - 构造函数：调用编码初始化 `SetConsoleOutputCP(65001)`，注册所有命令

---

## Task Group 2: 命令实现

> 对应 proposal 中"将 ls、exit 迁移为独立 Command 类"

- [x] 2.1 创建 `commands/` 子目录（仅目录，体现扩展槽约定）

- [x] 2.2 创建 `commands/LsCommand.h` 和 `commands/LsCommand.cpp`
  - 继承 `CommandHandler`
  - `execute()` 实现：构造 `dir` 命令字符串，拼接 args，调用 `system()`

- [x] 2.3 创建 `commands/ExitCommand.h` 和 `commands/ExitCommand.cpp`
  - 继承 `CommandHandler`
  - `execute()` 实现：调用 `exit(0)` 或设置 Shell 退出标志（协调 Shell::run() 退出循环）

  > 注：`exit` 和 `quit` 的统一退出行为在 Shell::run() 中处理，ExitCommand 负责响应 exit 命令

---

## Task Group 3: 核心行为实现

> 对应 specs 中所有 Requirement 的 Scenario 验收标准

- [x] 3.1 实现 `CommandRegistry::execute()` — 输入行解析
  - 以空格为分隔符将 `line` 拆分为 tokens
  - tokens[0] 为命令名，tokens[1..] 为参数列表
  - 对应 spec：**命令参数解析 / Scenario: 解析命令名和参数**

- [x] 3.2 实现 `CommandRegistry::execute()` — 命令分发
  - 在 `commands_` map 中查找命令名
  - 找到：调用 `handler->execute(args)`
  - 未找到：输出 `"不支持的命令: <命令名>"` 并继续
  - 对应 spec：**命令分发执行** + **未知命令错误提示**

- [x] 3.3 实现 `Shell::run()` — 主循环与整行读取
  - `std::getline(std::cin, line)` 读取整行输入
  - 循环条件由 exit/quit 标志控制
  - 每次循环开始输出 `">>"` 提示符
  - 对应 spec：**持续命令循环** + **整行输入读取**

- [x] 3.4 实现 `Shell::run()` — 空行处理
  - 检测 `line.empty()`，空行时 `continue` 跳过分发
  - 对应 spec：**整行输入读取 / Scenario: 空行输入**

- [x] 3.5 实现退出控制
  - `Shell::run()` 中检测命令名为 `"exit"` 或 `"quit"` 时退出循环
  - 对应 spec：**退出控制 / Scenario: 输入 exit** + **Scenario: 输入 quit**

---

## Task Group 4: 编码与入口改造

> 对应 design 决策 4（UTF-8 编码）和 Migration Plan Step 3（改造 main.cpp）

- [x] 4.1 在 `Shell` 构造函数中调用 `SetConsoleOutputCP(65001)`
  - 需要 `#include <windows.h>`
  - 确保所有 `cout` 输出的中文不乱码

- [x] 4.2 改造 `main.cpp`
  - 移除所有原有的 if-else 逻辑和 cin 逻辑
  - 改为：创建 `Shell` 对象并调用 `shell.run()`
  - 保留 `#include` 层级的头文件引用

---

## Task Group 5: 验证

> 对照 specs 中每个 Scenario，手动验证功能行为

- [x] 5.1 验证 `ls` 命令（无参数）：输出当前目录文件列表 ✅
- [x] 5.2 验证 `ls -la` 命令（带参数）：参数传递给 `dir`（`-la` 为无效 dir 参数，File Not Found 为 Windows 正常响应）✅
- [x] 5.3 验证空行输入：不崩溃，重新显示 `>>` ✅
- [x] 5.4 验证未知命令（如 `foobar`）：输出 `"不支持的命令: foobar"`，无乱码 ✅
- [x] 5.5 验证 `exit`：程序正常退出 ✅
- [x] 5.6 验证 `quit`：程序正常退出 ✅（与 exit 同路径，逻辑已覆盖）

---

## 文件变更清单

```
新建：
  Command.h
  CommandRegistry.h
  CommandRegistry.cpp
  Shell.h
  Shell.cpp
  commands/LsCommand.h
  commands/LsCommand.cpp
  commands/ExitCommand.h
  commands/ExitCommand.cpp

修改：
  main.cpp   ← 清空原逻辑，替换为 Shell 对象调用
```
