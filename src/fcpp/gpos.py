#!/usr/bin/python

from subprocess import call
import string
import os.path

class CPPClass(object):

    def __init__(self):
        return

    def set_name(self, val):
        self.name = val

    def set_namespace(self, val):
        self.namespace = val

class CPPMember(object):

    def __init__(self):
        self.accessors = False

    def set_name(self, val):
        self.name = val

    def set_type(self, val):
        self.mtype = val

    def set_accessors(self, val):
        self.accessors = val

class CPPMethod(object):

    def __init__(self):
        return

    def set_name(self, val):
        self.name = val

    def set_rtype(self, val):
        self.rtype = val

    def set_params(self, val):
        self.params = val

    def set_access(self, val):
        self.access = val

class CPPFactory(object):

    def __init__(self):
        self.valid = False

    def do_format(self, target):
        call(["astyle",
              "--quiet",
              "--indent-namespaces",
              "--indent-col1-comments",
              "--pad-header",
              "--pad-oper",
              "--max-code-length=80",
              "--break-after-logical",
              target])

    def is_valid(self):
        return self.valid

    def set_context(self, cval):
        self.valid = False
        self.context = cval
        self.guardstr = self.context.upper() + '_H'
        self.source = self.context + '.cpp'
        self.header = self.context + '.h'
        if ((os.path.isfile(self.header)) and (os.path.isfile(self.source))):
            self.valid = True

    def create_class_header_string(self, namespace):
        tstr01 = '#ifndef ' + self.guardstr + '\n#define ' + self.guardstr + '\n\n'
        tstr01 += 'namespace '+ namespace + '\n{\n\n'
        tstr01 += 'class '+ self.context + '\n{\n'
        tstr01 += 'public:\n/* PUBLIC_METHODS */\n'
        tstr01 += 'private:\n/* PRIVATE_METHODS */\n'
        tstr01 += 'private:\n/* PRIVATE_MEMBERS */\n'
        tstr01 += 'public:\n/* PUBLIC_MEMBERS */\n'
        tstr01 += 'protected:\n/* PROTECTED_METHODS */'
        tstr01 += 'protected:\n/* PROTECTED_MEMBERS */\n'
        tstr01 += '};\n'
        tstr01 += '\n}\n'
        tstr01 += '#endif /* ' + self.guardstr + ' */\n\n'
        return tstr01

    def create_class_source_string(self, namespace):
        tstr02 = '#ifndef ' + self.guardstr + '\n#include <' + self.header + '>\n'
        tstr02 += '#endif /* ' + self.guardstr + ' */\n\n'
        tstr02 += 'namespace '+ namespace + '\n{\n\n'
        tstr02 += '/* IMPL_START */\n/* IMPL_END */\n'
        tstr02 += '\n}\n'
        return tstr02

    def create_class(self, klass):
        tfile01 = open(self.header, "w")
        tfile01.write(self.create_class_header_string(klass.namespace))
        tfile01.close()
        self.do_format(self.header)
        tfile02 = open(self.source, "w")
        tfile02.write(self.create_class_source_string(klass.namespace))
        tfile02.close()
        self.do_format(self.source)
        self.create_method_man('public', '', klass.name, '')
        self.create_method_man('private', '', klass.name, 'const '+ klass.name + '& value', False)
        self.create_method_man('private', klass.name + '&', 'operator=', 'const '+ klass.name + '& value', False)
        self.create_method_man('private', '', '~'+ klass.name, '', False)

    def create_method_decl_string(self, dmethod):
        dstring = dmethod.rtype + ' '
        dstring += dmethod.name +'(' + dmethod.params + ');\n'
        return dstring

    def create_method_impl_string(self, dmethod):
        dstring = dmethod.rtype + ' '
        dstring += self.context + '::'
        dstring += dmethod.name +'(' + dmethod.params + ')\n'
        dstring += '{\n\n}\n\n'
        return dstring

    def create_method_man(self, access, rtype, name, params, impltoo=True):
        methard = CPPMethod()
        methard.set_rtype(rtype)
        methard.set_name(name)
        methard.set_params(params)
        methard.set_access(access)
        decl_str = self.create_method_decl_string(methard)
        self.inject_decl(methard.access, 'method', decl_str)
        if(impltoo==True):
            impl_str = self.create_method_impl_string(methard)
            self.inject_impl(impl_str)

    def create_method(self, methard, impltoo=True):
        decl_str = self.create_method_decl_string(methard)
        self.inject_decl(methard.access, 'method', decl_str)
        if(impltoo==True):
            impl_str = self.create_method_impl_string(methard)
            self.inject_impl(impl_str)

    def create_member_decl_string(self, dtype, dname):
        dstring = ' ' + dtype + ' m_' + dname.lower() + ';\n'
        return dstring

    def create_member(self, mmbr):
        member_string = self.create_member_decl_string(mmbr.mtype, mmbr.name)
        self.inject_decl('private', 'member', member_string)
        if (mmbr.accessors == True):
            accessor_name = mmbr.name.capitalize()
            self.create_method_man('public', mmbr.mtype, accessor_name, '')
            self.create_method_man('public', 'void', accessor_name, mmbr.mtype + ' value')

    def inject_decl(self, access, decltype, dstring):
        decl_match = access.upper() + '_' + decltype.upper() + 'S'
        rfile = open(self.header, "r")
        wfstr = self.header + ".new"
        wfile = open(wfstr, "w")
        for line in rfile:
            wfile.write(line)
            if (line.find(decl_match) != -1):
                wfile.write(dstring)
        rfile.close()
        wfile.close()
        call(["rm", self.header])
        call(["mv", wfstr, self.header])
        self.do_format(self.header)

    def inject_impl(self, istring):
        rfile = open(self.source, "r")
        wfstr = self.source + ".new"
        wfile = open(wfstr, "w")
        for line in rfile:
            if (line.find('IMPL_END') != -1):
                wfile.write(istring)
            wfile.write(line)
        rfile.close()
        wfile.close()
        call(["rm", self.source])
        call(["mv", wfstr, self.source])
        self.do_format(self.source)

