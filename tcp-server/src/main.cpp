//#include "io_service_pool.hpp"
#include <iostream>
#include <cassert>

#include "tcp_server.hpp"

using namespace std;

int main()
{
	Log::Init("../log");
	LOG_INFO << "server start";

	tcp_server<tcp_handler> svr(6677, 1);
	svr.run();

    return 0;
}
