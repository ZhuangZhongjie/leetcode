#include <iostream>
#include "asionick.h"

class Connection 
{
public:
	const static int MAX_MSG = 1024;

	Connection(IoService &service): sock(service), is_started(false)
	{
	}

	void start(const EndPoint &ep) 
	{
		sock.async_connect(ep, [&this](const ErrorCode &err) { this->on_connect(err); });
	}

	void stop()
	{
		if (!is_started)
		{
			return ;
		}

		is_started = false;
		sock.close();
	}

	bool started()
	{
		return is_started;
	}


private:
	void on_connect(const ErrorCode &err)
	{
		if (!err)
		{
			do_read();
		}
		else
		{
			stop();
		}
	}

	void do_read()
	{
		sock.async_receive(asio::buffer(rbuf), [&this](const ErrorCode &err, std::size_t bytes) { this->on_read(err, bytes); });
	}

	void on_read(const ErrorCode &err, std::size_t bytes)
	{
		if (!is_started)
		{
			return ;
		}

		std::string msg(rbuf, bytes);
		if (msg == "can_login")
		{
			do_write("access_data");
		}
		else if (msg.find("data ") == 0)
		{
			process_data(msg);
		}
		else if (msg == "login_fail")
		{
			stop();
		}
	}

private:
	TcpSocket sock;
	char rbuf[MAX_MSG]; // read buffer
	char wbuf[MAX_MSG]; // write buffer
	bool is_started;

};

int main(int argc, char const *argv[])
{
	
	return 0;
}