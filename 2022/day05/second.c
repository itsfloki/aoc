#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>

#define MAXLEN 100
#define STACK_ARRAY_LEN 10
#define STACK_CAPACITY 100

typedef struct {
    int top;
    unsigned capacity;
    char* array;
} Stack;

void reverse(char *, int, int);

Stack* createStack(unsigned capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->capacity = capacity;
    stack->top = -1;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));
    return stack;
}

int isFull(Stack* stack) { 
    return stack->top == stack->capacity - 1; 
} 

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

void push(Stack* stack, char item) {
    if(isFull(stack)) return;
    stack->array[++stack->top] = item;
}

int pop(Stack* stack) {
    if(isEmpty(stack)) return INT_MIN;
    return stack->array[stack->top--];
}

int main(int argc, char *argv[]) {
    if(argc < 2) {
        printf("call with input file path.\n");
        return -1;
    }

    Stack* stack_arr[STACK_ARRAY_LEN];
    char *line = (char *) malloc(sizeof(char) * MAXLEN);

    // intialize stack array
    for(int i = 0; i < STACK_ARRAY_LEN; i++) {
        stack_arr[i] = createStack(STACK_CAPACITY);
    }

    FILE* fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("file not found.\n");
        return -1;
    }

    int iter_done = 0;
    while(fgets(line, MAXLEN, fp)) {
        int iter_count = 0;
        int stack_index = 0;
        int move_quantity, from_index, to_index;
        int flag = -1;

        move_quantity = 0;
        from_index = to_index = 0;

        // call reverse
        // currently this will only excecute once
        if(line[1] == '1' && iter_done == 0) {
            printf("stack reversed!\n");
            for(int i = 0; i < STACK_ARRAY_LEN; i++) {
                if(!isEmpty(stack_arr[i])) {
                   reverse(stack_arr[i]->array, 0, stack_arr[i]->top + 1);
                }
            }
            iter_done = 1;
        }

        for(int i = 0; line[i]; i++) {
            // check for uppercase alphabet
            if(isalpha(line[i]) && isupper(line[i])) {
                push(stack_arr[stack_index], line[i]);
            }
            
            // handle stack index
            if(iter_count % 4 == 0) {
                stack_index++;
            }

            // check moves
            if(line[0] == 'm') {
                // increase flag
                if(line[i] == 'e' && line[i+1] == ' ') {
                    flag = 0;
                }
                if(line[i] == 'm' && line[i+1] == ' ') {
                    flag = 1;
                } 
                if(line[i] == 'o' && line[i+1] == ' ') {
                    flag = 2;
                }


                if(isdigit(line[i])) {
                    switch (flag) {
                        case 0:
                            move_quantity = (move_quantity * 10) + (line[i] - '0');
                            break;
                        case 1:
                            from_index = (from_index * 10) + (line[i] - '0');
                            break;
                        case 2:
                            to_index = (to_index * 10) + (line[i] - '0');
                            break;
                        default:
                            break;
                    }
                }
            }

            iter_count++;
        }

        printf("moving %d from %d to %d\n", move_quantity, from_index, to_index);

        int prev_top_index = stack_arr[to_index]->top + 1;

        // handle stack movement
        for(int i = 0; i < move_quantity; i++) {
            int poped_item = pop(stack_arr[from_index]);
            push(stack_arr[to_index], poped_item);
        }

        if(move_quantity > 1) {
            reverse(stack_arr[to_index]->array, prev_top_index, stack_arr[to_index]->top + 1);
        }
    }

    for(int i = 1; i <= 9; i++) {
        if(!isEmpty(stack_arr[i])) {
            putchar(pop(stack_arr[i]));
        }
    }
    printf("\n");


    return 0;
}

void reverse(char arr[], int from, int to) {
    int start = from;
    int end = to - 1;

    while (start < end) {
        // Swap elements at start and end indices
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        // Move the indices towards the center
        start++;
        end--;
    }
}
