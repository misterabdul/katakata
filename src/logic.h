#ifndef __LOGIC_H
#define __LOGIC_H

#include "utils.h"

/**
 * Check the guess word.
 *
 * @param[in]  guessWord    The guess word
 * @param[in]  theWord      The correct word
 * @param[out] resultColors Result colors for each characters in the guess word
 * @param[in]  wordLength   Length of the word
 * @return                  1 if guess word right, 0 for opposite
 **/
int
Logic__CheckWord(char* guessWord,
                 char* theWord,
                 Utils__ColorNames_t* resultColors,
                 int wordLength)
{
  int sameWord = 1;
  for (int i = 0; i < wordLength; i++) {
    resultColors[i] = UTILS__CN_GRAY;
    if (guessWord[i] == theWord[i]) {
      resultColors[i] = UTILS__CN_GREEN;
    } else {
      for (int j = 0; j < wordLength; j++)
        if (i != j && guessWord[i] == theWord[j]) {
          resultColors[i] = (i == j) ? UTILS__CN_GREEN : UTILS__CN_YELLOW;
          break;
        }
    }
    sameWord = sameWord && resultColors[i] == UTILS__CN_GREEN ? 1 : 0;
  }
  return sameWord;
}

#endif
