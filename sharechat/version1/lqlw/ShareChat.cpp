/*********************************************************************
 * 文件名		：ServerChat.cpp
 * 创建时间	：2014-11-15
 * 程序描述	：服务器端程序
 * 其他			：无
 *********************************************************************/
#include "common.h"


/*---------------------------------------------------------------------------------------------------------------------------
全局变量定义
 ---------------------------------------------------------------------------------------------------------------------------*/
// 服务器端套接字
int g_nSocket = 0;
unsigned int unMsgIndex = 0;
vector<roomMember> g_vecRoomList;
list<dataPacket> g_dataPacketList;


/*---------------------------------------------------------------------------------------------------------------------------
子模块函数声明
 ---------------------------------------------------------------------------------------------------------------------------*/
static void* DataDoWithProc(void* ThreadParam);																// 测试通过
void InitRoomList(void);																													// 测试通过
void Connect(struct sockaddr_in sockaddrTemp);																		// 待测
void JoinRoom(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam);					// 测试通过
void ExitRoom(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam);					// 测试通过
void MsgDealWith(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam);			// 测试通过
void PrintDataRecvInfo(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam);	// 测试通过


/*---------------------------------------------------------------------------------------------------------------------------
 入口点main函数
 ---------------------------------------------------------------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		cout<<"usage: ./Share2 xxx.xxx.xxx.xxx"<<endl;
		return -1;
	}

	// 服务器端地址信息结构体
	struct sockaddr_in sockaddrServer = {0};

	// 地址结构体大小
	int nAddrSize = sizeof(struct sockaddr_in);	

	// 创建Udp服务器端套接字	 
	g_nSocket = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == g_nSocket)
	{
		cout<<"服务器套接字创建失败！"	<<endl;
		return -1;
	}

	// 初始化服务器地址信息结构体
	sockaddrServer.sin_family = AF_INET;
	sockaddrServer.sin_addr.s_addr = inet_addr(argv[1]);
	sockaddrServer.sin_port = htons(SERVER_PORT);

	// 将套接字与服务器地址信息结构体绑定 	 
	int nBindRet = bind(
			g_nSocket, 
			(struct sockaddr*)(&sockaddrServer), 
			sizeof(sockaddrServer));

	// 初始化房间列表信息
	InitRoomList();	

	while(1)
	{
		// 定义并初始化接收数据的缓冲区
		sendMsg bufferRecv;
		memset((void*)&bufferRecv, 0, sizeof(sendMsg));

		// 客户端地址信息结构体
		struct sockaddr_in sockaddrTemp = {0};
		memset(&sockaddrTemp, 0, sizeof(sockaddrTemp));

		// 接收信息
		int nRecvRet = recvfrom(
			g_nSocket, 															// 服务器本端套接字
			(char*)(&bufferRecv), 										// 数据缓冲区
			sizeof(sendMsg), 											// 接收数据大小
			0, 
			(struct sockaddr*)&sockaddrTemp, 				// 保存发送方地址信息
			(socklen_t *)&nAddrSize);								// 前一个参数大小	

		dataPacket DataPacketTemp = {0};
		memcpy(&(DataPacketTemp.sockAddr), &sockaddrTemp, sizeof(sockaddrTemp));
		memcpy(&(DataPacketTemp.sendMsgData), &bufferRecv, sizeof(bufferRecv));

		// 创建数据处理线程
		pthread_t thread;
		pthread_create(&thread, NULL, DataDoWithProc, (void*)&DataPacketTemp);
	}
	
	// 关闭服务器端套接字
	close(g_nSocket);

	return 0;
}


/*---------------------------------------------------------------------------------------------------------------------------
子模块函数实现
 ---------------------------------------------------------------------------------------------------------------------------*/
/** 
 功能		：处理数据包队列中的数据
 参数		：void
 返回值	：void
 */
