/*********************************************************************/
/* $File:: InMemoryLinkShortener.cpp                                 */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - InMemoryLinkShortener                               */
/*                                                                   */
/* Description - In-memory implementation of ILinkShortener.         */
/*               Generates short links using random Base62 encoding  */
/*               and stores mappings in a thread-safe hash map.      */
/*                                                                   */
/* Notes       - Uses mutex for thread-safety across concurrent      */
/*               access (e.g., .NET interop scenarios)               */
/*               Collision-safe via retry loop                       */
/*               Suitable for demo/testing (non-persistent storage)  */
/*                                                                   */
/* $Log: InMemoryLinkShortener.cpp                                   */
/*                                                                   */
/*  Revision 1.0  2026/04/26  Nitish Singh                           */
/*  Initial implementation of InMemoryLinkShortener.                 */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
/*********************************************************************/
/* $File:: InMemoryLinkShortener.cpp                                 */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "InMemoryLinkShortener.hpp"
#include <random>

/*********************************************************************/
/* Private Methods                                                   */
/*********************************************************************/
std::string InMemoryLinkShortener::generateRandomCode(int length) const {
    static const std::string chars =
        "abcdefghijklmnopqrstuvwxyz"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "0123456789";

    thread_local std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<size_t> dist(0, chars.size() - 1);

    std::string code;
    code.reserve(length);

    for (int i = 0; i < length; ++i) {
        code += chars[dist(generator)];
    }

    return code;
}

/*********************************************************************/
/* Constructor                                                      */
/*********************************************************************/
InMemoryLinkShortener::InMemoryLinkShortener(const std::string& baseUrl)
    : _baseUrl(baseUrl) {}

/*********************************************************************/
/* Public Methods                                                   */
/*********************************************************************/
std::string InMemoryLinkShortener::shortenLink(const std::string& originalLink) {
    std::lock_guard<std::mutex> lock(_mapMutex);

    std::string shortCode;
    std::string shortenedLink;

    do {
        shortCode = generateRandomCode(6);
        shortenedLink = _baseUrl + shortCode;
    } while (_links.find(shortenedLink) != _links.end());

    _links[shortenedLink] = originalLink;
    return shortenedLink;
}

std::string InMemoryLinkShortener::getOriginalLink(const std::string& shortenedLink) const {
    std::lock_guard<std::mutex> lock(_mapMutex);

    auto it = _links.find(shortenedLink);
    return (it != _links.end()) ? it->second : "";
}