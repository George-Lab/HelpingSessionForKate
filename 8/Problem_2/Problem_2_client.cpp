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

void write_thread(tcp::socket & socket_, string & user_name) {
    string message;
    cin.ignore();
    while (true) {   
        std::getline(std::cin, message);
        message = user_name + ": " + message + "\n";
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
//obtaining the IP-adress and the protocol port number
    string raw_ip_address;
    cout << "Enter IPv4 of server to connect to: ";
    cin >> raw_ip_address;
    unsigned short port_num;
    cout << "Enter server\'s port number: ";
    cin >> port_num;
// Used to store information about error that happens
// while parsing the raw IP-address.
    boost::system::error_code ec;
// Using IP protocol version independent address
// representation.
    boost::asio::ip::address ip_address =
        boost::asio::ip::address::from_string(raw_ip_address, ec);

    if (ec.value() != 0) {
        // Provided IP address is invalid. Breaking execution.
        std::cout 
        << "Failed to parse the IP address. Error code = "
        << ec.value() << ". Message: " << ec.message();
        return ec.value();
    }

    boost::asio::ip::tcp::endpoint ep(ip_address, port_num);
    boost::asio::io_service io_service;
//socket creation
     tcp::socket socket_(io_service, ep.protocol());
//connection
    cout << "Connecting to the server...\n";
    socket_.connect(ep);
    cout << "Connected successfully!\n";

//thread group
    int already_read_ = 0; 
    char buff_[1024];
    boost::thread_group threads;

    string user_name; 
    cout << "Enter your name: ";
    cin >> user_name;
    threads.create_thread(boost::bind(write_thread, boost::ref(socket_), boost::ref(user_name)));

    threads.create_thread(boost::bind(read_thread, boost::ref(socket_), boost::ref(already_read_), boost::ref(buff_)));
    
    threads.join_all();

    return 0;

}