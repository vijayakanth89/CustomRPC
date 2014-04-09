#ifndef __THREAD_H
#define __THREAD_H
#include <iostream>
#include <pthread.h>

using namespace std;

class Thread
{
	public:
		Thread();
		~Thread();
		pthread_t start(void *data);
		virtual void run();
		void *thread_data;
};

#endif
