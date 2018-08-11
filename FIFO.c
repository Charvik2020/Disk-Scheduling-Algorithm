#include <stdio.h> 
#include <stdlib.h> 
#include <assert.h> 
#include <windows.h> 
#include <conio.h> 
#include <time.h> 
#define SIZE 3

int fullframe = 0; //check all frames
int input[21]; //input of reference string
int frame[SIZE];
int rep_point = 0; //replaced page Pointer
int count = 0; //page faults counter

int display() //Display Frames
  {
    int i;
    printf("\nThe elements in the frame are\n");
    for (i = 0; i < fullframe; i++)
      printf("%d\n", frame[i]);
  }

int page_rep(int ele) //Returns the victim page
  {
    int temp;
    temp = frame[rep_point];
    frame[rep_point] = ele;
    rep_point++;
    if (rep_point == SIZE)
      rep_point = 0;

    return temp;
  }

int page_fault(int ele) //for checking if fault was there or not
  {
    if (fullframe != SIZE)
      frame[fullframe++] = ele;
    else
      printf("The page replaced is %d", page_rep(ele));
  }

int search(int ele) //search the element in a frame
  {
    int i, flag;
    flag = 0;
    if (fullframe != 0) {
      for (i = 0; i < fullframe; i++)
        if (ele == frame[i]) {
          flag = 1;
          break;
        }
    }
    return flag;
  }

int main() {
  int n, i;
  FILE * out;
  out = fopen("pages.in", "r");
  printf("The number of page requested are:");
  fscanf(out, "%d", & n);
  printf("%d", n);
  for (i = 0; i < n; i++)
    fscanf(out, "%d", & input[i]);
  fclose(out);
  printf("\nThe pages present in the requested string are\n");
  for (i = 0; i < n; i++)
    printf("%d  ", input[i]);
  printf("\n\n");
  for (i = 0; i < n; i++) {
    if (search(input[i]) != 1) {
      page_fault(input[i]);
      display();
      count++;
    }
  }
  printf("\nThe number of page faults are %d\n", count);
  return 0;
}
