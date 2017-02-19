#include <networking.h>

Networking::Networking(udsConnectionType ctype, char* pphrase, u32 wcommid)
{
    this.udsConnectionType = ctype;
    this.passphrase = pphrase;
    this.wlancommID = wcommid;
    this.server = server;
}

Networking::Networking(bool server)
{
    this.server = server;
}

Result Networking::Init()
{
    this.ret = udsInit(0x3000,NULL); //Magic RAM size and use the 3DS username as the server name
    if(R_FAILED(ret))
    {
        printf("udsInit failed.");
        return this.ret;
    }
    
    strncpy((char*)&appdata[4], "Test appdata.", sizeof(appdata)-1);
    return this.ret;
}

void Networking::Fini()
{
    udsExit();
}

//THIS RETURNS AN ARRAY! BE VERY CAREFUL NOT TO CONFUSE THIS.
udsNetworkScanInfo* Networking::Scan()
{
    this.tmpbuf_size = 0x4000;
    this.tmpbuf = malloc(this.tmpbuf_size);
    if(this.tmpbuf == NULL)
    {
        return NULL;
    }
    this.total_networks = 0;
    memset(this.tmpbuf,0,sizeof(this.tmpbuf_size));
    this.ret = udsScanBeacons(this.tmpbuf,this.tmpbuf_size, &this.networks, &this.total_networks, this.wlancommID, 0, NULL, false);
    return this.networks;
}

Result Networking::Connect(udsNetworkScanInfo* network, udsConnectionType cType)
{
    this.network = network;
    this.conntype = cType;

    ret = udsConnectNetwork(this.network->network,this.passphrase,strlen(passphrase)+1,&this.bindctx,UDS_BROADCAST_NETWORKNODEID, this.conntype, this.data_channel, this.recv_buffer_size);
    if(!R_FAILED(ret))
        free(networks);
    return ret;
}

Result Networking::RecieveData(void* buf, size_t bufsize)
{
    udsBindContext tmpbindctx;
    if(server)
    {
        //udsBind(&tmpbindctx,)
    }
    else
    {}
    this.ret = udsPullPacket(&this.bindctx, buf, bufsize, &this.actual_size, &this.network);
    return this.ret;
}

Result Networking::SendData(void* buf,size_t bufsize)
{
    u16 netnode;
    u8 tmpdatchan;
    u8 tmpflags;
    if(server)
    {
        netnode = UDS_BROADCAST_NETWORKNODEID;
        tmpdatchan = 1;
        tmpflags = UDS_SENDFLAG_Broadcast;
    }
    else
    {
        netnode = UDS_HOST_NETWORKNODEID;
        tmpdatchan = 2;
        tmpflags = UDS_SENDFLAG_Default;
    }
    udsSendTo(netnode,tmpdatchan,tmpflags,buf,bufsize);
}