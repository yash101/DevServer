#include "preprocessor.hxx"

inline bool start_server()
{
    try
    {
        glob::srv.start_async();
        return true;
    }
    catch(std::exception& e)
    {
        std::cout << "Failed to launch the server!" << std::endl;
        return false;
    }
}

inline void shutdown_server()
{
    try
    {
        dlib::iosockstream sock("localhost:" + dlib::cast_to_string(glob::server_port));
        sock << "GET /force_shdn HTTP/1.0\r\n\r\n";
        while(sock.get() != EOF)
        {
            //Just ignore everything. We probably won't be getting anything anyways!
        }
    }
    catch(std::exception& e)
    {
        //This means that there is no server to shut down!
        std::cout << e.what() << std::endl;
    }
}

void server()
{
    //Try to create a connection on localhost:same port and send a polite shutdown signal. This
    //signal will be read by the server and std::terminate() will be caused. This will cause a program
    //crash, but we don't care. That means the program is running properly!
    shutdown_server();
    //Try to start the server. If this fails, that means there is a problem. We call terminate() and crash
    //the program. This is an actual crash!
    if(!start_server())
    {
        std::cout << "Failed at launching server!" << std::endl;
        std::terminate();
    }
}

void program()
{
    prog::load();
    glob::srv.set_listening_port(glob::server_port);
    //glob::srv.start_async();
    server();
}

//Main function. Called upon program launch
int main(int argc, char* argv[])
{
    std::thread prgm(program);
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    return 0;
}
