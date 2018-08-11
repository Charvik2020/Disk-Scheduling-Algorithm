#include <stdio.h>
#define SIZE 3
int fullframe = 0; //check all frames
int input[21], n; //To take the input
int frame[SIZE];
static int f = 0;
int rep_point;//replaced page Pointer
int count = 0;//page faults counter
//Display Frames
int display() {
  int i;
  printf("\nThe elements in the frame are\n");
  for (i = 0; i < fullframe; i++)
    printf("%d\n", frame[i]);

}
//Returning the replacement pointer with the value of victim page
int Longestopt() {
  int temp[SIZE] = {
    0
  }; //checking the occurence of nearest possible future pages,Assumming zero page is nearest in the beginning
  int c = 0; 
  int id, i, k, j = SIZE;
  id = 0;

  for (i = f + 1; i < n; i++) //Checking from the current time of use till the end of string for future references
  {
    for (k = 0; k < j; k++) //page occurs in future or not
    {
      if (input[i] == frame[k]) {
        if (temp[k] != 1) {
          temp[k] = 1;
          c++;
        }

        break;
      }
    }

    if (c == 2)//Once we get two future pages then break
      break; 

  }

  id = 2;
  while (id != 0) {
    if (temp[id] == 0) //the page which is not the nearest future reference then break
      break;
    id--;
  }

  rep_point = id;
  return rep_point; 

}
int page_rep(int ele) {
  int temp;
  rep_point = Longestopt();
  temp = frame[rep_point];
  frame[rep_point] = ele;

  return temp;
}
int page_fault(int ele) {
  if (fullframe != SIZE)
    frame[fullframe++] = ele;
  else
    printf("The page replaced is %d", page_rep(ele));
}
int search(int ele) {
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
    f = i;
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
