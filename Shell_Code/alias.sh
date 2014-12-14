#!/bin/bash 
# 别名设置  
# 对于别名设置，意义不是很大，当是请考虑下面一种情况:  
# 假如有一天要完成很多次操作，而这些操作的名字又很长
# 我们应该很想少敲几个字母,这时候，别名操作就很重要了  

# 使用alias name='command line'取别名    
# 比如
alias get='sudo apt-get'
# 下来，我们就可以这样更新软件源了  
get update
# 假如你不想要这个别名，那么取消它吧  
# 使用unalias name
unalias get 
# 假如你想全部取消的话  
# 使用unalias -a

# 假如你忘记你为什么命令去了别名，那么查查吧  
# 使用aliae
alias

# 当然,你也可以自定义函数包含相应命令放到.bashrc，同样能达到创建别名的效果
# 一个有意思的别名  
alias rm='
if [[ ! -d ~/backup ]]; then
	mkdir -p ~/backup
fi
cp $@ ~/backup 
rm $@'

# 尽管某些情况下，别名很适合，但有些情况下，我们也不希望使用别名  
# 但是我们并不希望unalias它(可能之后还需要),因此我们这样做：  
# 在命令行执行别名之前添加'\',例如
# 首先我们查看ls 
alias ls
# 发现:aliasls='ls --color=auto'
# 我们想看看其本来面目,但又不想破坏此别名，因此    
\ls

# 一本书籍定义了这样一个alias:alias rm='cp $@ ~/backup; rm $@'
# 理论上没问题，但是结果总有问题，不知道原因  

