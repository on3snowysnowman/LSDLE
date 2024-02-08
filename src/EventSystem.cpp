#include <unordered_map>
#include <string>

#include "EventSystem.h"

std::unordered_map<std::string, std::unique_ptr<SubscriptionBase>> CallbackManager::subscriptions;
