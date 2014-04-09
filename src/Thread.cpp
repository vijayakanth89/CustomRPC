#include "Thread.h"

static void* __call_back_(void *data)
{
	Thread *p = static_cast<Thread*>(data);
	p->run();		
}

Thread::Thread()
{
	
}

Thread::~Thread()
{
}

pthread_t Thread::start(void *data)
{
	pthread_t tid;
	this->thread_data = data;
	pthread_create(&tid, NULL, __call_back_ , (void *)this);
}
void Thread::run()
{
	cout << "in thread: " << pthread_self() << endl;
}
