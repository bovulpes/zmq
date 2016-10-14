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
    zmq_connect (receiver, "tcp://localhost:5557");

    //  Socket to send messages to
    void *sender = zmq_socket (context, ZMQ_PUSH);
    zmq_connect (sender, "tcp://localhost:5558");

    //  Identify the worker
    int workerID = (argc > 1) ? atoi(argv[1]) : 0;

    //  Process tasks forever
    int task_nbr = 0;
    char string_1[10];
    while (1) {
        char *string = s_recv (receiver);
        printf ("w%d:%s",workerID,string);     //  Show progress
        fflush (stdout);
        s_sleep (atoi (string));    //  Do the work
	sprintf(string_1,"%010d ",workerID*1000000+atoi(string));
        s_send (sender, string_1);        //  Send results to sink
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
