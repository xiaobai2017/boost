#ifndef CHARGEN_HANDLER_HPP
#define CHARGEN_HANDLER_HPP

#include "tcp_handler.hpp"
#include "log.h"
#include <boost/circular_buffer.hpp>
#include <boost/next_prior.hpp>
#include <boost/range/counting_range.hpp>
//#include <boost/range/algorithm.hpp>
#include <boost/range/algorithm/copy.hpp>

class chargen_handler : public tcp_handler
{
public:
	chargen_handler()
	{
		handle_open = &chargen_handler::chargen_handle_open;
		handle_write = &chargen_handler::chargen_handle_write;
	}

private:
	static void chargen_handle_open(tcp_session_type session)
	{
		LOG_INFO << "chargen start from: " << session->socket().remote_endpoint().address() ;

		write(session);
	}

	static void chargen_handle_write(tcp_session_type session, std::size_t n)
	{
		LOG_INFO << "write complete: " << n;
		write(session);
	}

	typedef boost::circular_buffer<char> cb_type;
	static void write(tcp_session_type session)
	{
		static cb_type msg(0x7f - 0x20);
		if(msg.empty() )
		{
			init(msg);
		}

		std::vector<char> tmp(msg.begin(), msg.begin() + 72);

		session->write_buf().append(&tmp[0], tmp.size());
		session->write_buf().append("\n", 1);
		//LOG_INFO << std::string (session->write_buf().peek(), session->write_buf().size() );
		session->write();

		msg.rotate(boost::next(msg.begin() ) );
	}

private:
	static void init(cb_type & msg)
	{
		boost::copy(
				boost::counting_range(0x20, 0x7f),
				std::back_inserter(msg) );
	}

};//chargen_handler

#endif //CHARGEN_HANDLER_HPP
