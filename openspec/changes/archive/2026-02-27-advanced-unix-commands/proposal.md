# Proposal: advanced-unix-commands

## 背景

`basic-unix-commands` 已实现 pwd/cd/mkdir/rm/echo 五个基础目录操作命令。
但 Shell 仍缺少对文件内容的读取与复制/移动能力，
用户无法查看文件内容、复制或重命名文件，日常使用场景存在明显缺口。

## 目标

为 Shell 新增 3 个文件操作命令：

| Unix 命令 | 功能 | Windows 映射 |
|-----------|------|-------------|
| `cat`     | 读取并输出文件内容 | `std::ifstream` 逐行读取 |
| `cp`      | 复制文件 | `std::filesystem::copy_file()` |
| `mv`      | 移动/重命名文件或目录 | `std::filesystem::rename()` |

## 能力边界

新增 3 个 CommandHandler 子类，在 Shell 构造函数中注册，零改动核心架构。

## Non-goals（本次不做）

- `cat` 的多文件合并输出（如 `cat a.txt b.txt`，留后续）
- `cp -r` 递归复制目录（留后续）
- `mv` 跨磁盘移动的特殊处理
- 管道（`|`）和重定向（`>`）支持
- 进度条或大文件分块读取
