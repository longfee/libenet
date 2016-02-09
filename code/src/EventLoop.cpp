#include "EventLoop.h"


EventLoop::EventLoop(){
  epoll_fd_ = epoll_create(65535);
  if(epoll_fd_ < 0){
    exit(-1);
  }
  curr_tid_ = std::this_thread::get_id();
  quit_ = false;
  epoll_events_.resize(512);
}

EventLoop::~EventLoop(){
}


std::thread::id EventLoop::ownerThread() const{
  return curr_tid_;
}

void EventLoop::assertInOwnerThread() const{
  if(curr_tid_ != std::this_thread::get_id()){
    exit(-1);
  }
}

void EventLoop::quit(){
  quit_ = true;
}

void EventLoop::loop(int timeout){
  assertInOwnerThread();
  while(!quit_){
    int active_nums = epoll_wait(epoll_fd_,
				 &*epoll_events_.begin(),
				 epoll_events_.size(),
				 timeout);
    if(active_nums < 0){
      //error
    }else if (active_nums == 0){
      //nothing
    }else{
      //handle
      std::size_t i;
      Fd* fd;
      for(i = 0; i < active_nums; ++i){
	fd = (Fd*)epoll_events_[i].data.ptr;
	fd->activeEvents(epoll_events_[i].events);
	fd->dispatch();
      }
      if(epoll_events_.size() == active_nums){
	epoll_events_.resize(epoll_events_.size() * 2);
      }
      //do pending
    }
  }
}


void EventLoop::updateFd(Fd* fd){
  struct epoll_event epe;
  bzero(&epe, sizeof(struct epoll_event));
  int index = fd->getIndex();
  int ifd = fd->fd();
  event.events = fd->events();
  event.data.ptr = fd;
  if(index == INDEX_NEW || index == INDEX_DELETED){
    epoll_ctl(epoll_fd_, EPOLL_CTL_ADD, ifd, &epe);
    fd->setIndex(INDEX_ADD);
  }else{
    //mod
    epoll_ctl(epoll_fd_, EPOLL_CTL_MOD, ifd, &epe);
  }
  
}
