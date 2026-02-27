#pragma once
#include "../Command.h"

class CatCommand : public CommandHandler {
public:
    void execute(const std::vector<std::string>& args) override;
};
