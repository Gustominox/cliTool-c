#ifndef BOX_H_
#define BOX_H_

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/**
 * \brief Function that concatenates a dynamic string with a string literal
 *        allocating space for the new concatenated dynamic string.
 * @param str1 Dynamic string or NULL pointer
 * @param str2 String literal
 * @return Dynamic string (concat of str1 + str2)
 */
char *strcatrealloc(char *str1, char str2[]);

/**
 * \brief Creates Header for box that is being created.
 * @param col Number of column's in box
 * @param output Dynamic string to which header is added
 * @return Dynamic string with header
 */
char *printHead(size_t col, char *output);

/**
 * \brief Creates Bottom for box that is being created.
 * @param col Number of column's in box
 * @param output Dynamic string to which Bottom is added
 * @return Dynamic string with Bottom
 */
char *printClose(size_t col, char *output);

/**
 * \brief Adds horizontal border/buffer of spaces speciefied.
 * @param h_border Number of spaces
 * @param output Dynamic string to which spaces are added
 * @return Dynamic string with spaces
 */
char *printHBorder(size_t h_border, char *output);

/**
 * \brief Adds Empty line with horizontal border.
 * @param col Number of columns to add
 * @param output Dynamic string to which line is added
 * @return Dynamic string with Empty line
 */
char *printEmptyLine(size_t col, char *output);

/**
 * \brief Adds vertical border/buffer of lines speciefied.
 * @param v_border Number of lines
 * @param col Size of lines
 * @param output Dynamic string to which lines are added
 * @return Dynamic string with lines
 */
char *printVBorder(size_t v_border, size_t col, char *output);

/**
 * \brief Calculates string length taking into account unicode simbols.
 * @param string String
 * @return Size of string
 */
size_t strlen_unicode(char string[]);

/**
 * \brief Adds line with argument in the middle.
 * @param line Argument to add
 * @param h_border Number of spaces to add to the horizontal border
 * @param  maxArgsSize Size of the bigger argument, used for formating
 * @param output Dynamic string to which line is added
 * @return Dynamic string with Argument line
 */
char *printLine(char line[], size_t h_border, size_t maxArgsSize, char *output);

/**
 * \brief Given an array of strings, returns the size of the bigger one.
 * @param args Array of strings (where string is char*)
 * @return Size of the biggest string
 */
size_t maxArgsSize(char **args);

/**
 * \brief Creates a Cli Box using unicode characters
 * @param text Content to be added to box, separating lines with '\\n' char
 * @param h_border Number of spaces to add to the horizontal border
 * @param v_border Number of lines to add to the vertical border
 * @return Dynamic string that contains the box specified in the function arguments
 */
char *makeBox(char text[], size_t h_border, size_t v_border);

#endif // BOX_H_
