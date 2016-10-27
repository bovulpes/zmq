The code examples (from the book ZeroMQ by Peter Hintjens, O'Reilly)
--------------------------------------------------------------------

https://github.com/imatix/zguide/tree/master/examples

Compiling the code examples
---------------------------

```bash
g++ -o hwserver -lzmq hwserver.c
```

The examples
------------

- **0**, print the zmq library version

```bash
./version
Current 0MQ version is 4.1.4
```
- **1**, one server which replies to the request of one client (REQ, REP)

run in two terminals the server and the client

```bash
./hwserver
./hwclient
```

- **2**, a publishing server, a client which subscribes and publishes further and a sink which subscribes and collects the results (PUSH, PULL)

start the workers

```bash
source workers.sh
```

start the sink

```bash
./tasksink
```

start the ventilator (sampler)

```bash
./taskvent
(enter)
```

- **3**, a publishing server and a filtering client (PUB, SUB)

start the server

```bash
./wuserver
```

start the client with a zip code to filter

```bash
./wuclient 63000
```

