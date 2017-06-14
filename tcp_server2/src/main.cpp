#include <iostream>
#include "job_queue.hpp"
#include <boost/core/lightweight_test.hpp>

#include "worker.hpp"

void test_queue()
{
	job_queue<int> q;
	q.push(10);
	q.push(20);

	int tmp = q.pop();
	BOOST_TEST_EQ(tmp, 10);
	BOOST_TEST_EQ (q.pop(), 20);
	q.push(30);
	q.stop();
	tmp = q.pop();
	BOOST_TEST_EQ(tmp, 0);

	boost::report_errors();
}

bool func_int(int& x)
{
	std::cout << "work on : " << x << std::endl;
	return true;
}

void test_worker()
{
	typedef job_queue<int> queue_type;
	queue_type q;

	q.push(10);
	q.push(20);

	worker<queue_type> w(q);

	w.start(func_int);
	boost::this_thread::sleep(boost::posix_time::milliseconds(100) );

	q.push(20);
	boost::this_thread::sleep(boost::posix_time::milliseconds(100) );

	w.stop();
	boost::this_thread::sleep(boost::posix_time::milliseconds(100) );
}


int main()
{
	//test_queue();
	test_worker();
	return 0;
}
