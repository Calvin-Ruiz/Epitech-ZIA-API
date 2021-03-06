/*
** EPITECH PROJECT, 2020
** B-YEP-500-MAR-5-1-zia-calvin.ruiz
** File description:
** PipelineModule.hpp
*/

#ifndef PIPELINE_MODULE_HPP_
#define PIPELINE_MODULE_HPP_

#include <vector>
#define STAGE_COUNT 9
#define HAS_FLAGS(flags_available, flags_expected) ((flags_available & flags_expected) == flags_expected)

// Note : Use a #define FLAG yourflag, a #define FLAG_USABLE, then the DISP_FEATURE, to end with #undef FLAG and #undef FLAG_ALLOWED
#ifdef __linux__
#define DISP_FEATURE(feature) std::cout << #feature << " :\t" << (\
    (FLAG & feature) ? \
    ((FLAG_USABLE & feature) ? "\e[92;1menabled\e[0m" : "\e[91;1minvalid\e[0m") : \
    ((FLAG_USABLE & feature) ? "\e[93mdisabled\e[0m" : "\e[33munavailable\e[0m") \
    ) << '\n'
#else
#define DISP_FEATURE(feature) std::cout << #feature << " :\t" << (\
    (FLAG & feature) ? \
    ((FLAG_USABLE & feature) ? "enabled" : "invalid") : \
    ((FLAG_USABLE & feature) ? "disabled" : "unavailable") \
    ) << '\n'
#endif

// This define the stage of execution
enum PipelineStage {
    PIPELINE_STAGE_NONE = 0, // No stage, only valid when no stage can be designed
    PIPELINE_STAGE_TOP_OF_PIPE_BIT = 0x00000001,
    PIPELINE_STAGE_DECODING_BIT = 0x00000002,
    PIPELINE_STAGE_ROUTING_BIT = 0x00000004,
    PIPELINE_STAGE_EARLY_PROCCESS_BIT = 0x00000008,
    PIPELINE_STAGE_PROCESS_BIT = 0x00000010,
    PIPELINE_STAGE_LATE_PROCCESS_BIT = 0x00000020,
    PIPELINE_STAGE_OUTPUT_CONTROL_BIT = 0x00000040,
    PIPELINE_STAGE_ENCODING_BIT = 0x00000080,
    PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT = 0x00000100,
};

// This define the routing behavior
enum RoutingBehavior {
    ROUTING_BEHAVIOR_PASSIVE_BIT = 0x0000,
    ROUTING_BEHAVIOR_PASSTHROUGH_BIT = 0x0001,
    ROUTING_BEHAVIOR_CONDITIONNAL_BIT = 0x0002,
    ROUTING_BEHAVIOR_MULTI_OUTPUT_BIT = 0x0004,
    ROUTING_BEHAVIOR_SWITCH_BIT_EXT = 0x0008,
    ROUTING_BEHAVIOR_ASYNC_BIT_EXT = 0x0010,
    ROUTING_BEHAVIOR_CONDITIONNAL_STAGE_BIT_EXT = 0x0020,
    ROUTING_BEHAVIOR_DYNAMIC_PUSH_BIT_EXT = 0x0040,
    ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT = 0x0080,
};

struct PipelineModule {
    // Requests which should be caught. Empty = nothing with requestID, {-1} = any request
    // Ignored if ROUTING_BEHAVIOR_SWITCH_BIT_EXT is not supported
    std::vector<int> requestFilter;
    PipelineStage srcStage;
    PipelineStage dstStage;
    RoutingBehavior routing;
};

// srcStage & dstStage MUST be 0
// srcStage must define one and only one stage
// dstStage must define several stages if the following is true :
// - routing has the ROUTING_BEHAVIOR_CONDITIONNAL_STAGE_BIT_EXT flag set
// - ICore have the ROUTING_BEHAVIOR_CONDITIONNAL_STAGE_BIT_EXT capability
// dstStage mustn't define any stage if routing is ROUTING_BEHAVIOR_PASSIVE_BIT or ROUTING_BEHAVIOR_PASSIVE_BIT | ROUTING_BEHAVIOR_DYNAMIC_PUSH_BIT_EXT
// In every other cases, dstStage must define one and only one stage
// dstStage must be a later stage than srcStage if ICore doesn't support ROUTING_BEHAVIOR_DYNAMIC_PUSH_BIT_EXT

/* Pipeline stages :
PIPELINE_STAGE_TOP_OF_PIPE_BIT
    This stage represent the tcp message reception
PIPELINE_STAGE_DECODING_BIT
    This stage represent the message decoding.
    Everything related to ssh message decoding should be done there.
PIPELINE_STAGE_ROUTING_BIT
    This stage represent the message routing to the proper processor module.
    Any message send back must be a complete single message.
PIPELINE_STAGE_EARLY_PROCCESS_BIT
    This stage is the message pre-processing.
    The output message can be binary and include additionnal informations.
PIPELINE_STAGE_PROCESS_BIT
    This stage is the process engine.
PIPELINE_STAGE_LATE_PROCCESS_BIT
    This stage is the message post-processing.
    It is responsible to transform the possibly binary message into one or several sync and/or async replies.
PIPELINE_STAGE_OUTPUT_CONTROL_BIT
    This stage represent the control of the order of outputs.
    It must ensure that sync and async replies are send in the right order if ROUTING_BEHAVIOR_ASYNC_BIT_EXT is supported.
    Due to async message, the right order can differ of the reception order if ROUTING_BEHAVIOR_ASYNC_BIT_EXT is supported.
PIPELINE_STAGE_ENCODING_BIT
    This stage represent the message encoding.
    Everything related to ssh message encoding should be done there.
PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT
    This stage represent the tcp message emission
*/

/* Routing behaviors :
ROUTING_BEHAVIOR_PASSIVE_BIT
    No output is generated in any case
    If every modules of a srcStage either only have ROUTING_BEHAVIOR_PASSIVE_BIT or include ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT, messages can fallback to the next stage
ROUTING_BEHAVIOR_PASSTHROUGH_BIT
    One input will result in one output
ROUTING_BEHAVIOR_CONDITIONNAL_BIT
    Input can result in output being generated
ROUTING_BEHAVIOR_MULTI_OUTPUT_BIT
    One input can generate one or more outputs.
    If it is combined with ROUTING_BEHAVIOR_PASSTHROUGH_BIT, the number of output generated per input is constant
    If it is combined with ROUTING_BEHAVIOR_CONDITIONNAL_BIT, the number of output can be null and vary
ROUTING_BEHAVIOR_SWITCH_BIT_EXT
    The generated output will have a request type attributed.
    This enable filtering requests for the next stages.
ROUTING_BEHAVIOR_ASYNC_BIT_EXT
    An output can be generated at any time without matching input.
    If combined with ROUTING_BEHAVIOR_PASSTHROUGH_BIT, the non-async output generated must directly reply to the input
ROUTING_BEHAVIOR_CONDITIONNAL_STAGE_BIT_EXT
    The dstStage mask is a combination of several stages, and the output must be rooted to the proper dstStage
ROUTING_BEHAVIOR_DYNAMIC_PUSH_BIT_EXT
    Output message can be pushed with the IPipeline::pushMessage mechanism
ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT
    Like ROUTING_BEHAVIOR_CONDITIONNAL_BIT, excepted that :
    If no output is generated by any module in this srcStage, the input will continue to the next stages
    If at least one output is generated by one module with ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT set, the reply will not been send to every modules with ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT set at this srcStage
*/

#endif /* PIPELINE_MODULE_HPP_ */
