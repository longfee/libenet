#ifndef LIBFEI_EVENTLOOP_H
#define LIBFEI_EVENTLOOP_H

#include <sys/epoll.h>
#include <unistd.h>
#include <thread>
#include <vector>
#include <map>

class Fd;

class EventLoop{
public:
EventLoop();

void loop(int timeout);

void quit();

std::thread::id ownerThread() const;

void assertInOwnerThread() const;

void updateFd(Fd* fd);


private:
~EventLoop();

private:

int epoll_fd_;
std::thread::id curr_tid_;
bool quit_;
std::vector<struct epoll_event> epoll_events_;
std::map<int, Fd*> fdMap_;
};

#endif
