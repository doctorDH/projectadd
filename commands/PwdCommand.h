#pragma once
#include "../Command.h"

class PwdCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
