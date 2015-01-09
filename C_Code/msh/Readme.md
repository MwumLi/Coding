
### 编译  

1.  安装flex  

		$ sudo apt-get install flex

2. 安装`libreadline6`和`libreadline6-dev`  

		$ sudo apt-get install libreadline6 libreadline6-dev

3. 编译  

		$ make 

#### 问题  
1. 编译时错误： 

		msh.c:9:31: fatal error: readline/readline.h: No such file or directory 

遇到这种错误，是因为系统中缺乏`readline`的包，那么请执行编译过程的第2步安装  

