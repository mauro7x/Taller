#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct param {
    char* param;
    size_t param_len;
} param_t;

typedef struct call {
    int already_filled;

    char* dest;
    size_t dest_len;
    char* path;
    size_t path_len;
    char* interface;
    size_t interface_len;
    char* method;
    size_t method_len;
    char* params_string;
    size_t params_string_len;

    param_t* params;
    size_t n_params;
} call_t;

static void parser(call_t* self, char delimiter) {
    char* string = self->params_string;
    size_t len = self->params_string_len;

    size_t n_params = 1;
    for (int i = 0; i < len; i++) { // cuento cuantos hay
        if (string[i] == delimiter) {
            n_params++;
        }
    }
   
    param_t* params = (param_t*) malloc(sizeof(param_t)*n_params);

    
    

    char* current_param;
    int last_delimiter = 0;
    size_t current_param_len = 0;
    int params_added = 0;

    for (int i = 0; i < len; i++) {
        if ((string[i] == delimiter) || (i == len-1)) {

            if (i == len-1) {
                current_param_len++;
            }

            current_param = (char*) malloc(sizeof(char)*(current_param_len+1));
            strncpy(current_param, string + last_delimiter, current_param_len);

            // param_t new_param;
            // new_param.param = current_param;
            // new_param.param_len = current_param_len;
            // params[params_added] = new_param;
            
            params[params_added].param = current_param;
            params[params_added].param_len = current_param_len;
            
            printf("agregue el parametro %d \n\n", params_added);

            current_param_len = 0;
            params_added++;
            last_delimiter = i+1;

        } else {
            printf("todavia no explote, caracter: %c\n", string[i]);
            current_param_len++;
        }
    }




    

    self->n_params = n_params;
    self->params = params;
    // free(string);

}

int main() {

    call_t call;

    call.params_string = "param1,param2";
    call.params_string_len = 13;

    parser(&call, ',');


    printf("long del primer param: %ld\n", call.params[0].param_len);
    printf("long del segundo param: %ld\n", call.params[1].param_len);

    call.params[0].param[call.params[0].param_len] = '\0';
    call.params[1].param[call.params[1].param_len] = '\0';

    printf("primer param: %s\n", call.params[0].param);
    printf("segundo param: %s\n", call.params[1].param);


    // printf();

    
    if (call.params != NULL) {
        for (int i = 0; i < (call.n_params); i++) {
            free(call.params[i].param);
        }
        free(call.params);
    }
    


    return 0;
}