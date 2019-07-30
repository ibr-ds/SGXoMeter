# SGX-AppsBench

### **Description**
-------------------

This is originally a project thesis and its target is to implement multiple application benchmarks for SGX 

### **Prerequisites, Setup & Run**
----------------------------------

1. SGX driver & SGX-SDK version 2.3  
2. Go to *sgx* directory and create **"build"** folder. Then open a terminal inside the *build* folder and execute ***"cmake-gui .."*** .
3. After you chose the modules to test, execute ***"make"*** in order to build the Benchmarking tool.
4. ***"Ctrl+C"*** would stop the benchmarks and print out the results or you can start the benchmark with a desired number of iterations OR for a desired warmup and runtime phases.
5. Python 3 is required in case you want to plot the generated benchmark data from the tool. The tool can also be configured to either directly write the generated data in a text file or just print the results out to the standard output file.
The latter also allows to pipe the outputed results into a file for later reviews/plots.


### **Features & Configurations**
---------------------------------
The benchmarking tool is implemented in a modular way. Such that, each each test is a module that can be added or removed if desired.
In order to do so, there exists multiple cmake files, through which you can configure the whole tool to only compile&prepare the desired modules(tests).

##### *GlobalVariables.cmake*
Here you can configure the runtime options of the tool. For example: compile with debug outputs, enable the desired features or set some global variables(number of benchmark iterations, warmup/runtime phase) etc...

##### *TestVariables.cmake*
Here you can choose the wanted applications/modules to benchmark and set the possible runtime flags for some of them. 
It also offers the opportunity for third developer parties to benchmark their applications/function payloads inside enclaves by offering an "interface"-like function ("customtest.c") 
that can be implemented as desired(as long as SGX driver/SDK support the used libraries/operations).

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