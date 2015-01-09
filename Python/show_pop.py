#coding=utf-8
#此例展示了面向过程的编程思想  
#计算一个圆的面积  
print "Process-Oriented Prohramming"
import math
def circle_area(r):
    area = math.pi*r*r
    return area

rl = [1, 2, 3, 4, 5]
rl.append(6)
for r in rl:
    s = circle_area(r)
    print s


