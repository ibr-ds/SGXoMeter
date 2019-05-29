# SGX-AppsBench

### **Description**
-------------------

This is originally a project thesis and its target is to implement multiple application benchmarks for SGX 

### **Prerequisites, Setup & Run**
----------------------------------

1. SGX driver & SGX-SDK version 2.3  
2. ***Source*** [Path of SGX-SDK]/environment   (default: source /opt/intel/sgxsdk/environment)
3. Go to *test-app* directory and execute ***make all***. Then you can start the tool by simply running ***./TestApp***
4. ***Ctrl+C*** would stop the benchmarks and print out the results or you can start the benchmark with a desired number of iterations
5. Python 3 is required in case you want to play the generated benchmark data from the tool. The tool can also be configured to either directly write the generated data in a text file or just print the results out to the standard output file.
The latter also allows to pipe the outputed results into a file for later reviews/plots.


### **Features & Configurations**
---------------------------------
The benchmarking tool is implemented in a modular way. Such that, each each test is a module that can be added or removed if desired.
In order to do so, there exists two header files "GobalMacros.h" & "TestMacros.h", through which you can configure the whole tool to only compile&prepare the desired modules(tests).

##### *GlobalMacros*
Here you can configure the runtime options of the tool. For example: compile with debug outputs, enable the desired features or set some global variables(number of benchmark iterations) etc...

##### *TestMacros*
Here you can choose the wanted applications to benchmark and set the possible runntime flags for some of them. 
It also offers the opportunity for third developer parties to benchmark their applications/function payloads inside enclaves by offering an "interface"-like function ("customtest.c") 
that can be implemented as desired(as long as SGX driver/SDK supports the used libraries/operations).

### **Available Benchmark Applications**
-----------------------------------------
Currently there are couple modules(tests) available:

1.  RSA key generation
2.  Elliptic curve key generation
3.  RSA tests. This includes: generating different public/private keys and encrypting and decrypting a plain text
4.  Elliptic curve tests similar to the RSA tests
5.  Elliptic curve with diffie hellman method tests
6.  Elliptic curve with digital signature algorithm(DSA) tests
7.  Diffie Hellman tests
8.  SHA 256 & SHA 1 tests
9.  Multi threaded tests with crypto rw locks 
10. SGX-Port version of "seeq" library fpr DNA pattern search
11. Custom test. Which can be implemented by third dev parties for their own benchmarking reasons