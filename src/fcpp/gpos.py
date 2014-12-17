#!/usr/bin/python

from subprocess import call

class Processor(object):

    def __init__(self, contval):
        self.set_context(contval)
        self.running = True

    def command(self):
        for case in switch(self.task):
            if case('quit'):
                self.running = False
                break
            if case('class'):
                self.make_class()
                self.do_format()
                break
            if case():
                print "Unknown command"

    def create_class_header_string(self, namespace):
        tstr01 = '#ifndef ' + self.guardstr + '\n#define ' + self.guardstr + '\n\n'
        tstr01 += 'namespace '+ namespace + '\n{\n\n'
        tstr01 += 'class '+ self.context + '\n{\n'
        tstr01 += 'public:\n/* PUBLIC_METHODS */\n/* PUBLIC_MEMBERS */\n'
        tstr01 += 'protected:\n/* PROTECTED_METHODS */\n/* PROTECTED_MEMBERS */\n'
        tstr01 += 'private:\n/* PRIVATE_METHODS */\n/* PRIVATE_MEMBERS */\n'
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

    def create_method_decl_string(self):
        return

    def create_method_impl_string(self):
        return

    def create_member_decl_string(self, dtype, dname):
        dstring = ' ' + dtype + 'm_' + dname.lower() + ';\n'
        return dstring

    def do_format(self):
        call(["astyle", "--quiet", self.header])
        call(["astyle", "--quiet", self.source])

    def inject_decl(self, access, decltype, dstring):
        decl_match = access.upper() + '_' + decltype.upper() + 'S'
        rfile = open(self.source, "r")
        wfstr = self.source + ".new"
        wfile = open(wfstr, "w")
        for line in rfile:
            wfile.write(line)
            if (line.find(decl_match) != -1):
                wfile.write(dstring)
        rfile.close()
        wfile.close()
        call(["rm", self.source])
        call(["mv", wfstr, self.source])

    def inject_impl(self, istring):
        rfile = open(self.header, "r")
        wfstr = self.header + ".new"
        wfile = open(wfstr, "w")
        for line in rfile:
            if (line.find('IMPL_END') != -1):
                wfile.write(istring)
            wfile.write(line)
        rfile.close()
        wfile.close()
        call(["rm", self.header])
        call(["mv", wfstr, self.header])

    def make_class(self):
        class_name = raw_input('\tClass Name : ')
        self.set_context(class_name)
        class_namespace = raw_input('\tClass Namespace : ')
        tfile01 = open(self.header, "w")
        tfile01.write(self.create_class_header_string(class_namespace))
        tfile01.close()
        tfile02 = open(self.source, "w")
        tfile02.write(self.create_class_source_string(class_namespace))
        tfile02.close()

    def make_member(self):
        member_type = raw_input('\tMember Type')
        member_name = raw_input('\tMember Name')
        member_accessors = raw_input('\tPublic Accessors (y/n)?')
        member_string = create_member_decl_string(member_type, member_name)
        return

    def make_method(self):
        return

    def run(self):
        while self.running:
            prompt = self.context + ' : '
            self.task = raw_input(prompt)
            self.command()

    def set_context(self, cval):
        self.context = cval
        self.guardstr = self.context.upper() + '_H'
        self.source = self.context + '.cpp'
        self.header = self.context + '.h'

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
