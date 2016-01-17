#ifndef LIBFEI_IOEVENT_H
#define LIBFEI_IOEVENT_H

#include <functional>

class IoEvent{
public:
	using Functor = std::function<void()>;
public:
	IoEvent();
	~IoEvent();



	int loop();

private:

};

#endif
