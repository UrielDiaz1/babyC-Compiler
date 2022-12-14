## babyC-Compiler
A compiler for babyC.

The program was developed and tested in Ubuntu 22.04.1 & the ECS coding terminal.

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
    
4. Drag and drop the *bcc* into the testing directory. 

5. To run the program on one of the testing files and have the output be displayed
   in the terminal, run the following command:<br />
   `./bcc <name_of_file>.bc`
    
6. To run the program on one of the testing files and have the AST generation output
   be saved in a file, run the following command:<br />
   `./bcc <name_of_file>.bc > <name_of_file>.out`
    
7. Example:<br />
   `./bcc test1.bc > test1.out`

8. The ILOC is generated in an *iloc* file. The *iloc* filename will be the same as the
   *bc* filename. For example, *./bcc test1.bc* will generate a *test1.iloc* file. Be
   warned that if the iloc file already exists, its content will be replaced.

8. To display the differences between two files, the following command can be used:<br />
   `diff <name_of_file>.<file's extension> <name_of_file>.<file's extension>`

9. Example:<br />
   `diff test1.iloc test1_ref.iloc`

# Cleaning Files
1. To delete some of the auto-generated or junk files, run the following command:<br />
   `make clean`

2. The make clean command will only delete files with the following extensions:
   - .o
   - .out