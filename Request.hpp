/*
** EPITECH PROJECT, 2020
** base
** File description:
** Request.hpp
*/

#ifndef REQUEST_HPP_
#define REQUEST_HPP_

#include "VString.hpp"

struct Request {
    std::vector<char> data; // Raw message content
    std::vector<VString> entries; // Hold metadata
    // The VString hold is the content of the metadata
    // The body is always the first element of entries.
    // If there is no body, the size of the first entry MUST be 0
    // The id is the SectionID of the data, used to identify the type of metadata
};

#endif /* REQUEST_HPP_ */