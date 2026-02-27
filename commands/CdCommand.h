#pragma once
#include "../Command.h"

class CdCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
