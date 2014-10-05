#pragma once
#include "preprocessor.hxx"
#include "server_actions.hxx"
#include "load.hxx"

//Server API tutorial:
//All server code is under the namespace, srv.
//In this program though, we have a certain server object that we are to use.
//This is because the program has to play with the server too!
//To use the server in your code, use the one under the namespace glob.
//This is the preconfigured server.
//To use it within userprgm.hxx:
//The API is already set up!
//To put data into the table, use the command, glob::srv.put(std::string key, std::string value).
//To get a C++ Basic String (std::string) of the value associated with a key,
//use glob::srv.get(std::string key). To get an std::unordered_map of the key/value
//pairs, use the glob::srv.getTable() function.
//Enjoy! That's the basics!
//
//
//
//===============[CODE START]==================

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
        //We will use a timed mutex to prevent major server failures. If DLib crashes a thread, the mutex will stay locked
        //so the server will freeze and build up threads! Not what we want! We can set a timeout here!
        std::timed_mutex mtx;

        //This is the function that processes the request!
        inline const std::string process_request(const dlib::incoming_things& incoming, dlib::outgoing_things& outgoing)
        {
            //This is where I send a random number and hex string to the databaase! This is just for demonstration purposes
            #ifdef DEBUG_RNG
            database["RNG"] = dlib::cast_to_string(rand());
            database["CRNG"] = dev::str::cast_to_string(dev::math::random::random_hex_string(32));
            #endif

            //check for the put request, web form based!

            if(!strcmp(incoming.path.c_str(), "/put_wf_new"))
            {
                std::string key = incoming.queries["key"];
                std::string data = incoming.queries["data"];
                if(key.size() != 0 && data.size() != 0)
                {
                    #ifdef DETAILED_DEBUG
                    std::cout << "Key/Value Pair [" << key << ", " << data << "] injected!" << std::endl;
                    #endif
                    database[key] = data;
                    return "Add Successful!";
                }
                else
                {
                    return "Add Failure! Perhaps the form is incomplete";
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

            //Check for Heartbeat
            if(!strcmp(incoming.path.c_str(), "/heartbeat"))
            {
                return "";
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

            //Check if the database is to be cleared!
            if(!strcmp(incoming.path.c_str(), "/clear_db"))
            {
                database.clear();
                return "Success!";
            }

            if(!strcmp(incoming.path.c_str(), "/del"))
            {
                if(incoming.queries["key"].size() != 0)
                {
                    database.erase(incoming.queries["key"]);
                    return "Success!";
                }
                else
                {
                    return "Delete Failed! Invalid Key!";
                }
            }

            if(!strcmp(incoming.path.c_str(), "/force_shdn"))
            {
                std::cout << "Recieved the signal to force shutdown! :(" << std::endl;
                std::terminate();
            }

            if(!strcmp(incoming.path.c_str(), "/shdn"))
            {
                std::cout << "Server signaled to shut down!" << std::endl;
#ifdef ENABLE_WEB_SHUTDOWN
                //Lambdas are soooo lovely! No need to write a completely new function to do this simple task!
                std::thread shdn_t(
                []()
                {
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::terminate();
                });
                std::cout << "Shutting down using thread: " << shdn_t.get_id() << std::endl;
                shdn_t.detach();
                return "Shutting down server in one second!";
#else
                std::cout << "Sorry! Shutdown Prohibited!" << std::endl;
                return "Sorry! Shutdown Prohibited!";
#endif
            }

            //FOR THE NEW WEB INTERFACE
            if(!strcmp(incoming.path.c_str(), "/"))
            {
                return fs::ramfs::filesystem.read_file_autocache(homepage);
            }

            if(!strcmp(incoming.path.c_str(), "/css"))
            {
                outgoing.headers["Content-type"] = "text/css";
                return fs::ramfs::filesystem.read_file_autocache(css_file);
            }

            if(!strcmp(incoming.path.c_str(), "/js"))
            {
                outgoing.headers["Content-type"] = "text/javascript";
                return fs::ramfs::filesystem.read_file_autocache(js_file);
            }

            if(!strcmp(incoming.path.c_str(), "/inet"))
            {
                outgoing.headers["Content-type"] = "image/png";
                return fs::ramfs::filesystem.read_file_autocache(inet_png);
            }

            if(!strcmp(incoming.path.c_str(), "/server"))
            {
                outgoing.headers["Content-type"] = "image/png";
                return fs::ramfs::filesystem.read_file_autocache(net_png);
            }

            if(!strcmp(incoming.path.c_str(), "/inet_check"))
            {
                return "Y";
            }

            if(!strcmp(incoming.path.c_str(), "/inject_frm"))
            {
                return fs::ramfs::filesystem.read_file_autocache(inject_form);
            }

            if(!strcmp(incoming.path.c_str(), "/monitor_frm"))
            {
                return fs::ramfs::filesystem.read_file_autocache(monitor_form);
            }

            if(!strcmp(incoming.path.c_str(), "/api.js"))
            {
                outgoing.headers["Content-type"] = "text/javascript";
                return fs::ramfs::filesystem.read_file_autocache(api_file);
            }

            //If nothing is left to do, error handler!
            outgoing.http_return = 404;
            //return fs::ramfs::filesystem.read_file("input.html");
            return "";
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
            mtx.try_lock_for(std::chrono::milliseconds(SERVER_MUTEX_TIMEOUT));
            //Process the request
            std::string x = process_request(incoming, outgoing);
            //Unlock the mutex so we do not have our server freezing!
            mtx.unlock();
#ifdef DETAILED_DEBUG
#ifdef DEBUG_WEBINF
            //Display some output info
            std::cout << "Content Type: " << outgoing.headers["Content-type"] << std::endl;
            std::cout << "Return Code: " << outgoing.http_return << std::endl;
#endif
#endif

#ifdef ENABLE_CORS
            outgoing.headers["Access-Control-Allow-Origin"] = "*";
#endif
            //Return the serve data!
            return x + " ";
        }

        //This function allows you to put a value into the table without using the network. This yields a much lower latency!
        void put(std::string key, std::string value)
        {
            //Lock the resources
            mtx.try_lock_for(std::chrono::milliseconds(SERVER_MUTEX_TIMEOUT));
            //Assign the value to the key in the map
            database[key] = value;
            //Unlock the resources
            mtx.unlock();
        }

        //Just like above. This function, however, gets an assigned value
        std::string get(std::string key)
        {
            mtx.try_lock_for(std::chrono::milliseconds(SERVER_MUTEX_TIMEOUT));
            std::string x = database[key];
            mtx.unlock();
            return x;
        }

        //This sends a copy of the entire table!
        std::unordered_map<std::string, std::string> getTable()
        {
            mtx.try_lock_for(std::chrono::milliseconds(SERVER_MUTEX_TIMEOUT));
            std::unordered_map<std::string, std::string> x = database;
            mtx.unlock();
            return x;
        }

        void clearTable()
        {
            mtx.try_lock_for(std::chrono::milliseconds(SERVER_MUTEX_TIMEOUT));
            database.clear();
            mtx.unlock();
        }
    };
}

namespace glob
{
    //The DevServer!!!
    static srv::dev_server srv;
}
