/*********************************************************************/
/* $Header: ILinkShortener.hpp                                       */
/*                                                                   */
/* Copyright (c) 2016-2026 nitishhsinghh. All rights reserved.       */
/* This material may be reproduced for teaching and learning         */
/* purposes only. It is not to be used in industry or for            */
/* commercial purposes.                                              */
/*                                                                   */
/* Class       - ILinkShortener                                      */
/*                                                                   */
/* Description - Defines the contract for URL shortening services.   */
/*               Provides methods to generate a shortened link and   */
/*               retrieve the original URL from a shortened token.   */
/*                                                                   */
/* Notes       - Acts as an abstraction layer for multiple           */
/*               shortening strategies (e.g., hash-based, base62,    */
/*               distributed ID generators).                         */
/*                                                                   */
/* $Log: ILinkShortener.hpp                                          */
/*                                                                   */
/*  Revision 1.0  2026/04/26  Nitish Singh                           */
/*  Initial definition of ILinkShortener interface.                  */
/*********************************************************************/

#ifndef ILINKSHORTENER_HPP
#define ILINKSHORTENER_HPP

/*********************************************************************/
/* Dependencies                                                      */
/*********************************************************************/
#include <string>

/**
 * @class ILinkShortener
 * @brief Abstract interface for URL shortening and resolution.
 *
 * Defines the core contract for:
 *  - Generating a shortened representation of a URL
 *  - Resolving a shortened URL back to its original form
 *
 * This interface enables interchangeable implementations such as:
 *  - In-memory mapping
 *  - Database-backed storage
 *  - Distributed ID-based systems
 */
class ILinkShortener {
public:
    /**
     * @brief Virtual destructor for safe polymorphic usage.
     */
    virtual ~ILinkShortener() = default;

    /**
     * @brief Generates a shortened link from the original URL.
     *
     * @param originalLink The full-length URL to be shortened.
     * @return A shortened URL or token representing the original link.
     *
     * @note Implementations should ensure:
     *       - Idempotency (same input may produce same output)
     *       - Collision handling strategy
     *       - Thread-safety if used in concurrent environments
     */
    virtual std::string shortenLink(const std::string& originalLink) = 0;

    /**
     * @brief Retrieves the original URL from a shortened link.
     *
     * @param shortenedLink The shortened URL or token.
     * @return The original full-length URL.
     *
     * @note Implementations should handle:
     *       - Invalid or expired links
     *       - Lookup failures (may throw or return empty string)
     */
    virtual std::string getOriginalLink(const std::string& shortenedLink) const = 0;
};

#endif // ILINKSHORTENER_HPP