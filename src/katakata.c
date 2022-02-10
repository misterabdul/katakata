#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "logic.h"
#include "utils.h"
#include "word_list.h"

#define CHAR_COUNT 5

/**
 * Print empty lines.
 *
 * @param[in]  lineCount
 * @param[in]  wordLength
 **/
void
printEmpty(int lineCount, int wordLength);

/**
 * Print result lines.
 *
 * @param[in]  lineCount
 * @param[in]  colors
 * @param[in]  words
 * @param[in]  wordLength
 **/
void
printResult(int lineCount,
            Utils__ColorNames_t** colors,
            char** words,
            int wordLength);

/**
 * Make string lowercase.
 *
 * @param[in]  str
 * @param[in]  wordLength
 **/
void
lowerCase(char* str, int wordLength);

/**
 * Check if word exist in the word list.
 *
 * @param[in]  str
 * @param[in]  wordLength
 **/
int
wordExist(char* str, int wordLength);

/**
 * Main function.
 **/
int
main(void)
{
  char scanFormat[7];
  char guessWord[CHAR_COUNT + 1];
  char attempWords[6][CHAR_COUNT + 1];
  Utils__ColorNames_t attempColors[6][CHAR_COUNT];

  char theWord[6];
  srand(time(NULL));
  strncpy(theWord, WordList__Words[rand() % WordList__Count], CHAR_COUNT);

  int attempLeft = 6;
  int sameWord = 0;
  while (1) {
    printResult(6 - attempLeft, (Utils__ColorNames_t**)attempColors, (char**)attempWords, CHAR_COUNT);
    printEmpty(attempLeft, CHAR_COUNT);
    printf("\n");
    if (sameWord)
      break;

    if(attempLeft == 0) {
      printf("Maaf, kesempatan kamu habis.\nKata yang benar adalah: %s\n", theWord);
      break;
    }

    sprintf(scanFormat, " %%%d[^\n]", CHAR_COUNT);
    printf("Masukkan kata (%d huruf)> ", CHAR_COUNT);
    scanf(scanFormat, guessWord);
    while (getchar() != '\n')
      ;
    lowerCase(guessWord, CHAR_COUNT);
    if (wordExist(guessWord, CHAR_COUNT) == 0) {
      printf("Maaf, kata yang dimasukkan tidak dapat ditemukan di KBBI.\n");
      continue;
    }
    printf("\n");

    sameWord = Logic__CheckWord(
      guessWord, theWord, attempColors[6 - attempLeft], CHAR_COUNT);
    strncpy(attempWords[6 - attempLeft], guessWord, CHAR_COUNT);
    attempLeft--;
  }

  return 0;
}

void
printResult(int lineCount,
            Utils__ColorNames_t** colors,
            char** words,
            int wordLength)
{
  for (unsigned int i = 0; i < lineCount; i++) {
    Utils__ColorNames_t* _colors =
      (Utils__ColorNames_t*)colors + (i * wordLength);
    char* _words = (char*)words + (i * (wordLength + 1));
    Utils__PrintCharsColored(_colors, _words, wordLength);
  }
}

void
printEmpty(int lineCount, int wordLength)
{
  for (int i = 0; i < lineCount; i++) {
    for (int j = 0; j < wordLength; j++) {
      Utils__PrintCharColored(UTILS__CN_GRAY, ' ');
      Utils__PrintCharColored(UTILS__CN_GRAY, '_');
      Utils__PrintCharColored(UTILS__CN_GRAY, ' ');
    }
    Utils__PrintCharColored(UTILS__CN_NO_COLOR, '\n');
  }
}

void
lowerCase(char* str, int wordLength)
{
  for (int i = 0; i < wordLength; i++) {
    if (str[i] >= 'A' && str[i] <= 'Z')
      str[i] = str[i] + 0x20;
  }
}

int
wordExist(char* str, int wordLength)
{
  for (int i = 0; i < WordList__Count; i++)
    if (strncmp(str, WordList__Words[i], wordLength) == 0)
      return 1;
  return 0;
}
