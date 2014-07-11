#ifndef GPXMLWRITER_H
#define GPXMLWRITER_H
#ifndef GPCODEMODEL_H
#include <gpxmlio/GpCodeModel.hpp>
#endif

#include <debug.hpp>
namespace gpos
{
  class GpXmlWriter
  {
  public:
    GpXmlWriter();
    ~GpXmlWriter();

    void WriteToFile(GpCodeModel* model);
  private:
  };
}

#endif /* GPXMLWRITER_H */
