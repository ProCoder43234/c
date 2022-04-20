#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

int k = 0;
int seekSequence[100];

int smallerThanHead(int tracks[], int n, int position)
{
  int pos;
  for (int i = 0; i < n; i++)
  {
    if (tracks[i] == position)
    {
      pos = i;
      break;
    }
  }
  return pos;
}

void SCAN(int tracks[], int n, int position, char direction[])
{
  int trackMovements = 0;
  int test = position;
  int pos = smallerThanHead(tracks, n, position);
  int value = strcmp(direction, "left");
  if (value == 0)
  {
    for (int i = pos - 1; i >= 0; i--)
    {
      seekSequence[k] = tracks[i];
      k += 1;
      int difference = abs(test - tracks[i]);
      trackMovements += difference;
      test = tracks[i];
    }
    int difference = abs(test - 0);
    trackMovements += difference;
    test = 0;
    seekSequence[k] = test;
    k += 1;
    for (int i = pos + 1; i < n; i++)
    {
      seekSequence[k] = tracks[i];
      k += 1;
      int difference = abs(test - tracks[i]);
      trackMovements += difference;
      test = tracks[i];
    }

    printf("The total number of track movements is %d\n", trackMovements);
    printf("\nThe seek sequence is \n");
    // printf("%d-->", position);
    for (int i = 0; i < k; i++)
    {
      printf("%d-->", seekSequence[i]);
    }
  }
  else
  {

    for (int i = pos + 1; i < n; i++)
    {
      seekSequence[k] = tracks[i];
      k += 1;
      int difference = abs(test - tracks[i]);
      trackMovements += difference;
      test = tracks[i];
    }
    int difference = abs(test - 199);
    trackMovements += difference;
    test = 199;
    seekSequence[k] = test;
    k += 1;
    for (int i = pos - 1; i >= 0; i--)
    {
      seekSequence[k] = tracks[i];
      k += 1;
      int difference = abs(test - tracks[i]);
      trackMovements += difference;
      test = tracks[i];
    }
    printf("The total number of track movements is %d\n", trackMovements);
    printf("\nThe seek sequence is \n");
    printf("%d-->", position);
    for (int i = 0; i < k; i++)
    {
      printf("%d-->", seekSequence[i]);
    }
    printf("\n");
  }
}

int main()
{
  int n, tracks[200], position;
  char direction[50];
  printf("Enter the  number of requests\n");
  scanf("%d", &n);
  printf("Enter the request sequence\n");
  for (int i = 0; i < n; i++)
  {
    scanf("%d", &tracks[i]);
  }
  printf("Enter the current position of r/w head\n");
  scanf("%d", &position);
  printf("Enter the direction of traversal (Type 'left' or 'right')\n");
  scanf("%s", direction);

  tracks[n] = position;
  n += 1;

  for (int i = 0; i < n - 1; i++)
  {
    for (int j = 0; j < n - i - 1; j++)
    {
      if (tracks[j] > tracks[j + 1])
      {
        int temp = tracks[j];
        tracks[j] = tracks[j + 1];
        tracks[j + 1] = temp;
      }
    }
  }

  SCAN(tracks, n, position, direction);

  return 0;
}