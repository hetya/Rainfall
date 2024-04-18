First we start by finding the address of our buffer:
```Shell
(gdb) start AAAA                                                                                                                                                                                                   
The program being debugged has been started already.                                                                                                                                                               
Start it from the beginning? (y or n) y                                                                                                                                                                            
Temporary breakpoint 4 at 0x80485f8                                                                                                                                                                                
Starting program: /home/user/level9/level9 AAAA
(gdb) i proc map
process 6280
Mapped address spaces:

        Start Addr   End Addr       Size     Offset objfile
         0x8048000  0x8049000     0x1000        0x0 /home/user/level9/level9
         0x8049000  0x804a000     0x1000        0x0 /home/user/level9/level9
        0xb7cfa000 0xb7cfc000     0x2000        0x0 
        0xb7cfc000 0xb7d18000    0x1c000        0x0 /lib/i386-linux-gnu/libgcc_s.so.1
        0xb7d18000 0xb7d19000     0x1000    0x1b000 /lib/i386-linux-gnu/libgcc_s.so.1
        0xb7d19000 0xb7d1a000     0x1000    0x1c000 /lib/i386-linux-gnu/libgcc_s.so.1
        0xb7d1a000 0xb7d44000    0x2a000        0x0 /lib/i386-linux-gnu/libm-2.15.so
        0xb7d44000 0xb7d45000     0x1000    0x29000 /lib/i386-linux-gnu/libm-2.15.so
        0xb7d45000 0xb7d46000     0x1000    0x2a000 /lib/i386-linux-gnu/libm-2.15.so
        0xb7d46000 0xb7d47000     0x1000        0x0 
        0xb7d47000 0xb7eea000   0x1a3000        0x0 /lib/i386-linux-gnu/libc-2.15.so
        0xb7eea000 0xb7eec000     0x2000   0x1a3000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7eec000 0xb7eed000     0x1000   0x1a5000 /lib/i386-linux-gnu/libc-2.15.so
        0xb7eed000 0xb7ef0000     0x3000        0x0 
        0xb7ef0000 0xb7fc8000    0xd8000        0x0 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fc8000 0xb7fc9000     0x1000    0xd8000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fc9000 0xb7fcd000     0x4000    0xd8000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fcd000 0xb7fce000     0x1000    0xdc000 /usr/lib/i386-linux-gnu/libstdc++.so.6.0.16
        0xb7fce000 0xb7fd5000     0x7000        0x0 
        0xb7fdb000 0xb7fdd000     0x2000        0x0 
        0xb7fdd000 0xb7fde000     0x1000        0x0 [vdso]
        0xb7fde000 0xb7ffe000    0x20000        0x0 /lib/i386-linux-gnu/ld-2.15.so
        0xb7ffe000 0xb7fff000     0x1000    0x1f000 /lib/i386-linux-gnu/ld-2.15.so
        0xb7fff000 0xb8000000     0x1000    0x20000 /lib/i386-linux-gnu/ld-2.15.so
        0xbffdf000 0xc0000000    0x21000        0x0 [stack]
(gdb) info stack
#0  0x080485fe in main ()
(gdb) info frame
Stack level 0, frame at 0xbffff740:
 eip = 0x80485fe in main; saved eip 0xb7d604d3
 Arglist at 0xbffff738, args: 
 Locals at 0xbffff738, Previous frame's sp is 0xbffff740
 Saved registers:
  ebp at 0xbffff738, eip at 0xbffff73c
(gdb) find 0xbffdf000, 0xbfffffff, "AAAA"
0xbffff90e
1 pattern found.
```
address stack end - 1 