#!/usr/bin/python
#coding=utf-8
'''一个file读写的demo.
'''
import time
source = file("/etc/passwd", "r")

dest = file("passwd", "w")

try:
    while True:
        line = source.readline()
        if len(line) == 0:
            break
        dest.write(line)
        time.sleep(2)       
        print line,
finally:
    source.close()
    dest.close()
    print "close file"
