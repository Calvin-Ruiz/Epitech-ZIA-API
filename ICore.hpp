/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** ICore.hpp
*/

#ifndef ICORE_HPP_
#define ICORE_HPP_

#include "PipelineModule.hpp"
#include <string>
#include "VString.hpp"
class IModuleMgr;
class IModule;

enum CoreExtension {
    IMPLICIT_ROUTING_EXT = 0x01,
    DYNAMIC_MODULE_EXT = 0x02,
};

// Core is a global class
class ICore {
public:
    // Return the request ID for this request string
    // If this request string isn't registered, assign a new unique request ID for this request string and return it
    // Calling this function outside of IModuleMgr::preinit will result in undefined behavior
    virtual int getRequestID(const std::string &request) = 0;
    // Return -1 if this request doesn't exist
    virtual int getRequestIDIfExist(const std::string &request) const = 0;
    // Return the ID of a section name, should be called in IModuleMgr::preinit ir IModuleMgr::init
    virtual int getSectionID(const VString &section) = 0;
    // Return request name, requestID MUST be a valid requestID (otherwise, it will result in undefined behavior)
    virtual const std::string &getRequestName(int requestID) const = 0;
    // Add the description of a Module to create for each IPipeline
    // userData must be carried as argument when calling IModuleMgr::createModule to create the specified module for each IPipeline
    // Calling this function outside of IModuleMgr::init will result in undefined behavior
    virtual void addPipelineModule(IModuleMgr *moduleMgr, const PipelineModule &pipelineModule, void *userData = nullptr) = 0;
    // Return the supported flags. Every non-_EXT flags must be supported.
    // Use of any unsupported flag will result in undefined behavior. Any module using _EXT flags should have a fallback strategy.
    // The 2 mandatory modules MUST have a fallback strategy if every _EXT flag aren't available
    // Other modules which can't work without MUST tell so calling
    // Override this function to add every flags you support
    virtual RoutingBehavior getRoutingBehaviorCapabilities() {
        return static_cast<RoutingBehavior>(ROUTING_BEHAVIOR_PASSTHROUGH_BIT | ROUTING_BEHAVIOR_CONDITIONNAL_BIT | ROUTING_BEHAVIOR_MULTI_OUTPUT_BIT);
    }
    // Tell if this combination of flag is supported
    // Any combination of non-_EXT flags MUST be supported
    virtual bool isRoutingCombinationValid(RoutingBehavior routing) {
        return HAS_FLAGS(getRoutingBehaviorCapabilities(), routing);
    }
    // Call this function to inform a module require missing features
    // If fatal is true, any call to IModuleMgr will result in undefined behavior
    // If fatal is false, further use of IModuleMgr is valid, but the IModuleMgr features will be limited
    virtual void moduleUnavailable(IModuleMgr *moduleMgr, const std::string &moduleName, const std::string &reason = "\0", bool fatal = true) = 0;

    // ========== CORE EXTENSION FEATURES ========== //
    // A single extension or a combination of several extensions
    virtual bool isExtensionAvailable(CoreExtension extension) const {return false;}
    // Enable one or several extensions. Mustn't be used with unsupported extensions
    virtual void enableExtension(CoreExtension extensions) {}
};

/* Core extensions :
IMPLICIT_ROUTING_EXT
    When enabled, perform an implicit routing at PIPELINE_STAGE_ROUTING_BIT
    Implicit routing MUST include the following operations :
        Collect messages received to form complete requests (Single lines which end with \r\n)
        Send back request one after the other with a requestID attached, whose value is the return value of ICore::getRequestIDIfExist() of the first word of the request.
        Fill the metadata and body sections reading from the raw data
DYNAMIC_MODULE_EXT
    When enabled, allow to dynamically add or remove a Module of a pipeline
*/

#endif /* ICORE_HPP_ */
