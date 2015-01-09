#!/usr/bin/python 
#coding=utf-8
'''这是个简单的备份程序  

设计思路：  
    1、需要备份的文件和目录由一个列表指定  
    2、指定一个备份的主目录:之后所有的备份都放在此目录中,即备份主目录  
    3、文件备份成一个zip或者.tar.gz、.tar.bz2  
    4、存档的名称是当前的日期和时间,外加提示信息  
    5、使用Linux内部的压缩命令zip或者tar 

最终效果：  
    指定的需要备份的文件在每次备份完成后会被保存在：备份主目录/day/  
    备份文件命名为comment_time.zip
'''

import os 
import time 

# 备份资源列表
bak_list = ['/home/mwumli/code_temp', '/home/mwumli/Desktop']  

# 备份主目录  
bak_main = '/home/mwumli/bak'

if not os.path.exists(bak_main):
    os.mkdir(bak_main)


# 备份子目录
today = bak_main+os.sep+time.strftime('%Y%m%d')

if not os.path.exists(today):
    os.mkdir(today) 

# 构造备份存放文件
now = time.strftime('%H%M%S')
comment = raw_input('Enter a comment >>> ')

if len(comment) != 0:
    now = comment + '_@_' + now

now += '.tar.gz'

# 构造备份命令  
target = today + os.sep + now
#zip_cmd = 'zip -qvr %s %s' % (target, ' '.join(bak_list))
# change zip to tar  
tar_cmd = 'tar -cvzf %s %s -X ~/excludes.txt' \
                % (target, ' '.join(bak_list))

if os.system(tar_cmd) == 0:
    print 'Successful bakup to', target
else:
    print 'Backup FAILED'


