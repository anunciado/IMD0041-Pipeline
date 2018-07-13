# Pipeline

The pipeline simulator will be the implementation of a tool that simulates pipeline execution 5 stages of MIPS. The simulator will receive as input a set of instructions in Assembly MIPS, simulates the execution of these instructions considering all data dependencies and structural conflicts, and has as output the amount of cycles required to execute these instructions and the information about the stages in each cycle.

In this context, the project received some restrictions in the form of execution and exit, where it was considered a pipeline of 5 stages in the architecture Harvard where the stages are: IF, ID, EX, MEM, WB. Also for this project was restricted only the instructions ADD, SUB, BEQ, BNE, LW, SW and JUMP. Also, there can be no reordering and redirection of instructions for optimizing cycles. So the program will have in the case of data conflict, that the tool will be able to detect the data dependencies and stop the pipeline until the dependency and in the case of control conflict, where there are functions that will have labels, will always be taken the jump.

For this implementation, the C ++ language was used with the use of two non-standard libraries of the language, being: the string, where the declared strings behave like objects that represent sequences of characters; and the vector, where the vector when declared behave as vectors of any data types, where they are internally allocated dynamically to store their elements.

The program is based on the following logic, it will be allocated in a vector of strings all the lines of code, soon after, a vector of strings with "0" will be initialized for each stage of execution in its worst case, that is, if there is dependence in all lines of code. Afterwards, each instruction will be read, where the dependencies of registers will be tested with the previously executed code line and the delay is placed in the first cycle of execution of the read line, in the perspective of bubbles if it is necessary, otherwise, its initialization. In both perspectives, the current execution cycle will be read and the code line read in the vector of each stage, making it go through all stages, cycle after cycle, until its conclusion. Also when you put functions that will have to jump to a label, the label will be searched in the instructions below and soon after it will be allocated again in each corresponding cycle, respecting the dependencies. After all the instructions have been allocated, the number of cycles to execute the program in the paradigm put in the description will be shown on the screen and its execution will be shown per cycle, thus ending the execution of the program.
In order to execute the program, any input file, such as input.in, must be put in the program's strings folder, so it will be necessary via the Linux terminal to receive the input file (in .in format) with the instructions and create a file with the final result of the program implementation, such as output.out.
    
### Prerequisites

You will need to install the modules below to run the program: 
* [GCC 8.1 or greater](http://gcc.gnu.org/)

### Running

To run this software, we gonna compile in the terminal:
1. Enter the folder and compile all the .cpp files with the following command:
```
$ make
```
2. Enter the bin folder and run the following command:
```
$ ./lab01 < <input> > <output>
```
An example would be:
```
$ ./lab01 < entrada.in > saida.out
```
3. From this it only interacts with the system.

## Built With

* [Atom](https://atom.io/) - A code editor used

## Authors
### Developers: 
* **Luís Eduardo Anunciado Silva ([cruxiu@ufrn.edu.br](mailto:cruxiu@ufrn.edu.br))** 
### Project Advisor: 
* **Gustavo Girao Barreto Da Silva ([girao@imd.ufrn.br](mailto:girao@imd.ufrn.br))** 

See also the list of [contributors](https://github.com/cruxiu/IMD0041-Pipeline/contributors) who participated in this project.

## License

This project is licensed under the GPL 3.0 - see the [LICENSE](LICENSE) file for details
