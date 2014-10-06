#pragma once
#include "preprocessor.hxx"

namespace prog
{
    //This function reads the file cache list into a vector of strings, for easy processing
    std::vector<std::string> load_file_list()
    {
        //This is the vector we will return
        std::vector<std::string> file_list;
        //Open the filestream for the file listing
        std::ifstream fin(glob::file_list.c_str());
        //Check to make sure the file is properly opened
        if(fin.is_open())
        {
            //Create a stringstream. Much easier for manipulating strings than fstream ;)
            std::stringstream sstream;
            //Put the fstream contents into sstream
            sstream << fin.rdbuf();
            //This is the buffer for the next step
            std::string file;
            //Iterate through getting data, one line at a time
            while(sstream >> file)
            {
                //Add it into the vector
                file_list.push_back(file);
#ifdef DETAILED_DEBUG
                std::cout << "Added " << file << " to the filecache list" << std::endl;
#endif
            }
            fin.close();
        }
        return file_list;
    }

    //This generates the file cache so loads are speedy :D
    void gen_file_cache()
    {
        //Load the file listing
        glob::preload_db = load_file_list();
        //Push the files into the RAMCache
        fs::ramfs::filesystem.cache_list(glob::preload_db);
    }

    void load()
	{

#ifdef USE_OPENMP
		std::cout << "OpenMP Thread Count: " << omp_get_num_threads() << std::endl;
#endif

        if(glob::use_hardware_concurrency_count_openmp)
        {
#ifdef DETAILED_DEBUG
            std::cout << "Config Set: Use Hardware Concurrency Max" << std::endl;
#endif
            glob::openmp_thread_count = std::thread::hardware_concurrency();
        }

#ifdef DETAILED_DEBUG
		std::cout << "Setting OpenMP thread count to: " << glob::openmp_thread_count << std::endl;
#endif
#ifdef USE_OPENMP
		omp_set_num_threads(glob::openmp_thread_count);
#endif
#ifdef DETAILED_DEBUG
#ifdef USE_OPENMP
        std::cout << "OpenMP Thread Count: " << omp_get_num_threads() << std::endl;
#else
        std::cout << "OpenMP Disabled!" << std::endl;
#endif
        std::cout << "Generating File Cache!" << std::endl;
        std::cout << "Server port: " << glob::server_port << std::endl;
        std::cout << "Server Access: localhost:" << glob::server_port << std::endl;
#endif

#ifdef PREPOPULATE_RAMFS
        //C++11 Threads are soooooo easy to use! :D. Why not just create the cache in another thread? We can do other initializations while we are waiting!
        std::thread file_list_thread(gen_file_cache);   //is the same as doing gen_file_cache();, but does it in a separate thread! :D
        //Join the thread to prevent problems (program crash)
        file_list_thread.join();
        //Uncomment this and comment the above two functions if you don't like C++11 threading and want to do everything one at a time! :D
        //gen_file_cache();
#endif
	}
}
