/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** IPipeline.hpp
*/

#ifndef IPIPELINE_HPP_
#define IPIPELINE_HPP_

#include "PipelineModule.hpp"

// Pipeline is a class dedicated to one connection.
class IPipeline {
public:
    // Only needed if ROUTING_BEHAVIOR_DYNAMIC_OUTPUT_BIT_EXT is supported
    virtual void pushMessage(std::vector<char> data, PipelineStage dstStage, int requestID = -1) {}
};

#endif /* IPIPELINE_HPP_ */
