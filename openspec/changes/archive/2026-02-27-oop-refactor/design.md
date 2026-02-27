## Context

当前 `main.cpp` 为 30 行的面向过程实现，所有命令逻辑通过 if-else 链处理，
参数解析使用 `cin >>` 导致多参数丢失，中文错误信息因编码问题乱码。
本次重构为多文件 OOP 架构，为后续 Change 2（basic-unix-commands）持续添加命令提供扩展基础。

平台约束：仅 Windows，使用 MSVC 编译器，C++14 标准。

## Goals / Non-Goals

**Goals:**
- 建立可扩展的命令注册/分发架构（新增命令无需修改核心逻辑）
- 修复整行参数解析（`getline` 替代 `cin >>`）
- 修复中文错误信息输出乱码
- 保持 `ls` 和 `exit` 原有功能行为不变

**Non-Goals:**
- 添加新的 Unix 命令（属于 Change 2）
- 实现管道、重定向等高级 Shell 特性
- 跨平台支持（仅针对 Windows）
- 单元测试框架接入（当前阶段不引入）

## Decisions

### 决策 1：命令处理器使用抽象基类而非 std::function

**选择：** 抽象基类 `CommandHandler`
```
class CommandHandler {
public:
    virtual void execute(const std::vector<std::string>& args) = 0;
    virtual ~CommandHandler() = default;
};
```

**备选：** `std::function<void(std::vector<std::string>)>`

**理由：**
- 抽象基类允许每个命令封装**自身状态**（如 `cd` 后续需要记录当前目录）
- 对 OOP 学习目的更直观，体现多态、继承的核心概念
- 析构函数的虚声明确保 Registry 清理时正确调用子类析构

---

### 决策 2：CommandRegistry 使用裸指针 map

**选择：** `std::map<std::string, CommandHandler*>`，Registry 拥有所有权，析构时 delete

**备选：** `std::map<std::string, std::unique_ptr<CommandHandler>>`

**理由：**
- 命令对象生命周期与 Shell/Registry 完全一致，无需共享所有权
- 裸指针 + 显式析构对 C++ 初学者更易理解内存管理概念
- 后续可无破坏性地升级为 `unique_ptr`（仅改 Registry 内部实现）

---

### 决策 3：多文件项目结构

**选择：**
```
main.cpp                      ← 仅含 main()，构建 Shell 并 run()
Shell.h / Shell.cpp           ← 主循环、输入读取、命令分发
Command.h                     ← CommandHandler 抽象基类（纯头文件）
CommandRegistry.h / .cpp      ← 命令注册与查找
commands/
  LsCommand.h / .cpp          ← ls 命令实现
  ExitCommand.h / .cpp        ← exit/quit 命令实现
```

**理由：**
- 每个类一个文件，符合单一职责原则
- `commands/` 子目录形成扩展槽：Change 2 只需在此目录新增文件，
  并在 `main.cpp` 中注册，核心代码零修改
- `Command.h` 纯头文件无需编译单元，减少依赖

---

### 决策 4：编码修复使用 SetConsoleOutputCP

**选择：** 在 `main()` 开头调用 `SetConsoleOutputCP(65001)` 切换为 UTF-8 输出

**备选：** 改用 `wcout` 宽字符输出

**理由：**
- `SetConsoleOutputCP` 一行代码生效，无需修改所有输出语句
- 源文件统一保存为 UTF-8，配合 CP65001 可正确显示中文
- `wcout` 需要全面替换 `cout`，改动范围大且与 `string` 混用复杂

---

### 决策 5：Shell 整行读取使用 getline

**选择：** `std::getline(std::cin, line)` 读取整行，再按空格 split 为 tokens

**备选：** `cin >> word` 逐词读取

**理由：**
- `getline` 保留完整行内容，支持带空格的路径参数（如 `cd "My Documents"`）
- 当前 split 不处理引号，记录为已知限制（后续可扩展）

## Risks / Trade-offs

- **[裸指针内存管理]** Registry 析构时若遗漏 delete 会内存泄漏
  → 在 `CommandRegistry::~CommandRegistry()` 中遍历 map 逐一 delete

- **[system() 命令注入]** `ls` 底层调用 `system("dir " + arg)`，
  恶意参数可执行任意系统命令
  → 当前为学习项目，暂不处理；记录为已知安全限制，生产环境不可直接使用

- **[引号和空格路径]** `split` 按空格分割，`cd "My Documents"` 会被错误解析
  → 当前 spec 未要求支持，记录为已知限制，Change 3 可扩展

- **[CP65001 兼容性]** 旧版 Windows 控制台对 UTF-8 支持不完整
  → 目标环境为 Windows 10+，已知兼容

## Migration Plan

1. 新建各头文件和实现文件（不删除 `main.cpp`）
2. 逐类实现，每个类独立可编译验证
3. 最后修改 `main.cpp`，接入新架构
4. 编译运行，验证 `ls`、`exit`、`quit` 功能与重构前一致
5. 验证未知命令输出正确的中文错误信息（无乱码）
