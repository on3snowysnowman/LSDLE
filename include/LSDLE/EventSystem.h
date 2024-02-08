#pragma once

#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>


class SubscriptionBase {
public:
    virtual ~SubscriptionBase() = default;
    virtual void invoke() = 0;
};

template <typename T>
class Subscription : public SubscriptionBase {
public:
    Subscription(T* obj, std::function<void(T&)> callback)
        : objPtr(obj), callback_function(callback) {}

    void invoke() override {
        if (objPtr) {
            callback_function(*objPtr);
        } else {
            std::cerr << "Error: Invalid object pointer." << std::endl;
        }
    }

private:
    T* objPtr;
    std::function<void(T&)> callback_function;
};


class CallbackManager {
public:
    template <typename T>
    static void subscribe(std::string callback_token, T* obj, std::function<void(T&)> callback) {
        subscriptions[callback_token] = std::make_unique<Subscription<T>>(obj, callback);
    }

    static void trigger_callback(std::string callback_token) {
        auto it = subscriptions.find(callback_token);
        if (it != subscriptions.end()) {
            it->second->invoke();
        } else {
            std::cerr << "Error: Callback token not found." << std::endl;
        }
    }

private:
    static std::unordered_map<std::string, std::unique_ptr<SubscriptionBase>> subscriptions;
};
