#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

char* postfixArray;
char* stack;

int postfixArrayPosition = 0;

int getPresidence(char element) {
  switch(element)
  {
    case '+': return 1;
    case '-': return 1;
    case '*': return 2;
    case '/': return 2;
  }

}

void push (int position, char element){
  postfixArray[position] = element;
  postfixArrayPosition++;
}

char* convert_to_postfix(char* infixArray)
{
  int size = sizeof(infixArray)/sizeof(infixArray[0]);
  postfixArray = malloc(size);
  stack = malloc(size);

  int infixArrayPosition = 0;
  int stackPosition = 0;

  while (infixArray[infixArrayPosition] != '\0')
  {
    if (isalnum(infixArray[infixArrayPosition])) 
    {
      push(postfixArrayPosition, infixArray[infixArrayPosition]);
    } else {
      if (getPresidence(infixArray[infixArrayPosition]) < getPresidence(stack[stackPosition -1])){
//dump stack on postfix  array
        while( stackPosition > 0)
        {
          push(postfixArrayPosition, stack[stackPosition -1]);
          stackPosition--;
        } 

      }
//THEN add to operand stack as normal
      stack[stackPosition] = infixArray[infixArrayPosition];
      stackPosition++;
    }
    infixArrayPosition++;
  
  }

  while( stackPosition > 0)
  {
    push(postfixArrayPosition, stack[stackPosition -1]);
    stackPosition--;
  } 
  
  return postfixArray;
}
