#ifndef SCREEN_H
#define SCREEN_H

#include <iostream>
#include <string>

class Screen;

class Window_mgr {
public:
    using ScreenIndex = std::vector<Screen>::size_type;
    void clear(ScreenIndex);
private:
    std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s = screens[i];
    s.contents = string(s.height*s.width, ' ');
}

class Screen {
    friend void Window_mgr::clear(ScreenIndex);

public:
    using pos = std::string::size_type;

    Screen() = default;
    Screen(pos ht, pos wd): height(ht), width(wd), contents(ht * wd, ' ') {}
    Screen(pos ht, pos wd, char c): height(ht), width(wd), contents(ht*wd, c) {}

    char get() const { return contents[cursor]; }
    char get(pos row, pos col) const { return contents[row * width + col]; }

    Screen &move(pos, pos);

    Screen &set(char);
    Screen &set(pos, pos, char);

    // 根据调用对象是否为const，重载了display函数，const成员函数返回 const Screen 类型
    Screen &display(std::ostream &os) { do_display(os); return *this; }
    const Screen &display(std::ostream &os) const { do_display(os); return *this; }

    pos size() const;

private:
    pos cursor = 0;
    pos height = 0, width = 0;
    std::string contents;

    void do_display(std::ostream &os) const { os << contents; }
};

inline Screen &Screen::set(char c)
{
    contents[cursor] = c;
    return *this;
}

inline Screen &Screen::set(pos row, pos col, char c)
{
    contents[row*width + col] = c;
    return *this;
}

inline Screen &Screen::move(pos row, pos col)
{
    cursor = row * width + col;
    return *this;
}

inline Screen::pos Screen::size() const 
{
    return height * width;
}
#endif