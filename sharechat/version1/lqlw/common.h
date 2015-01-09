/*********************************************************************
 * 文件名		：common.h
 * 创建时间	：2014-11-15
 * 程序描述	：使用到的数据结构、宏定义
 * 其他			：无
 * ---------------------------------------------------------start  file-----------------------------------------------------
 *********************************************************************/
#ifndef 		_COMMON_H
#define 		_COMMON_H


// 包含必要的系统头文件、C++库文件
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>
#include <list>
using namespace std;


/**-------------------------------------------------------------------------------------------------------------------------
 宏定义
 ---------------------------------------------------------------------------------------------------------------------------*/
#define BUF_SIZE					512
#define SERVER_PORT 			8888
#define CONNECT  				0
#define JOIN	 						1
#define EXIT	 						2
#define DOWNLOAD 			3
#define UPLOAD  				4
#define MSG_MSG		 		5
#define MSG_FILE		 		6					// 因为有DOWNLOAD和UPLOAD，因此可以不使用这个宏
#define CONN_SUCCESS 	10
#define JOIN_SUCCESS 		11
#define DEBUG_HELP			0
#define DEBUG_HELP1		0

/**-------------------------------------------------------------------------------------------------------------------------
 使用到的数据结构
 ---------------------------------------------------------------------------------------------------------------------------*/
// 聊天成员信息
typedef struct chatMember {
	char 		*name;									// 客户名称
	char 		*ip;											// 客户IP地址
	int  			port;										// 客户端口
}chatMember;

// 聊天房间信息
typedef struct roomMember {
	char								*name;			// 房间名称
	vector<chatMember>	chat_list; 		// 聊天成员列表
}roomMember;	

// 接收发送信息的数据包格式
typedef struct sendMsg {
	int		msg_type;									// 消息类型
	char	room[128];									// 房间名称
	char 	member[128];							// 用户名称
	char	msg[BUF_SIZE];							// 消息内容
}sendMsg;

typedef struct dataPacket {
	struct sockaddr_in sockAddr;				// 地址信息结构体
	sendMsg sendMsgData; 						// 接收到的数据包
}dataPacket;


#endif
/*********************************************************************
------------------------------------------------------------end  file------------------------------------------------------
 *********************************************************************/

