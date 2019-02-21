//  Task sink
//  Binds PULL socket to tcp://localhost:5558
//  Collects results from workers via that socket

#include "zhelpers.h"

int main (int argc, char *argv []) 
{

    //  Number of ventilated tasks
    int nofTasks = (argc > 1) ? atoi(argv[1]) : 100;

    //  Prepare our context and socket
    void *context = zmq_ctx_new ();
    void *receiver = zmq_socket (context, ZMQ_PULL);
    zmq_bind (receiver, "tcp://*:5558");

    //  Wait for start of batch
    char *string_1 = s_recv (receiver);
    //free (string_1);

    //  Start our clock now
    int64_t start_time = s_clock ();

    //  Process 100 confirmations
    int task_nbr;
    for (task_nbr = 0; task_nbr < nofTasks; task_nbr++) {

        zmq_msg_t message;
        zmq_msg_init(&message);
        int size = zmq_msg_recv(&message,receiver,0);
        if (size == -1) break;
        char *string = (char*)malloc(size+1);
        memcpy(string,zmq_msg_data(&message),size);
        zmq_msg_close(&message);
        string[size] = 0;

        printf ("%s", string);
        //free (string);
        if ((task_nbr+1) % 5 == 0)
            printf ("\n");
        else
            printf ("");
        fflush (stdout);

    }
    //  Calculate and report duration of batch
    printf ("Total elapsed time: %d msec\n", 
        (int) (s_clock () - start_time));

    zmq_close (receiver);
    zmq_ctx_destroy (context);
    return 0;
}