static void* DataDoWithProc(void* DataPacketTemp)
{
	dataPacket dataPacketTemp = {0};
	memcpy(&dataPacketTemp, DataPacketTemp, sizeof(DataPacketTemp));
	struct sockaddr_in sockaddrTemp = {0};
	sendMsg bufferRecv = {0};
	memcpy(&bufferRecv, &(((dataPacket*)DataPacketTemp)->sendMsgData), sizeof(bufferRecv));
	memcpy(&sockaddrTemp, &(((dataPacket*)DataPacketTemp)->sockAddr), sizeof(sockaddrTemp));

	PrintDataRecvInfo(sockaddrTemp, bufferRecv);

	// 信息处理枢纽
	switch(bufferRecv.msg_type)
	{
		// 客户端首次连接
		case CONNECT:
		{
			Connect(sockaddrTemp);
			break;
		}
		// 客户端加入某个房间
		case JOIN:
		{
			JoinRoom(sockaddrTemp, bufferRecv);
			break;
		}
		// 客户端退出某个房间
		case EXIT:
		{
			ExitRoom(sockaddrTemp, bufferRecv);
			break;
		}
		// 下载文件
		case DOWNLOAD:
		{

			break;
		}
		// 上传文件
		case UPLOAD:
		{

			break;
		}
		// 普通聊天消息
		case MSG_MSG:
		{
//			cout<<"MSG_MSG"<<endl;
			MsgDealWith(sockaddrTemp, bufferRecv);
			break;
		}
		// 上传文件
		case MSG_FILE:
		{

			break;
		}
		// 其他消息，不做处理
		default:
		{
			cout<<"Waring : Exception message, Server can not deal with the message!"<<endl;
			break;
		}
	}		
	
	return NULL;
}

/** 
 功能		：初始化服务器端的房间列表信息
 参数		：void
 返回值	：void
 */
void InitRoomList(void)
{
	vector<roomMember>::iterator itrTemp;
	/**
	 外层循环： 将房间列表中的信息进行初始化
						 房间名称初始化为NULL
						 房间的聊天成员列表初始化为NULL
	 */
	for(itrTemp = g_vecRoomList.begin(); itrTemp != g_vecRoomList.end(); itrTemp++)
	{
		(*itrTemp).name = NULL;
		vector<chatMember>::iterator itrInner;
		/** 
		 内层循环：初始化指定房间的聊天成员列表
						 成员名称初始化为NULL
						 成员ip字符串初始化为NULL
						 成员的port初始化为-1
		 */
		for(itrInner = ((*itrTemp).chat_list).begin(); itrInner != ((*itrTemp).chat_list).end(); itrInner++)
		{
			(*itrInner).name = NULL;
			(*itrInner).ip = NULL;
			(*itrInner).port = -1;
		}
	}
	
	return;
}

/** 
 功能		：向参数指定的客户端发送连接成功的信息
 参数		：sockaddrTemp	：接收信息的客户端地址信息
 返回值	：void
 */
void Connect(struct sockaddr_in sockaddrTemp)
{
	// 保存sendto的返回值
	int nRetSend = -1;
	// 地址结构体大小
	int nAddrSize = sizeof(struct sockaddr_in);

	// 要发送的数据包
	sendMsg sendMsgTemp = {0};

	// 数据填充
	sendMsgTemp.msg_type = CONN_SUCCESS;			// 消息类型
	memset(sendMsgTemp.room, 0, 128);						// 房间名称
	strcpy(sendMsgTemp.msg, "Connect Success!");		// 消息内容
//	cout<<sendMsgTemp.msg<<endl;
	nRetSend = sendto(
			g_nSocket, 
			(char*)(&sendMsgTemp), 
			sizeof(sendMsgTemp), 
			0, 
			(struct sockaddr*)&sockaddrTemp, 
			nAddrSize);
	if(nRetSend == -1)
	{
	#if DEBUG_HELP
		cout<<"sendto is called fail in connect()\r\n"<<endl;
	#endif
	}

	return;
}

/** 
 功能		：处理客户端JOIN命令的消息
 参数		：sockaddrParam：客户端的地址信息
					sendMsgParam：客户端所发送的信息
 返回值	：void
 */
