#!/bin/bash 
# 这是一个定时器脚本  

i=0
if [[ $# -ne 1 ]]; then
	echo "Usage:$0 num[SUFFIX]"
	echo "SUFFIX may be s/m/h/d"
	exit 1
fi


timer="$1"
#假如第一字母不是数字，不合法
ch=${timer:0:1}
if [[ $ch < "0" ]] && [[ $ch > "9" ]] ; then	
	echo "Usage:$0 num[SUFFIX]"
	echo "SUFFIX may be s/m/h/d"
	exit 2
fi
len=${#timer}
temp=""
for (( i = 0; i < ${len}; i++ )); do
	ch=${timer:$i:1}
	
	if [[ $ch = "s" ]] ; then
		break;
	elif [[ $ch = "m" ]] ; then
		let temp=${temp}*60
		break;
	elif [[ $ch = "h" ]] ; then 
		let temp=${temp}*3600
		break;
	elif [[ $ch = "d" ]] ; then
		let temp=${temp}*24*3600
		break
	elif [[ $ch -ge 0 ]] && [[ $ch -le 9 ]]; then
		temp=${temp}${ch}
	else
		echo "Usage:$0 num[SUFFIX]"
		echo "SUFFIX may be s/m/h/d"
		exit 3
	fi
done

timer=$temp 
second=00;
minute=00;
hour=00;
day=00;
echo  "Day Hour Minute Second"
tput sc
for (( i = 0; i < $timer; i++ )); do
	sleep 1s
	tput rc 
	tput ed
	let second++
	if [[ `expr ${second} / 60` -gt 0 ]]; then
		let minute++
		second=0
	fi
	if [[ `expr ${minute} / 60` -gt 0 ]]; then
		let hour++
		minute=0
	fi
	if [[ `expr ${hour} / 24` -gt 0 ]]; then
		let day++
		hour=0
	fi
	
	if [[ ${day} -lt 10 ]]; then
		printf "%2d%d " 0 $day
	else 
		printf "%3d " $day
	fi

	if [[ ${hour} -lt 10 ]]; then
		printf "%3d%d " 0 $hour
	else 
		printf "%4d " $hour
	fi

	if [[ ${minute} -lt 10 ]]; then
		printf "%5d%d " 0 $minute
	else 
		printf "%6d " $minute
	fi

	if [[ ${second} -lt 10 ]]; then
		printf "%5d%d " 0 $second
	else 
		printf "%6d " $second
	fi
done

google-chrome ./songs.mp3  1>/dev/null 2>/dev/null
echo
exit 0
