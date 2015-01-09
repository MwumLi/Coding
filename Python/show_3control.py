#coding=utf-8
#Three control structure: order 、choose 、loop  
'''
python的控制语句:
if ... else ..
if ... elif ... else 
'''
a = "str"

# if ... else ...
if a == "str": 
    print a
else:
    print a 

a = "int"

# if ... elif ... else ...
if a == "str":
    print "is str"
elif a == "int":
    print "is int"
else:
    print "nothing"

'''
python的循环结构:
while ...: ...
for ... in range()/list/tuple
'''

i = 0
a = ""
# while
print "while i < 10:"
while i < 10:
    a +=str(i)+","
    i+=1
print a
print ""

#for a in range/list/tuple
a=""
print "for a in range(0, 10):"
for i in range(0, 10):
    a +=str(i)+","
print a
print ""

a = ["type", 33, 3.14]
print "for a in list:"
for i in a:
    print i

