/*
** EPITECH PROJECT, 2020
** base
** File description:
** Request.hpp
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include "VString.hpp"
#include <vector>

struct Request {
    std::vector<char> data; // Raw message content
    std::vector<VString> entries; // Hold metadata
    // The VString hold is the content of the metadata
    // The body is always the first element of entries.
    // If there is no body, the size of the first entry MUST be 0
    // The id is the SectionID of the data, used to identify the type of metadata
    unsigned int useCount = -1;
    // The minimum between the number of parallel use of the Request by modules which doesn't have ROUTING_BEHAVIOR_CONDITIONNAL_ROUTING_BIT_EXT set and 1
    // Request content can be modified if useCount is 1
    std::vector<std::pair<std::vector<char>, unsigned int>> cache;
    // For caching entries data.
    // The packet should be reconstructed at PIPELINE_STAGE_OUTPUT_CONTROL_BIT, thus cache MUST be empty after this stage
};

#endif /* REQUEST_HPP_ */
