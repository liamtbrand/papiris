# PapIris
The purpose of papiris is to use image recognition to index pdf documents by their contents. Papiris leverages the operating systems search functionality, providing the operating system with data to search. Developed and tested on MacOS.

TODO write this..

The job of the papiris daemon is to crawl the file system and inspect the files.
A database will be built containing references to the files on disk.
Files will be created in a local area which contain metadata.
When the papiris files are opened, they are opened by the daemon.
The daemon will then check the database for the file, and then open the correct file.
