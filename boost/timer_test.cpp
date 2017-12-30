#include <chrono>
#include <iostream>
#include "asionick.h"

int main(int argc, char const *argv[])
{
	asio::io_service service;
	asio::deadline_timer timer(service, boost::posix_time::milliseconds(100));
	timer.async_wait([](const ErrorCode& e) { std::cout << "timeout.\n"; });
	std::cout << "after async_wait." << std::endl;

	IpResolver resolver(service);
	IpResolver::query query("www.baidu.com", "80");
	auto iter = resolver.resolve(query);
	EndPoint ep = *iter;
	std::cout << ep.address().to_string() << ":" << ep.port() << std::endl;

	service.run();
	return 0;
}