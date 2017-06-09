#include "tcp_server.h"

#include <boost/bind.hpp>
#include <boost/functional/factory.hpp>
using namespace boost;
using namespace boost::asio;

tcp_server::tcp_server (unsigned short port, int n) :
		m_ios_pool (n),
		m_acceptor (m_ios_pool.get(),
				ip::tcp::endpoint (ip::tcp::v4(), port) )
{
	start_accept();
}

void tcp_server::start_accept ()
{
	//tcp_session_ptr session = factory<tcp_session_ptr> () (m_ios_pool.get() );
	tcp_session_ptr session = make_shared<tcp_session> (m_ios_pool.get() );
	m_acceptor.async_accept (session->socket(),
			bind (&tcp_server::handle_accept, this, asio::placeholders::error, session) );
}

void tcp_server::handle_accept (const system::error_code& error, tcp_session_ptr session)
{
	start_accept ();

	if (error)
	{
		session->close();
		return;
	}

	session->start();
	// or session->io_service().dispatch (bind(&tcp_session::start, session) );
}

void tcp_server::start()
{
	m_ios_pool.start();
}

void tcp_server::run()
{
	m_ios_pool.run();
}
