#ifndef _PLAYDAR_DARKNET_SERVENT_H_
#define _PLAYDAR_DARKNET_SERVENT_H_

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <iostream>
#include <vector>

#include "msgs.h"
#include "connection.hpp"

namespace playdar {
namespace resolvers {

class darknet; //fwd

const boost::uint32_t SERVER_VERSION = 1;

class Servent
{
public:
    /// Constructor opens the acceptor and starts waiting for the first incoming
    /// Connection.
    Servent( boost::asio::io_service& io_service, 
             unsigned short port, 
             darknet * p );
    
    /// Handle completion of a accept operation.
    void handle_accept(const boost::system::error_code& e, connection_ptr conn);
    
    /// Handle completion of a write operation.
    void handle_write(  const boost::system::error_code& e, 
                        connection_ptr conn,
                        msg_ptr msg);
    
    /// Handle completion of a read operation.
    void handle_read(   const boost::system::error_code& e, 
                        msg_ptr msg, 
                        connection_ptr conn);
                        
    /// Connect out to a remote Servent:
    void connect_to_remote(boost::asio::ip::tcp::endpoint &endpoint);
    
    /// Handle completion of a connect operation.
    void handle_connect(const boost::system::error_code& e,
                        boost::asio::ip::tcp::endpoint &endpoint,
                        connection_ptr conn);
                        
    boost::asio::io_service & get_io_service() 
    {
        return m_acceptor.get_io_service();
    }

private:


    /// The acceptor object used to accept incoming socket connections.
    boost::asio::ip::tcp::acceptor m_acceptor;
    /// protocol state machine
    darknet * m_protocol;
};

} // namespace 
} // namespace playdar

#endif
