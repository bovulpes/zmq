The code examples (from the book "ZeroMQ" by Peter Hintjens, O'Reilly)
----------------------------------------------------------------------

https://github.com/imatix/zguide/tree/master/examples

Compiling the code examples
---------------------------

```bash
g++ -o hwserver -lzmq hwserver.c
```

The examples
------------

- **0**, print the zmq library version
- **1**, one server which replies to the request of one client
- **2**, a pushing server, a processing client and a sink collecting the results
- **3**, a publishing server and a filtering client
