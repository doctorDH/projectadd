# Tasks: basic-unix-commands

## 关于 design.md

> 本次 Change 跳过 design.md。
> 理由：所有命令均复用已有 Command Pattern + Registry 架构，无架构变动；
> 实现方案唯一（`std::filesystem` C++17 标准库），不存在需要权衡取舍的关键决策。
> 原则：design.md 仅在"架构新增"或"多方案取舍"时才有价值，纯功能扩展可跳过。

---

## Task 1: 新增 PwdCommand

**做什么**：在 `commands/` 下新建 `PwdCommand.h` 和 `PwdCommand.cpp`，
实现 `execute()`：调用 `std::filesystem::current_path()` 并输出到 `std::cout`。

**验证方式**：
- 运行 Shell，输入 `pwd` → 输出当前目录绝对路径（对应 Scenario 1.1）
- 路径含中文时输出不乱码（对应 Scenario 1.2）
- 输入 `pwd foo` 时照常输出路径，不报错（对应 Scenario 1.3）

---

## Task 2: 新增 CdCommand

**做什么**：在 `commands/` 下新建 `CdCommand.h` 和 `CdCommand.cpp`，
实现 `execute()`：取 `args[0]` 作为目标路径，调用 `std::filesystem::current_path(newPath)`，
捕获异常并输出友好错误信息；无参数时输出用法提示。

**验证方式**：
- 输入 `cd <存在的相对路径>` → 切换成功，后续 `pwd` 输出新路径（Scenario 2.1）
- 输入 `cd C:\Windows` → 切换到绝对路径（Scenario 2.2）
- 输入 `cd nonexistent` → 打印错误信息，工作目录不变（Scenario 2.3）
- 输入 `cd`（无参数）→ 打印用法提示（Scenario 2.4）

---

## Task 3: 新增 MkdirCommand

**做什么**：在 `commands/` 下新建 `MkdirCommand.h` 和 `MkdirCommand.cpp`，
实现 `execute()`：取 `args[0]` 作为目录名，调用 `std::filesystem::create_directory()`，
目录已存在时输出错误提示；无参数时输出用法提示。

**验证方式**：
- 输入 `mkdir newdir` → 目录被创建，输出成功提示（Scenario 3.1）
- 再次输入 `mkdir newdir` → 输出"目录已存在"错误，不崩溃（Scenario 3.2）
- 输入 `mkdir`（无参数）→ 打印用法提示（Scenario 3.3）

---

## Task 4: 新增 RmCommand

**做什么**：在 `commands/` 下新建 `RmCommand.h` 和 `RmCommand.cpp`，
实现 `execute()`：取 `args[0]` 作为路径，调用 `std::filesystem::remove()`，
路径不存在时输出错误提示；无参数时输出用法提示。

**验证方式**：
- 输入 `rm test.txt`（文件存在）→ 文件被删除，输出成功提示（Scenario 4.1）
- 输入 `rm emptydir`（空目录存在）→ 目录被删除，输出成功提示（Scenario 4.2）
- 输入 `rm ghost.txt`（不存在）→ 输出错误信息，不崩溃（Scenario 4.3）
- 输入 `rm`（无参数）→ 打印用法提示（Scenario 4.4）

---

## Task 5: 新增 EchoCommand

**做什么**：在 `commands/` 下新建 `EchoCommand.h` 和 `EchoCommand.cpp`，
实现 `execute()`：将 `args` 中所有元素用空格拼接后输出到 `std::cout`；
无参数时输出一个空行。

**验证方式**：
- 输入 `echo hello` → 输出 `hello`（Scenario 5.1）
- 输入 `echo hello world` → 输出 `hello world`（Scenario 5.2）
- 输入 `echo 你好世界` → 正确输出中文（Scenario 5.3）
- 输入 `echo`（无参数）→ 输出空行（Scenario 5.4）

---

## Task 6: 在 Shell.cpp 中注册新命令

**做什么**：在 `Shell.cpp` 中 `#include` 5 个新命令头文件，
并在构造函数中调用 `registry_.registerCommand()` 完成注册。

**验证方式**：
- 编译通过，无 LNK2019 错误
- Shell 启动后以上 5 个命令均可响应

---

## Task 7: 更新 .vcxproj 项目文件

**做什么**：在 `projectsdd.vcxproj` 中添加 10 个新条目：
5 个 `<ClCompile>` (`.cpp`) + 5 个 `<ClInclude>` (`.h`)，
对应 Task 1~5 新增的文件。

**验证方式**：
- VS IDE 中直接"本地 Windows 调试器"启动，编译成功，无 LNK2019 错误
- （此步骤是 oop-refactor 中遇到的真实坑，提前规避）
