#coding=utf-8
#这是个python版的hello程序  
#pyhton每条语句的结束以换行为标志  
#以缩进划分块  
#使用关键字"def"定义函数，"def 函数名([函数列表]):"
#python有两种注释方式:单行注释和多行注释  
#单行注释使用"#"开始  
#多行注释使用三个单引号"'''"开始和三个单引号"'''"结束把注释包围起来  
'''
这是多行注释
'''
#需要注意的是，python默认使用ASCII码保存，那么你代码中有中文的话，就会报错，即使你的中文在注释中
#所以在脚本第一行生命编码方式，格式如下:"#coding=utf-8"或者"coding="gbk"
def hello():
    print "Hello,python"
    return 2
version="0.1"
hello()

