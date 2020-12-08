# Cm_VM_Team7

Soen 422 - Cm VM project Team 7

Hau Gilles Che 
Carl Neil Cortes
Akhilesh Warty


Test files and informations:

Task0_AUnit:
  -Only contains Aunit executable built/ported to be used for Task1
  
Task1_Host_VM_Port: 
  -cm executable along with the given Test Suite of 12 precompiled programs. 
  -runCodePatterns.bat: script to run the precompiled tests against the host port of the Cm VM and validated with Aunit
  -source code of vm port on host. Ported on Windows using gcc and conditional compilation flag -D ConsoleOutputWithPrintf

Task3_Tests_Files:
  - .hex bsl/hal implementation test files mainly for VM Operand Stack & console output 
  - Compiled & tested using batch scripts in root directory "testBslXtoa.bat", "testHalCout.bat", "testVMOperandStack.bat"

Task4_Tests_Files:
  - .hex vm port on target with pre-allocated program (T11.exe from original test suite) 
  - admin_testPrecompiledProgram.c: version of admin.c file with the bytes representing T11.exe pre-allocated and executed by the VM used to produce vmport.hex
  - Compiled & tested using batch script in root directory "testStaticProgram.bat"
  
Task5_Tests_Files:
  -.hex vm port on target with serial memory loader implementation.
  - hal_TestLoader.c: version of admin.c used for testing of Task5 *modified from original given hal_TestLoader.c*
  - Compiled & tested using batch script in root directory "testLoader.bat"
