# Spec: basic-unix-commands

## Capability 1: pwd —— 打印当前工作目录

**描述**：用户输入 `pwd`，Shell SHALL 输出当前进程的工作目录绝对路径，并换行。

### Scenario 1.1 正常路径
- Given: Shell 正在运行，当前工作目录为任意有效路径（如 `C:\Users\dev`）
- When: 用户输入 `pwd`
- Then: 标准输出打印该绝对路径字符串，末尾换行

### Scenario 1.2 路径包含中文
- Given: 当前工作目录路径包含中文字符（如 `C:\用户\桌面`）
- When: 用户输入 `pwd`
- Then: 标准输出正确打印含中文的路径，不出现乱码

### Scenario 1.3 附带多余参数
- Given: 用户输入 `pwd somearg`
- When: 命令执行
- Then: 忽略多余参数，照常打印当前路径（不报错）

---

## Capability 2: cd —— 切换工作目录

**描述**：用户输入 `cd <目标路径>`，Shell SHALL 将进程当前工作目录切换到指定路径。

### Scenario 2.1 切换到已存在的目录（相对路径）
- Given: 当前目录下存在子目录 `foo`
- When: 用户输入 `cd foo`
- Then: 进程工作目录变为 `<原路径>\foo`，下次 `pwd` 输出新路径

### Scenario 2.2 切换到已存在的目录（绝对路径）
- Given: 目录 `C:\Windows` 存在
- When: 用户输入 `cd C:\Windows`
- Then: 进程工作目录变为 `C:\Windows`

### Scenario 2.3 目标目录不存在
- Given: 目标路径不存在
- When: 用户输入 `cd nonexistent`
- Then: 标准输出打印错误信息（如 `cd: 目录不存在: nonexistent`），工作目录不变

### Scenario 2.4 未提供路径参数
- Given: 用户仅输入 `cd`（无参数）
- When: 命令执行
- Then: 标准输出打印用法提示（如 `用法: cd <目录>`），工作目录不变

---

## Capability 3: mkdir —— 创建目录

**描述**：用户输入 `mkdir <目录名>`，Shell SHALL 在当前工作目录下创建该目录。

### Scenario 3.1 创建新目录（成功）
- Given: 当前目录下不存在名为 `newdir` 的目录
- When: 用户输入 `mkdir newdir`
- Then: 文件系统中创建该目录，标准输出打印成功提示（如 `已创建目录: newdir`）

### Scenario 3.2 目录已存在
- Given: 当前目录下已存在名为 `newdir` 的目录
- When: 用户输入 `mkdir newdir`
- Then: 标准输出打印错误信息（如 `mkdir: 目录已存在: newdir`），不抛出异常

### Scenario 3.3 未提供目录名
- Given: 用户仅输入 `mkdir`（无参数）
- When: 命令执行
- Then: 标准输出打印用法提示（如 `用法: mkdir <目录名>`）

---

## Capability 4: rm —— 删除文件或目录

**描述**：用户输入 `rm <路径>`，Shell SHALL 删除指定的文件或目录。

### Scenario 4.1 删除已存在的文件
- Given: 当前目录下存在文件 `test.txt`
- When: 用户输入 `rm test.txt`
- Then: 该文件被从文件系统中删除，标准输出打印成功提示（如 `已删除: test.txt`）

### Scenario 4.2 删除已存在的空目录
- Given: 当前目录下存在空目录 `emptydir`
- When: 用户输入 `rm emptydir`
- Then: 该目录被删除，标准输出打印成功提示

### Scenario 4.3 目标路径不存在
- Given: 目标路径不存在
- When: 用户输入 `rm ghost.txt`
- Then: 标准输出打印错误信息（如 `rm: 路径不存在: ghost.txt`），不抛出异常

### Scenario 4.4 未提供路径参数
- Given: 用户仅输入 `rm`（无参数）
- When: 命令执行
- Then: 标准输出打印用法提示（如 `用法: rm <路径>`）

---

## Capability 5: echo —— 打印文本到标准输出

**描述**：用户输入 `echo <文本>`，Shell SHALL 将文本原样输出到标准输出并换行。

### Scenario 5.1 打印单词
- Given: 用户输入 `echo hello`
- When: 命令执行
- Then: 标准输出打印 `hello`，末尾换行

### Scenario 5.2 打印多个词（含空格）
- Given: 用户输入 `echo hello world`
- When: 命令执行
- Then: 标准输出打印 `hello world`（保留词间空格），末尾换行

### Scenario 5.3 打印中文
- Given: 用户输入 `echo 你好世界`
- When: 命令执行
- Then: 标准输出正确打印 `你好世界`，不出现乱码

### Scenario 5.4 无参数（空 echo）
- Given: 用户仅输入 `echo`（无参数）
- When: 命令执行
- Then: 标准输出打印一个空行（与 Unix 行为一致）
