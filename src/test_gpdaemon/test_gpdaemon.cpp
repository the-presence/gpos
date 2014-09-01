#include <unistd.h>
#include <string>
#include <gpdaemon/GpScan.hpp>

using namespace std;
using namespace gpos;

#include <debug.hpp>

int main(int /* argc */, char** /* argv */)
{
  int ctdown = 10;
  int cntsecs = 2;
  string nano1dir("/home/jeremy/www/builds/nano1");
  string nano2dir("/home/jeremy/www/builds/nano2");


  int cntr = ctdown;
  while(cntr)
    {
      DEBOUT(cntr);

      sleep(cntsecs);
      cntr--;
    }

  GpScan *n1 = new GpScan(nano1dir);

  GpScan *n2 = new GpScan(nano2dir);
  return 0;
}
