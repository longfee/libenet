#include "Fd.h"

Fd::Fd(EventLoop* loop, int fd):loop_(loop),
				fd_(fd){
  events_ = FDEVENT_NONE;
  active_events_ = FDEVENT_NONE;
  index_ = INDEX_NEW;
}

Fd::~Fd(){
}

int Fd::fd() const{
  return fd_;
}

void Fd::setReadCallback(Functor const& f){
  readCb_ = f;
}

void Fd::setWriteCallback(Functor const& f){
  writeCb_ = f;
}

void Fd::setErrorCallback(Functor const& f){
  errCb_ = f;
}

void Fd::enableReading(){
  events_ |= FDEVENT_IN;
  events_ |= FDEVENT_PRI;
  update();
  operation_ = 0;
}

void Fd::disableReading(){
  events_ &= ~FDEVENT_IN;
  events_ &= ~FDEVENT_PRI;
  update();
}

void Fd::enableWriting(){
  events_ |= FDEVENT_OUT;
  update();
}

void Fd::disableWriting(){
  events_ &= ~FDEVENT_OUT;
  update();
}

void Fd::disableAll(){
  events_ = FDEVENT_NONE;
  update();
}

void Fd::update(){
  loop_->updateFd(this);
}

int Fd::getIndex() const{
  return index_;
}

int Fd::setIndex(int index){
  index_ = index;
}

int Fd::events() const{
  return events_;
}

void Fd::activeEvents(int events){
  active_events_ = events;
}

int Fd::activeEvents() const{
  return active_events_;
}
