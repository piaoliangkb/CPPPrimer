#include <condition_variable>
#include <thread>
#include <mutex>
#include <iostream>
#include <queue>
#include <string>

class Message {
public:
    Message(const std::string &s) : msg{s} {}

    std::string get() const {
        return msg;
    }

private:
    std::string msg;
};

std::queue<Message> mqueue;
std::condition_variable mcond;
std::mutex mmutex;

// consumer read and process Messages
void consumer() {
    while (true) {
        std::unique_lock<std::mutex> lck{mmutex};
        mcond.wait(lck);   // release lock and wait notify
                           // acquire lock again
        auto m = mqueue.front();
        mqueue.pop();
        lck.unlock();

        std::cout << m.get() << std::endl;
    }
}

void producer() {
    while (true) {
        Message m{"something just like that"};

        std::unique_lock<std::mutex> lck{mmutex};
        mqueue.push(m);
        mcond.notify_one();
    }
}

int main() 
{
    std::thread csum{consumer};
    std::thread pdcr{producer};

    csum.join();
    pdcr.join();
}