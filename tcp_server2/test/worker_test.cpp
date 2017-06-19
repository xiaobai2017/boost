#define BOOST_TEST_DYC_LINK
#include <boost/test/unit_test.hpp>

#include <iostream>
#include <boost/smart_ptr.hpp>
using namespace boost;

#if 0
struct global_fixture
{
	global_fixture()
	{
		std::cout << "global setup\n";
	}
	~global_fixture()
	{
		std::cout << "global teardown\n";
	}
};


BOOST_GLOBAL_FIXTURE(global_fixture);

struct smart_ptr_fixture
{
	smart_ptr_fixture()
	{
		std::cout << "suit setup\n";
	}
	~smart_ptr_fixture()
	{
		std::cout << "suit teardown\n";
	}

	shared_ptr<int> p;
};

BOOST_FIXTURE_TEST_SUITE(s_smart_ptr, smart_ptr_fixture)

BOOST_AUTO_TEST_CASE(t_scoped_ptr1)
{
	scoped_ptr<int> p(new int(874) );
	BOOST_CHECK(p);
	BOOST_CHECK_EQUAL(*p, 87);
	p.reset();
	BOOST_CHECK(p == nullptr);
}

BOOST_AUTO_TEST_SUITE_END()	//s_smart_ptr
#endif
