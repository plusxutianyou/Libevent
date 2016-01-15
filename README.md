# Libevent

Libevent 是一个用C语言编写的、轻量级的开源高性能网络库，主要有以下几个亮点：事件驱动（ event-driven），高性能;轻量级，专注于网络，不如 ACE 那么臃肿庞大；源代码相当精炼、易读；跨平台，支持 Windows、 Linux、 *BSD 和 Mac Os；支持多种 I/O 多路复用技术， epoll、 poll、 dev/poll、 select 和 kqueue 等；支持 I/O，定时器和信号等事件；注册事件优先级。
Libevent 已经被广泛的应用，作为底层的网络库；比如 memcached、 Vomit、 Nylon、 Netchat等等。

libevent包括事件管理、缓存管理、DNS、HTTP、缓存事件几大部分。事件管理包括各种IO（socket）、定时器、信号等事件；缓存管理是指evbuffer功能；DNS是libevent提供的一个异步DNS查询功能；HTTP是libevent的一个轻量级http实现，包括服务器和客户端。libevent也支持ssl，这对于有安全需求的网络程序非常的重要，但是其支持不是很完善，比如http server的实现就不支持ssl。


目前这个版本在原libevent-2.0.21-stable版本基础之上，追加http server支持ssl的功能(需要依赖openssl)，详见http_ssl_demo.cpp

