#include <stdio.h>
#include <math.h>
#include <stdlib.h>
void FCFS(int tracks[], int n, int position)
{
  int trackMovements = 0;

  for (int i = 0; i < n; i++)
  {
    int difference = abs(position - tracks[i]);
    trackMovements += difference;
    position = tracks[i];
  }
  printf("The total number of track movements is %d\n", trackMovements);
  printf("The seek sequence is \n");
  for (int i = 0; i < n; i++)
  {
    printf("%d\n", tracks[i]);
  }
}

int main()
{
  int n, tracks[100], position;
  printf("Enter the  number of requests\n");
  scanf("%d", &n);
  printf("Enter the request sequence\n");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &tracks[i]);
  }
  printf("Enter the current position of r/w head\n");
  scanf("%d", &position);
  FCFS(tracks, n, position);

  return 0;
}