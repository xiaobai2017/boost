#ifndef TCP_SERVER.H
#define TCP_SERVER_H

#include "tcp_session.h"
#include "io_service_pool.hpp"

class tcp_server
{
public:
	typedef io_service_pool::ios_type ios_type;

	tcp_server (unsigned short port, int n = 1);
	void start();
	void run();

private:
	io_service_pool 		m_ios_pool;
	typedef boost::asio::ip::tcp::acceptor acceptor_type;
	acceptor_type		m_acceptor;
	void start_accept();
	void handle_accept (const boost::system::error_code& error,
			tcp_session_ptr session);
};

#endif //TCP_SERVER_H
