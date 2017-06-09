#include "tcp_server.h"

#include <boost/bind.hpp>
#include <boost/functional/factory.hpp>
using namespace boost;
using namespace boost::asio;

template<typename Handler>
tcp_server<Handler>::tcp_server (unsigned short port, int n) :
		m_ios_pool (n),
		m_acceptor (m_ios_pool.get(),
				ip::tcp::endpoint (ip::tcp::v4(), port) )
{
	start_accept();
}

template<typename Handler>
void tcp_server<Handler>::start_accept ()
{
	//tcp_session_ptr session = factory<tcp_session_ptr> () (m_ios_pool.get() );
	tcp_session_ptr session = make_shared<tcp_session> (m_ios_pool.get() );
	m_acceptor.async_accept (session->socket(),
			bind (&tcp_server::handle_accept, this, asio::placeholders::error, session) );
}

template<typename Handler>
void tcp_server<Handler>::handle_accept (const system::error_code& error, tcp_session_ptr session)
{
	start_accept ();

	if (error)
	{
		session->close();
		return;
	}

	session->start(m_handler);
	// or session->io_service().dispatch (bind(&tcp_session::start, session) );
}

template<typename Handler>
void tcp_server<Handler>::start()
{
	m_ios_pool.start();
}

template<typename Handler>
void tcp_server<Handler>::run()
{
	m_ios_pool.run();
}
