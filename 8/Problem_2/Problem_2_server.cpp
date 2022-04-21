#include <iostream>
#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/bind.hpp>
#include <boost/chrono.hpp>

using namespace boost::asio;
using ip::tcp;
using std::string;
using std::cout;
using std::cin;
using std::endl;

// thread safe read/write operations
boost::recursive_mutex rw;

void send_(tcp::socket & socket, const string& message) {
       const string msg = message + "\n";
       boost::asio::write( socket, boost::asio::buffer(message) );
}

void write_thread(tcp::socket & socket_) {
    string message;
    cin.ignore();
    while (true) {
        std::getline(std::cin, message);
        message = "Server: " + message + "\n";
        boost::recursive_mutex::scoped_lock lk(rw);
        send_(socket_, message);
        //cout << "Server: " << message << endl;
    }
}

void read_thread(tcp::socket & socket_, int & already_read_, char buff_[]) {
    while (true) {
        boost::this_thread::sleep( boost::posix_time::millisec(1));
        boost::recursive_mutex::scoped_lock lk(rw);
        if ( socket_.available())
            already_read_ += socket_.read_some(
                buffer(buff_ + already_read_, 1024 - already_read_));
        bool found_enter = std::find(buff_, buff_ + already_read_, '\n') 
                          < buff_ + already_read_;
        if ( !found_enter)
            continue; // message is not full
        // process the message
        size_t pos = std::find(buff_, buff_ + already_read_, '\n') - buff_;
        std::string message(buff_, pos);
        std::copy(buff_ + already_read_, buff_ + 1024, buff_);
        already_read_ -= pos + 1;
        cout << message << endl;
    }
}


int main() {
// Create special object of asio::ip::address class
// that specifies all IP-addresses available on the host.
    const std::size_t size = 30;
    unsigned short port_num;
    cout << "Enter port number to start the server: ";
    cin >> port_num;
    boost::asio::ip::address ip_address = boost::asio::ip::address_v4::any();
    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);

//listen for new connection
    boost::asio::io_service io_service;
    tcp::acceptor acceptor_(io_service, ep.protocol());
    acceptor_.bind(ep);
    acceptor_.listen(size);
//socket creation 
    tcp::socket socket_(io_service);
//waiting for connection
    cout << "Waiting for a user...\n";
    acceptor_.accept(socket_);
    cout << "User joined!\n";

//thread group
    int already_read_ = 0; 
    char buff_[1024];
    boost::thread_group threads;
    threads.create_thread(boost::bind(write_thread, boost::ref(socket_)));

    threads.create_thread(boost::bind(read_thread, boost::ref(socket_), boost::ref(already_read_), boost::ref(buff_)));
    
    threads.join_all();

    return 0;

}