#ifndef GPXMLWRITER_H
#define GPXMLWRITER_H
#ifndef GPCODEMODEL_H
#include <gpxmlio/GpCodeModel.hpp>
#endif
#include <string>
namespace gpos
{
using namespace std;

  class GpXmlWriter
  {
  public:
    GpXmlWriter();
    ~GpXmlWriter();

    int WriteFile(GpCodeModel* model, string& filename);
  private:
  };
}

#endif /* GPXMLWRITER_H */
