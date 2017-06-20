#include "tcp_session.h"
#include <boost/bind.hpp>
using namespace boost;
using namespace boost::asio;

tcp_session::object_pool_type tcp_session::m_msg_pool;

tcp_session::tcp_session(ios_type& ios, queue_type& q) :
		m_socket(ios),
		m_strand(ios),
		m_queue(q)
{ }

tcp_session::socket_type& tcp_session::socket()
{
	return m_socket;
}

tcp_session::ios_type& tcp_session::io_service()
{
	return m_socket.get_io_service();
}

void tcp_session::close()
{
	boost::system::error_code ignored_ec;
	m_socket.shutdown(ip::tcp::socket::shutdown_both, ignored_ec);
	m_socket.close(ignored_ec);
}

void tcp_session::start()
{
	tcp_message* req = create_request();
	read(req);
}

tcp_message* tcp_session::create_request()
{
	return m_msg_pool.construct(
			shared_from_this(),
			bind(&object_pool_type::destroy, ref(m_msg_pool), _1) );
}

void tcp_session::read(tcp_message* req)
{
	async_read(m_socket,
			buffer(req->head_data().data(), req->head_data().size() ),
			m_strand.wrap(
					bind(&tcp_session::handle_read_head,
							this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred,
							req) )
					);
}

void tcp_session::handle_read_head(const boost::system::error_code& error, size_t bytes_transferred, tcp_message* req)
{
	if(error || !req->check_head() )
	{
		close();
		req->destory();
		return;
	}

	async_read(m_socket,
			buffer(req->msg_data().data(), req->get_head()->size ),
			m_strand.wrap(
					bind(&tcp_session::handle_read_msg,
							this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred,
							req) )
					);
}

void tcp_session::handle_read_msg(const boost::system::error_code& error, size_t bytes_transferred, tcp_message* req)
{
	if(error || !req->check_msg_crc() )
	{
		close();
		req->destory();
		return;
	}

	m_queue.push(req);

	start();
}

void tcp_session::write(tcp_message* resp)
{
	async_write(m_socket,
			buffer(resp->head_data().data(), resp->head_data().size() ),
			m_strand.wrap(
					bind(&tcp_session::handle_write_head,
							this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred,
							resp) )
					);
}

void tcp_session::handle_write_head(const boost::system::error_code& error, size_t bytes_transferred, tcp_message* resp)
{
	if(error || bytes_transferred != resp->head_data().size() )
	{
		close();
		resp->destory();
		return;
	}

	async_write(m_socket,
			buffer(resp->msg_data().data(), resp->get_head()->size ),
			m_strand.wrap(
					bind(&tcp_session::handle_write_msg,
							this,
							boost::asio::placeholders::error,
							boost::asio::placeholders::bytes_transferred,
							resp) )
					);
}

void tcp_session::handle_write_msg(const boost::system::error_code& error, size_t bytes_transferred, tcp_message* resp)
{
	if(error || bytes_transferred != resp->get_head()->size )
	{
		close();
		resp->destory();
		return;
	}

	resp->destory();
}










