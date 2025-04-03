# Welcome to My Printf
***

## Task
The goal of this project is to code again the function printf from C langage.
## Description
To solve this problem, I am using vargs, a C library that makes me able to use function with a "infite" possibility of arguments cause the user might have from 2 to 999 arguments using printf.
I had to code again <ins>%d, %o, %u, %x, %c, %s, %p</ins>.
## Installation
To install and compile the project, use the following commands:

make
## Usage
To use the program, run the compiled binary and provide the necessary arguments:
```
  int main() {
    my_printf("some text [your flags]", [arguments]);
    return 0;
}
```
For exemple, if you do: my_printf("Well done, you finished with %d points!", 27);
It will print: "Well done, you finished with 27 points!".
