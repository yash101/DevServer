#pragma once
#include "preprocessor.hxx"

namespace srv
{
    //This generates the monitor table we see on the web interface!
    inline std::string montbl(std::unordered_map<std::string, std::string> map)
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
}
