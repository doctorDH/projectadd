#pragma once
#include "../Command.h"

class MvCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
