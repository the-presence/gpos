#!/usr/bin/python

import sys
#from gpos import Processor, switch

def main(argv):
    #proc = Processor(argv)
    #proc.run()
    return

if __name__ == '__main__':
    if len(sys.argv) > 1:
        main(sys.argv[1:])
    else:
        main("undefined")
