#include "prabi.h"
/**
 * Current goal:
 * 1. Enstablish connection from machine A and B
 * 2. machine A listen on 0.0.0.0:port and forword pass all packet to machine B:port
 * 3. machine B resend all packet from A to an ipaddress:port
 */

/**
prabi -s 0.0.0.0:1045 # listen at 0.0.0.0:1045 
prabi -p 0.0.0.0:1045 # connect to server
*/
int main(int argc, char* argv[])
{
    InitNetworkEnv();

    auto splt = strstr(argv[2], ":");
    auto port = atoi(splt+1);
    auto addrl = splt - argv[2] ;
    auto ipaddr = new char[addrl + 1]{ 0 };
    memcpy(ipaddr, argv[2], addrl);
    // for test purpose
    try
    {
        if (strcmp(argv[1], "-s") == 0)
        {
            SOCKET server = PrabiStartServer(ipaddr, port);
            PrabiStartServerDeamon(server);
        }
    }
    catch (const std::exception& e)
    {
        printf("%s", e.what());
    }

}