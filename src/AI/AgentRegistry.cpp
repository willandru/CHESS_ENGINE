#include "AgentRegistry.h"

std::unordered_map<std::string, AgentRegistry::Creator>& AgentRegistry::getMap()
{
    static std::unordered_map<std::string, Creator> map;
    return map;
}

void AgentRegistry::registerAgent(
    const std::string& name,
    Creator creator)
{
    getMap()[name] = creator;
}

std::unique_ptr<Agent> AgentRegistry::create(const std::string& name)
{
    auto& map = getMap();

    auto it = map.find(name);
    if (it == map.end())
        return nullptr;

    return (it->second)();
}