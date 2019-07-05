Exercise 1 (60 marks)
In this exercise you will practice the ideas of copy and move semantics as well as the construction of a simple class. You are asked to implement a container for Transitions and string labels. The container contains two resizable arrays of Transitions and strings, gives access to them, and disposes of them. The details regarding the implementation of this class are given in its header file.

For the purpose of this assessment a State has a name, a list of labels (string), and a list of transitions that originate from this state.

I have set up State.cpp and State.h with the signature of the State class and the skeleton of the implementation. You should complete the implementation of the State class.

The Transition class
A Transition contains pointers to two states. It is a very simple class that just manipulates these two pointers. The intention is that the first state in the transition is the source and the second is the target. Accordingly, when adding a transition to a state we expect the first state in the transition to be the same state (i.e., the pointer should be to this state).

I am also inculding the files Transition.cpp and Transition.h with the full implementation of Transition. There is no need to change these files and you will not be submitting them.

The supplied file main.cpp includes a basic usage of the State.

Notice that you do not have to understand the rest of this assessment or the theoretical concept of automata in order to succeed in this exercise.

Automata Background
The classes that you write are a basic data structure to hold Automata. In order to solve the second exercise you will need very basic understanding of what are automata. An automaton has states and transitions. Transitions are between two states. States have many transitions originating from them. This is a simplified setting. If you need, additional details are available at: Wikipedia or in the first few chapters of Hopcroft, Motwani, and Ullman (available also in the library). However, in-depth knowledge of automata is completely not required. What is written above (or the wikipedia page) are completely sufficient.

Exercise 2 (30 marks)
In this exercise you will create a more complicated system that needs copying and moving. Every automaton has a name and a collection of States and Transitions between them. The container contains resizable arrays of States and Transitions but this time, these pieces of data are intelinked between them. The different functions give access to the internal data. The details regarding the implementation of this class are given in its header file.

The given main.cpp is a short executable program that tests the functionality of the classes. It tries to read the automaton from this file. Notice that the program compiles. However, it uses a few of the unimplemented members. As a result it does not work quite as expected. You might want to consider writing additional tests for your programs.

Materials Provided
Automaton.cpp
Automaton.h
aut.txt a sample input file
hugeAutomaton.txt another sample input file
main.cpp
makefile
ModelAutomaton.h
ModelAutomaton.o
ModelState.h
ModelState.o
State.cpp
State.h
Transition.cpp
Transition.h
As promised, I am supplying libraries implementing a solution to this two classes. Their header files are supplied in ModelState.h and ModelAutomaton.h. There are corresponding compilations in ModelState.o and ModelAutomaton.o. I am supplying these for linux only.
The makefile produces two executables: main and modelmain. modelmain is constructed by combining the given libraries. main is constructed by combining the libraries resulting from your files. Notice that currently, main includes the model files. This works also with your files because there are no data members for State and Automaton classes. Once you add data members to these classes you will need to change the inclusion in main and then will not be able to compile both main and mainmodel.

The files you will have to submit are: Automaton.cpp, Automaton.h, State.cpp, and State.h.

Dynamic Memory
Dynamic memory is a feature that allows a programmer to use an amount of memory that varies according to the program needs. In many cases, the exact amount of memory that a program needs is not known in advance and may change during the run of the program. In C++, this is solved by a thing called a pointer, an allocation command (called new), and a deallocation command (called delete or delete[]).

For the initial purpose of this assessment (until you learn to use dynamic memory in the lecture), it is enough to know that a pointer can give access to something that behaves like an array. So in our case, we would define a pointer variable to an integer, like this:
int *arrayName{nullptr};
The difference from an array, is that this thing cannot be used before it is allocated memory. So before you can use it you need to do something like:
arrayName = new int[sizeOfRequiredArray];
The two can be combined to one command:
int *arrayName = new int[sizeOfRequiredArray];
After this you can access the memory like you access arrays:
for (int i=0 ; i<sizeOfRequiredArray ; ++i) { 
    arrayName[i]=i*5;
}
Another difference, is that when you are finished using this memory, you have to release (or deallocate) it.
This is done by writing:
delete [] arrayName;
The beauty of this thing is that it allows you to have a structure that changes in size through the lifetime of the program.
In order to change its size you have to do something like the following:
int* temp = new int[biggerSize];
// copy the old contents from arrayName to temp;
delete [] arrayName;
arrayName = temp;
That is, in order to replace the memory that you are using by a larger memory, you have to (1) ask for a larger memory, (2) copy the old contents of the memory from the array to the new temporary object, (3) release the old memory, and (4) move the temporary object to the main object.
Further details will be given in the lecture. There is also an example of how this is used in the Log. There the dynamic array stores strings and not integers, but the ideas are the same.