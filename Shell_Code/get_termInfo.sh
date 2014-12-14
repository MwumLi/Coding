#!/bin/bash 
# 获取终端的信息  
# 工具:tput and stty  

# 获取终端行数和列数
tput cols		#列数  
tput lines		#列数  

# 打印终端名字  
tput longname && echo 

# 移动光标到(100, 102)
tput cup 100 102

# 设置背景色和前景色  
# tput setb num -- 设置背景色
# tput setf num -- 设置前景色  
# num的值:0---7

# 设置粗体  
tput bold

# 设置下划线 
tput smul
echo "设置下划线起止"
tput rmul

# 删除光标到行尾所有内容  
tpur ed

# 输入密码  

echo -e "Enter your password:"
stty -echo	#禁止将输出发送到终端
read passwd
stty echo	#允许发送输出到终端
echo
echo $passwd

