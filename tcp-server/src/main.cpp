//#include "io_service_pool.hpp"
#include <iostream>
#include <cassert>

#include "tcp_server.hpp"
#include "echo_handler.hpp"
#include "daytime_handler.hpp"
#include "chargen_handler.hpp"

using namespace std;

int main()
{
	Log::Init("../log");
	LOG_INFO << "server start";

	auto ios = boost::make_shared<io_service_pool> ();
	tcp_server<echo_handler> echo_svr(ios, 7);
	tcp_server<daytime_handler> daytime_svr(ios, 13);
	tcp_server<chargen_handler> chargen_svr(ios, 19);
	ios->run();

    return 0;
}
