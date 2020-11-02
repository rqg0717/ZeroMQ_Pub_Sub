
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "zmq.h"
 
int main()
{
    int count = 0;
    int rc = -1;
    char msg[32] = { 0 };
    void *context = zmq_ctx_new();
    void *publisher = zmq_socket(context, ZMQ_PUB);

    if (publisher != NULL) {
        rc = zmq_bind(publisher, "tcp://*:5555");
        for(;;)
        {
            if (count > 1000) {
                break;
            }
            snprintf(msg, sizeof(msg), "message #%d.", count++);
            rc = zmq_send(publisher, msg, strlen(msg) + 1, 0);
    
            sleep(1);
        }
    }
 
    if (publisher != NULL) {
        zmq_close (publisher);
        publisher = NULL;
    }

    if (context != NULL) {
        zmq_ctx_destroy (context);
    }
 
    return 0;
}
