/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** IModuleMgr.hpp
*/

#ifndef IMODULEMGR_HPP_
#define IMODULEMGR_HPP_

class IModule;
class ICore;
#include "PipelineModule.hpp"

enum ModuleCapabilities {
    MODULE_EXTENSION_PIPELINE_RESET = 0x01,
    MODULE_EXTENSION_SHARED_USE = 0x02,
    MODULE_EXTENSION_DEBUG_ENGINE = 0x04
};

class IModuleMgr {
public:
    // static IModuleMgr *createMgr(); // Called only once to create the module mgr
    // Pre-initialization. This allow to prepair links. Do NOT fecth other IModuleMgr here !
    virtual void preinit(ICore *core, const std::string &configPath, const std::string &userPath) = 0;
    // Initialize. You can fetch IModuleMgr and perform links here.
    virtual void init();
    virtual IModule *createModule(IPipeline *pipeline, PipelineModule pipelineModule, void *userData) = 0;

    // Return module capabilities
    virtual int getModuleCapabilities() const {return 0;}
    // Enable module capabilities if they are available. Mustn't be called after init();
    // Use of non-enabled module capability will result in undefined behavior
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
    The ModuleMgr will display debug informations for debug purpose
*/

#endif /* IMODULEMGR_HPP_ */
