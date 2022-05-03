# Compiler240

DESCRIPTION:
============
    A simplified compiler capable of parsing variable/parameter declarations and initializations 
    for single-function programs. Compiler240 is capable of converting basic addition into a 
    non-professional, textbook Assembly code created for use in this class (known as LC3). 
    Reliably detects syntax errors and errors in declaration.

    An LC3 machine simulator can be downloaded here: 
    
    https://drive.google.com/file/d/1iK0KW0s8rFWPTE6F18FJNIbFNjNwCE6W/view
    
    although this link may break by end of spring semester 2022.

Contributers:
=====
	Grace Choe (@gechoe)
    Jac McCarty (@jamccarty)

Program Files:
===============
    Map.c
    Map.h
    Makefile
    Compiler.c
	
How to Compile:
===============
    make Compiler
       
How to Run:
===========
    ./Compiler <program_name.code>
    EX: ./Compiler sample.code


Approximate Hours worked:
=========================
    30-45 hours, over the course of roughly 3 weeks.

Known Bugs or Limitations:
==========================
    Reliably detects errors in type when declaring a new variable (i.e. "cat a = 6 ;"), 
    however also throws an additional error that says that the variable "cat" has not 
    been declared.
