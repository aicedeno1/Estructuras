#ifndef VALIDACIONES_H
#define VALIDACIONES_H

#include <string>

class Validaciones {
public:
    int ingresarEntero(const char* msj);
    float ingresarFloat(const char* msj);
    double ingresarDouble(const char* msj);

private:
    int convertirAEntero(const std::string& input);
    float convertirAFloat(const std::string& input);
    double convertirADouble(const std::string& input);
};

#endif
