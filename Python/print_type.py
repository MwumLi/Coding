#coding=utf-8
'''
This is a example, which is used to show `type()`'s usage and all typea in python
'''

a = 2 #创建一个int型的变量  
print "a = 2 : "+str(type(a))

a = 324234234234324234234  #创建一个long型的变量  
print "a = 324234234234324234234 : "+str(type(a))

a = 3.14 #创建一个float型的变量  
print "a = 3.14 : "+str(type(a))

a = complex(2, -3) #创建一个compex型的变量  
print "a = complex(2, -3) : "+str(type(a))

a = True
print "a =True : "+str(type(a))
def hello():
    print "show function type"

print "hello() : " +str(type(hello))

class Dog:
    def bake():
        print "bake"

print "class Dog : "+str(type(Dog)) 

a = Dog()
print "a = Dog() : "+str(type(a))
print "a.bake() : "+str(type(a.bake))


