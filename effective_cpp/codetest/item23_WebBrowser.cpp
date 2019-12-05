#include "item23_WebBrowserCookies.h"
#include "item23_WebBrowserBookmarks.h"
#include "item23_WebBrowser.h"
#include <iostream>

int main()
{
    WebBrowserStuff::WebBrowser wb;

    WebBrowserStuff::clearCookies(wb);

    WebBrowserStuff::clearBookmarks(wb);
}