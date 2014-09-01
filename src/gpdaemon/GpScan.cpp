#include <gpdaemon/GpScan.hpp>
#include <dirent.h>
#include <iostream>
#include <string>
#include <string.h>

using namespace std;
namespace gpos
{
  GpScan::GpScan(const string& direc)
  {
    DIR *d = NULL;
    struct dirent *dir = NULL;

    d = opendir(direc.c_str());
    if(d)
      {
        while((dir = readdir(d)) != NULL)
          {
            if((dir->d_type == DT_DIR) &&
               strcmp(dir->d_name,".") &&
               strcmp(dir->d_name,".."))
              {
                string tstring = direc;
                string dstring = string(dir->d_name);
                tstring += "/";
                tstring += dstring;
                dirnames.push_back(tstring);
              }
          }
      }
    closedir(d);
    for(size_t i = 0; i < dirnames.size(); i++)
      cout << dirnames[i] << endl;
  }

}
