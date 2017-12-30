// -*- coding:utf8 -*-

#include <iostream>
#include <boost/asio.hpp>

using IoService = boost::asio::io_service;
using TcpSocket = boost::asio::ip::tcp::socket;
using ErrorCode = boost::system::error_code;
// using Buffer = boost::asio::buffer;
using EndPoint = boost::asio::ip::tcp::endpoint;
using IPAddress = boost::asio::ip::address;

static const int BUFSIZE = 1024;
char rbuf[BUFSIZE], wbuf[BUFSIZE] = "OK";

IoService service;
TcpSocket sock(service);

void on_read(const ErrorCode &err, std::size_t bytes);

void on_write(const ErrorCode &err, std::size_t bytes)
{
	sock.async_read_some(boost::asio::buffer(rbuf), on_read);
}

void on_read(const ErrorCode &err, std::size_t bytes)
{
	std::cout << bytes << "bytes read.\n";
	sock.async_write_some(boost::asio::buffer(wbuf, 3), on_write);
}

void on_connect(const ErrorCode &err)
{
	sock.async_read_some(boost::asio::buffer(rbuf), on_read);
}

int main(int argc, char* argv[])
{
	EndPoint ep(IPAddress::from_string("127.0.0.1"), 2001);	
	sock.async_connect(ep, on_connect);
	service.run();

	return 0;
}