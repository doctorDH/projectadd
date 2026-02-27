# Spec: command-system

### Requirement: 命令注册
系统 SHALL 提供命令注册机制，允许将命令名称与其处理器绑定，且同一名称不可重复注册。

#### Scenario: 注册新命令
- **WHEN** 以命令名称和处理器对象注册一条命令
- **THEN** 该命令名称可被后续执行调用识别

### Requirement: 命令分发执行
系统 SHALL 根据用户输入的命令名称查找对应处理器并执行，同时将参数列表传递给处理器。

#### Scenario: 执行已注册命令（无参数）
- **WHEN** 用户输入已注册的命令名（如 "ls"），无附加参数
- **THEN** 对应的处理器被调用，参数列表为空

#### Scenario: 执行已注册命令（带参数）
- **WHEN** 用户输入已注册的命令名及若干参数（如 "ls -la /path"）
- **THEN** 对应的处理器被调用，参数列表包含 ["-la", "/path"]

### Requirement: 未知命令错误提示
系统 SHALL 在用户输入未注册的命令时，输出明确的错误提示，且程序不崩溃。

#### Scenario: 输入未知命令
- **WHEN** 用户输入一个未注册的命令名称
- **THEN** 系统输出 "不支持的命令: <命令名>"，继续等待下一条输入

### Requirement: 命令参数解析
系统 SHALL 将用户输入的整行字符串解析为命令名和参数列表，以空格为分隔符。

#### Scenario: 解析命令名和参数
- **WHEN** 用户输入 "cp source.txt dest.txt"
- **THEN** 命令名为 "cp"，参数列表为 ["source.txt", "dest.txt"]
