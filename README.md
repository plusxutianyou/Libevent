# Libevent

Libevent 是一个用C语言编写的、轻量级的开源高性能网络库，主要有以下几个亮点：事件驱动（ event-driven），高性能;轻量级，专注于网络，不如 ACE 那么臃肿庞大；源代码相当精炼、易读；跨平台，支持 Windows、 Linux、 *BSD 和 Mac Os；支持多种 I/O 多路复用技术， epoll、 poll、 dev/poll、 select 和 kqueue 等；支持 I/O，定时器和信号等事件；注册事件优先级。
Libevent 已经被广泛的应用，作为底层的网络库；比如 memcached、 Vomit、 Nylon、 Netchat等等。

libevent包括事件管理、缓存管理、DNS、HTTP、缓存事件几大部分。事件管理包括各种IO（socket）、定时器、信号等事件；缓存管理是指evbuffer功能；DNS是libevent提供的一个异步DNS查询功能；HTTP是libevent的一个轻量级http实现，包括服务器和客户端。libevent也支持ssl，这对于有安全需求的网络程序非常的重要，但是其支持不是很完善，比如http server的实现就不支持ssl。


目前这个版本在原libevent-2.0.21-stable版本基础之上，追加http server支持ssl的功能(需要依赖openssl);
如下：

struct evhttp *ev_ssl = NULL;
struct event_base *evbase = NULL;
std::sting certfile_url = "./ssl/server-cert.pem";
std::string key_file = "./ssl/server-key.pem";

// SSL握手前的环境准备
SSL_CTX *get_ssl_ctx(const char *cert_file, const char *key_file){
    if(NULL == ev_ssl){
        return NULL;
    }

    if (ev_ssl->ctx != NULL){
        return ev_ssl->ctx;
    }

    ev_ssl->ctx = SSL_CTX_new(SSLv23_method());
    if (NULL == ev_ssl->ctx){
      return NULL;
    }

    if (SSL_CTX_use_certificate_file(ev_ssl->ctx, cert_file, SSL_FILETYPE_PEM) < 0) {
        SSL_CTX_free(ev_ssl->ctx);
        return NULL;
    }

    if (SSL_CTX_use_PrivateKey_file(ev_ssl->ctx, key_file, SSL_FILETYPE_PEM) < 0) {
        SSL_CTX_free(ev_ssl->ctx);
        return NULL;
    }

    if (!SSL_CTX_check_private_key(ev_ssl->ctx)){
        return NULL;
    }

    return ev_ssl->ctx;
}

void ssl_accept_error_cb(struct evconnlistener *lis, void *ptr){
    // do nothing
}

void ping_handler(struct evhttp_request *req, void *arg){
  
  string ping = "ok";
	struct evbuffer * buf = evhttp_request_get_output_buffer(req);
	evbuffer_add_printf(buf,
        "%s",
        ping.c_str());

	evhttp_send_reply(req, HTTP_OK, "OK", buf);
}

int main(int argc,char** argv){

  evbase = event_base_new();
	if(!evbase){
		fprintf(stderr, "create evbase error!\n");
		exit(0);
	}
	
	// 创建http server实例
	ev_ssl = evhttp_new(evbase);
  if(!ev_ssl){
        exit(0);
  }

  // openssl 初始化
  SSL_library_init();
  ERR_load_crypto_strings();
  SSL_load_error_strings();
  OpenSSL_add_all_algorithms();

  if (SSLeay() != OPENSSL_VERSION_NUMBER) {
  }
    
  ev_ssl->ctx = get_ssl_ctx(certfile_url.c_str(),keyfile_url.c_str());
  ev_ssl->ssl_cb = bufferevent_openssl_socket_new;
  
  std::string ev_ssl_ip="192.168.1.10";
  int ev_ssl_port = 8080;
  
  // evhttp_bind_socket_with_handle这个函数在原基础上追加一个参数，标示http server知否支持ssl(0:不支持  1:支持)
  struct evhttp_bound_socket *ssl_handle = evhttp_bind_socket_with_handle(ev_ssl, ev_ssl_ip.c_str(), ev_ssl_port,1);
  if(!ssl_handle){
      exit(0);
  }

  struct evconnlistener *ssl_listener = evhttp_bound_socket_get_listener(ssl_handle);
  evconnlistener_set_error_cb(ssl_listener, ssl_accept_error_cb);

  evhttp_set_cb(ev_ssl, "/ping", ping_handler, NULL);
    
  event_base_dispatch(evbase);

  evhttp_free(ev_ssl);
  event_base_free(evbase);
	
  return 0;
}
