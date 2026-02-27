# Tasks: advanced-unix-commands

## 关于 design.md

> 本次 Change 跳过 design.md。
> 理由：与 basic-unix-commands 相同——完全复用已有架构，实现方案唯一
>（`std::ifstream` 读文件、`std::filesystem::copy_file/rename`），无关键决策需权衡。

---

## Task 1: 新增 CatCommand

**做什么**：在 `commands/` 下新建 `CatCommand.h` 和 `CatCommand.cpp`，
实现 `execute()`：取 `args[0]` 作为文件路径，用 `std::ifstream` 逐行读取并输出；
路径不存在或是目录时输出友好错误；无参数时输出用法提示。

**验证方式**：
- 输入 `cat hello.txt`（存在）→ 逐行输出内容（Scenario 1.1）
- 文件含中文 → 正确输出不乱码（Scenario 1.2）
- 输入 `cat ghost.txt`（不存在）→ 输出错误信息，不崩溃（Scenario 1.3）
- 输入 `cat commands`（目录）→ 输出"不是文件"错误（Scenario 1.4）
- 输入 `cat`（无参数）→ 输出用法提示（Scenario 1.5）

---

## Task 2: 新增 CpCommand

**做什么**：在 `commands/` 下新建 `CpCommand.h` 和 `CpCommand.cpp`，
实现 `execute()`：取 `args[0]` 为源路径、`args[1]` 为目标路径，
调用 `std::filesystem::copy_file()` 并传入 `copy_options::overwrite_existing`；
源文件不存在或参数不足时输出友好提示。

**验证方式**：
- 输入 `cp a.txt b.txt`（b.txt 不存在）→ b.txt 被创建，输出成功提示（Scenario 2.1）
- 输入 `cp a.txt b.txt`（b.txt 已存在）→ b.txt 被覆盖，输出成功提示（Scenario 2.2）
- 输入 `cp ghost.txt b.txt` → 输出源文件不存在错误（Scenario 2.3）
- 输入 `cp a.txt` 或 `cp` → 输出用法提示（Scenario 2.4）

---

## Task 3: 新增 MvCommand

**做什么**：在 `commands/` 下新建 `MvCommand.h` 和 `MvCommand.cpp`，
实现 `execute()`：取 `args[0]` 为源路径、`args[1]` 为目标路径，
调用 `std::filesystem::rename()`；
若目标是已存在的目录则将源文件移入该目录下（保持原文件名）；
源路径不存在或参数不足时输出友好提示。

**验证方式**：
- 输入 `mv old.txt new.txt` → old.txt 消失，new.txt 出现（Scenario 3.1）
- 输入 `mv a.txt subdir`（subdir 是目录）→ subdir\a.txt 出现（Scenario 3.2）
- 输入 `mv olddir newdir` → 目录被重命名（Scenario 3.3）
- 输入 `mv ghost.txt new.txt` → 输出源路径不存在错误（Scenario 3.4）
- 输入 `mv a.txt` 或 `mv` → 输出用法提示（Scenario 3.5）

---

## Task 4: 在 Shell.cpp 中注册新命令

**做什么**：在 `Shell.cpp` 中 `#include` 3 个新命令头文件，
并在构造函数中调用 `registry_.registerCommand()` 完成注册。

**验证方式**：
- 编译通过，无 LNK2019 错误
- Shell 启动后 cat / cp / mv 均可响应

---

## Task 5: 更新 .vcxproj 项目文件

**做什么**：在 `projectsdd.vcxproj` 中添加 6 个新条目：
3 个 `<ClCompile>` (`.cpp`) + 3 个 `<ClInclude>` (`.h`)。

**验证方式**：
- VS IDE F5 启动，编译成功，无 LNK2019 错误