void JoinRoom(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam)
{
	// 保存sendto的返回值
	int nRetSend = -1;
	// 地址结构体大小
	int nAddrSize = sizeof(struct sockaddr_in);

	// 要发送的数据包
	sendMsg sendMsgTemp = {0};

	// 数据填充
	sendMsgTemp.msg_type = JOIN_SUCCESS;				// 消息类型
	memset(sendMsgTemp.room, 0, 128);						// 房间名称
	strcpy(sendMsgTemp.msg, "Join Success!");				// 消息内容
//	cout<<sendMsgTemp.msg<<endl;
	nRetSend = sendto(
			g_nSocket, 
			(char*)(&sendMsgTemp), 
			sizeof(sendMsgTemp), 
			0, 
			(struct sockaddr*)&sockaddrParam, 
			nAddrSize);
	if(nRetSend == -1)
	{
	#if DEBUG_HELP
		cout<<"sendto is called fail in JoinRoom()\r\n"<<endl;
	#endif
	}

	vector<roomMember>::iterator itrTemp;
	int flag = 0;

	// 如果房间队列不为空，再去查找
	if(!g_vecRoomList.empty())
	{
		for(itrTemp = g_vecRoomList.begin(); itrTemp != g_vecRoomList.end(); itrTemp++)
		{
			if(!strcmp(sendMsgParam.room, (*itrTemp).name))
			{
				flag = 1;
				break;
			}		
		}
	}


#if DEBUG_HELP1
	/** 
	 打印出当前所有房间信息
	 */
	cout<<"当前房间信息: "<<endl;
	vector<roomMember>::iterator itrTempTemp;
	for(itrTempTemp = g_vecRoomList.begin(); itrTempTemp != g_vecRoomList.end(); itrTempTemp++)
	{
		cout<<(*itrTempTemp).name<<endl;
	}
	cout<<endl<<endl<<endl;
#endif

	// 如果房间存在
	if(1 == flag)
	{
		// 2.2 向其他成员发送该成员的信息（仅仅是名称）
		vector<chatMember>::iterator itrChatMember;
		if(((*itrTemp).chat_list).empty())
		{	
			cout<<"房间: "<<(*itrTemp).name<<"列表为空!"<<endl;
			return;
		}

#if DEBUG_HELP1
		/**
		 打印该房间中的成员列表信息
		 */
		cout<<"Room : "<<(*itrTemp).name<<" 列表信息是： "<<endl;
		for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
		{		
			cout<<"user name : "<<(*itrChatMember).name<<endl;
			cout<<"user ip : "<<(*itrChatMember).ip<<endl;
			cout<<"user port : "<<(*itrChatMember).port<<endl;
		}
		cout<<endl<<endl<<endl;
#endif

		for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
		{
			// 构造地址信息结构体
			struct sockaddr_in sockaddrTemp = {0};
			sockaddrTemp.sin_family = AF_INET;
			sockaddrTemp.sin_addr.s_addr = inet_addr((*itrChatMember).ip);
			sockaddrTemp.sin_port = (*itrChatMember).port;

//			cout<<"for inner"<<endl;

			// 构造要发送的数据包
			sendMsg sendMsgTemp = {0};
			sendMsgTemp.msg_type = JOIN;										// 消息类型
			strcpy(sendMsgTemp.room ," ");										// 房间名称
			strcpy(sendMsgTemp.msg, sendMsgParam.msg);			// 用户名称

//			cout<<"sendto before"<<endl;

			// 向其他客户发送该成员的信息
			int nRetSend = sendto(
							g_nSocket, 
							(char*)(&sendMsgTemp), 
							sizeof(sendMsgTemp), 
							0, (struct sockaddr*)(&sockaddrTemp), 
							sizeof(sockaddrTemp));
			if(nRetSend == -1)
			{
			#if DEBUG_HELP
				printf("1st sendto is called failed in RoomExist\r\n");
			#endif	
			}
		}

		// 2.3 向该成员发送其他成员的信息（仅仅是名称）
		for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
		{
			// 构造要发送的数据包
			sendMsg sendMsgTemp = {0};
			sendMsgTemp.msg_type = JOIN;												// 消息类型
			strcpy(sendMsgTemp.room ," ");												// 房间名称
			strcpy(sendMsgTemp.msg, (*itrChatMember).name);			// 用户名称

			int nRetSend = sendto(
					g_nSocket, 
					(char*)(&sendMsgTemp), 
					sizeof(sendMsgTemp), 
					0, (struct sockaddr*)(&sockaddrParam), 
					sizeof(sockaddrParam));
			if(nRetSend == -1)
			{
			#if DEBUG_HELP
				printf("2nd sendto is called failed in RoomExist\r\n");
			#endif	
			}
		}

		// 2.4 将该客户端的地址、客户端名称信息保存到指定的房间列表中
		int nIsExist = 0;
		for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
		{		
			if(!(strcmp((*itrChatMember).ip, inet_ntoa(sockaddrParam.sin_addr))) 
				&& ((*itrChatMember).port == sockaddrParam.sin_port))
			{
				nIsExist = 1;
				cout<<"客户存在！"<<endl;
				break;
			}
		}
		if(nIsExist == 0)			// 房间中不存在这个客户，将这个客户添加到该房间的列表中
		{
			chatMember chatMemberTemp;
			chatMemberTemp.name = (char*)malloc(128);
			strcpy(chatMemberTemp.name, sendMsgParam.msg);
			chatMemberTemp.ip = (char*)malloc(128);
			strcpy(chatMemberTemp.ip, inet_ntoa(sockaddrParam.sin_addr));
			chatMemberTemp.port = sockaddrParam.sin_port;
			(*itrTemp).chat_list.push_back(chatMemberTemp);

#if 0
		/**
		 打印该房间中的成员列表信息
		 */
		cout<<"Room : "<<(*itrTemp).name<<" 列表信息是： "<<endl;
		for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
		{		
			cout<<"user name : "<<(*itrChatMember).name<<endl;
			cout<<"user ip : "<<(*itrChatMember).ip<<endl;
			cout<<"user port : "<<(*itrChatMember).port<<endl;
		}
		cout<<endl<<endl<<endl;
#endif
		}
		else							// 房间中存在这个客户，不用添加
		{
			;
		}
	}
	else	// 如果房间不存在
	{
//		cout<<"房间不存在！"<<endl;

		// 2.2 创建房间，在服务器端的房间列表中创建一个房间
		roomMember roomMemberUnit = {0};
		roomMemberUnit.name = (char*)malloc(128);
		strcpy(roomMemberUnit.name, sendMsgParam.room);

		// 将该客户端的信息添加到该房间的聊天成员列表中
		chatMember chatMemberTemp = {0};
		chatMemberTemp.name = (char*)malloc(128);											// 客户名称申请空间
		chatMemberTemp.ip = (char*)malloc(128);												// 客户IP申请空间保存
		strcpy(chatMemberTemp.name, sendMsgParam.msg);								// 拷贝客户名称
		strcpy(chatMemberTemp.ip, inet_ntoa(sockaddrParam.sin_addr));			// 拷贝客户IP
		chatMemberTemp.port = sockaddrParam.sin_port;									// 拷贝客户PORT
/*
		cout<<sendMsgParam.room<<endl;
		cout<<sendMsgParam.msg<<endl;
		cout<<inet_ntoa(sockaddrParam.sin_addr)<<endl;
*/
		// 2.3 该该客户端的信息添加到该房间的成员列表中
		// 将聊天成员添加到房间中		
		roomMemberUnit.chat_list.push_back(chatMemberTemp);
		// 将房间添加到房间列表中
		g_vecRoomList.push_back(roomMemberUnit);
	}
	
	return;
}

