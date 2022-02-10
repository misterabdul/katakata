#ifndef __UTILS_H
#define __UTILS_H

#include <stdio.h>

/**
 * ANSI Color Names
 **/
typedef enum ColorNames
{
  UTILS__CN_NO_COLOR,
  UTILS__CN_GRAY,
  UTILS__CN_YELLOW,
  UTILS__CN_GREEN,
} Utils__ColorNames_t;

/**
 * Print char with given background color code.
 *
 * @param[in]  code  The color code.
 * @param[in]  c     The character to be printed.
 **/
void
Utils__PrintCharColored(Utils__ColorNames_t code, char c)
{
  switch (code) {
    default:
    case UTILS__CN_NO_COLOR:
      printf("\e[m%c", c);
      return;
    case UTILS__CN_GRAY:
      printf("\e[40m%c", c);
      return;
    case UTILS__CN_YELLOW:
      printf("\e[43m%c", c);
      return;
    case UTILS__CN_GREEN:
      printf("\e[42m%c", c);
      return;
  }
}

/**
 * Print characters with colored background.
 *
 * @param[in]  colors  The array of colors.
 * @param[in]  chars   The array of characters.
 * @param[in]  arrLen  The array length.
 **/
void
Utils__PrintCharsColored(Utils__ColorNames_t* colors, char* chars, int arrLen)
{
  for (int i = 0; i < arrLen; i++) {
    Utils__PrintCharColored(colors[i], ' ');
    Utils__PrintCharColored(colors[i], chars[i]);
    Utils__PrintCharColored(colors[i], ' ');
  }
  Utils__PrintCharColored(UTILS__CN_NO_COLOR, '\n');
}

#endif
