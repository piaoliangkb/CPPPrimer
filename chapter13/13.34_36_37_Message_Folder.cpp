#include <iostream>
#include <set>
#include <string>
#include <utility>

class Folder;
class Message;

//----------------class Folder--------------------//

class Folder {
    friend void swap(Folder &, Folder &);
    friend Message;

public:
    Folder() = default;
    Folder(const Folder &);
    Folder &operator=(const Folder &);
    ~Folder();

    void addMsg(Message *msg) { messages.insert(msg); }

    void remMsg(Message *msg) { messages.erase(msg); }

    void show_messages(); 

private:
    std::set<Message *> messages;

    void add_to_messages(const Folder &);
    void remove_from_messages();
};

//----------------class Message------------------//

class Message {
    friend class Folder;
    friend void swap(Message&, Message&);

public:
    explicit Message(const std::string &s = std::string()) : contents(s) {}

    Message(const Message &);
    Message &operator=(const Message &);

    Message(Message &&);
    Message &operator=(Message &&);

    ~Message();

    // 从给定 Folder 集合中添加/删除本 Message
    void save(Folder &);
    void remove(Folder &);

    // 向 folders 添加或删除指定的 Folder
    void addFolder(Folder* folder) {
        folders.insert(folder);
    }

    void remFolder(Folder* folder) {
        folders.erase(folder);
    }

    // swap 函数
    void swap(Message &, Message &);

private:
    std::string contents;
    std::set<Folder *> folders;

    // 拷贝构造函数，拷贝赋值运算符使用的工具函数
    void add_to_folders(const Message &);

    // 从当前类的 folders 中的每个 Folder 删除当前 Message
    void remove_from_folders();

    // 用于移动操作来更新所有的 Message 在 Folder 中的信息
    void move_Folders(Message *);
};

//----------------implementation of message--------//

void Message::save(Folder &f) {
    folders.insert(&f); // message.folders 添加对应 folder
    f.addMsg(this);     // 对应 folder 添加本 message
}

void Message::remove(Folder &f) {
    folders.erase(&f); // message.folders 删除指定 folder
    f.remMsg(this);    // 指定 folder 删除本 message
}

// m 是被拷贝的 Message
// 将当前 message 添加到所有包含被拷贝元素的 folders 中去
void Message::add_to_folders(const Message &m) {
    for (auto f : m.folders)
        f->addMsg(this);
}

Message::Message(const Message &m) : contents(m.contents), folders(m.folders) {
    add_to_folders(m);
}

// 从当前所有包含该对象的 Folder 中移除该对象
// 为析构函数和复制构造运算符的左侧运算对象准备
void Message::remove_from_folders() {
    for (auto f : folders)
        f->remMsg(this);
}

Message::~Message() { remove_from_folders(); }

Message &Message::operator=(const Message &rhs) {
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

void swap(Message &lhs, Message &rhs) {
    using std::swap;

    // 将每个指针从原来的 Folder 中删除
    for (auto f : lhs.folders) // 左侧 Message 的所有 Folder 移除左侧 Message
        f->remMsg(&lhs);
    for (auto f : rhs.folders) // 右侧 Message 的所有 Folder 移除右侧 Message
        f->remMsg(&rhs);

    swap(lhs.folders, rhs.folders);
    swap(lhs.contents, rhs.contents);

    // 将新的指针添加到 Folder 中
    for (auto f : lhs.folders)
        f->addMsg(&lhs);
    for (auto f : rhs.folders)
        f->addMsg(&rhs);
}

void Message::move_Folders(Message *m) {
    folders = std::move(m->folders); // 避免了拷贝 set
    for (auto f : folders) {
        f->remMsg(m);
        f->addMsg(this);
    }
    m->folders.clear(); // 确保销毁 m 是无害的
}

Message::Message(Message &&m)
    : contents(std::move(m.contents))
{
    move_Folders(&m);
}

Message& Message::operator=(Message &&rhs)
{
    if (this != &rhs)
    {
        remove_from_folders();
        contents = std::move(rhs.contents);
        move_Folders(&rhs);
    }
    return *this;
}
//----------------implementation of folder----------//

// 拷贝时使用，参数作为右侧的被拷贝对象，
// 将拷贝后的Folder(*this) 添加到所有被拷贝对象的 message 中去
void Folder::add_to_messages(const Folder &f) {
    for (auto msg : f.messages) {
        msg->addFolder(this);
    }
}

// 在所有包含当前 Folder 的 Message 中删除当前 Folder
void Folder::remove_from_messages() {
    for (auto msg : messages) {
        msg->remFolder(this);
    }
}

Folder::Folder(const Folder &rhs) : messages(rhs.messages) {
    // 将拷贝后的 Folder 添加到拷贝前对象所有的 Message 中去
    add_to_messages(rhs);
}

Folder &Folder::operator=(const Folder &rhs) {
    remove_from_messages(); // 为了处理自赋值情况，先删除左侧
    messages = rhs.messages;
    add_to_messages(rhs); // 将新的 folder 添加到所有右侧对应的 message 中
    return *this;
}

Folder::~Folder() { remove_from_messages(); }

void swap(Folder &lhs, Folder &rhs) {
    using std::swap;
    lhs.remove_from_messages();
    rhs.remove_from_messages();

    swap(lhs.messages, rhs.messages);

    lhs.add_to_messages(lhs);
    rhs.add_to_messages(rhs);
}

void Folder::show_messages() {
    for (auto msg : messages) {
        std::cout << msg->contents << " ";
    }
}

//---------------MAIN FUNC----------------//

int main()
{
    Message m1("hello"), m2("cppprimer"), m3("fluentpython");
    Folder says, books, cpp;

    m1.save(says);
    m2.save(books);
    m2.save(cpp);
    m3.save(books);

    std::cout << "show whats in [books] : ";
    books.show_messages();
    std::cout << std::endl;

    std::cout << "after move m2 to m1: " << std::endl;
    m1 = std::move(m2);
    std::cout << "show whats in [says] : ";
    says.show_messages();
    std::cout << "\nshow whats in [books] : ";
    books.show_messages();

    return 0;
}