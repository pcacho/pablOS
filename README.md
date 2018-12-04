# pablOS
RISC-V RTOS

Target: SiFive HiFive1

License: 3-Clause BSD License

Install:

1) Clone SiFive HiFive1 repo

	-> git clone --recursive https://github.com/sifive/freedom-e-sdk.git

	-> cd freedom-e-sdk

	-> make tools

2) Clone pablOS to freedom-e-sdk/software

	-> cd freedom-e-sdk/software

	-> git clone https://github.com/pcacho/pablOS.git

3) Compile using the RISC-V cross-compiler

	-> make software PROGRAM=pablOS

