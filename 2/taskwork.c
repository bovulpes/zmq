//  Task worker
//  Connects PULL socket to tcp://localhost:5557
//  Collects workloads from ventilator via that socket
//  Connects PUSH socket to tcp://localhost:5558
//  Sends results to sink via that socket

#include "zhelpers.h"

int main (int argc, char *argv []) 
{
    //  Socket to receive messages on
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    //zmq_connect (receiver, "tcp://172.17.5.6:5557");
    zmq_connect (receiver, "tcp://localhost:5557");

    //  Socket to send messages to
    void *sender = zmq_socket (context, ZMQ_PUSH);
    //zmq_connect (sender, "tcp://172.17.5.8:5558");
    zmq_connect (sender, "tcp://localhost:5558");

    //  Identify the worker
    int workerID = (argc > 1) ? atoi(argv[1]) : 0;

    //  Process tasks forever
    int task_nbr = 0;
    char string_1[8];
    while (1) {

        zmq_msg_t message;
        zmq_msg_init(&message);
        int size = zmq_msg_recv(&message,receiver,0);
        if (size == -1) break;
        char *string = (char*)malloc(size+1);
        memcpy(string,zmq_msg_data(&message),size);
        zmq_msg_close(&message);
        string[size] = 0;

        printf ("w%d:%s ",workerID,string);     //  Show progress
        fflush (stdout);
        s_sleep (atoi (string));    //  Do the work
        sprintf(string_1,"%06d ",workerID*10000+atoi(string));

        zmq_msg_t message_1;
        zmq_msg_init_size(&message_1,strlen(string_1));
        memcpy(zmq_msg_data(&message_1),string_1,strlen(string_1));
        int size_1 = zmq_msg_send(&message_1,sender,0);
        zmq_msg_close(&message_1);

        free (string);
        if ((task_nbr+1) % 5 == 0)
            printf ("\n");
        else
            printf ("");
        task_nbr++;
    }
    zmq_close (receiver);
    zmq_close (sender);
    zmq_ctx_destroy (context);
    return 0;
}

