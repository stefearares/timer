# timer
A linux kernel module that measures the time(in seconds) since it was loaded. The timer in seconds is made using jiffies and HZ.

COMMANDS(or as root):

$ sudo insmod time.ko
$ sudo dmesg -c
$ dmesg
$ cat /proc/time
$ sudo rmmod time
$ dmesg
