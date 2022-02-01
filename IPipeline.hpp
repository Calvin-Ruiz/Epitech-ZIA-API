/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** IPipeline.hpp
*/

#ifndef IPIPELINE_HPP_
#define IPIPELINE_HPP_

#include "PipelineModule.hpp"

// Pipeline is a class dedicated to a connection with one client
class IPipeline {
public:
    // Only needed if ROUTING_BEHAVIOR_DYNAMIC_OUTPUT_BIT_EXT is supported
    virtual void pushMessage(std::vector<char> data, PipelineStage dstStage, int requestID = -1) {}
    // Request the IPipeline to add a Module to his processing line
    // A single IPipeline MUSTN'T have 2 or more IModule with the same address if MODULE_EXTENSION_SHARED_USE is not set
    // Only needed if DYNAMIC_MODULE_EXT is supported and enabled
    virtual void addModule(ModuleMgr *moduleMgr, Module *module, PipelineModule pipelineModule) {}
    // Request the IPipeline to remove a Module from his processing line
    // Only needed if DYNAMIC_MODULE_EXT is supported and enabled
    virtual void removeModule(ModuleMgr *moduleMgr, IModule *module);
};

#endif /* IPIPELINE_HPP_ */
