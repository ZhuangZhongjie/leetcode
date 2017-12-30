#include <boost/asio.hpp> 

// namespace alias
namespace asio = boost::asio;
namespace ip = boost::asio::ip;

// class alias
using IpResolver = ip::tcp::resolver;
using EndPoint = ip::tcp::endpoint;
using ErrorCode = boost::system::error_code;
using TcpSocket = ip::tcp::socket;
