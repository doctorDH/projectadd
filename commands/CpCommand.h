#pragma once
#include "../Command.h"

class CpCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
