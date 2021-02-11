# CS 100 Fall 2019 Project: RShell

>Joshua McIntyre | SID: 862054277  
>Cody Steimle | SID: 862137374

&nbsp;

## Introduction
For our CS 100 group project we created and extended upon a fully functioning shell that operates via the Linux terminal. 
Not only does this shell manage the creation of new processes and handle parallel processing, but it also is compatible with the following command line connectors:  

`&&` Combines two commands, only runs the second one if the first one succeeds.  

`||` Combines two commands, only runs the second one if the first one fails.  

`;` Always runs the next command.

`#` Takes any input following it as a comment (ignores input).

`()` Defines command precedence.

`|` Pipes commands input (right) and output (left) together.

`<` Redirects input from a file.

`>` Redirects output to a file, if file exists it will be replaced.

`>>` Redirects output to a file, if file exists it will be appended.

These connectors and functions can be strung together indefinitely for example:

```
ls -a; echo hello && mkdir test || echo world; git status
```

As well as be defined by precedence, example:

```
(echo A && echo B) || (echo C && echo D)
```

Would print:
```
A
B
```

For the final version of RShell we now support piping and I/O redirection, example:

```
ls | grep .txt | cat

grep ucr < names.txt
```

Where the first line prints out all the files with .txt in the file name. While the second line will print all lines with ucr in them from our names.txt file.


We also created a new `test` function that also be utilized through `[ args_here ]`.
This function will take in a name for a file/directory and an argument of:
+ `-e` checks if the file/directory exists (default).
+ `-f` checks if the file/directory exists and is a regular file.
+ `-d` checks if the file/directory exists and is a directory.
After that it will either echo (True) or (False) based on the result.


&nbsp;

The generalized process for RShell (classes have since changed but the core functionality remains the same):
1. If arguments are passed in through the command line, then those commands are executed through rshell.

2. Otherwise the program starts by reading in and storing the users line of commands into a `string`.

3. After the input `string` is stored, we tokenize it by spaces.

4. Then we begin long and complicated process of parsing the input for the desired behaviour. We account for and handle each of the following during this step:

   + Checking for quotations `""`, ignoring any tokens inbetween them.

   + Each token is checked for `(`, `&&`, `||`, `;`, or `#`.
   
     - If the token is an `(`, we create an instance of the Container class. It handles whats inside `()` in isolation, storing the final return status (also works recursively). 
     
     - Else If the token is an `&&`, we create an instance of the And class using the pre and post commands `Label*` and push it back on a `vector<Cmd*>`.
     
     - Else if the token is an `||`, we create an instance of the Or class using the pre and post commands `Label*` and push it back on a `vector<Cmd*>`.
     
     - Else if the token is an `;`, we create an instance of the Dual class using the pre and post commands `Label*` and push it back on a `vector<Cmd*>`.
     
     - Else if the token is an `#`, we then ingore the rest of the input treating it as a comment.
      
     - Otherwise the token is treated as just a singluar `Label` class command. 

5. Upon completing the creation of the `vector<Cmd*>`, the vector is iterated through and calls the `handle()` function for each element.

   + During this time, the `Label` class is the one that uses `fork()`, `waitpid()`, and `execvp()`, the other classes utilize the stored status of each class to determine thier execution.

6. Finally we loop the entire process, ready to accept more inputs. However the user may exit by simply typing `exit`.

&nbsp;

We utilied the composite design pattern as our project's core. The following is the structural outline:

#### Component: `Cmd`
This is our base class which sets up the entire structure for our program. It holds pure virtual functions to define later with the children classes.

#### Leafs: `Label`, `And`, `Or`, `Dual`
The commands themselves, `Label`, will act as the leafs. This class is where we fork a new process and execute terminal commands. The `And`, `Or`, and `Dual` classes take two `Cmd*` classes as parameters, using their stored status to determine whether or not to run a command.

#### Composite: `Container`
This composite stores a `vector<Cmd*>` and iterates through it calling the children's `handle()` functions. The final `handle()` call is stored as the Container's status for use by the other operator classes.

&nbsp;  
&nbsp;

## Object-Modeling Technique Diagram

