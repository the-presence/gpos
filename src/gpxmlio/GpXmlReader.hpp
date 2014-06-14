#ifndef GPXMLREADER_H
#define GPXMLREADER_H

#ifndef GPCODEMODEL_H
#include <gpxmlio/GpCodeModel.hpp>
#endif

#include <string>

using namespace std;

namespace gpos
{
  class GpXmlReader
  {
  public:
    GpXmlReader();
    ~GpXmlReader();

    GpCodeModel* ReadFile(string& filename);
  private:
  };
};

#endif /* GPXMLREADER_H */
