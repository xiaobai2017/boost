#include "io_service_pool.hpp"
#include <iostream>
#include <cassert>
#include "tcp_buffer.hpp"

int main()
{
	//io_service_pool  ios_pool;
	const char* str = "Hello World!";
	tcp_buffer buf;
	buf.prepare();
	assert (buf.size() == 0);
	buf.append(str, strlen(str));

	std::cout << "["<< buf.peek() <<"]\n";
	assert (buf.size() == strlen(str));
	assert(strlen(str) == 12);

	buf.consume(2);
	std::cout << "["<< buf.peek() <<"]\n";


    return 0;
}
