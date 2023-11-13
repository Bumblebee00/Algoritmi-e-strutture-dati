// Mattia Micheletta Merlin, esercizio 1, laboratorio 1

#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 100

char *cercaRegexp(char *src, char *regexp);
bool isUpper(char chr);
bool isLower(char chr);

int main()
{
    char src[MAX], regexp[MAX];
    char *result;

    printf("Inserisci la stringa sorgente (max 100 caratteri)   : ");
    scanf(" %[^\n]", src);
    printf("Inserisci l'espressione regolare (max 100 caratteri): ");
    scanf(" %[^\n]", regexp);

    result = cercaRegexp(src, regexp);
    if (result == NULL)
    {
        printf("Regexp non ha nessun match\n");
    }
    else
    {
        printf("Primo match trovato: %s\n", result);
    }
}

/*
. matches any single character
[abc] matches any character contained in the brackets
[^abc] matches any character not contained in the brackets
\A matches a uppercase letter
\a matches a lowercase letter
\. matches a dot
*/
char *cercaRegexp(char *src, char *regexp)
{
    size_t src_len = strlen(src);

    for (int i = 0; i < src_len; i++)
    {
        // we have to check wether src[i] matches the first char of regex exp. if yes, check with the second and so on until either the whole regex expression is matched, or at some point the string is not matched

        // we need two separate indices because one regex block may be more than one charachter
        int str_i = 0;
        int regex_i = 0;

        // check wether characther matches to the regex block
        while (regexp[regex_i] != '\0')
        {
            bool this_char_matches;
            // create a switch case to check if the regex_char is a metacharacter
            switch (regexp[regex_i])
            {
            case '.':
                this_char_matches = true;
                break;

            case '[':
                regex_i++;                                      // to count for the [
                bool case_contained = (regexp[regex_i] != '^'); // true we are in the case [abc], false in the case [^abc]
                // if [abc] this_char_matches is set to false and if we find a match set to true.
                // if [^abc] this_char_matches is set to true and if we find a match set to flase.
                this_char_matches = !case_contained;

                while (regexp[regex_i] != ']')
                {
                    if (regexp[regex_i] == src[i + str_i])
                    {
                        // it counts only the first time it's toggled, but we have to loop for all the brackets anyway
                        this_char_matches = case_contained;
                    }
                    regex_i++;
                }
                break;

            case '\\':
                regex_i++; // to count for the backslash
                if (regexp[regex_i] == 'A')
                {
                    this_char_matches = isUpper(src[i + str_i]);
                }
                else if (regexp[regex_i] == 'a')
                {
                    this_char_matches = isLower(src[i + str_i]);
                }
                else if (regexp[regex_i] == '.')
                {
                    this_char_matches = (src[i + str_i] == '.');
                }
                break;

            default:
                this_char_matches = (src[i + str_i] == regexp[regex_i]);
                break;
            }

            regex_i++;
            str_i++;

            // if a charachter doesnt match
            if (!this_char_matches)
            {
                break;
            } // and continue to check the next string charachter
            // if it matches and we are at the end of the regexp return the pointer to the first charachter of the match
            if (this_char_matches && regexp[regex_i] == '\0')
            {
                return &src[i];
            }
        }
    }
    return NULL;
}

bool isUpper(char chr)
{
    return chr >= 'A' && chr <= 'Z';
}

bool isLower(char chr)
{
    return chr >= 'a' && chr <= 'z';
}