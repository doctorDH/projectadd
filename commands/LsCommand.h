#pragma once
#include "../Command.h"

// ls 命令：将 Unix ls 映射为 Windows dir
class LsCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
