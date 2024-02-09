#include <unordered_map>
#include <string>

#include "EventSystem.h"

std::unordered_map<std::string, 
    std::vector<SubscriptionBase*>> CallbackManager::subscriptions;
