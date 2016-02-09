#ifndef LIBFEI_FD_H
#define LIBFEI_FD_H
#include <functional>

#define FDEVENT_NONE     	(0)
#define FDEVENT_IN		(1<<0)
#define FDEVENT_PRI		(1<<1)
#define FDEVENT_OUT		(1<<2)
#define FDEVENT_HUP		(1<<3)
#define FDEVENT_ERR		(1<<4)

#define INDEX_NEW               -3
#define INDEX_ADD               -2
#define INDEX_DELETED           -1 

class EventLoop;
class Fd{
public:
  using Functor = std::function<void()>;
public:
  Fd(EventLoop* loop, int fd);
  
  ~Fd();

  int fd() const;

  void setReadCallback(Functor const& f);

  void setWriteCallback(Functor const& f);

  void setErrorCallback(Functor const& f);

  void enableReading();

  void disableReading();

  void enableWriting();

  void disableWriting();

  void disableAll();

  void activeEvents(int events);//call by eventloop

  int events() const;

  int activeEvents() const;

  int getIndex() const;

  int setIndex(int index);

  int dispatch();

private:
  void update();
  
private:
  EventLoop* loop_;
  int fd_;
  Functor errCb_;
  Functor writeCb_;
  Functor readCb_;
  int events_;
  int active_events_;
  int index_;
};

#endif
