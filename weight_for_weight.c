#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void show(char** arr, int arr_size);

int
main() {
    char *str = "1 200 2 4 4 6 6 7 7 9 18 27 72 81 91 425 7920 31064 67407 96488 34608557 71899703",
         *in = (char*) malloc(sizeof(char) * strlen(str)),  // needed to pass char* to strtok
             *sep = " ";

    in = strcpy(in, str);

    char* number = strtok(in, sep);

    int arr_size = 0;

    char** arr = (char**) calloc(1, sizeof(char*));
    *arr = number;
    arr_size++;

    for (int i = 1; (number = strtok(NULL, sep)) != NULL; i++) {
        int aux = i - 1;

        arr = (char**) realloc(arr, sizeof(char*) * (i + 1));
        arr[i] = number;
        arr_size++;

        for (int j = i; aux >= 0; j--) {
            char* tmp;
            int cur_size = 0, aux_size = 0,
                size = strlen(number) > strlen(arr[aux]) ? strlen(number) : strlen(arr[aux]);

            for (int i = 0; i < size; i++) {
                if ((unsigned int) i < strlen(arr[aux]))
                    aux_size += arr[aux][i] - '0';  // convert char to int
                if ((unsigned int) i < strlen(number))
                    cur_size += number[i] - '0';  // convert char to int
            }

            if (cur_size < aux_size) {
                tmp = arr[aux];
                arr[aux] = arr[j];
                arr[j] = tmp;
            }

            if (cur_size == aux_size) {
                for (int i = 0; i < size; i++) {
                    if ((unsigned int) i == strlen(number) || (unsigned int) i == strlen(arr[aux]))
                        break;

                    if (number[i] < arr[aux][i]) {
                        tmp = arr[aux];
                        arr[aux] = arr[j];
                        arr[j] = tmp;
                        break;
                    };
                }
            }

            aux--;
        }
    }

    char* res = (char*) malloc(sizeof(char) * strlen(str));

    for (int i = 0; i < arr_size; i++)
        strcat(strcat(res, arr[i]), " ");

    res[strlen(str)] = '\0';

    free(arr);
    free(in);

    printf("%s\n", res);

    return 0;
}

void
show(char** arr, int arr_size) {
    for (int i = 0; i < arr_size; i++)
        printf("%s ", arr[i]);

    printf("\n");
}
