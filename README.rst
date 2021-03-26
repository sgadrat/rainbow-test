Dependencies
============

* ca65: https://github.com/cc65/cc65
* gcc-6502-bits: https://github.com/itszor/gcc-6502-bits

``ca65`` and ``6502-gcc`` should be compiled and in PATH.

Build
=====

::

	$ GCC_SRC=/path/to/gcc-6502-bits make

The path to gcc-6502-bits src is used to find standard libraries compiled with ``6502-gcc``.
