#include <iostream>
#include <boost/assert.hpp>
#include <boost/static_assert.hpp>

#include"tcp_server.hpp"
#include "worker.hpp"
using namespace std;

bool handle_msg(tcp_message*& p)
{
	cout << p->get_head()->size << endl;
	p->msg_data() [p->get_head()->size] = 0;
	cout << p->msg_data().data() << endl;

	p->get_session()->write(p);
	return true;
}


int main ()
{
	cout << "echo server" << endl;
	typedef tcp_server::queue_type queue_type;
	queue_type msg_q;

	worker<queue_type> w(msg_q, handle_msg);
	w.start();

	tcp_server svr(6688, msg_q, 1);
	svr.run();

	return 0;
}
