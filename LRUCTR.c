#include <stdio.h> 
#define SIZE 3
int fullframe = 0; //check all frames
int input[21], n; //input of reference string
int frame[SIZE];
int ctr[SIZE] = {
  0
};
static int f = 0; 
int rep_point;//replaced page Pointer
int count = 0;//page faults counter
int display() {//Display Frames
  int i;
  printf("\nThe elements in the frame are\n");
  for (i = 0; i < fullframe; i++)
    printf("%d\n", frame[i]);

}
int Longestopt() //Fucntion for discovering the LRU page using their corresponding counter values
  {
    int i, min;
    min = 0;
    for (i = 0; i < SIZE; i++)
      if (ctr[min] > ctr[i])
        min = i;

    rep_point = min;
    return rep_point;

  }
int page_rep(int ele) {//page replacement
  int temp;
  rep_point = Longestopt(); 
  temp = frame[rep_point];
  frame[rep_point] = ele;
  ctr[rep_point] = f; 

  return temp;
}
int page_fault(int ele) {//page fault
  if (fullframe != SIZE) {
    ctr[fullframe] = f; 
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
        ctr[i] = f; 
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
  printf("\nThe pages present in the frame are\n");
  for (i = 0; i < n; i++)
    printf("%d  ", input[i]);
  printf("\n\n");
  for (i = 0; i < n; i++) {
    f++; 
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