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
	while (pattern[i] != '\0')
	{
		if (partial_line[j] == '\0')
		{
			return 0; //nothing matches
		}
		else if ((pattern[i] == partial_line[j]) || ((pattern[i] == '.')&&(partial_line[j + 1] != '\0'))) //'.' acts like a match
		{
			i++; //next char of pattern
			j++; //next char of partial_line
		}
		else if (pattern[i] == '+')
		{
			char characterBeforePlus = pattern [i - 1];
			while(characterBeforePlus == partial_line[j])
			{
					j++;
			}	
			i++;
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
  int return_value = matches_leading(line, pattern);
  
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
