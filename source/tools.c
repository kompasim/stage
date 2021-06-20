// tools

#include "head.h"

#ifdef WIN32
    #include <Windows.h>
#else
    // TODO
#endif

int get_max(int a, int b)
{
	return (a > b ? a : b);
}
 
int get_min(int a, int b)
{
	return (a < b ? a : b);
}

void do_message(char * msg)
{
    char txt[1024];
    sprintf(txt, "MSG:%s", msg);
    #ifdef WIN32
        MessageBox(NULL, txt, "Message", MB_OK);
    #else
        // TODO
    #endif
}

void do_error(const char *msg)
{
    char txt[1024];
    sprintf(txt, "ERR:%s", msg);
    #ifdef WIN32
        MessageBox(NULL, txt, "Error", MB_ICONERROR);
    #else
        // TODO
    #endif
    exit(EXIT_FAILURE);
}

void do_assert(bool value, char *txt)
{
    if(value) return;
    do_error(txt);
}

inline bool is_empty(char ch)
{
	return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
}

char *do_copy(char* ch, int start, int end)  
{ 
    int count = 0;
    int length = (end - start + 1);
    char *temp = (char*)calloc(sizeof(char), end - start + 1);
    int len = strlen(ch);
    for (int i = 0; i < len; i++)
    {
        if (i < start || i > end) continue;
        temp[count] = ch[i];
        count++;
    }
    return temp;
} 

char *do_trim(char *str)
{
	char *target;
    int len = strlen(str);
    // left
    int left = 0;
    char a = str[left];
	while (is_empty(a) && left < len)
    {
        left++;
        a = str[left];
    }
    // right
    int right = len - 1;
    char z = str[right];
	while (is_empty(z) && right > 0)
    {
        right--;
        z = str[right];
    }
    // copy
    char *r = do_copy(str, left, right);
	return r;
}

bool is_contains(char *source, char *find)
{
    return strstr(source, find) != NULL;
}

bool is_starts(char *source, char *find)
{
    return strncmp(find, source, strlen(find)) == 0;
}

bool is_ends(const char *source, const char *find)
{
    bool result = true;
    int fLen = strlen(find);
    int sLen = strlen(source);
    for (size_t i = strlen(find); i > 0 ; i--)
    {
        int index = fLen - i + 1;
        char a = find[fLen - index];
        char b = source[sLen - index];
        if(a != b)
        {
            result = false;
        }
    }
    return result;
}

char *to_uppercase(char* ch)  
{ 
    int len = strlen(ch);
    char *temp = (char*)calloc(sizeof(char), len);
    for (int i = 0; i < len; i++)
    {
        temp[i] = toupper(ch[i]);
    }
    return temp;
}

char *to_lowercase(char* ch)  
{ 
    int len = strlen(ch);
    char *temp = (char*)calloc(sizeof(char), len);
    for (int i = 0; i < len; i++)
    {
        temp[i] = tolower(ch[i]);
    }
    return temp;
} 

bool is_similar(char *a, char *b)
{
    return strcmp(to_lowercase(a), to_lowercase(b)) == 0;
}

char *do_concat(const char *this, const char *that)
{
    char* result;
    result = malloc(strlen(this) + strlen(that));
    strcpy(result, this);
    strcat(result, that);
    return result;
}
