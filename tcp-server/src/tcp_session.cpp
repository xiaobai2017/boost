#include "tcp_session.h"

#include <iostream>
#include <string>
using namespace std;

#include <boost/bind.hpp>
using namespace boost;
using namespace boost::asio;

tcp_session::tcp_session (ios_type& ios) :
		m_socket (ios) {}

tcp_session::socket_type& tcp_session::socket()
{
	return m_socket;
}

tcp_session::ios_type& tcp_session::io_service()
{
	return m_socket.get_io_service();
}

tcp_session::buffer_type& tcp_session::read_buf()
{
	return m_read_buf;
}

tcp_session::buffer_type& tcp_session::write_buf()
{
	return m_write_buf;
}

void tcp_session::start()
{
	cout << "session start" << endl;

	read();
}

void tcp_session::close()
{
	boost::system::error_code ignored_ec;
	m_socket.shutdown (ip::tcp::socket::shutdown_both, ignored_ec);
	m_socket.close (ignored_ec);
}

void tcp_session::read()
{
	m_socket.async_read_some(
			m_read_buf.prepare(),
			bind (&tcp_session::handle_read, shared_from_this() ,
					asio::placeholders::error, asio::placeholders::bytes_transferred) );
}

void tcp_session::handle_read (const system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		close();
		return;
	}

	cout << "read size" << bytes_transferred << endl;

	m_read_buf.retrieve (bytes_transferred);
	cout << string (m_read_buf.peek(), bytes_transferred) << endl;

	write (m_read_buf.peek() ,bytes_transferred);

	m_read_buf.consume (bytes_transferred);
	read();
}

void tcp_session::write (const void* data, size_t len)
{
	cout << "write:" << len << endl;
	cout << static_cast<const char*> (data) << endl;

	m_write_buf.append (data, len);

	write();
}

void tcp_session::write()
{
	m_socket.async_write_some(
			m_write_buf.data(),
			bind (&tcp_session::handle_write, shared_from_this(),
					asio::placeholders::error, asio::placeholders::bytes_transferred )
			);
}

void tcp_session::handle_write (const system::error_code& error, size_t bytes_transferred)
{
	if (error)
	{
		close();
		return;
	}

	m_write_buf.consume (bytes_transferred);
	cout << "write complete" << endl;
}


















