#include <unordered_map>
#include <string>
#include <thread>
#include <iostream>
#include <memory>

void f(std::string s) {
    std::cout << "function f, param " << s << std::endl;
}

int main() {
    std::unordered_map<std::string, std::thread> m;
    std::thread t{f, "hello"};
    m["myfunc"] = std::move(t);

    m["myfunc"].join();


    std::unordered_map<std::string, std::unique_ptr<std::thread>> mm;
    std::unique_ptr<std::thread> tt(new std::thread{f, "something"});
    mm["somefunc"] = std::unique_ptr<std::thread>(std::move(tt));

    mm["somefunc"]->join();

    return 0;
}