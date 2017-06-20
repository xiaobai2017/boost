#ifndef TCP_MSG_DEF_H
#define TCP_MSG_DEF_H

struct msg_head
{
	unsigned int type;
	unsigned int size;
	unsigned int chksum;
};
#define MAX_BODY_SIZE  1024

#endif //TCP_MSG_DEF_H
