/*********************************************************************/
/* $File:: InMemoryLinkShortener.hpp                                 */
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
/* $Log: InMemoryLinkShortener.hpp                                   */
/*                                                                   */
/*  Revision 1.0  2026/04/26  Nitish Singh                           */
/*  Initial implementation of InMemoryLinkShortener.                 */
/*********************************************************************/

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
/*********************************************************************/
/* $File:: InMemoryLinkShortener.hpp                                 */
/*********************************************************************/

#ifndef INMEMORYLINKSHORTENER_HPP
#define INMEMORYLINKSHORTENER_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/

#include "ILinkShortener.hpp"
#include <unordered_map>
#include <string>
#include <mutex>

/**
 * @class InMemoryLinkShortener
 * @brief Thread-safe in-memory URL shortener implementation.
 */
class InMemoryLinkShortener : public ILinkShortener {
private:
    std::unordered_map<std::string, std::string> _links;
    std::string _baseUrl;
    mutable std::mutex _mapMutex;

    std::string generateRandomCode(int length) const;

public:
    explicit InMemoryLinkShortener(const std::string& baseUrl);

    std::string shortenLink(const std::string& originalLink) override;

    std::string getOriginalLink(const std::string& shortenedLink) const override;
};

#endif // INMEMORYLINKSHORTENER_HPP