#include "WebBrowserCookies.h"
#include "WebBrowserBookmarks.h"
#include "WebBrowser.h"
#include <iostream>

int main()
{
    WebBrowserStuff::WebBrowser wb;

    WebBrowserStuff::clearCookies(wb);

    WebBrowserStuff::clearBookmarks(wb);
}