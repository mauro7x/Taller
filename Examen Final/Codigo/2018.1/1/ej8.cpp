// includes
#include <stdio.h>
#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <list>
#include <vector>
#include <algorithm>
#include <cstdint>

#include <string.h>

class Oracion {
    private:
        char *a;

    public:
        Oracion() : a(NULL) {}

        Oracion(char* a) : a(a) {} // adquiere el owner-ship

        Oracion(const Oracion& copiable) {
            size_t len = strlen(copiable.a);
            this->a = (char*) malloc(len+1);
            strncpy(this->a, copiable.a, len+1);
        }

        Oracion& operator=(const Oracion& copiable) {
            size_t len = strlen(copiable.a);
            this->a = (char*) malloc(len+1);
            strncpy(this->a, copiable.a, len+1);
            return *this;
        }

        ~Oracion() {
            if (a) {
                free(a);
                a = NULL;
            }
        } 

        Oracion operator-(const Oracion& other) const {
            size_t this_size = strlen(this->a);
            size_t other_size = strlen(other.a);

            size_t ocurrencias = 0;
            char* aux = strstr(this->a, other.a);
            while (aux) {
                ocurrencias++;
                aux = strstr(aux+1, other.a);
            }

            size_t final_size = this_size - (other_size * ocurrencias);
            char* res = (char*) malloc(final_size + 1);
            res[final_size] = '\0';

            size_t res_i = 0;
            for (size_t i = 0; i < this_size; i++) {
                if (strncmp(&(this->a)[i], other.a, other_size) == 0) {
                    i += (other_size - 1);
                    continue;
                }

                res[res_i++] = (this->a)[i];
            }

            return Oracion(res);
        }
        
        friend std::ostream& operator<<(std::ostream& ostream, const Oracion& oracion) {
            ostream << oracion.a;
            return ostream;
        }
};

int main(int argc, char* argv[]) {
    char a[] = "holacomoestas?";
    size_t len = strlen(a);
    char* b = (char*)malloc(len+1);
    strncpy(b, a, len+1);
    Oracion o1(b);

    char a2[] = "como";
    len = strlen(a2);
    b = (char*)malloc(len+1);
    strncpy(b, a2, len+1);
    Oracion o2(b);

    std::cout << o1 << std::endl;
    std::cout << o2 << std::endl;
    std::cout << (o1 - o2) << std::endl;
    
    return 0;
}