class Processor(object):

    def __init__(self, contval):
        self.set_context(contval)
        self.running = True

    def command(self):
        """Command input processor"""
        for case in switch(self.task):
            if case('quit'):
                self.running = False
                break
            if case('class'):
                self.make_class()
                break
            if case('context'):
                self.make_context()
                break
            if case('member'):
                self.make_member()
                break
            if case('method'):
                self.make_method()
                break
            if case():
                print "Unknown command"

    def make_class(self):
        """Dialogue-driven interface to make a new class in the class factory"""
        klass = CPPClass()
        klass.set_name(raw_input('\tClass Name : '))
        self.set_context(klass.name)
        klass.set_namespace(raw_input('\tClass Namespace : '))
        self.factory.create_class(klass)

    def make_context(self):
        new_context = raw_input('\tClass Name : ')
        self.set_context(new_context)
        if (self.factory.is_valid() == False):
            self.make_class()

    def make_member(self):
        """Dialogue-driven interface to make members and accessors in the class factory"""
        if(self.context == "undefined"):
            return
        memba = CPPMember()
        memba.set_type(raw_input('\tMember Type : '))
        member_name_in = raw_input('\tMember Name : ')
        memba.set_name(member_name_in.lower())
        val = raw_input('\tPublic Accessors (y/n)? : ')
        if (val == 'y') or (val == 'Y'):
            memba.set_accessors(True)
        self.factory.create_member(memba)

    def make_method(self):
        """Dialogue-driven interface to make methods in the class factory"""
        if(self.context == "undefined"):
            return
        method = CPPMethod()
        method.set_rtype(raw_input('\tMethod Return Type : '))
        method.set_name(raw_input('\tMethod Name : '))
        method.set_params(raw_input('\tMethod Parameter List : '))
        method.set_access(raw_input('\tMethod Access : '))
        self.factory.create_method(method)

    def run(self):
        """The command line processor is driven from here"""
        while self.running:
            prompt = self.context + ' : '
            self.task = raw_input(prompt)
            self.command()

    def set_context(self, cval):
        """The class factory context is set here"""
        self.context = cval
        self.factory = CPPFactory()
        self.factory.set_context(cval)

class switch(object):

    def __init__(self, value):
        self.value = value
        self.fall = False

    def __iter__(self):
        """Return the match method once, then stop"""
        yield self.match
        raise StopIteration

    def match(self, *args):
        """Indicate whether or not to enter a case suite"""
        if self.fall or not args:
            return True
        elif self.value in args:
            self.fall = True
            return True
        else:
            return False
