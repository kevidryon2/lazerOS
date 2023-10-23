# lazerOS

An open source operating system for 386+ VGA computers.

## Requirements

- A 386 processor or newer;
- At least 2MB of RAM;
- A 16-bit ISA bus;
- A hard drive, at least 20MB;
- Support for VGA video mode 03h.

**Note**: lazerOS does **not** work on Bochs, at least with my compilation settings.

## Technical Details

lazerOS is divided into four main parts:

- The **Bootloader** or **Bootstrap**, which comunicated with the BIOS to obtain a memory map, and then loads and runs the **Lower Kernel**.

- The **Lower Kernel**, which contains a basic **SATA** and **lbFS** driver to load the **Higher Kernel**, which is stored in the **filesystem**.

- The **Higher kernel**, which deals with advanced stuff like processes, memory management, the VFS, various other drivers, etc.

- The **Userspace**, which contains all the apps such as the shell, basic utilities, etc.

### lbFS

A disk on which lazerOS is installed (lazerOS cannot be installed in a partition) is formatted with lbFS (LazerOS Boot FileSystem).

The first 4 sectors are dedicated to the bootstrap; then, there is a header sector which specifies the number of files in the root directory, the size of the Lower Kernel in sectors, etc., and then the Lower Kernel itself.

After the Lower Kernel, there is the Root Directory itself; it the root directory, the file "kernel" gets loaded into memory as the Higher Kernel.