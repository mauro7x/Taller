#include <stdio.h>
#include <string.h>
#include <stdint.h>


// constantes para el header

#define ENDIANNESS 'l'
#define BYTE_FOR_METHOD_CALLS 0x01
#define HEADER_FLAGS 0x00
#define PROTOCOL_VERSION 0x01



int main() {

    uint32_t body_length = 18;
    uint32_t id_msg = 1;
    char header[12];

    sprintf(header, "%c%d%d%d", 'l', 1, 0, 1);

    memcpy(header+4, &body_length, sizeof(body_length));
    memcpy(header+8, &id_msg, sizeof(id_msg));

    for (int i = 0; i < 4; i++) {
        printf("byte%i = %c\n", i, header[i]);
    }

    for (int i = 4; i < 12; i++) {
        printf("byte%i = %d\n", i, header[i]);
    }

    // ahora leemos desde nuestro header, de a bytes.

    char r_1;
    char r_2;
    char r_3;
    char r_4;
    uint32_t r_5;
    uint32_t r_6;

    memcpy(&r_1, header, sizeof(r_1));
    memcpy(&r_2, header+1, sizeof(r_2));
    memcpy(&r_3, header+2, sizeof(r_3));
    memcpy(&r_4, header+3, sizeof(r_4));
    memcpy(&r_5, header+4, sizeof(r_5));
    memcpy(&r_6, header+8, sizeof(r_6));


    printf("r1 = %c, r2 = %c, r3 = %c, r4 = %c, r5 = %d, r6 = %d\n",
            r_1, r_2, r_3, r_4, r_5, r_6);

    return 0;
}