## ADDED Requirements

### Requirement: 持续命令循环
Shell 程序 SHALL 在启动后进入持续循环，每轮显示提示符并等待用户输入，直到用户主动退出。

#### Scenario: 正常启动循环
- **WHEN** 程序启动
- **THEN** 显示 ">>" 提示符并等待输入

#### Scenario: 命令执行后继续循环
- **WHEN** 用户输入并执行一条命令
- **THEN** 命令执行完毕后再次显示 ">>" 提示符

### Requirement: 整行输入读取
Shell 程序 SHALL 将用户的一行输入（包含命令名和所有参数）作为整体读取，不丢失任何内容。

#### Scenario: 带参数的命令输入
- **WHEN** 用户输入 "ls -la /path"
- **THEN** 系统将完整字符串传递给命令解析器，不丢失任何参数

#### Scenario: 空行输入
- **WHEN** 用户直接按下回车，输入为空行
- **THEN** 系统忽略该输入，重新显示 ">>" 提示符

### Requirement: 退出控制
Shell 程序 SHALL 在用户输入 "exit" 或 "quit" 时正常终止程序。

#### Scenario: 输入 exit
- **WHEN** 用户输入 "exit"
- **THEN** 程序正常终止，退出码为 0

#### Scenario: 输入 quit
- **WHEN** 用户输入 "quit"
- **THEN** 程序正常终止，退出码为 0
