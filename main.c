#include "functions.h"

int main(int argc, char const *argv[])
{
	const char *help_options = "\n\tDocumentation\n \toptions: \n\t-i <input file>\n optional:\n\t-o <output file> // by default output.txt \n\n";

    if(argc < 2)
    {
        printf("%s", help_options);
        return 1;
    }                    

    const char * _i = getOption("-i",(char*)0, argc, argv);
    const char * _o = getOption("-o","output.txt", argc, argv);

    if ((char*)0 == _i || ('-' == _i[0] || '-' == _o[0]))
    {
        printf("%s", help_options);
        return 1;
    }

    FILE *f_i;
    f_i = fopen(_i, "r");
    if(f_i == NULL)
    {
        printf("! error: file %s not found!\n", _i);
        return 1;
    }

    char* buf = malloc(255*sizeof(char));
    if(buf == NULL)
    {
        printf("! error: not enough memory!\n");
        free(buf);
        fclose(f_i);
        return 1;
    }



    struct book *book_head = NULL;
    struct list *list_head = NULL;

    char c;
    do{
        
        c = getFileData(',', buf, f_i);

        if(buf[0]==' ') buf = &(buf[1]); 
        char* autor = malloc(strlen(buf)*sizeof(char));
        strcpy(autor, buf);

        c = getFileData(',', buf, f_i);
        if(buf[0]==' ') buf = &(buf[1]); 
        char* title = malloc(strlen(buf)*sizeof(char));
        strcpy(title, buf);

        struct book *new = malloc(sizeof(struct book));
        new->autor = autor;
        new->title = title;
        new->next = book_head;
        book_head = new;

        while(c = getFileData(',', buf, f_i), true){
            if(buf[0]==' ') buf = &(buf[1]); 
            if(c == '\n') buf[strlen(buf)-1] = '\0';

            struct books *tmp_books = malloc(sizeof(struct books));
            tmp_books->b = new;

            struct list* tmp = list_head;
            while(tmp != NULL)
            {
                if(!strcmp(tmp->name, buf)) break;
                tmp = tmp->next;
            }

            if(tmp != NULL)
            {
                tmp_books->next = tmp->b;
                tmp->b = tmp_books;
            } else {
                struct list* new_list = malloc(sizeof(struct list));
                char* list_name = malloc(strlen(buf)*sizeof(char));
                strcpy(list_name, buf);
                new_list->name = list_name;
                new_list->b = tmp_books;

                if(list_head == NULL) list_head = new_list;
                else if(strcmp(new_list->name, list_head->name) < 0)
                {
                    new_list->next = list_head;
                    list_head = new_list;
                }
                else if(list_head->next == NULL)
                {
                    list_head->next = new_list;
                    new_list->next = NULL;
                }
                else
                {
                    tmp = list_head;
                    struct list* tmp2 = list_head->next;
                    while(tmp2 != NULL)
                    {
                        if(strcmp(new_list->name, tmp2->name) < 0)
                        {
                            new_list->next = tmp2;
                            tmp->next = new_list;
                            break;
                        }
                        tmp = tmp->next;
                        tmp2 = tmp2->next;
                    }
                    if(tmp2 == NULL)
                    {
                        tmp2->next = new_list;
                        new_list->next = NULL;
                    }
                }
            }

            if(c == EOF || c == '\n') break;
        }

    }while(c != EOF);

    while(list_head != NULL)
    {
        printf("\n%s:\n", list_head->name);
        struct books *tmp_books = list_head->b;
        while(tmp_books != NULL)
        {
            printf("\t%s,", tmp_books->b->autor);
            printf("%s\n", tmp_books->b->title);

            tmp_books = tmp_books->next;
        }
        list_head = list_head->next;
    }

	return 0;
}