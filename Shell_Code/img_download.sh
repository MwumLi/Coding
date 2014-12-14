#!/bin/bash 
# 图片抓取
if [ $# -ne 3 ];
then 
	echo "Usage: $0 URL -d DIRECTORY"
	exit 1
fi

#获取参数
for i in {1..4} ; do
	case $1 in 
		-d) shift; 
			directory=$1; 
			shift ;;
		*) url=${url:-$1};
			shift ;;
	esac
done

# 新建存取路径
mkdir -p $directory;

# 基路径
baseurl=$(echo $url | egrep -o "https?://[a-z.]+")

# 下载数据凝去除img标签中的src
curl -s $url | egrep -o "<img[^>]*>" | egrep -o "src=[^>]*>" |
sed 's%src=\"\([^"]*\).*%\1%g' > /tmp/$$.list;
# 如果是相对路径，则替换
sed "s%^\/%${baseurl}\/%g" -i /tmp/$$.list

cd $directory;

while read filename;
do
	curl -s -O "$filename" --silent
done < /tmp/$$.list

echo "下载完成"

exit 0
