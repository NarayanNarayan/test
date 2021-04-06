
	fd_set curr_sock,ready_sock;
	struct timeval timeout;

	struct {
		char name[24];
		char ip[16];
		int port;
	} user_info[5];



	typedef struct {
		char  name[24];
		char ip[16];
		int port;
		int fd;
	}connection;
