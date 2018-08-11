#include <stdio.h> 
#define SIZE 3
int fullframe = 0; //check all frames
int input[21], n; //input of reference string
int frame[SIZE];
int stk[SIZE]; //Stack for storing the page numbers as per their reference criteria

int rep_point;//replaced page Pointer
int count = 0;//page faults counter
int display() {//display Frame
    int i;
    printf("\nThe elements in the frame are\n");
    for (i = 0; i < fullframe; i++)
      printf("%d\n", stk[i]);

  }
int LRstackopt(int p) 
  {
    int temp;
    int i;
    for (i = 0; i < n; i++)
      if (stk[i] == p)
        break;
    temp = stk[i]; 
    while (i != SIZE - 1) //Moving the elements thus TOP is empty
    {
      stk[i] = stk[i + 1];
      i++;
    }
    stk[i] = temp; //Storing the element to TOP from temp

  }
int page_rep(int ele) {//page replacement
  int temp;

  rep_point = stk[0]; //victim page is selected as the 1st element of the stack

  temp = frame[rep_point];
  frame[rep_point] = ele;
  LRstackopt(rep_point); 

  return temp;
}
int page_fault(int ele) {//page fault
  if (fullframe != SIZE) {
    stk[fullframe] = fullframe; 
    frame[fullframe++] = ele;
  } else
    printf("The page replaced is %d", page_rep(ele));
}
int search(int ele) {
  int i, flag;
  flag = 0;
  if (fullframe != 0) {
    for (i = 0; i < fullframe; i++)
      if (ele == frame[i]) {
        flag = 1;
        LRstackopt(i); 
        break;
      }
  }
  return flag;
}
int main() {
  int i;
  FILE * out;
  out = fopen("pages.in", "r");
  printf("The number of page request are:");
  fscanf(out, "%d", & n);
  printf("%d", n);
  for (i = 0; i < n; i++)
    fscanf(out, "%d", & input[i]);
  printf("\nThe pages present in the requested string are\n");
  for (i = 0; i < n; i++)
    printf("%d  ", input[i]);
  printf("\n\n");
  for (i = 0; i < n; i++) {
    if (search(input[i]) != 1) {
      page_fault(input[i]);

      count++;
    }
    display();
  }
  printf("\nThe number of page faults are %d\n", count);
  getche();
  return 0;
}
