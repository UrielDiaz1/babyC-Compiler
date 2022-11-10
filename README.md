## babyC-Compiler
A compiler for babyC.

The program was developed and tested in Ubuntu 22.04.1

# Environment Setup (Linux Machine)
1. Open a terminal.
2. Update current packages by using the following command:<br />
   `sudo apt-get update`
   
3. Install Flex, a tool that generates a scanner that will help us recognize lexical patterns in text:<br />
   `sudo apt-get install flex`
   
4. Install Bison, the parser generator:<br />
   `sudo apt-get install bison`
   
5. A compiler, such as GCC is needed. To ensure its installed, along with other
   useful tools such as `make`, run the following command:<br />
   `sudo apt-get install build-essential`
   
6. To specifically install make, run the following command:<br />
   `sudo apt-install make`
   
# Running the Program
1. Open a terminal in the program's directory, where the makefile is located.

2. Run the following command to compile and create the executable file *bcc*:<br />
   `make`
   
3. In the circumstance that you don't have the appropriate environment, a pre-built
   executable file will be provided. It is called *bcc*.
    
4. Drag and drop the "bcc" into the tests folder. 

5. To run the program on one of the testing files and have the output be displayed
   in the terminal, run the following command:<br />
   `./bcc <name_of_file>.bc`
    
6. To run the program on one of the testing files and have the output be saved in
   a file, run the following command:<br />
   `./bcc <name_of_file>.bc > <name_of_file>.out`
    
7. Example:<br />
   `./bcc test1.bc > test1.out`
