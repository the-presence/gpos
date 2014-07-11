#ifndef GPCLASS_H
#define GPCLASS_H
#include <gpxmlio/GpMethod.hpp>
#include <gpxmlio/GpMember.hpp>
// #include <debug.hpp>
#include <ostream>
#include <string>
#include <vector>
namespace gpos
{
  using namespace std;

  class GpClass
  {
  public:
    GpClass();
    void Name(const string&);
    const string& Name();
    void Namespace(const string&);
    const string& Namespace();

    void AddDeclDepend(const string&);
    void AddDeclUsingDepend(const string&);
    void AddImplDepend(const string&);
    void AddImplUsingDepend(const string&);
    void AddMethod(GpMethod*);
    void AddMember(GpMember*);

    void WriteAsXml();

    // friend ostream& operator<< (ostream& , const GpClass&);

  private:
    string mName;
    string mNSpace;
    vector<string> mDeclarationDependencies;
    vector<string> mDeclarationUsingDependencies;
    vector<string> mImplementationDependencies;
    vector<string> mImplementationUsingDependencies;
    vector<GpMethod*> mInterface;
    vector<GpMember*> mState;
  };
}
#endif
