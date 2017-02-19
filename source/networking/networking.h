#include <common.h>
#ifndef NETWORKING_H
#define NETWORKING_H

class Networking
{
public:
    Networking(bool server);
    Networking(udsConnectionType ctype, char* pphrase, u32 wcommid, bool server);

    Result Init();
    udsNetworkScanInfo* Scan();
	Result Connect(udsNetworkScanInfo* network, udsConnectionType cType);
	Result RecieveData(void* buf, size_t bufsize);
	Result SendData(void* buf, size_t bufsize);

    void Fini();

	size_t total_networks = 0;
private:
	bool server;

    Result ret=0;
	u32 con_type=0;

	u32 *tmpbuf;
	size_t tmpbuf_size;

	u8 data_channel = 1;
	udsNetworkStruct networkstruct;
	udsBindContext bindctx; //Bindctx to recieve from server on channel 1
	udsNetworkScanInfo *networks = NULL;
	udsNetworkScanInfo *network = NULL;



	u32 recv_buffer_size = UDS_DEFAULT_RECVBUFSIZE;
	u32 wlancommID = 0x48126544;//Unique ID, change this to your own.
	char *passphrase = "allahuackbar";//Change this passphrase to your own. The input you use for the passphrase doesn't matter since it's a raw buffer.

	udsConnectionType conntype = UDSCONTYPE_Client;

	u32 transfer_data, prev_transfer_data = 0;
	size_t actual_size;
	u16 src_NetworkNodeID;
	u32 tmp=0;
	u32 pos;

	udsNodeInfo tmpnode;

	u8 appdata[0x14] = {0x69, 0x8a, 0x05, 0x5c};
	u8 out_appdata[0x14];

	char tmpstr[256];
};

#endif