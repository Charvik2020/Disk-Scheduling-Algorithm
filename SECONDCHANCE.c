#include <stdio.h> 
#define SIZE 3
int fullframe = 0; //check all frames are filled
int input[21]; //To take the input
int ref[SIZE]; //This is for reference bits for each frame
int frame[SIZE];
int ret_point = 0;//replaced page Pointer
int count = 0;//page faults counter
int display() {
  int i;
  printf("\nThe elements in the frame are\n");
  for (i = 0; i < fullframe; i++)
    printf("%d\n", frame[i]);

}
int page_rep(int ele) {
  int temp;
  while (ref[ret_point] != 0) {
    ref[ret_point++] = 0;
    if (ret_point == SIZE)
      ret_point = 0;
  }
  temp = frame[ret_point];
  frame[ret_point] = ele;
  ref[ret_point] = 1; 

  return temp;
}
int page_fault(int ele) {
  if (fullframe != SIZE) {
    ref[fullframe] = 1; //refrence bits = 1 as each frame is being filled firstly
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
        ref[i] = 1; //When page reference occurs, it's rference bit = 1
        break;
      }
  }
  return flag;
}
int main() {
  int n, i;
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
      display();
      count++;
    }

  }
  printf("\nThe number of page faults are %d\n", count);
  getche();
  return 0;
}
