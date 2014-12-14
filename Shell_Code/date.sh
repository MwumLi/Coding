#!/bin/bash 
# 获取、设置日期和延时  

# 读取日期，当然不仅仅是日期,还有准确到秒的时间
date  

# 纪元时 
# 在类UNIX系统中，日期会被存储为一个整数，其大小被记为自1970年1月1日至今所流逝的秒数
# 这种计时方式被称为纪元时或UNIX时间
date +%s 

# 将日期串转化成纪元时  
# 注意日期串的格式
# --date提供日期串作为输入
date --date "Tue Sep 23 19:52:39 CST 2014" +%s
# 获取星期几  
date --date "Sep 23 2014" +%A:w

# 日期格式字符串列表  
# 星期:			%a(Sat) %A(Saturday)
# 月:			%b(Nov) %B(November)
# 日:			%d(31)
# 固定格式日期: %D(mm/dd/yy)
# 年:			%y(14) %Y(2014)
# 小时:			%I(08) %H(20)	下午八点  
# 分钟:			%M(01)
# 秒数:			%S(01)
# 纳秒:			%N(012008434)
# UNIX纪元时:	%s(1411473749)

# 设置日期和时间  
# date -s "格式化日期字符串"
# 修改日期时间需要root权限  

# 计算一组命令执行所需时间  

start=$(date +%s)
ls -R / 1>./date_out 2>./date_err
end=$(date +%s)
time_gap=$((end-start))
echo "ls的执行时间${time_gap}"
