#include "../include/utils.h"
#include <ctype.h>
#include <string.h>

// Function to check if a number is prime
int is_prime(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
}

// Case-insensitive string comparison
char *str_case_str(const char *haystack, const char *needle)
{
    if (!needle || !*needle)
    {
        return (char *)haystack;
    }

    while (*haystack)
    {
        const char *h = haystack;
        const char *n = needle;
        while (*h && *n && (tolower((unsigned char)*h) == tolower((unsigned char)*n)))
        {
            h++;
            n++;
        }
        if (!*n)
        {
            return (char *)haystack;
        }
        haystack++;
    }
    return NULL;
}
