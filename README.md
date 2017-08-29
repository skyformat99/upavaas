# About This Project

A fast, simple, efficient web server written in c.  
It will soon support more platforms than bsd and linux.  
It will also grow to include multithreading.  
It will also support http and https requests once completed.

# About Project Model
Unlike most web-server models, upavaas avoids user-level thread pools.  
The parent daemon process will spawns one worker thread per core unless specified.  
Then the parent will also spawn one manager process to accept connections.  
The manager will basically block on accept until a new connection comes.  
The manager will then add the new connection to the worker thread with the least work.  
Each worker thread will use kqueue or epoll for connection events and handle them. (if kqueue or epoll are unavailable we will tragically use select())  
It is simple and efficient and will provide a nice set of options after the basic model is done.  
