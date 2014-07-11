#ifndef GPXMLREADER_H
#include <gpxmlio/GpXmlReader.hpp>
#endif
#ifndef GPXMLSAXCONTENTHANDLER_H
#include <gpxmlio/GpXmlSAXContentHandler.hpp>
#endif
#include <debug.hpp>

#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/sax2/SAX2XMLReader.hpp>
#include <xercesc/sax2/XMLReaderFactory.hpp>
#include <xercesc/util/XMLString.hpp>
#include <stdexcept>
#include <iostream>

XERCES_CPP_NAMESPACE_USE

  namespace gpos
{
  using namespace std;

  GpXmlReader::GpXmlReader()
  {
    DEBOUT("GpXmlReader::GpXmlReader()");
    try
    {
      XMLPlatformUtils::Initialize();
    }
    catch (const XMLException& toCatch)
    {
      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Error during initialization! :\n";
      cout << "Exception message is: \n"
        << message << "\n";
      XMLString::release(&message);
      exit(1);
    }
  }

  GpXmlReader::~GpXmlReader()
  {
    DEBOUT("GpXmlReader::~GpXmlReader()");
    XMLPlatformUtils::Terminate();
  }

  int GpXmlReader::ReadFile(string& filename, GpCodeModel* model)
  {
    DEBOUT("GpXmlReader::ReadFile()");
    SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();
    parser->setFeature(XMLUni::fgSAX2CoreValidation, true);
    parser->setFeature(XMLUni::fgSAX2CoreNameSpaces, true);   // optional

    if(!model)
    {
      throw std::invalid_argument("Null pointer passed to  GpXmlReader::ReadFile()");
    }

    GpXmlSAXContentHandler* handler = new GpXmlSAXContentHandler(model);
    parser->setContentHandler(handler);
    parser->setErrorHandler(handler);

    try
    {
      parser->parse(filename.c_str());
    }
    catch (const XMLException& toCatch)
    {
      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Exception message is: \n"
        << message << "\n";
      XMLString::release(&message);
      return -1;
    }
    catch (const SAXParseException& toCatch)
    {
      char* message = XMLString::transcode(toCatch.getMessage());
      cout << "Exception message is: \n"
        << message << "\n";
      XMLString::release(&message);
      return -1;
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

    delete parser;
    delete handler;
    return 0;
  }
}
