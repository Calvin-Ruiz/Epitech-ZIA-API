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

class IModuleMgr {
public:
    // static IModuleMgr *createMgr(); // Called only once to create the module mgr
    // Pre-initialization. This allow to prepair links. Do NOT fecth other IModuleMgr here !
    virtual void preinit(ICore *core, const std::string &configPath, const std::string &userPath) = 0;
    // Initialize. You can fetch IModuleMgr and perform links here.
    virtual void init();
    virtual IModule *createModule(IPipeline *pipeline, PipelineModule pipelineModule) = 0;
    // Return the modules to be created for each connection, and their dependencies with the general flow
    virtual std::vector<PipelineStage> querryPipelineStages() = 0;
};

#endif /* IMODULEMGR_HPP_ */
