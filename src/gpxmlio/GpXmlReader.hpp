#ifndef GPXMLREADER_H
#define GPXMLREADER_H
#ifndef GPCODEMODEL_H
#include <gpxmlio/GpCodeModel.hpp>
#endif

#include <string>
namespace gpos
{
  using namespace std;
  
  class GpXmlReader
  {
  public:
    GpXmlReader();
    ~GpXmlReader();
    int ReadFile(string& filename, GpCodeModel* model);
  private:
    
  };
}

#endif /* GPXMLREADER_H */
