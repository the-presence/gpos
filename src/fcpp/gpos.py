#!/usr/bin/python

class Processor(object):

    def __init__(self, contval):
        self.setcontext(contval)
        self.running = True

    def setcontext(self, cval):
        self.context = cval
        self.source = self.context + '.cpp'
        self.header = self.context + '.h'

    def createclass(self):
        class_name = raw_input('\tClass Name : ')
        self.setcontext(class_name)
        class_namespace = raw_input('\tClass Namespace : ')
        guardstr = class_name.upper() + '_H'
        tfile01 = open(self.header, "w")
        tstr01 = '#ifndef ' + guardstr + '\n#define ' + guardstr + '\n\n'
        tstr01 += 'namespace '+ class_namespace + '\n{\n'
        tstr01 += 'class '+ class_name + '\n{\n'
        tstr01 += '};\n'
        tstr01 += '}\n'
        tstr01 += '#endif /* ' + guardstr + ' */\n\n'
        tfile01.write(tstr01)
        tfile01.close()

        
    def command(self):
        for case in switch(self.task):
            if case('quit'):
                self.running = False
                break
            if case('class'):
                self.createclass()
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
