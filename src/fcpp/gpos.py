#!/usr/bin/python

from subprocess import call

class Processor(object):

    def __init__(self, contval):
        self.setcontext(contval)
        self.running = True

    def doformat(self):
        call(["astyle", "--quiet", self.header])
        call(["astyle", "--quiet", self.source])

    def setcontext(self, cval):
        self.context = cval
        self.guardstr = self.context.upper() + '_H'
        self.source = self.context + '.cpp'
        self.header = self.context + '.h'

    def createbasicheader(self, namespace):
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

    def createbasicsource(self, namespace):
        tstr02 = '#ifndef ' + self.guardstr + '\n#include <' + self.header + '>\n'
        tstr02 += '#endif /* ' + self.guardstr + ' */\n\n'
        tstr02 += 'namespace '+ namespace + '\n{\n\n'
        tstr02 += '/* IMPL_START */\n/* IMPL_END */\n'
        tstr02 += '\n}\n'
        return tstr02

    def createclass(self):
        class_name = raw_input('\tClass Name : ')
        self.setcontext(class_name)
        class_namespace = raw_input('\tClass Namespace : ')
        tfile01 = open(self.header, "w")
        tfile01.write(self.createbasicheader(class_namespace))
        tfile01.close()
        tfile02 = open(self.source, "w")
        tfile02.write(self.createbasicsource(class_namespace))
        tfile02.close()

    def command(self):
        for case in switch(self.task):
            if case('quit'):
                self.running = False
                break
            if case('class'):
                self.createclass()
                self.doformat()
                break
            if case():
                print "Unknown command"

    def run(self):
        while self.running:
            prompt = self.context + ' : '
            self.task = raw_input(prompt)
            self.command()

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
