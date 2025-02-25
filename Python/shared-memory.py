import mmap
import os
import ctypes
import posix_ipc
import time

if __name__ == "__main__":
        
    SHM_NAME = "/shared-memory"
    SIZE =  256

    SEM_NAME = "/semaphore"

    with open (f'/dev/shm{SHM_NAME}', "r+b") as f:
        memory = mmap.mmap (f.fileno(), 256)

        sem = posix_ipc.Semaphore(SEM_NAME)

        while True:
            sem.acquire()
            memory.seek(0)
            message = memory[:256].decode(errors="replace").rstrip("\x00")
            
            sem.release()
            print(message)

            time.sleep(1);

    memory.close()