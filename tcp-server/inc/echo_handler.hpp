#ifndef ECHO_HANDLER_HPP
#define ECHO_HANDLER_HPP

#include "tcp_handler.hpp"
#include "log.h"

class echo_handler : public tcp_handler
{
public:
	echo_handler()
	{
		handle_open = &echo_handler::echo_handle_open;
		handle_close = &echo_handler::echo_handle_close;
		handle_read = &echo_handler::echo_handle_read;
		handle_write = &echo_handler::echo_handle_write;
	}

private:
	static void echo_handle_open(tcp_session_type session)
	{
		LOG_INFO << "session start from: " << session->socket().remote_endpoint().address() ;
	}

	static void echo_handle_close(tcp_session_type session)
	{
		LOG_INFO << "session close";
	}

	static void echo_handle_read(tcp_session_type session, std::size_t n)
	{
		LOG_INFO << "read size: " << n;
		LOG_INFO << std::string (session->read_buf().peek(), n);

		session->write (session->read_buf().peek(), n);
	}

	static void echo_handle_write(tcp_session_type session, std::size_t n)
	{
		LOG_INFO << "write complete: " << n;
	}
};//echo_handler

#endif //ECHO_HANDLER_HPP
