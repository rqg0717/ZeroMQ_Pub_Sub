
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zmq.h"
 
int main()
{
    int count = 0;
    int rc = -1;
    char msg[32] = { 0 };
    char *filter = "message ";
    void *context = zmq_ctx_new();
    void *subscriber = zmq_socket(context, ZMQ_SUB);

    if (subscriber != NULL) {
        rc = zmq_bind(subscriber, "tcp://*:5555");
        if (rc == 0) {
            rc = zmq_setsockopt (subscriber, ZMQ_SUBSCRIBE, filter, strlen (filter));
            for(;;)
            {
                if (count >= 1000) {
                    break;
                }
                rc = zmq_recv(subscriber, msg, sizeof(msg) - 1, 0);
                if (rc > 0)
                {
                    printf("%s\n", msg);
                }
            }
        }
        
    }
 
    if (subscriber != NULL) {
        zmq_close (subscriber);
        subscriber = NULL;
    }
    
    if (context != NULL) {
        zmq_ctx_destroy (context);
    }
 
    return 0;
}
