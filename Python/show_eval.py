#coding=utf-8
'''
python的动态代码:
精髓:把代码当作数据处理，把数据当作代码执行 
使用eval(),execfile()内建函数和exec语句来把数据当作代码执行  
eval:计算字符串中的表达式
exec:执行字符串中的语句  
execfile:用来执行一个文件
input(prompt) == eval(raw_input(prompt))
'''

def square(x):
    return x*x
l = ['square', '(3)','+','square', '(2)']

code = "".join(l)
print code+" = "+str(eval(code))

code = "print 'hh'\nprint square(3)"
exec code

code = "for i in range(0,10): print i"
c = compile(code,'', "single")
exec c
