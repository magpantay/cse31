#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#define MAXSIZE 4096

/**
 * You can use this recommended helper function
 * Returns true if partial_line matches pattern, starting from
 * the first char of partial_line.
 */
  
int matches_leading(char *partial_line, char *pattern) {
	int i = 0;
	int j = 0;
	int plusCount = 0;
	while (pattern[i] != '\0')
	{
		if (partial_line[j] == '\0')
		{
			return 0; //nothing matches
		}
		else if (partial_line[j] == '\n')
		{
			j++; //next line (since it would be a newline)
		}
		else if (pattern[i] == '?' && pattern[i-1] == '\\')
		{
			if (pattern[i] == partial_line[j])
			{
				i++; //next char of pattern
				j++; //next char of partial_line
			}
			else
			{
				i = 0; //reset pattern to start at 0
				j++; //but still traverse partial_line
			}
		}
		else if (pattern[i] == '.' && pattern[i-1] == '\\')
		{
			if (pattern[i] == partial_line[j])
			{
				i++; //next char of pattern
				j++; //next char of partial_line
			}
			else
			{
				i = 0; //reset pattern to start at 0
				j++; //but still traverse partial_line
			}
		}
		else if (pattern [i] == '+' && pattern[i-1] == '\\')
		{
			if (pattern[i] == partial_line[j])
			{
				i++; //next char of pattern
				j++; //next char of partial_line
			}
			else
			{
				i = 0; //reset pattern to start at 0
				j++; //but still traverse partial_line
			}
		}
		else if (pattern[i+1] == '\\' && pattern[i] == '\\')
		{
			if (pattern[i+1] == partial_line[j])
			{
				i+=2; //next char of pattern
				j++; //next char of partial_line
			}
			else
			{
				i = 0; //reset pattern to start at 0
				j++; //but still traverse partial_line
			}
		}
		else if (pattern[i] == '\\' && (pattern[i+1] != '+' || pattern[i+1] != '.' || pattern[i+1] != '?' || pattern[i+1] != '\\'))
		{
			if (pattern[i+1] == partial_line[j])
			{
				i+=2;
				j++;
			}
			else
			{
				i = 0;
				j++;
			}
		}
		else if ((pattern[i] == '+') && (pattern[i-1] != '\\'))
		{
			plusCount++;
			char characterBeforePlus = pattern [i-1];
			if (characterBeforePlus == '.') //now if the character before plus is a dot (ex. w.+h)
			{
				characterBeforePlus = partial_line[j]; //make character before plus equal the current character of partial_line
			} 	//necessary for the special case of dot, because if it didn't do this, it would literally match dot to whatever partial_line
			
			while(characterBeforePlus == partial_line[j])
			{
					j++; //keep going while it's a match
			}	
			i++; //increment pattern to go to the next character
			int pattern_length = strlen(pattern); //get the lengths
			int line_length = strlen(partial_line); //of the strings
			
			while ((pattern[i] == characterBeforePlus) && ((pattern_length - plusCount) < (line_length)))
			{
				i++; //"ignore" the next character if the next character after + matches the character before plus, but check the string lengths so it doesn't print out any non-matches
			}	

		} 
		else if ((pattern[i] == partial_line[j]) || (pattern[i] == '.' && partial_line[j+1] != '\0' && pattern[i-1] != '\\')) //'.' acts like a match and checks ahead for a null terminator
		{
			i++; //next char of pattern
			j++; //next char of partial_line
		}
		else if (pattern[i] == '\\')
		{
			i++; //here because all of my checks for \[symbol] have it so if the previous character is a '\\'
		}
		else if (pattern[i] != partial_line[j])
		{
			i = 0; //reset pattern to start at 0
			j++; //but still traverse partial_line
		}
		else
		{
			return 0; //nothing matches
		}
	}

   return 1;
}
/**
 * You may assume that all strings are properly null terminated
 * and will not overrun the buffer set by MAXSIZE
 *
 * Implementation of the rgrep matcher function
 */
int rgrep_matches(char *line, char *pattern) {
	int i = 0;
	int symbolCheck = 1; //checks if there are certain symbols ('\\' and '?') before calling matches_leading 
	int return_value = 0; //because make was warning that I didn't return a value in the end, so I just made a return_value that equals 0 unless changed to 1 by a match from matches_leading
	while (pattern[i] != '\0') //traverse pattern to see if there are special characters (except for '.' and '+')
	{
		if ((pattern[i] == '?')	|| (pattern[i] == '\\'))
		{
			symbolCheck = 0;
		}
		i++;
	}
	
	if (symbolCheck == 1) //if there are no special characters after traversing the pattern (except for '.' and '+')
	{
		return_value = matches_leading(line, pattern); //call matches_leading
	}
	
	else //now if symbolCheck == 0, reset and trace down symbols
	{
		i = 0;
		if (pattern[i] == '?' || pattern[i-1] != '\\') //flawed logic works 
		{
			char string_without_char[strlen(pattern) - 2]; 
			char string_with_char[strlen(pattern) - 1];
	
			int traverse_1 = 0;
			int traverse_2 = 0;
			
			while (pattern[traverse_1] != '\0') //with the character
			{
				if (pattern [traverse_1] == '?') 
				{
					traverse_1++;
				}
				string_with_char [traverse_2] = pattern [traverse_1];
	
				traverse_1++;
				traverse_2++;
			}
			
			traverse_1 = 0;
			traverse_2 = 0;
			
			while (pattern[traverse_1] != '\0') //without the character
			{
				if (pattern[traverse_1 + 1] == '?') //if the next character over is a question mark
				{
					traverse_1 += 2; //skip that character and the question mark
				}
				string_without_char[traverse_2] = pattern[traverse_1];
				traverse_1++;
				traverse_2++;
			}
			
			/* because calling the matches_leading function within an if statement like 
			   if ((matches_leading(string_without_char)) || (matches_leading (string_with_char)))
			   made question mark only work partially, just separated calling matches_leading into two boolean ints
			   as seen below
		   */
		   
			int return_with_char = 0; 
			int return_without_char = 0;
			return_without_char = matches_leading(line, string_without_char);
			return_with_char = matches_leading(line, string_with_char);
			
			if (return_without_char || return_with_char)
			{
				return_value = 1;
			}
		}
		if (pattern[i] == '?' && pattern[i-1] == '\\')
		{
			matches_leading(line,pattern);
		}
	}
	return return_value;
} 

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <PATTERN>\n", argv[0]);
        return 2;
    }

    /* we're not going to worry about long lines */
    char buf[MAXSIZE];

    while (!feof(stdin) && !ferror(stdin)) {
        if (!fgets(buf, sizeof(buf), stdin)) {
            break;
        }
        if (rgrep_matches(buf, argv[1])) {
            fputs(buf, stdout);
            fflush(stdout);
        }
    }

    if (ferror(stdin)) {
        perror(argv[0]);
        return 1;
    }

    return 0;
}
