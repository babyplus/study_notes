# How The Kernel Sources Are Arranged

* arch: The arch subdirectory contains all of the architecture specific kernel code. It has further subdirectories, one per supported architecture, for example i386 and alpha.
* block: The include subdirectory contains most of the include files needed to build the kernel code. It too has further subdirectories including one for every architecture supported. The include/asm subdirectory is a soft link to the real include directory needed for this architecture, for example include/asm-i386. To change architectures you need to edit the kernel makefile and rerun the Linux kernel configuration program.
* certs: 
* crypto: 
* Documentation: 
* drivers: All of the system's device drivers live in this directory. They are further sub-divided into classes of device driver, for example block.
* fs: All of the file system code. This is further sub-divided into directories, one per supported file system, for example vfat and ext2.
* include: 
* init: This directory contains the initialization code for the kernel and it is a very good place to start looking at how the kernel works.
* ipc: This directory contains the kernels inter-process communications code.
* kernel: The main kernel code. Again, the architecture specific kernel code is in arch/*/kernel.
* lib: This directory contains the kernel's library code. The architecture specific library code can be found in arch/*/lib/.
* LICENSES: 
* mm: This directory contains all of the memory management code. The architecture specific memory management code lives down in arch/*/mm/, for example arch/i386/mm/fault.c.
* net: The kernel's networking code.
* samples: 
* scripts: This directory contains the scripts (for example awk and tk scripts) that are used when the kernel is configured.
* security: 
* sound: 
* tools: 
* usr: 
* virt: 
  

* COPYING: 
* CREDITS: 
* Kbuild: 
* Kconfig: 
* MAINTAINERS: 
* Makefile: 
* README: 


