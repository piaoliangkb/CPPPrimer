#include <iostream>
#include <memory>
#include <string>

class destination {
public:
  destination(const std::string &ip, const int port) : ip(ip), port(port) {}

  std::string ip;
  int port;
};

class connection {
public:
  connection(const std::string &ip, const int port) : ip(ip), port(port) {}

  std::string ip;
  int port;
};

connection connect(destination *des)
{
    std::shared_ptr<connection> pConn(new connection(des->ip, des->port));
    std::cout << "Creating connection, use_count is " << pConn.use_count() << std::endl;

    return *pConn;
}

void disconnect(connection c)
{
    std::cout << "Disconnect connection to (" << c.ip << ", " << c.port << ")\n";
}

void end_connection(connection *pConn)
{
    disconnect(*pConn);
}

void f(destination& d)
{
    connection c = connect(&d);
    std::shared_ptr<connection> p(&c, [](connection *p) { disconnect(*p); });
    std::cout << "Connection use_count is " << p.use_count() << std::endl;
}

int main()
{
    destination des("127.0.0.1", 1080);
    f(des);
}