#ifndef _WEBBROWSER_H_
#define _WEBBROWSER_H_

#include <iostream>

namespace WebBrowserStuff {
class WebBrowser {
public:
    void clearCache() { 
        std::cout << "[call func] clearCache()" << std::endl; 
    }

    void clearHistory() {
        std::cout << "[call func] clearHistory()" << std::endl;
    }

    void removeCookies() {
        std::cout << "[call func] removeCookies()" << std::endl;
    }

    void clearBookmarks() {
        std::cout << "[call func] clearBookmarks()" << std::endl;
    }
};
} // namespace WebBrowserStuff

#endif