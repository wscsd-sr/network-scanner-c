# C Language Network Asset Scanner

A lightweight TCP port scanner written in pure C for network asset detection and internal network security inspection.

## Features
- TCP full-connection scan
- Common service recognition (21,22,80,443,3306,6379,8080)
- Support IP + port range scanning
- Cross-platform (Linux / Windows with MinGW)
- Simple, clean, no third-party libraries

## Usage
### Compile
```bash
gcc scan.c -o scan
