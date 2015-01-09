#coding=utf-8
#展示函数式编程的基本概念,使用map()

print "Functional Programming"
def multiply(x,y):
    print str(x)+"*"+str(y)
    return x*y

x = [1, 2, 3, 4, 5]
print x
print reduce(multiply, x)
print ""
print reduce(multiply, x, 2)
