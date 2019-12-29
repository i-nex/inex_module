 <eloaders_at_linux_pl>
===========

The module was written for the needs of the I-Nex program to improve the retrieval of information about processors.
The module is for testing purposes only.

Installation:

- `make`
- `make install`

(`make install` may fail if your kernel has never been recompiled, in which case you can just keep
the `inex.ko` file around.

Usage:

- `modprobe inex` (Or if `make install` failed, `insmod inex.ko`)
- `echo -n "Intel(R) Core(TM) i7-10710U CPU @ 1.10GHz" >/sys/modules/inex/parameters/cpuname`
