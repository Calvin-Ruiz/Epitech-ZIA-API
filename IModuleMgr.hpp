/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** IModuleMgr.hpp
*/

#ifndef IMODULEMGR_HPP_
#define IMODULEMGR_HPP_

class ICore;
class IPipeline;
#include "PipelineModule.hpp"
#include "IModule.hpp"
#include <string>

#ifdef __linux__
#define VISIBLE
#else
#define VISIBLE __declspec(dllexport)
#endif

enum ModuleCapabilities {
    MODULE_EXTENSION_PIPELINE_RESET = 0x01,
    MODULE_EXTENSION_SHARED_USE = 0x02,
    MODULE_EXTENSION_DEBUG_ENGINE = 0x04,
    MODULE_EXTENSION_CONCURRENT_CREATE = 0x08,
    MODULE_EXTENSION_HOT_RELOAD = 0x10,
    MODULE_EXTENSION_STATE_TRACKING = 0x20,
};

class IModuleMgr {
public:
    // static IModuleMgr *createMgr(); // Called only once to create the module mgr
    // Pre-initialization. This allow to prepair links. Do not call Core::addPipelineModule here
    virtual void preinit(ICore *core, const std::string &configPath, const std::string &userPath) = 0;
    // Initialize. You can fetch IModuleMgr and perform links here.
    virtual void init() = 0;
    virtual IModule *createModule(IPipeline *pipeline, const PipelineModule &pipelineModule, void *userData) = 0;
    // Return true if the configuration files are not up to date
    virtual bool isOutdated() = 0;
    // Reload the configuration files for future IPipeline
    virtual void hotReload() {}

    // Return module capabilities
    virtual int getModuleCapabilities() const {return 0;}
    // Enable one or several module capabilities if they are available.
    // This mustn't be called by the core after init()
    // Use of non-enabled and/or unsupported module capability will result in undefined behavior
    virtual void enableModuleCapabilities(int moduleCapabilities) {}
};

/* Module Capabilities (all are extensions) :
MODULE_EXTENSION_PIPELINE_RESET
    IModule created from this IModuleMgr can be .reset() and reused for another client
    It will be used by the same IPipeline
MODULE_EXTENSION_SHARED_USE
    IModule created from this IModuleMgr can be successively used in several IPipeline
    It is ensured that the IModule will be fully executed in one single IPipeline at a time
    This mean any IModule can be used to manage request from any client
MODULE_EXTENSION_DEBUG_ENGINE
    The ModuleMgr will display debug and/or store informations for debug purpose
    If this extension is not enabled :
        Module created from this ModuleMgr MUSTN'T display or store any debug information
        This ModuleMgr SHOULDN'T display or write any debug information
MODULE_EXTENSION_CONCURRENT_CREATE
    IModuleMgr::createModule can be concurrently called
MODULE_EXTENSION_HOT_RELOAD
    Allow this module to reload his configuration files and apply changes to future IModule.
    Any IModule created before a hot reload MUSTN'T be affected by the configuration changes
    If MODULE_EXTENSION_PIPELINE_RESET is set, the changes also apply to IModule which are .reset() after the hot reload
    If MODULE_EXTENSION_CONCURRENT_CREATE is set, hotReload can be called concurrently to IModuleMgr::create
    If MODULE_EXTENSION_SHARED_USE is set, the following is expected :
        IModule created before the hotReload() must only be used by IPipeline created before the hotReload()
        IModule created after the hotReload() must only be used by IPipeline created after the hotReload()
MODULE_EXTENSION_STATE_TRACKING
    Implement the isOutdated method, to allow the server to periodically check changes.
    If this extension is not supported, isOutdated MUST return false
    If this extension is supported and enabled, isOutdated MUST return true if the configuration files have changed
    Note that a configuration file change can be detected either by looking at the file update time, or looking at the file content
*/

#endif /* IMODULEMGR_HPP_ */
