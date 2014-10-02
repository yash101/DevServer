#pragma once
#include "preprocessor.hxx"

namespace fs
{
    bool stat_file(std::string file_location)
    {
        //Open the filestream
        std::ifstream fin(file_location.c_str());
        //Check if the filestream is open
        if(fin.is_open())
        {
            //Close the filestream
            fin.close();
            return true;
        }
        else
        {
            return false;
        }
    }

    std::string read_file(std::string file_location)
    {
        //Create and open the filestream
        std::ifstream fin(file_location.c_str());
        //Check to see if the file is open
        if(fin.is_open())
        {
#ifdef DETAILED_DEBUG
            std::cout << "Successfully Read: " << file_location << std::endl;
#endif
            std::string x = dlib::cast_to_string(fin.rdbuf());
            return x;
        }
        else
        {
            //ERROR: Unable to open file! :(
#ifdef DETAILED_DEBUG
            std::cout << "fs::read_file(): Could not open/read the file!" << std::endl;
#endif
            //Return a nullptr
            return nullptr;
        }
    }

    void write_file(std::string file_location, std::string data)
    {
        std::ofstream fout(file_location.c_str());
        if(fout.is_open())
        {
            fout << data;
        }
    }

    void write_file_async(std::string file_location, std::string data)
    {
        std::thread x(write_file, file_location, data);
        x.detach();
    }

    namespace ramfs
    {
        //I like RAMCaches. They are nice and zippy. That's what this is for! :D
        class ramfs
        {
        private:
            //This is the Hash Map (unordered map) that will house all the file data. These are UBER fast! :D
            std::unordered_map<std::string, std::string> map;
            //I will try to do some stuff asynchronously! Probably will need a mutex for safety!
            std::mutex mtx;

            //This function checks to see if a key exists in the map. In this case, a key is a filename
            inline bool stat_map(std::string key)
            {
                std::unordered_map<std::string, std::string>::const_iterator iterator = map.find(key);
                bool x = iterator != map.end();
                return x;
            }

        public:
            bool stat_file(std::string file_location)
            {
                return stat_map(file_location);
            }

            //This is how we read a file into the filecache. Supposedly, this is to be used at boot
            bool preload_file_from_disk(std::string file_location)
            {
                //Check to see if the file exists!
                if(fs::stat_file(file_location))
                {
                    //Read the file from the disk into a buffer
                    std::string file = fs::read_file(file_location);
                    //Save the buffer into the map
                    map[file_location] = file;
                }
                else
                {
#ifdef DETAILED_DEBUG
                    std::cout << "Unable to stat " << file_location << std::endl;
#endif
                    return false;
                }
                return false;
            }

            //This function checks to see if a file exists in the RAMCache. If is does not exist, it will read the
            std::string read_file_autocache(std::string file_location)
            {
#ifndef DISABLE_CACHE
                //Check if the file is in the RAMCache
                if(stat_map(file_location))
                {
                    //Return the file
                    return map[file_location];
                }
                else
                {
                    //Load the file and check for success
                    if(!preload_file_from_disk(file_location))
                    {
#ifdef DETAILED_DEBUG
                        std::cout << "Failed to load " << file_location << " from the disk! :(" << std::endl;
#endif
                    }

                    //Return the file from the RAMCache
                    return map[file_location];
                }
#else
                return fs::read_file(file_location);
#endif
            }

            //This function reads a file from the buffer
            std::string read_file(std::string file_location)
            {
                //Return the value stored under the key
                return map[file_location];
            }

            //This function is quite impressive. It basically iterates through the entire ramfs and reloads the data from the hard disk!
            void rebuild_cache()
            {
                //Create the iterator. You can see how I tried the C++11 "auto" and loved it! :D
                for(auto it = map.begin(); it != map.end(); ++it)
                {
                    //Access the "first" value and store it in a buffer.
                    std::string file_location = it->first;
#ifdef DETAILED_DEBUG
                    std::cout << "Reloading file: " << file_location << std::endl;
#endif
                    //Reload the file and check to make sure it worked perfectly!
                    if(!preload_file_from_disk(file_location))
                    {
#ifdef DETAILED_DEBUG
                        std::cout << "Unable to load file: " << file_location << std::endl;
#endif
                    }
                    else
                    {
#ifdef DETAILED_DEBUG
                        std::cout << "Successfully reloaded: " << file_location << std::endl;
#endif
                    }
                }
            }

            void show_listing()
            {
                for(auto it = map.begin(); it != map.end(); ++it)
                {
                    std::cout << it->first << "->" << it->second << std::endl;
                }
            }

            //This function is for "Why Not?" :D. Basically, it takes in a vector of strings (the file locations). It loads them into the cache!
            void cache_list(std::vector<std::string> file_locations)
            {
                for(unsigned int i = 0; i < file_locations.size(); i++)
                {
                    preload_file_from_disk(file_locations[i]);
#ifdef DETAILED_DEBUG
                    std::cout << "Loaded " << file_locations[i] << " from the disk!" << std::endl;
#endif
                }
            }

            //This function will push the file with the specified location to the hard disk!
            //Note that this is a threaded function! :D. It uses the write_file_async to
            //asynchronously write the data!
            bool push_file(std::string file_location)
            {
                if(stat_file(file_location))
                {
#ifdef DETAILED_DEBUG
                    std::cout << "Pushing " << file_location << " to the hard disk...";
#endif
                    write_file_async(file_location, map[file_location]);
#ifdef DETAILED_DEBUG
                    std::cout << "Success!" << std::endl;
#endif
                    return true;
                }
                else
                {
#ifdef DETAILED_DEBUG
                    std::cout << "Failed to push: " << file_location << " to the hard disk!" << std::endl << "  File does not exist in the cache!" << std::endl;
#endif
                    return false;
                }
            }
        };

        //This is just a ramfs object that is there for general use. This is the one we will use throughout the entire program!
        //The ramfs is a class to allow you (the programmer) to play around with it with utmost freedom!
        static ramfs filesystem;
    }
}
