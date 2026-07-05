#pragma once

#include <memory>
#include <functional>
#include <unordered_map>
#include <string>

#include "Agent.h"

class AgentRegistry
{
public:

    using Creator = std::function<std::unique_ptr<Agent>()>;

    static void registerAgent(const std::string& name, Creator creator);

    static std::unique_ptr<Agent> create(const std::string& name);

private:

    static std::unordered_map<std::string, Creator>& getMap();
};