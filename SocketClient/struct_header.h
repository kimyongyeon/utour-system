#define MSG_SiZE   32
#define MSG_HEADER 8

struct MsgBuff
{
	int		 msgID;
	int		 data_sz;
	char     data[MSG_SiZE];
};
