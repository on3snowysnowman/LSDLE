#pragma once

#include <functional>
#include <unordered_map>
#include <memory>
#include <string>
#include <iostream>
#include <vector>


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

    void invoke() final 
    {
        callback_function(*objPtr);
    }

private:

    T* objPtr; // The object that contains the callback function
    std::function<void(T&)> callback_function; // Function that will be called
    
};


class CallbackManager {

public:

    template <typename T>
    static void subscribe(std::string callback_token, T* obj, 
        std::function<void(T&)> callback) 
    {
        subscriptions[callback_token].push_back(new Subscription<T>(obj, callback));
    }

    static void trigger_callback(std::string callback_token) 
    {
        
        // Find the vector of callbacks this token is associated with
        auto it = subscriptions.find(callback_token);

        // Token is valid
        if (it != subscriptions.end()) {
            
            // Iterate through each function pointer associated with this token
            for(auto sub : it->second)
            {
                // Invoke this callback
                sub->invoke();
            }

            // it->second->invoke();
        } 
        
        // Token is not valid
        else {
            std::cerr << "Error: Callback token not found." << std::endl;
        }
    }

private:
    
    static std::unordered_map<std::string, 
        std::vector<SubscriptionBase*>> subscriptions;
};
