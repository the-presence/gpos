#include <vector>
#include <string>
//#include <gpdaemon/GpBuild.hpp>

#include <debug.hpp>


namespace gpos
{
  using namespace std;

  class GpScan
  {
  public:
    GpScan(const string&);
  private:
    vector<string> dirnames;
  };

}
