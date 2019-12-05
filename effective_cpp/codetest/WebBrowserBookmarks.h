#ifndef _WEBBROWSERBOOKMARKS_H_
#define _WEBBROWSERBOOKMARKS_H_

#include "WebBrowser.h"
#include <iostream>

namespace WebBrowserStuff {
    void clearBookmarks(WebBrowser &wb) {
        wb.clearBookmarks();
    }
} // namespace WebBrowserStuff

#endif