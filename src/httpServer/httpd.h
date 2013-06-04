#ifndef HTTPD__H
#define HTTPD__H


struct SimpleHTMLService {
	virtual ~SimpleHTMLService(){}
	virtual void callback(const char * command, const char *parameters, char * buffer, int buffer_size) = 0;
};

int server_main(SimpleHTMLService *service);
void set_shutdown_flag(void);

#endif
