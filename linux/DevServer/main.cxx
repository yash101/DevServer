#include "preprocessor.hxx"

void server()
{
    glob::srv.start();
}

void program()
{
    prog::load();
    glob::srv.set_listening_port(glob::server_port);
    glob::srv.start_async();
}

//Main function. Called upon program launch
int main(int argc, char* argv[])
{
    program();
    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(300));
    }
    return 0;
}
