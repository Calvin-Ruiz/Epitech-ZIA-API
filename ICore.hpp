/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** ICore.hpp
*/

#ifndef ICORE_HPP_
#define ICORE_HPP_

#include "PipelineStage.hpp"

// Core is a global class
class ICore {
public:
    // Use this in the IModuleMgr::preinit function
    virtual int getRequestID(const std::string &request) = 0;
    // Return -1 if this request doesn't exist
    virtual int getRequestIDIfExist(const std::string &request) const = 0;
    // Return request name, requestID MUST be a valid requestID (otherwise, it will result in undefined behavior)
    virtual const std::string &getRequestName(int requestID) const = 0;
    virtual void addPipelineModule(IModuleMgr *moduleMgr, PipelineModule pipelineModule, void *userData = nullptr) = 0;
    // Return the supported flags. Every non-_EXT flags must be supported.
    // Use of any unsupported flag will result in undefined behavior. Any module using _EXT flags should have a fallback strategy.
    // The 2 mandatory modules MUST have a fallback strategy if every _EXT flag aren't available
    // Other modules which can't work without MUST tell so calling
    // Override this function to add every flags you support
    virtual RoutingBehavior getRoutingBehaviorCapabilities() {
        return ROUTING_BEHAVIOR_PASSTHROUGH_BIT | ROUTING_BEHAVIOR_CONDITIONNAL_BIT | ROUTING_BEHAVIOR_MULTI_OUTPUT_BIT;
    }
    // Tell if this combination of flag is supported
    // Any combination of non-_EXT flags MUST be supported
    virtual bool isRoutingCombinationValid(RoutingBehavior routing) {
        return (getRoutingBehaviorCapabilities() & routing) == routing;
    }
    // Call this function to inform a module require missing features
    virtual void moduleUnavailable(IModuleMgr *moduleMgr, const std::string &moduleName, const std::string &reason = "\0") = 0;
};

#endif /* ICORE_HPP_ */
