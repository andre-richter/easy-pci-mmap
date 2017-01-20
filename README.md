# easy-pci-mmap
C++ class for easy read and write of PCI(e) device BARs via mmap

## Usage
See `example/example.cpp`, it should explain most.

An easy way to get Vendor and Device IDs of your PCI(e) device is to compare `lspci -n` output with `lspci` output.
For example,
```bash
00:1f.2 0106: 8086:8c02 (rev 05)
```
0x8086 would be the Vendor ID, and 0x8c02 the Device ID.