/** 
 功能		：处理客户端EXIT命令的消息
 参数		：sockaddrParam：客户端的地址信息
					sendMsgParam：客户端所发送的信息
 返回值	：void
 */
void ExitRoom(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam)
{
	vector<roomMember>::iterator itrTemp;
	int flag = 0;
	if(g_vecRoomList.empty())				// 房间列表为空
	{
		cout<<"没有房间！"<<endl;
		return;
	}

	// 找到房间名字
	for(itrTemp = g_vecRoomList.begin(); itrTemp != g_vecRoomList.end(); itrTemp++)
	{
		if(!strcmp(sendMsgParam.room, (*itrTemp).name))
		{
			flag = 1;
		//	cout<<"找到的房间名字："<<(*itrTemp).name<<endl;
			break;
		}		
	}
	
	// 找到了房间的名字
	if(flag == 1)
	{
		// 只有1个成员（必然也是最后一个发送exit的客户）
		if(1 == (*itrTemp).chat_list.size())
		{
			// 2.2 将该客户端的信息从所属房间成员中剔除，销毁房间成员列表
			free((*(*itrTemp).chat_list.begin()).name);		// 释放客户名称申请的空间
			free((*(*itrTemp).chat_list.begin()).ip);				// 释放IP地址所占用的空间
			(*itrTemp).chat_list.pop_back();							

			// 2.3 服务器端删除该房间的信息
			free((*itrTemp).name);										// 释放房间名称申请的空间
			g_vecRoomList.erase(itrTemp);
			
			/** 
			 打印房间中的信息
			 */
			
		}
		else	// 房间中有 >1个成员
		{
			//	2.2 从房间成员列表中剔除该客户的信息
			vector<chatMember>::iterator itrChatMember1;
			for(itrChatMember1 = ((*itrTemp).chat_list).begin(); itrChatMember1 != ((*itrTemp).chat_list).end(); itrChatMember1++)
			{
				char strIp[128] = {0};
				memcpy(strIp, inet_ntoa(sockaddrParam.sin_addr), sizeof(strIp));
				if(((*itrChatMember1).port == sockaddrParam.sin_port) || !strcmp(strIp, (*itrChatMember1).ip))
				{
					// 释放客户名字所占用的空间
					free((*itrChatMember1).name);
					// 释放客户ip所占用的空间
					free((*itrChatMember1).ip);
					((*itrTemp).chat_list).erase(itrChatMember1);
					break;
				}
			}

			// 2.3 向其他客户发送该客户离开的信息
			vector<chatMember>::iterator itrChatMember;
			for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
			{
				// 构造地址信息结构体
				struct sockaddr_in sockaddrTemp = {0};
				sockaddrTemp.sin_family = AF_INET;
				sockaddrTemp.sin_addr.s_addr = inet_addr((*itrChatMember).ip);
				sockaddrTemp.sin_port = (*itrChatMember).port;	

				// 发送给其他客户
				int nRetSend = sendto(
						g_nSocket, 
						(char*)(&sendMsgParam), 
						sizeof(sendMsgParam), 
						0, (struct sockaddr*)(&sockaddrTemp), 
						sizeof(sockaddrTemp));
				if(nRetSend == -1)
				{
				#if DEBUG_HELP
					printf("sendto is called failed in ExitRoom\r\n");
				#endif	
				}
			}
		}
	}
	else	// 没有找到房间的名字
	{
	#if DEBUG_HELP	
		printf("房间名称不存在!\r\n");
	#endif
	}		

	return;
}

