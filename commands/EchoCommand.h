#pragma once
#include "../Command.h"

class EchoCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
