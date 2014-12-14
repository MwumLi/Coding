#!/bin/bash 
#用来演示数组的用法
#包括普通数组和关联数组  
#

# 单行定义普通数组
echo "单行定义普通数组,并以for循环输出"
arr=(1 2 3 4 5 6)
for (( i = 0; i < 6; i++ )); do
	echo ${arr[i]}
done

# 普通数组定义一组索引值(index-value pair)
arr[0]="arr1"
arr[1]="arr2"
arr[2]="arr3"

# 以清单形式打印数组所有值
echo "以清单形式打印数组所有值:"
echo ${arr[*]} 
# 也可以这样做  
echo "也可以这样输出清单"
echo ${arr[@]}

#打印数组长度  
echo ${#arr[*]}

echo "由此可见，数组元素一旦定义，不会消除"  

# 声明关联数组
# 首先使用单独的声明语句将一个变量名声明为关联数组  

declare -A associative_arr
# 下来将有两种方法添加元素  
# 第一种，内嵌索引-值值列表  
associative_arr=([ass1]='value1' [ass2]='value2')
echo ${associative_arr[*]}

# 第二种，使用独立索引-值进行赋值  
associative_arr[ass3]='woaini'
echo ${associative_arr[*]}

# 对于关联数组，我想我们不仅仅是列举值，有时候还希望看到索引  
echo ${!associative_arr[*]}
