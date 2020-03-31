#include <cassert>

#include "SmartStack.h"
#include "SmartQueue.h"
#include "QueueStack.h"
#include <iostream>

using namespace SmartQueueStack;

int main()
{
	SmartStack<float> ss;

	ss.Push(3.4f);
	ss.Push(1.2f);
	ss.Push(4.6f);
	ss.Push(3.32f);
	ss.Push(10.2f);
	ss.Push(1.1f);
	ss.Push(-5.9f);
	ss.Push(1.1f);
	ss.Push(-12.4f);
	ss.Push(9.2f);

	assert(ss.Count() == 10U);
	assert(ss.Peek() == 9.2f);
	assert(ss.Max() == 10.2f);
	assert(ss.Min() == -12.4f);
	assert(ss.Average() == 1.582);
	assert(ss.Variance() == 39.983);
	assert(ss.StandardDeviation() == 6.323);
	assert(ss.Peek() == 9.2f);

	float popped1 = ss.Pop();
	float popped2 = ss.Pop();

	assert(popped1 == 9.2f);
	assert(popped2 == -12.4f);
	assert(ss.Min() == -5.9f);

	ss.Push(101.1f);
	ss.Push(101.1f);
	ss.Pop();
	assert(ss.Max() == 101.1f);


	SmartQueue<float> tt;
	
	tt.Enqueue(3.4f);
	tt.Enqueue(1.2f);
	tt.Enqueue(4.6f);
	tt.Enqueue(3.32f);
	tt.Enqueue(10.2f);
	tt.Enqueue(1.1f);
	tt.Enqueue(-5.9f);
	tt.Enqueue(1.1f);
	tt.Enqueue(-12.4f);
	tt.Enqueue(9.2f);
	std::cout << tt.Peek() << std::endl;

	assert(tt.Count() == 10U);
	assert(tt.Peek() == 3.4f);
	assert(tt.Max() == 10.2f);
	assert(tt.Min() == -12.4f);
	assert(tt.Average() == 1.582);
	assert(tt.Variance() == 39.983);
	assert(tt.StandardDeviation() == 6.323);
	assert(tt.Peek() == 3.4f);

	float popped11 = tt.Dequeue();
	float popped12 = tt.Dequeue();

	assert(popped11 == 3.4f);
	assert(popped12 == 1.2f);
	assert(tt.Min() == -12.4f);

	tt.Enqueue(101.1f);
	tt.Enqueue(101.1f);
	tt.Dequeue();
	assert(tt.Max() == 101.1f);

	QueueStack<float> qq(3);

	qq.Enqueue(3.4f);
	qq.Enqueue(1.2f);
	qq.Enqueue(4.6f);
	qq.Enqueue(3.32f);
	qq.Enqueue(10.2f);
	qq.Enqueue(1.1f);
	qq.Enqueue(-5.9f);
	qq.Enqueue(1.1f);
	qq.Enqueue(-12.4f);
	qq.Enqueue(9.2f);
	std::cout << qq.Min() << std::endl;
	assert(qq.Count() == 10U);
	assert(qq.Peek() == 4.6f);
	assert(qq.Max() == 10.2f);
	assert(qq.Min() == -12.4f);
	assert(qq.Average() == 1.582);

	float popped111 = qq.Dequeue();
	float popped112 = qq.Dequeue();
	float popped113 = qq.Dequeue();
	float popped114 = qq.Dequeue();
	float popped115 = qq.Dequeue();

	return 0;
}