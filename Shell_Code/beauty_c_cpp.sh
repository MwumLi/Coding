#!/bin/sh

#请确保你已经安装了indent,否则本脚本不能正常使用
# -npro   不要读取indent的配置文件.indent.pro
# -kr     使用Kernighan&Ritchie的格式
# -i4     设置缩排的格数为4
# -di28   将声明区段的变量置于指定的栏位(28) 
# -ts4    设置tab的长度为4 
# -bls    定义结构，"struct"和"{"分行
# -bl     if(或是else,for等等)与后面执行区段的”{“不同行，且”}”自成一行。
# -bli0   设置{ }缩排的格数为0 
# -cli2   使用case时，switch缩排的格数
# -ss     若for或whiile区段只有一行时，在分号前加上空格
# -bad    在声明区段后加上空白行
# -bbb    块注释前加空行
# -bap    函数结束后加空行
# -sc     在每行注释左侧加上星号(*)。
# -bc     在声明区段中，若出现逗号即换行。
# -sob    删除多余的空白行
# -l100   非注释行最长100
# -ncs    不要在类型转换后面加空格
# -nce    不要将else置于”}”之后
# -nut    不要使用tab来缩进

param=" -npro -kr -i4 -ts4 -sob -l80 -ss -ncs -cp1 -bap -nce"
indent $param $1
echo $1 "beauty successfully!"
echo $1~ "is old file"
