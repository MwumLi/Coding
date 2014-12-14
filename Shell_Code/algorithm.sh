#!/bin/bash 

#以下这些是整数运算
no1=3;	
no2=4;

let result=no1+no2
echo "(let result=no1+no2): "$result

let no1++
echo "(no1++): "$no1

let no2++
echo "(no2++): "$no2

let no1+=4
echo "(no1+=4): "$no1

let no2-=20
echo "(no2-=8): "$no2

#可以使用$[],在内部变量名可以带$或者不带
result=$[no1+no2]
echo '(result[$no1+no2]: )'$result

result=$[$no1+result]
echo '(result=$[$no1+result]): '$result

#也可以使用$(())
result=$(($no1+50))
echo $result

#expr用于基本算数操作  

result=`expr 3 + $no1`
echo $result

#以上这些是整数运算  

#使用bc工具进行浮点运算  
#bc首先从给定的文件中读取计算表达式计算
#然后从标准输入中读取计算表达式计算
#故可以使用管道

#自定义小数输出位
echo "scale=3;4/3"|bc 

#进制转换  
#ibase定义输入数据的进制类型  
#obase定义输出数据的进制类型
no1=1110
printf "$no1 = "
echo "ibase=2;$no1" | bc

#last是bc计算最后一个计算结果

#计算平方根  
printf "sqrt(10000) | bc ="
echo "sqrt(10000)" | bc  

