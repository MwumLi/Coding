## DNS是什么  
DNS,*Domain Name Service*的缩写,也就是域名服务的意思  
但在某些场合，我们也把其理解为域名解析服务器，比如:  

当你电脑qq或者其他服务可以通信，而web服务停止，很有可能是你的dns挂了，那么修改一下你的机子的DNS吧    

在这种场合，我们就可以理解为域名解析服务器  

有了DNS,我们才可以把可读性非常强的域名(比如www.mwumli.com)转化成这个名字所代表的IP地址，你可以使用`ping`命令解析域名所对应的ip,比如:  


	$ ping www.baidu.com  
	PING www.a.shifen.com (119.75.217.56) 56(84) bytes of data.
	64 bytes from 119.75.217.56: icmp_seq=1 ttl=54 time=18.4 ms 
	...

## 和DNS有关的函数和结构  
### gethostbyname()  
#### 原型  

	#include <netdb.h>
	extern int h_errno;
	struct hostent *gethostbyname(const char *name);
#### 相关数据结构  

	struct hostent {
		Char	*h_name;		// official name of host
		char	**h_aliases;	// alias list
		int		h_addrtype;		// host address type
		int		h_length		// length  of address 
		char	**h_addr_list;	// list of addresses
	}
	#define h_addr h_addr_list[0]
*hostent结构成员意义*  
* h_name 主机的正式名称
* h_aliases 
	一个二维char型指针数组，用来存储当前指定机器的别名，以`NULL`结尾
* h_addrtype  
	地址类型: `AF_INET` 代表ipv4 or `AF_INET6` 代表ipv6  
* h_length  
	ip地址长度，以byte为单位  
* h_addr_list  
	一个二维char型指针数组，用来存储当前机器的ip(网络字节序，即大端模式),以`NULL`结尾  
* h_addr 
	*h_addr_list*的第一个成员地址，这个是为了向后兼容  

#### 返回值及错误  
执行成功，返回一个`struct hostent`指针  
否则，返回`NULL`,此时，错误代码存在`h_errno`变量，可以使用`void herror(const char *s)`打印当前错误信息,或者`const char *hstrerror(int err)`  
*需要注意的是*: 返回的`struct hostent`指针指向一个静态数据，即会被后继的调用所覆盖。所以，在多线程和多进程中不安全  


在man手册中有这么一段话:  
>The gethostbyname*(), gethostbyaddr*(), herror(), and hstrerror() functions are obsolete.  Applications should  use  getaddrinfo(3), getnameinfo(3), and gai_strerror(3) instead.  


### getaddrinfo()
#### 原型  

	`int getaddrinfo( const char *hostname, const char *service, const struct addrinfo *hints, struct addrinfo **result );`
