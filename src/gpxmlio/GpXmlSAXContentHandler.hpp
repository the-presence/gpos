#ifndef GPXMLSAXCONTENTHANDLER_H
#define GPXMLSAXCONTENTHANDLER_H

#include <xercesc/sax2/Attributes.hpp>
#include <xercesc/sax2/DefaultHandler.hpp>

#include <string>

XERCES_CPP_NAMESPACE_USE

namespace gpos
{
  using namespace std;

  class GpXmlSAXContentHandler : public DefaultHandler {
  public:
    GpXmlSAXContentHandler();
    void startElement(const   XMLCh* const    uri,
                      const   XMLCh* const    localname,
                      const   XMLCh* const    qname,
                      const   Attributes&     attrs);

    void endElement(const   XMLCh* const    uri,
                    const   XMLCh* const    localname,
                    const   XMLCh* const    qname);

    void fatalError(const SAXParseException&);

    void characters(const XMLCh* const chars,
                    const XMLSize_t len);
  private:
    // bool isEmpty(const string& str);
  };
}

#endif
