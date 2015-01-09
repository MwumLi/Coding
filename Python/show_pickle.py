#!/usr/bin/python 
#coding=utf-8
#FileName:use_pickle.py

import cPickle as p #import pickle as p

shoplistfile = 'shoplist.data'

shoplist = ['apple', 'mango', 'carrot']

f = file(shoplistfile, 'w')
p.dump(shoplist, f)
p.dump([1, 2, 3], f)
f.close()
del shoplist 

f = file(shoplistfile)
                                                             
storedlist = p.load(f)

print storedlist

print p.load(f)