/** 
 功能		：处理客户端文字信息命令的消息
 参数		：sockaddrParam：客户端的地址信息
					sendMsgParam：客户端所发送的信息
 返回值	：void
 */
void MsgDealWith(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam)
{
	vector<roomMember>::iterator itrTemp;
	int flag = 0;
	// 找到房间名称
	if(g_vecRoomList.empty())
	{
		cout<<"暂时没有房间！"<<endl;
		return;
	}

	cout<<"本消息所属房间编号：";
	cout<<sendMsgParam.room<<endl;
	for(itrTemp = g_vecRoomList.begin(); itrTemp != g_vecRoomList.end(); itrTemp++)
	{
//		cout<<(*itrTemp).name<<endl;
		if(!strcmp(sendMsgParam.room, (*itrTemp).name))
		{		
			flag = 1;
			break;
		}		
	}

	vector<chatMember>::iterator itrChatMember;
	if(((*itrTemp).chat_list).empty())
	{
		cout<<"The room no have list"<<endl;
		return;
	}
	
	if(flag != 1)
	{
		return;
	}
	else
	{
		for(itrChatMember = ((*itrTemp).chat_list).begin(); itrChatMember != ((*itrTemp).chat_list).end(); itrChatMember++)
		{
			// 构造地址信息结构体
			struct sockaddr_in sockaddrTemp = {0};
			sockaddrTemp.sin_family = AF_INET;
			sockaddrTemp.sin_addr.s_addr = inet_addr((*itrChatMember).ip);
			sockaddrTemp.sin_port = (*itrChatMember).port;
	
			// 发送给其他客户
			/** 
			 不能再次发送给自己
	 		 */
			char strIp[128] = {0};
			strcpy(strIp, inet_ntoa(sockaddrParam.sin_addr));
			if(((*itrChatMember).port != sockaddrParam.sin_port) || strcmp(strIp, (*itrChatMember).ip))
			{
				int nRetSend = sendto(
						g_nSocket, 
						(char*)(&sendMsgParam), 
						sizeof(sendMsgParam), 
						0, (struct sockaddr*)(&sockaddrTemp), 
						sizeof(sockaddrTemp));

				if(nRetSend == -1)
				{
				#if DEBUG_HELP
					printf("sendto is called failed in ExitRoom ! \r\n");
				#endif	
				}
			}
		}
	}	

	return;
}

/** 
 功能		：将接收到的信息打印出来
 参数		：sockaddrParam：客户端的地址信息
					sendMsgParam：客户端所发送的信息
 返回值	：void
 */
void PrintDataRecvInfo(struct sockaddr_in sockaddrParam, sendMsg sendMsgParam)
{
#if 1
	cout<<"recv message from client "<<unMsgIndex++<<" message "<<endl;
	cout<<"msg_type: "<<sendMsgParam.msg_type<<endl;
	cout<<"room: "<<sendMsgParam.room<<endl;
	cout<<"member: "<<sendMsgParam.member<<endl;
	cout<<"msg: "<<sendMsgParam.msg<<endl;
	cout<<"ip: "<<inet_ntoa(sockaddrParam.sin_addr)<<endl;
	cout<<"port: "<<sockaddrParam.sin_port<<endl;
	cout<<endl;
#endif

	return;
}
