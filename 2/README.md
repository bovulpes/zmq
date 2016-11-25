Can be run locally, with sampler, processor and sink on the same node or 
remote, on three machines (OpenStack@CC) with IPs:

Remote 1 = 1 sampler, 1 processor, 1 sink

```bash
172.17.5.6  sampler = ./taskvent
172.17.5.7  worker  = ./taskwork
172.17.5.8  sink    = ./tasksink
```

Remote 2 = 1 sampler, 2 processors, 1 sink

```bash
172.17.5.6  sampler = ./taskvent
172.17.5.7  worker1 = ./taskwork 1
172.17.5.8  worker2 = ./taskwork 2
172.17.5.6  sink    = ./tasksink
```

- **taskvent**

- send start of batch message

- local

```bash
zmq_connect (sink, "tcp://localhost:5558");
```

- remote 1

```bash
zmq_connect (sink, "tcp://172.17.5.8:5558");
```

- remote 2

```bash
zmq_connect (sink, "tcp://localhost:5558");
```

- **taskwork**

- receive messages

- local

```bash
zmq_connect (receiver, "tcp://localhost:5557");
```

- remote

```bash
zmq_connect (receiver, "tcp://172.17.5.6:5557");
```
- send messages

- local

```bash
zmq_connect (sender, "tcp://localhost:5558");
```

- remote 1

```bash
zmq_connect (sender, "tcp://172.17.5.8:5558");
```

- remote 2

```bash
zmq_connect (sender, "tcp://172.17.5.6:5558");
```

