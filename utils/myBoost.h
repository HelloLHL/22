//
// Created by 李洪良 on 2023/6/12.
//

#ifndef DAILY_PRACTICE_MYBOOST_H
#define DAILY_PRACTICE_MYBOOST_H

#include "boost/asio.hpp"
#include "boost/array.hpp"
#include <string>

/*
boost::asio::io_service io_service;
boost::asio::ip::tcp::resolver resolver(io_service);
boost::asio::ip::tcp::socket sock(io_service);
boost::array<char,4096>buffer;

void read_handle(const boost::system::error_code &ec, std::size_t bytes_transferred) {
    if(!ec)  {
        cout<<std::string(buffer.data(), bytes_transferred)<<endl;
        sock.async_read_some(boost::asio::buffer(buffer), read_handle);
    }
}

void connect_handle(const boost::system::error_code &ec) {
    if(!ec) {
        boost::asio::write(sock, boost::asio::buffer("GET / HTTP/1.1\r\nHost: www.highscore.de\r\n\r\n"));
        sock.async_read_some(boost::asio::buffer(buffer), read_handle);
        cout<<"i  am here"<<endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    }
}

void resolve_handle(const boost::system::error_code  &ec, boost::asio::ip::tcp::resolver::iterator it){
    cout<<"resolve_handle"<<endl;
    if(!ec) {
        sock.async_connect(*it, connect_handle);
    }
}
*/
/*
boost::asio::io_service io_service1;
boost::asio::ip::tcp::endpoint endpoint(boost::asio::ip::tcp::v4(), 80);
boost::asio::ip::tcp::acceptor acceptor(io_service1, endpoint);
boost::asio::ip::tcp::socket sock1(io_service1);
std::string data1 = "HTTP/1.1 200 OK\r\nContent-Length:13\r\n\r\nHello.World!";

boost::array<char,4096>response;
*/

boost::asio::io_service io_service2;
boost::asio::ip::tcp::endpoint endpoint2(boost::asio::ip::tcp::v4(), 8000);
boost::asio::ip::tcp::acceptor acceptor2(io_service2, endpoint2);


void write_handler(const boost::system::error_code &ec, std::size_t bytes_transferred, boost::asio::ip::tcp::socket &sock)
{
    if (!ec)
    {
        // 写入成功后等待下一次请求
        boost::array<char,4096>buffer;
        boost::asio::async_read_until(sock, boost::asio::buffer(buffer), "\r\n\r\n",
                                      [&sock, buffer](const boost::system::error_code& ec, std::size_t bytes_transferred)
                                      {
                                          if (!ec)
                                          {
                                              std::string request(&buffer[0], &buffer[bytes_transferred]);
                                              std::cout << "Received request:\n" << request << "\n";
                                              boost::asio::async_write(sock, boost::asio::buffer("HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!"),
                                                                       [&sock](const boost::system::error_code& ec, std::size_t bytes_transferred)
                                                                       {
                                                                           if (!ec)
                                                                           {
                                                                               // 继续等待下一次请求
                                                                               write_handler(ec, bytes_transferred, sock);
                                                                           }
                                                                       });
                                          }
                                      });
    }
}



void accept_handler(boost::asio::ip::tcp::socket &sock, const boost::system::error_code &ec)
{
    if (!ec)
    {
        // 接收到连接后等待第一次请求
        std::vector<char> buffer(1024);
        cout<<"bytes:32445335346"<<endl;

        boost::asio::async_read_until(sock, boost::asio::dynamic_buffer(buffer), "\r\n\r\n",
                                      [&sock, buffer](const boost::system::error_code& ec, std::size_t bytes_transferred)
                                      {
            cout<<"bytes:"<<bytes_transferred<<endl;
                                          if (!ec)
                                          {
                                              std::string request(&buffer[0], &buffer[bytes_transferred]);
                                              std::cout << "Received request:\n" << request << "\n";
                                              boost::asio::async_write(sock, boost::asio::buffer("HTTP/1.1 200 OK\r\nContent-Length: 13\r\n\r\nHello, world!"),
                                                                       [&sock](const boost::system::error_code& ec, std::size_t bytes_transferred)
                                                                       {
                                                                           if (!ec)
                                                                           {
                                                                               // 等待下一次请求
                                                                               write_handler(ec, bytes_transferred, sock);
                                                                           }
                                                                       });
                                          }
                                      });
    }
}

void my_boost() {
    /*
    boost::asio::io_service _io_service;
    boost::asio::ip::tcp::resolver _resolver(_io_service);
    boost::asio::ip::tcp::resolver::query _query("baidu.com", "80");
    auto iter = _resolver.resolve(_query);
    std::cout<<iter->endpoint().address()<<":"<<iter->endpoint().port()<<"/"<<iter->host_name()<<std::endl;
     */

    /*
    boost::asio::ip::tcp::resolver::query  query("www.highscore.de", "80");
    resolver.async_resolve(query, resolve_handle);
    cout<<"world"<<endl;
    io_service.run();
    cout<<"hello"<<endl;
    */

    acceptor2.listen();
    while (true) {
        boost::asio::ip::tcp::socket sock2(io_service2);
        acceptor2.async_accept(sock2, boost::bind(accept_handler, boost::ref(sock2), boost::placeholders::_1));
        io_service2.run();

    }
}





#endif //DAILY_PRACTICE_MYBOOST_H
