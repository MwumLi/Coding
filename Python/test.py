#!/usr/bin/python2.7
#coding=utf-8

def show_1star(*args):
    print args
    print type(args)

show_1star(1,2,3)

def show_2stars(**args):
    a = args.items()
    print a
    for i,v in a:
        print i,v

show_2stars(a="ab", b="bc", c="cd")

a = (1, 3,'3')

print 2 in a
