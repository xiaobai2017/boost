//#include "io_service_pool.hpp"
#include <iostream>
#include <cassert>
//#include "tcp_buffer.hpp"
#include "tcp_server.h"

using namespace std;

int main()
{
	cout << "server start" << endl;

	tcp_server svr(6677);
	svr.run();

    return 0;
}
