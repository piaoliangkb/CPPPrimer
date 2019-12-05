#ifndef _WEBBROWSERCOOKIES_H_
#define _WEBBROWSERCOOKIES_H_

#include "WebBrowser.h"
#include <iostream>

namespace WebBrowserStuff {
    void clearCookies(WebBrowser &wb) {
        wb.removeCookies();
    } 
} // namespace WebBrowserStuff

#endif