![OMT](https://github.com/JMAK13/assignment-cosh/blob/master/images/OMT%20Diagram%20CS100%20Assignment%201.png)

&nbsp;  
&nbsp;

## Classes                     

| Name         | Function / Purpose                                                                                                                                                                                                                                    |
| ------------ | ----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------- |
| `Cmd`        | Base class containing pure virtual functions as a prototype for children classes.                                                                                                                                                                     |
| `Container`  | Inherits from `Cmd`, handles the `(` connector by handling what comes after it until number of `(`'s are equal to the number of `)`'s. This is handled in isolation for the rest of the input string (can call itself recursively for other `()`).    |
| `Label`      | Inherits from `Cmd`, contains individual commands with thier arguments, takes input `vector<strings>` and converts it into `char*[]`, then it forks a process and executes commands.                                                                  |
| `And`        | Inherits from `Cmd`, handles the `&&` connector by taking two objects (`Cmd*`, `Cmd*`) and checking the return status of the first object and runing the second object if the first was successful.                                                   |
| `Or`         | Inherits from `Cmd`, handles the `\|\|` connector by taking two objects (`Cmd*`, `Cmd*`) and checking the return status of the first object and runing the second object if the first one failed.                                                     |
| `Dual`       | Inherits from `Cmd`, handles the `;` connector by taking two objects (`Cmd*`, `Cmd*`) and always run both, stringing them together.                                                                                                                   |
| `Redirect`   | Inherits from `Cmd`, is a container for the label class. We use it as a way to separate the old connector parsing with new I\O connector parsing.                                                                                                     |
| `Override`   | Inherits from `Cmd`, handles the `>` and `>>` connectors by taking two objects (`Cmd*`, `Cmd*`) and selecting between two different file output behaviors at run time based on the `bool` values passed in during construction.                        |
| `Pipe`       | Inherits from `Cmd`, handles the `\|` connector by taking two objects (`Cmd*`, `Cmd*`) and doing a carefully constructed for loop that overwrites a forked program's standard input /output when necessary.                                           |
| `Reverse`    | Inherits from `Cmd`, handles the `<` connector by taking two objects (`Cmd*`, `Cmd*`) and handling the piping needed to take a file as input to a program / command.                                                                                  |


&nbsp;  
&nbsp;

## Prototypes / Research

UPDATE 12-11-2019 : RShell has been completed, for the factory pattern process we just used our main program to act as a factory. Understanding how to utilize the piping linux commands took many hours of prototyping before we had our current working version.  

UPDATE 11-24-2019 : We tried using a factory pattern for the parsing and creation of the classes, however it was interfering with setup of our command tree (this will likely still be added later).

UPDATE 11-12-2019: These assumptions were correct, we were able to add functionality and also reorganize the structure of our code with relative ease. The only portion of the project after our initial prototyping that gave us trouble was dealing with all the unique forms of parsing we needed to perform on the user's input string. In order to achieve the desired functionality, several checks were needed for dealing with spaces, quotations and `#`. However once we had our text properly paresed and store, the rest of the prpject was smooth sailing.


Our understanding of dealing with system processes was made possible through extensive prototyping. But before we could properly prototype, we needed to truly know exactly how these new commands `fork()`, `execvp()` and `wait()` behaved. After reading documentation online about these commands, we attempted to complete a working prototype that involved all three. 

It took us far longer than we expected, running into many errors mainly due to not being familiar with having multiple processes running simultaneously. Specifically, we were accidentally overwriting our main process, or forking too many children. These were problems that were difficult to debug due to the unexpected behavior and often at times lack of any output.

However, we were able to overcome these obstacles and currently have a working prototype that can connect commands together in an infinite chain. But we are still trying to figure out the best method for parsing if using quotations to ignore connectors, shown below.
```
echo "this && that" && echo hello
```

But thanks to all the leg work we have done in the early stages of development, we are confident that the rest of the project will be completed to specifications in a timely manner. For now, we will need to polish up all code created in our prototype, and also be positive the classes fit our design pattern before implementing it in the final product.


&nbsp;  
&nbsp;

## Development and Testing Road-map

Current order of tasks to be completed:

1. [X] [**Issue #1** : Composite Design Structuring](https://github.com/cs100/assignment-cosh/issues/1)
2. [X] [**Issue #3** : Create Interface Class](https://github.com/cs100/assignment-cosh/issues/3)
3. [X] [**Issue #4** : Create Parsing Function](https://github.com/cs100/assignment-cosh/issues/4)
4. [X] [**Issue #5** : Create Unit Test for && Connector](https://github.com/cs100/assignment-cosh/issues/5)
5. [X] [**Issue #6** : Create Unit Tests for || Connector](https://github.com/cs100/assignment-cosh/issues/6)
6. [X] [**Issue #7** : Integration Test for Parsing and Connectors](https://github.com/cs100/assignment-cosh/issues/7)
7. [X] [**Issue #8** : Support for backslashes in quotes](https://github.com/cs100/assignment-cosh/issues/8)
