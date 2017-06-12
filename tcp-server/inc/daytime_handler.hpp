#ifndef DAYTIME_HANDLER_HPP
#define DAYTIME_HANDLER_HPP

#include "tcp_handler.hpp"
#include "log.h"
#include <boost/date_time/posix_time/posix_time.hpp>

class daytime_handler : public tcp_handler
{
public:
	daytime_handler()
	{
		handle_open = &daytime_handler::daytime_handle_open;
		handle_write = &daytime_handler::daytime_handle_write;
	}

private:
	static void daytime_handle_open(tcp_session_type session)
	{
		LOG_INFO << "daytime start from: " << session->socket().remote_endpoint().address() ;

		using namespace boost::posix_time;
		auto ptime = microsec_clock::local_time();
		std::string str = to_simple_string (ptime);

		session->write(str.c_str(), str.size() );
	}

	static void daytime_handle_write(tcp_session_type session, std::size_t n)
	{
		LOG_INFO << "write complete: " << n;
		session->close();
	}
};//daytime_handler

#endif //DAYTIME_HANDLER_HPP
