#include <gpxmlio/GpXmlReader.hpp>
#include <gpxmlio/GpCodeModel.hpp>
#include <string>

using namespace std;
using namespace gpos;

int main(int argc, char* argv[])
{
  GpXmlReader reader;
  GpCodeModel *model = NULL;
  string fname("testdata/parserTest.xml");

  reader.ReadFile(fname, model);

  return 0;
}
