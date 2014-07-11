#include <gpxmlio/GpXmlReader.hpp>
#include <gpxmlio/GpXmlWriter.hpp>
#include <gpxmlio/GpCodeModel.hpp>

#include <fstream>
#include <debug.hpp>
#include <stdexcept>
#include <string>
#include <iostream>

using namespace std;
using namespace gpos;

int main(int argc, char* argv[])
{
  try
  {
    GpXmlReader reader;
    GpCodeModel model;

    string infname("testdata/parserTest.xml");

    reader.ReadFile(infname, &model);
    cout <<"\n";

    string outfname("testdata/writerTest.xml");
    GpXmlWriter writer;
    writer.WriteToFile(&model);

    // cout << model << "\n";;
  }
  catch (const std::exception& except)
  {
    cout << except.what() << '\n';
    return -1;
  }
  catch (...)
  {
    cout << "Unexpected Exception \n" ;
    return -1;
  }

  return 0;
}
