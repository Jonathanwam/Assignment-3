#include <stdio.h>
#include <stdlib.h>

#define MAX_WORD_SIZE 256

struct node {
    char word[MAX_WORD_SIZE];
    int count;
    struct node *next;
};

char* getNextWord(FILE* fd, struct node **root)
{
    char* word = (char*)malloc(MAX_WORD_SIZE);
    char ch;
    int size=0;

    word[0]='\0';

    while( (ch=fgetc(fd)) != ' ' )
    {
        if(ch==EOF)
            break;
        if(size > MAX_WORD_SIZE-1)
            break;
        word[size]=ch;
        size++;
    }
    if(word[0]=='\0')
        return NULL;
    word[size]='\0';

    int found = 0;
    struct node *head = *root;
    while(head!=NULL)
    {
        if(strcmp(head->word,word)==0)
        {
            found=1;
            head->count=head->count+1;
            break;
        }
        head = head->next;
    }
    if(found==0)
    {
        struct node * nd = (struct node *)malloc(sizeof(struct node));
        int i;
        for(i=0;i<size;i++)
        {
            nd->word[i]=word[i];
        }
        nd->word[i]='\0';
        nd->count = 1;
        nd->next = *root;
        *root = nd;
    }

    return word;
}
int main(int argc, char **argv)
{

    struct node *head = NULL;

    int i;
    for(i=1;i<argc;i++)
    {
        FILE *fd;
        fd = fopen(argv[i],"r");


        char* str;
        while( (str=getNextWord(fd, &head))!=NULL);

        fclose(fd);
    }

    while(head!=NULL)
    {
        printf("%10d %s\n",head->count,head->word);
        head=head->next;
    }

    return 0;
}
