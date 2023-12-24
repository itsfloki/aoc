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

void reverse(char *, int);

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
                   reverse(stack_arr[i]->array, stack_arr[i]->top + 1);
                }
            }
            iter_done = 1;
        }

        for(int i = 0; line[i]; i++) {
            // check for uppercase alphabet
            if(isalpha(line[i]) && isupper(line[i])) {
                // printf("%c %d", line[i], stack_index);
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

        // handle stack movement
        for(int i = 0; i < move_quantity; i++) {
            int poped_item = pop(stack_arr[from_index]);
            push(stack_arr[to_index], poped_item);

            // printf("pop item: %d, from: %d, to: %d, quantity: %d\n", poped_item, from_index, to_index, move_quantity);
        }
    }

    for(int i = 1; i <= 9; i++) {
        // printf("stack %d, top: %d\n", i, stack_arr[i]->top);

        if(!isEmpty(stack_arr[i])) {
            putchar(pop(stack_arr[i]));
        }

        // for(int j = 0; j < stack_arr[i]->top + 1; j++) {
        //    printf(" %c ", stack_arr[i]->array[j]);
        // }
        // printf("\n");
    }
    printf("\n");


    return 0;
}

void reverse(char arr[], int size) {

    int start = 0;
    int end = size - 1;

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
