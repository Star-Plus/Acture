# What is Acture

Acture is a media manipulation engine with interactive features and generic functions.

## How Acture is working

User only defines a series of steps sequential or in parallel. Acture provides an interface to feed it with a pipeline of execution nodes, then gets a result of the final media buffer.

### How does the pipeline (Kitchen) work

A pipeline consists of execution nodes, each node takes an input of asset buffer, and parameters (fixed/dynamic). And node outputs a single or multiple asset buffers based on the execution behaviour and configuration. Nodes internal behaviour is loaded with prebuilt executable (written by other users/contributers).

### What defines a node

A node is a container of a script that gets executed with extra information

- Input buffers (ex:- one image or more)
- Control arguments: the parameters those get changed by edge user on the media player.

A node outputs one or more asset buffers based on its configuration.

### How to contribute in nodes

Acture comes with a package manager that builds and composes nodes wirtten by the community. It will recognize Cmake as a start and will be extended to other languages later.
