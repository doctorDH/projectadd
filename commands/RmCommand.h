#pragma once
#include "../Command.h"

class RmCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
