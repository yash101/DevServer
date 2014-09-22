#pragma once
#include "preprocessor.hxx"
#include "server_actions.hxx"
#include "load.hxx"
namespace srv
{
    //This generates the monitor table we see on the web interface!
    inline std::string montable(std::unordered_map<std::string, std::string> map)
    {
        std::stringstream o;
        o << "<tr>" << std::endl;
        o << "  <th style=\"width: 20%; background-color: #424242;\">Key</th>" << std::endl;
        o << "  <th style=\"width: 80%; background-color: #424242;\">Value</th>" << std::endl;
        o << "</tr>" << std::endl;

        for(auto it = map.begin(); it != map.end(); ++it)
        {
            o << "<tr>" << std::endl;
            o << "  <td>" << it->first << "</td>" << std::endl;
            o << "  <td>" << it->second << "</td>" << std::endl;
            o << "</tr>" << std::endl;
        }
        return o.str();
    }

    //This is the extension of the dlib::server_http class. This gives us a beginner-friendly HTTP server implementation!
    class dev_server : public dlib::server_http
    {
    private:
        //This is the map that holds all the data!
        std::unordered_map<std::string, std::string> database;
        //We will use this Mutex to lock the resources. This will prevent all sorts of corruptions, segfaults and much more!
        std::mutex mtx;
        //This is the function that processes the request!
        const std::string process_request(const dlib::incoming_things& incoming)
        {
            //This is where I send a random number and hex string to the databaase! This is just for demonstration purposes
            #ifdef DEBUG_RNG
            database["RNG"] = dlib::cast_to_string(rand());
            database["CRNG"] = dev::str::cast_to_string(dev::math::random::random_hex_string(32));
            #endif

            //check for the put request, web form based!
            if(!strcmp(incoming.path.c_str(), "/put_wf"))
            {
                std::string key = incoming.queries["key"];
                std::string data = incoming.queries["data"];
                if(key.size() != 0 && data.size() != 0)
                {
                    #ifdef DETAILED_DEBUG
                    std::cout << "Key/Value Pair [" << key << ", " << data << "] injected!" << std::endl;
                    #endif
                    database[key] = data;
                    return "<span style=\"background-color: #98BF21; font-size: 36px;\">Successfully added [" + data + "] : [" + key + "]</span>";
                }
                else
                {
                    return "<span style=\"background-color: red; font-size: 36px;\">Failed adding value. Form incomplete!</span>";
                }
            }

            //check for the get command
            if(!strcmp(incoming.path.c_str(), "/get"))
            {
                return database[incoming.queries["key"]];
            }

            //Check for the monitor table request
            if(!strcmp(incoming.path.c_str(), "/monitor_tbl"))
            {
                return srv::montbl(database);
            }

            if(!strcmp(incoming.path.c_str(), "/"))
            {
                return fs::ramfs::filesystem.read_file("input.html");
            }

            if(!strcmp(incoming.path.c_str(), "/monitor_frm"))
            {
                return fs::ramfs::filesystem.read_file("monitor.htx");
            }

            if(!strcmp(incoming.path.c_str(), "/inject_frm"))
            {
                return fs::ramfs::filesystem.read_file("inject.htx");
            }

            if(!strcmp(incoming.path.c_str(), "/ref"))
            {
                prog::load();
                return "Success!";
            }
            //Check for RNG
            if(!strcmp(incoming.path.c_str(), "/rng"))
            {
                return dlib::cast_to_string(rand());
            }

            //Check for the put request
            if(!strcmp(incoming.path.c_str(), "/put"))
            {
                if(incoming.queries["key"].size() != 0 && incoming.queries["data"].size() != 0)
                {
                    database[incoming.queries["key"]] = incoming.queries["data"];
                    return "Y";
                }
                else
                {
                    return "N";
                }
            }

            if(!strcmp(incoming.path.c_str(), "/force_shdn"))
            {
                std::cout << "Recieved the signal to force shutdown! :(" << std::endl;
                std::terminate();
            }

#ifdef ENABLE_WEB_SHUTDOWN
            if(!strcmp(incoming.path.c_str(), "/shdn"))
            {
                std::cout << "Server signaled to shut down!" << std::endl;
                std::terminate();
            }
#endif

            //If nothing is left to do, error handler!
            return fs::ramfs::filesystem.read_file("input.html");
        }

    public:
        //This is my request handler
        const std::string on_request(const dlib::incoming_things &incoming, dlib::outgoing_things &outgoing)
        {
            //Let's just print out some DEBUG info
#ifdef DETAILED_DEBUG
#ifdef DEBUG_WEBINF
            std::cout << std::endl;
            std::cout << "Time: " << dev::str::getTime();
            std::cout << "Path Requested: " << incoming.path << std::endl;
            std::cout << "Incoming IP: " << incoming.foreign_ip << std::endl;
            std::cout << "Foreign Port: " << incoming.foreign_port << std::endl;
            std::cout << "Requested Protocol: " << incoming.protocol << std::endl;
            std::cout << "Request Type: " << incoming.request_type << std::endl;
#endif
#endif
            //Lock the Mutex. In the previous version, all the problems were happening because the mutexes weren't locking/unlocking properly.
            //This solves that problem by putting the mutexes in a specific place where they are much more serviciable!
            mtx.lock();
            //Process the request
            std::string x = process_request(incoming);
            //Unlock the mutex so we do not have our server freezing!
            mtx.unlock();
            //Return the serve data!
            return x;
        }
    };
}

namespace glob
{
    //The DevServer!!!
    static srv::dev_server srv;
}
