import mmap
import os
import ctypes

if __name__ == "__main__":
    class Message(ctypes.Structure):
        _fields_ = [
        ("id", ctypes.c_int),
        ("message", ctypes.c_char * 256),
        ("language", ctypes.c_int)
    ]
        
    SHM_NAME = "/shared-memory"
    SIZE =  256 ##ctypes.sizeof(Message)

    with open (f'/dev/shm{SHM_NAME}', "r+b") as f:
        memory = mmap.mmap (f.fileno(), 256)

        memory.seek(0)
        message = memory[:256].decode().strip()

        print(message)

    memory.close()