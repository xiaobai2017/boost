#ifndef TCP_SESSION_H
#define TCP_SESSION_H

#include "tcp_buffer.hpp"
#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>

class tcp_session :
		public boost::enable_shared_from_this<tcp_session>
{
public:
	typedef boost::asio::ip::tcp::socket 	socket_type;
	typedef boost::asio::io_service 				ios_type;
	typedef tcp_buffer 										buffer_type;

private:
	socket_type m_socket;
	buffer_type m_read_buf;
	buffer_type m_write_buf;

public:
	tcp_session (ios_type& ios);

	socket_type& socket();
	ios_type& io_service();
	buffer_type& read_buf();
	buffer_type& write_buf();

	void start();
	void close();

	void write();
	void write (const void* data, std::size_t len);


private:
	void read();
	void handle_read (const boost::system::error_code& error,
			size_t bytes_transferred);
	void handle_write (const boost::system::error_code& error,
			size_t bytes_transferred);
};//tcp_session

typedef boost::shared_ptr<tcp_session> tcp_session_ptr;

#endif //TCP_SESSION_H




























