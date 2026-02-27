# Proposal: basic-unix-commands

## 背景

`oop-refactor` 已建立多文件 OOP 架构，CommandRegistry 可零改动地扩展新命令。
但当前 Shell 实际可用命令只有 `ls` 和 `exit`，不具备任何实用价值。

## 目标

为 Shell 新增 5 个基础 Unix 命令，使其成为可日常使用的简易目录操作工具：

| Unix 命令 | 功能 | Windows 映射 |
|-----------|------|-------------|
| `pwd`     | 打印当前工作目录 | `std::filesystem::current_path()` |
| `cd`      | 切换工作目录 | `std::filesystem::current_path(newPath)` |
| `mkdir`   | 创建目录 | `std::filesystem::create_directory()` |
| `rm`      | 删除文件或目录 | `std::filesystem::remove()` / `remove_all()` |
| `echo`    | 打印文本到标准输出 | `std::cout` |

## 能力边界

新增 5 个 CommandHandler 子类，在 Shell 构造函数中注册，无需修改核心架构。

## Non-goals（本次不做）

- `cp`、`mv`、`cat` 等涉及文件内容读写的命令（留 Change 3）
- 命令参数的 flag 解析（如 `rm -rf`，留后续专项处理）
- 错误信息的国际化 / 本地化
- 管道（`|`）和重定向（`>`）支持
- 对 `ls` 的重构（当前 `system("dir")` 实现暂保留）
