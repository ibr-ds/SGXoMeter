# SGXoMeter

### **Description**
-------------------

This is originally a project thesis and its target is to implement multiple application benchmarks for SGX. <br/>
It supports single and multithreaded benchmark executions.


### **Paper**
-------------

The paper will be presented at Eurosec 2021 and is available here: https://www.ibr.cs.tu-bs.de/users/mahhouk/papers/eurosec2021.pdf and https://doi.org/10.1145/3447852.3458722

Please cite us if you use our work in your research:

```
@inproceedings{mahhouk2021EuroSec,
author = {Mahhouk, Mohammad and Weichbrodt, Nico and Kapitza, R\"{u}diger},
title = {SGXoMeter: Open and Modular Benchmarking for Intel SGX},
booktitle = {Proceedings of the 14th European Workshop on Systems Security},
series = {EuroSec '21},
year = {2021},
doi = {10.1145/3447852.3458722}
}
```

### **Prerequisites, Setup & Run**
----------------------------------
1. SGX driver & SGX-SDK [version 2.12](https://download.01.org/intel-sgx/sgx-linux/2.12/distro/ubuntu20.04-server/)
  - make sure you followed the installation steps of the SGX-SDK [here](https://github.com/intel/linux-sgx). 
  - run the ./download_prebuilt.sh from there and then copy the mitigation tools to the current OS distribution as explained in the [README](https://github.com/intel/linux-sgx/blob/master/README.md#prerequisites).
2. Developped and tested on Ubuntu 18 & 20 LTS
3. Go to *sgx* directory and create **"build"** folder. Then open a terminal inside the *build* folder and execute ***"cmake-gui .."*** .
4. After you chose the modules to test, execute ***"make"*** in order to build the Benchmarking tool.
5. ***"Ctrl+C"*** would stop the benchmarks and print out the results or you can start the benchmark with a desired number of iterations OR for a desired warmup and runtime phases.
6. Python 3 is required in case you want to plot the generated benchmark data from the tool. The tool can also be configured to either directly write the generated data in a text file or just print the results out to the standard output file.
The latter also allows to pipe the outputed results into a file for later reviews/plots.
7. For more usage instructions execute the binary with ***"-h"*** or ***"--help"*** to see the possible execution commands


### **Features & Configurations**
---------------------------------
The benchmarking tool is implemented in a modular way. Such that, each each test is a module that can be added or removed if desired.

In order to do so, there exists multiple cmake files, through which you can configure the whole tool to only compile&prepare the desired modules(tests).

##### *sgx/CMakeLists.txt*
Here are where the environment variables are set(for sgx, openssl, argon2 etc..) and its the first cmake file of the cmake hierarchy (Level 1). 

##### *ConfigSGX.cmake & FindSGXSDK.cmake*
Here ,as the name tells their content, the SGX-SDK libraries and configurations are set and prepared for later usages for building the enclave and signing it. 

These two cmake files are included in the sgx/CMakeLists.txt


##### *test-app/CMakeLists.txt*
Here exists some of macros definitions that will be used later at the module selection. It also contains global settings (like variables for common headers & utilities pathes etc.. ).

Furthermore, it includes Global/TestVariables.cmake and its the second cmake file of the hierarchy (Level 2).

##### *GlobalVariables.cmake*
Here you can configure the runtime options of the tool. For example: compile with debug outputs, enable the desired features or set some global variables(number of benchmark iterations, warmup/runtime phase) etc...

##### *TestVariables.cmake*
Here you can choose the wanted applications/modules to benchmark and set the possible runtime flags for some of them. 

It also offers the opportunity for third developer parties to benchmark their applications/function payloads inside enclaves by offering an "interface"-like function ("customtest.c") 
that can be implemented as desired(as long as SGX driver/SDK support the used libraries/operations).

##### *app/CMakeLists.txt*
Here is where the untrusted part of the sgx benchmark application is built and contains the dependencies and necessary src files and libraries.

This is the third cmake file of the hierarchy (Level 3).

##### *enclave/CMakeLists.txt*
Here is where the trust part of the sgx benchmark application is built and contains the dependencies and necessary src files and libraries. 

Also, it includes the building of the shared library and enclave signing. This is the third cmake file of the hierarchy (Level 3).

##### *baseline/CMakeLists.txt*
Here is where the baseline part of the benchmark application is built. This runs the same chosen test modules but with no sgx implementation.

This is the third cmake file of the hierarchy (Level 3).

### **Available Benchmark Applications**
-----------------------------------------
Currently there are couple modules(tests) available:

1.  RSA key generation
2.  Custom RSA key generation
3.  RSA Crypto tests (encryption and decryption of messages)
4.  RSA Signing tests
5.  Custom SHA256 test
6.  Elliptic curve key generation
7.  RSA tests. This includes: generating different public/private keys and encrypting and decrypting a plain text
8.  Elliptic curve tests similar to the RSA tests
9.  Elliptic curve with diffie hellman method tests
10. Elliptic curve with digital signature algorithm(DSA) tests
11. Diffie Hellman tests
12. SHA 256 & SHA 1 tests
13. SGX-Port version of "seeq" library fpr DNA pattern search
14. Custom test. Which can be implemented by third dev parties for their own benchmarking reasons
15. SGXSDK AES-GCM encryption & decryption on in-enclave or external buffers


### **Known Issues** 
---------------------
Since the start of this project till now, many changes happened (e.g. new kernels, libc versions and other SGX-SDK updates)

1. The structure and CMake files need to be refined more to fully support the modularity as intended too.

### **Detected and Reported Issues for Intel SGX-SDK**
-------------------------------------------------------
1. detected an error with sgx_tcmalloc at runtime in SGX simulation mode with SGX-SDK version > 12 and opened an [issue](https://github.com/intel/linux-sgx/issues/670) for it.
2. reported large performance degredation between SGX-SDK 2.7 and 2.12 [(link)](https://github.com/intel/linux-sgx/issues/679)


### **Future Work and Planned Ideas**
--------------------------------------
A list of new features and ideas we want to extend the framework with:
- automate the building process by shifting it to dockers 

### **Addition Marcel**
-------------------------
GrapheneBench ausführen:
1. Sichergehen, dass sudo sysctl vm.mmap_min_addr=0 ausgeführt wurde
2. make (im GrapheneSGX Ordner)
3. graphene-sgx GrapheneBench

