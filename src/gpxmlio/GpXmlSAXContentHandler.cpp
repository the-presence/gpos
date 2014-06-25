#ifndef GPXMLSAXCONTENTHANDLER_H
#include <gpxmlio/GpXmlSAXContentHandler.hpp>
#endif

#include <string>
#include <iostream>
#include <ctype.h>

XERCES_CPP_NAMESPACE_USE

  namespace gpos
{
  using namespace std;

  GpXmlSAXContentHandler::GpXmlSAXContentHandler(GpCodeModel* val)
  {
    model = val;
  }

  void GpXmlSAXContentHandler::startElement(const   XMLCh* const    uri,
                                            const   XMLCh* const    localname,
                                            const   XMLCh* const    qname,
                                            const   Attributes&     attrs)
  {
    string elementName(XMLString::transcode(localname));
    //statmach = FoundElement(elementName, attrs);
    // XMLSize_t numAtts = attrs.getLength();
    // if(numAtts > 0)
    // {
    //   for (XMLSize_t i = 0; i < numAtts; i++)
    //   {
    //     string Qname(XMLString::transcode(attrs.getQName(i)));
    //     string URI(XMLString::transcode(attrs.getURI(i)));
    //     string local(XMLString::transcode(attrs.getLocalName(i)));
    //     string type(XMLString::transcode(attrs.getType(i)));
    //     string value(XMLString::transcode(attrs.getValue(i)));
    //     cout << "\t" << i <<", "<<Qname<<", "<<URI<<", "<<local<<", "<<type<<", "<<value<<"\n";
    //   }
    // }

  }

  void GpXmlSAXContentHandler::endElement(const   XMLCh* const    uri,
                                          const   XMLCh* const    localname,
                                          const   XMLCh* const    qname)
  {
    string elementName(XMLString::transcode(localname));
    //statmach = ClosedElement(elementName);
  }

  void GpXmlSAXContentHandler::characters(const XMLCh* const chars,
                                          const XMLSize_t len)
  {
    string str(XMLString::transcode(chars));
    size_t strBegin = str.find_first_not_of(" \n\r\t");
    if (strBegin == std::string::npos)
    {
      return; // no content
    }
    statmach.ProcessChars(str);
  }

  void GpXmlSAXContentHandler::fatalError(const SAXParseException& exception)
  {
    char* message = XMLString::transcode(exception.getMessage());
    cout << "Fatal Error: " << message
      << " at line: " << exception.getLineNumber()
      << endl;
    XMLString::release(&message);
  }
}
