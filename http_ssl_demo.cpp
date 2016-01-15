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
	evbuffer_add_printf(buf, "%s", ping.c_str());

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

	if (SSLeay() != OPENSSL_VERSION_NUMBER){ 
	
	}

	ev_ssl->ctx = get_ssl_ctx(certfile_url.c_str(),keyfile_url.c_str()); 
	ev_ssl->ssl_cb = bufferevent_openssl_socket_new;

	std::string ev_ssl_ip="192.168.1.10"; int ev_ssl_port = 8080;

	// evhttp_bind_socket_with_handle这个函数在原基础上追加一个参数，标示http server知否支持ssl(0:不支持 1:支持) 
	struct evhttp_bound_socket *ssl_handle = evhttp_bind_socket_with_handle(ev_ssl, ev_ssl_ip.c_str(), ev_ssl_port,1); 
	if(!ssl_handle){ 
		exit(0); 
	}
	
	struct evconnlistener *ssl_listener = evhttp_bound_socket_get_listener(ssl_handle); 
	evconnlistener_set_error_cb(ssl_listener, ssl_accept_error_cb);

	evhttp_set_cb(ev_ssl, "/ping", ping_handler, NULL);

	event_base_dispatch(evbase);

	evhttp_free(ev_ssl); event_base_free(evbase);

	return 0; 
}