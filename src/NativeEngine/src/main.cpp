/*********************************************************************/
/* $File: LinkShortenerCLI.cpp                                       */
/*                                                                   */
/* Description - Diagnostic CLI for URL shortener engine.            */
/*********************************************************************/

#include <iostream>
#include <memory>
#include <vector>
#include <iomanip>

#include "ILinkShortener.hpp"
#include "InMemoryLinkShortener.hpp" 


/**
 * @brief Runs validation tests on the link shortener engine.
 */
void runDiagnostics(ILinkShortener& engine, const std::vector<std::string>& urls) {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << std::left << std::setw(30) << "ORIGINAL URL"
         << std::setw(30) << "SHORTENED"
         << "STATUS" << std::endl;
    std::cout << std::string(80, '-') << std::endl;

    for (const auto& url : urls) {
        try {
            std::string shortUrl = engine.shortenLink(url);
            std::string resolved = engine.getOriginalLink(shortUrl);

            bool success = (url == resolved);

            std::cout << std::left
                 << std::setw(30) << (url.length() > 27 ? url.substr(0, 24) + "..." : url)
                 << std::setw(30) << shortUrl
                 << (success ? "OK" : "FAIL")
                 << std::endl;

        } catch (...) {
            std::cout << "CRITICAL: Unexpected error in engine." << std::endl;
        }
    }

    std::cout << std::string(80, '=') << std::endl;
}

int main() {
    std::unique_ptr<ILinkShortener> engine =
        std::make_unique<InMemoryLinkShortener>("https://nano.url/");

    std::vector<std::string> testSuite = {
        "https://github.com/nitishhsinghhh",
        "https://apple.com/m2-chip-info",
        "https://dotnet.microsoft.com/en-us/",
        "https://en.wikipedia.org/wiki/C%2B%2B17",
        "https://developer.apple.com/metal/"
    };

    std::cout << "NanoURL Native Engine Diagnostic Tool" << std::endl;
    std::cout << "Author: Nitish Singh" << std::endl;
    std::cout << "Target: Cross-platform" << std::endl;

    runDiagnostics(*engine, testSuite);

    return 0;
}