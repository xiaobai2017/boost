#define BOOST_TEST_DYC_LINK
#include <boost/test/unit_test.hpp>

#include "job_queue.hpp"

BOOST_AUTO_TEST_SUITE (s_job_queue)

BOOST_AUTO_TEST_CASE(t_all)
{
	job_queue<int> q;
	q.push(10);
	q.push(20);

	int tmp = q.pop();
	BOOST_CHECK_EQUAL(tmp, 110);
	BOOST_CHECK_EQUAL (q.pop(), 20);
	q.push(30);
	q.stop();
	tmp = q.pop();
	BOOST_CHECK_EQUAL(tmp, 0);
}

BOOST_AUTO_TEST_SUITE_END()
