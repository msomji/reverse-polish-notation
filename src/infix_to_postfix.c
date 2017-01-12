#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include "validate_infix.h"
#include "error_messages.h"

char *postfixArray;
char *stack;

static int postfixArrayPosition = 0;
static int stackPosition = 0;
static int infixStringPosition = 0;

int get_precedence(char element) {
  switch (element) {
  case '+':
    return 1;
  case '-':
    return 1;
  case '*':
    return 2;
  case '/':
    return 2;
  case '^':
    return 3;
  }
  return 0;
}

void push(int position, char element) {
  postfixArray[position] = element;
  postfixArrayPosition++;
}

void dump_stack() {
  while (stackPosition > 0) {
    push(postfixArrayPosition, stack[stackPosition - 1]);
    stackPosition--;
  }
}

void push_stack(char element) {
  stack[stackPosition] = element;
  stackPosition++;
}

void build_postfix(char element) {
  if (isalnum(element)) {
    push(postfixArrayPosition, element);
  } else {
    if (get_precedence(element) < get_precedence(stack[stackPosition - 1])) {
      dump_stack();
    }
    push_stack(element);
  }
}

void dump_partial_stack() {
  while (stack[stackPosition - 1] != '(') {
    push(postfixArrayPosition, stack[stackPosition - 1]);
    stackPosition--;
  }
  stackPosition--;
}

void set_max_array_size(int length) {
  postfixArray = malloc(sizeof(char) * length);
  stack = malloc(sizeof(char) * length);
}

void exit_and_print_error(int err) {
  for (int j =0; j < 5; j++) {
    if(number_to_message[j].num == err) {
      printf("[DEBUG] Error: %s\n", number_to_message[j].error);
      exit(err);
    }
  }
}

const char *convert_to_postfix(char *infixString) {
  int validity = validate_infix(infixString);
  if (validity != 0) {
    exit_and_print_error(validity);
  }

  /* validate_infix(infixString); */
  set_max_array_size(strlen(infixString));

  while (infixString[infixStringPosition] != '\0') {
    if (infixString[infixStringPosition] == '(') {
      push_stack(infixString[infixStringPosition]);
      infixStringPosition++;
    } else if (infixString[infixStringPosition] == ')') {
      infixStringPosition++;
      dump_partial_stack();
    } else {
      build_postfix(infixString[infixStringPosition]);
      infixStringPosition++;
    }
  }
  dump_stack();
  free(stack);
  push(infixStringPosition, '\0');

  return postfixArray;
}
