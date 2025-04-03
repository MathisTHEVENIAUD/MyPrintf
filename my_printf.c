#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

int my_strlen(char* param_1) {
    if (param_1 == NULL) {
        return 0;
    }
    int index = 0;
    while(param_1[index] != '\0') {
        index += 1;
    }
    return index;
}

int my_write(char *buff, int size) {
    int ret = 0;

    ret = write(1, buff, size);
    if(ret == -1) {
        exit(-1);
    }
    return ret;
}

int print_char(char c) {
    return my_write(&c, 1);
}


int print_str(char *str) {
    return my_write(str, my_strlen(str));
}

int num_length(long int num) {
    if (num == 0) {
        return 1;
    }
    int limit = 0;
    if (num < 0) {
        limit++;
        num = -num;
    }
    while (num != 0) {
        limit++;
        num /= 10;
    }
    return limit;
}

int unsigned_num_length(unsigned int num) {
    int limit = 0;
    while(num != 0) {
        limit += 1;
        num /= 10;
    }
    return limit;
}

int print_octale(int octale) {
    int limit = num_length(octale);
    char* octale_result = malloc(sizeof(int) * limit + 1);
    char buffer = ' ';

    while(octale % 8 != 0) {
        buffer = '0' + octale % 8;
        octale_result[limit - 1] = buffer;
        octale /= 8;
        limit -= 1;
    }
    return my_write(octale_result, my_strlen(octale_result));
}

int print_int(int num) {
    int is_negative = (num < 0);
    int limit = num_length(num);
    char *int_result = malloc(limit + 1);
    int index = limit - 1;

    if (is_negative) {
        int_result[0] = '-';
        num = -num;
    }

    for (; index >= is_negative; index--) {
        int_result[index] = '0' + (num % 10);
        num /= 10;
    }

    int_result[limit] = '\0';
    int printed_size = my_write(int_result, limit);
    free(int_result);
    return printed_size;
}



int print_unsigned(int unsign) {
    int limit = num_length(unsign);
    char* result_unsigned = malloc(sizeof(int) * limit + 1);
    char buffer = ' ';
    if(unsign > 0) {
        while(unsign != 0){
            buffer = '0' + unsign % 10;
            result_unsigned[limit-1] = buffer;
            unsign /= 10;
            limit -= 1;
        }
    }
    else if (unsign < 0) {
        unsigned int unsigned_value = (unsigned int)unsign;
        int limit = unsigned_num_length(unsigned_value);
        while(unsigned_value != 0){
            buffer = '0' + unsigned_value % 10;
            result_unsigned[limit-1] = buffer;
            unsigned_value /= 10;
            limit -= 1;
        }
    }
    return my_write(result_unsigned, my_strlen(result_unsigned));
}

int print_hexa(int hexa) {
    int limit = num_length(hexa) - 1;
    char buffer = ' ';
    char* result_hexa = malloc(sizeof(int) * limit + 1);
    char* base = malloc(sizeof(int) * 9 + 5);
    base = "0123456789ABCDEF";
    int temp = 0;

    while(hexa /= 16 != 0) {
        buffer = '0' + hexa % 16;
        if(hexa % 16 > 9) {
            temp = hexa % 16;
            buffer = base[temp];
        }
        result_hexa[limit - 1] = buffer;
        hexa /= 16;
        limit -= 1;
    }
    
    return my_write(result_hexa, my_strlen(result_hexa));
}

long int print_pointers(long int pointer) {
    int limit = num_length(pointer);
    char buffer = ' ';
    char* result_pointer = malloc(sizeof(int) * limit + 1);
    char* base = malloc(sizeof(int) * 9 + 5);
    base = "0123456789abcdef";
    int temp = 0;

    result_pointer[0] = '0';
    result_pointer[1] = 'x';

    while(pointer /= 16 != 0) {
        buffer = '0' + pointer % 16;
        if(pointer % 16 > 9) {
            temp = pointer % 16;
            buffer = base[temp];
        }
        result_pointer[limit - 1] = buffer;
        pointer /= 16;
        limit -= 1;
    }

    return my_write(result_pointer, my_strlen(result_pointer));
}

int my_printf(char * restrict format, ...) {
    va_list args;
    va_start(args, format);
    int size = 0;
    int format_size = my_strlen(format);
    int index = 0;

    while (index < format_size) {
        if (format[index] == '%') {
            index += 1;
            if (index < format_size) {
                if (format[index] == 'd') {
                    int integer = va_arg(args, int);
                    print_int(integer);
                    size += num_length(integer);
                } else if (format[index] == 'c') {
                    char c = va_arg(args, int);
                    print_char(c);
                    size += 1;
                } 
                else if (format[index] == 's') {
                    char *str = va_arg(args, char *);
                    if (str == NULL) {
                        print_str("(null)");
                        size += my_strlen("(null)");
                    } else {
                        print_str(str);
                        size += my_strlen(str);
                    }
                }
                else if (format[index] == 'o') {
                    int octale = va_arg(args, int);
                    print_octale(octale);
                    size += num_length(octale);
                }
                else if (format[index] == 'u') {
                    int unsign = va_arg(args, int);
                    print_unsigned(unsign);
                    size += num_length(unsign);
                }
                else if (format[index] == 'x') {
                    int hexa = va_arg(args, int);
                    print_hexa(hexa);
                    size += num_length(hexa) - 1;
                }
                else if (format[index] == 'p') {
                    long int pointers = va_arg(args, long int);
                    print_pointers(pointers);
                    size += num_length(pointers);
                }
                index += 1;
                continue;
            }
        }
        print_char(format[index]);
        size += 1;
        index += 1;
    }
    va_end(args);
    return size;
}

int main() {
    char* str= NULL;
    my_printf("%s\n", str);
    return 0;
}