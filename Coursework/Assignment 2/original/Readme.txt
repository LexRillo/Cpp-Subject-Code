This is the second assessed course work in CO3105/CO7105. This exercise does not use Course Master and you need to submit your work via the handin system! . Student's registered to CO3105/CO7105 (or anyone else, for that matter) can submit here.

The deadline for this worksheet is 04/12/2017, 23:59:59.
A forum has been set up for questions regarding this assessment. Check out here.

Exercise 1 (60 marks)
In this exercise you will practice the idea inheritance. You are asked to implement a simple inheritance hierarchy of different Bank accounts. The details regarding the implementation of these classes are given in its header file.

I have set up BankAccount.cpp and BankAccount.h with the signature of the classes that you have to implement.

The main.cpp file includes an example for a simple usage of these classes.

Exercise 2 (30 marks)
In this exercise you will create a more complicated inheritance system. Here, you will create a data structure for storing Boolean formulas. As before, details regarding the implementation are given in the header file.

I have set up Formula.cpp and Formula.h with the signature of the classes that you have to implement.

Part of the implementation of this class depends on a class I implemented for you in Assignment.h and Assignment.cpp. This class, supports the functionality of given a variable name and returning a Boolean value for it. This is required in order to evaluate a Boolean formula that uses variables.

I am also supplying the class BoolFormula that is a wrapper for the Formula that you are creating and includes things like parsing a Boolean formula and creating the data structrue.

Finally, in the given main.cpp there is a short executable program that tests the functionality of the classes. It tries to read a formula and an assignment from the prompt and evaluates the formula.