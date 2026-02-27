# Spec: advanced-unix-commands

## Capability 1: cat —— 读取并输出文件内容

**描述**：用户输入 `cat <文件路径>`，Shell SHALL 将该文件的全部内容逐行输出到标准输出。

### Scenario 1.1 正常读取文本文件
- Given: 当前目录下存在文件 `hello.txt`，内容为若干行文本
- When: 用户输入 `cat hello.txt`
- Then: 标准输出逐行打印文件内容，末尾换行

### Scenario 1.2 文件包含中文内容
- Given: 文件内容包含中文字符
- When: 用户输入 `cat hello.txt`
- Then: 标准输出正确打印中文内容，不出现乱码

### Scenario 1.3 文件不存在
- Given: 目标文件路径不存在
- When: 用户输入 `cat ghost.txt`
- Then: 标准输出打印错误信息（如 `cat: 文件不存在: ghost.txt`），不崩溃

### Scenario 1.4 目标是目录而非文件
- Given: 目标路径是一个目录（如 `cat commands`）
- When: 命令执行
- Then: 标准输出打印错误信息（如 `cat: 不是文件: commands`），不崩溃

### Scenario 1.5 未提供文件参数
- Given: 用户仅输入 `cat`（无参数）
- When: 命令执行
- Then: 标准输出打印用法提示（如 `用法: cat <文件路径>`）

---

## Capability 2: cp —— 复制文件

**描述**：用户输入 `cp <源路径> <目标路径>`，Shell SHALL 将源文件复制到目标路径。

### Scenario 2.1 复制文件到新路径（成功）
- Given: 当前目录下存在文件 `a.txt`，目标路径 `b.txt` 不存在
- When: 用户输入 `cp a.txt b.txt`
- Then: `b.txt` 被创建，内容与 `a.txt` 完全一致，输出成功提示（如 `已复制: a.txt → b.txt`）

### Scenario 2.2 目标文件已存在（覆盖）
- Given: 源文件 `a.txt` 和目标文件 `b.txt` 均存在
- When: 用户输入 `cp a.txt b.txt`
- Then: `b.txt` 被覆盖为 `a.txt` 的内容，输出成功提示

### Scenario 2.3 源文件不存在
- Given: 源路径不存在
- When: 用户输入 `cp ghost.txt b.txt`
- Then: 标准输出打印错误信息（如 `cp: 源文件不存在: ghost.txt`），不崩溃

### Scenario 2.4 参数不足
- Given: 用户输入 `cp a.txt`（只有一个参数）或仅输入 `cp`
- When: 命令执行
- Then: 标准输出打印用法提示（如 `用法: cp <源路径> <目标路径>`）

---

## Capability 3: mv —— 移动或重命名文件/目录

**描述**：用户输入 `mv <源路径> <目标路径>`，Shell SHALL 将源文件或目录移动/重命名到目标路径。

### Scenario 3.1 重命名文件（成功）
- Given: 当前目录下存在文件 `old.txt`，目标路径 `new.txt` 不存在
- When: 用户输入 `mv old.txt new.txt`
- Then: `old.txt` 消失，`new.txt` 出现且内容一致，输出成功提示（如 `已移动: old.txt → new.txt`）

### Scenario 3.2 移动文件到另一目录（成功）
- Given: 当前目录下存在文件 `a.txt` 和目录 `subdir`
- When: 用户输入 `mv a.txt subdir`
- Then: `a.txt` 消失，`subdir\a.txt` 出现，输出成功提示

### Scenario 3.3 重命名目录（成功）
- Given: 当前目录下存在目录 `olddir`
- When: 用户输入 `mv olddir newdir`
- Then: `olddir` 消失，`newdir` 出现，输出成功提示

### Scenario 3.4 源路径不存在
- Given: 源路径不存在
- When: 用户输入 `mv ghost.txt new.txt`
- Then: 标准输出打印错误信息（如 `mv: 源路径不存在: ghost.txt`），不崩溃

### Scenario 3.5 参数不足
- Given: 用户输入 `mv a.txt`（只有一个参数）或仅输入 `mv`
- When: 命令执行
- Then: 标准输出打印用法提示（如 `用法: mv <源路径> <目标路径>`）
