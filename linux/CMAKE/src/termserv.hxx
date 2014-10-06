#pragma once
#include "preprocessor.hxx"
#include "globals.hxx"

namespace tsrv
{
    class termserv : public dlib::server_iostream
    {
        void on_connect(std::istream& in, std::ostream& out, const std::string& foreign_ip, const std::string& local_ip, unsigned short foreign_port, unsigned short local_port, dlib::uint64 connection_id)
        {
            out << "Welcome to the DevServer Console! Type \"help\" for assistance!" << std::endl;
            while(true)
            {
                while(in.peek() != EOF)
                {
                    out << "$";
                    std::string cmd;
                    std::getline(in, cmd);

                    if(!strcmp(cmd.c_str(), "halt"))
                    {
                        out << "Server Shutting Down!" << std::endl;
                        std::terminate();
                    }

                    out << "Syntax error! Invalid token!" << std::endl;
                }
            }
        }
    };
}
