/********************************************************************************************
 *            UNIVERSIDAD DE LAS FUERZAS ARMADAS ESPE                                       *
 * Proposito:                      Validaciones de entrada de datos                         *
 * Autor:                          Abner Arboleda, Christian Acuña, Christian Bonifaz       *
 * Fecha de creacion:              01/12/2024                                               *
 * Fecha de modificacion:          08/11/2024                                               *
 * Materia:                        Estructura de datos                                      *
 * NRC :                           1992                                                     *
 ********************************************************************************************/


#include "Validaciones.h"

// Validación de fecha
bool Validaciones::validarFecha(const string& fecha) {
    regex formatoFecha(R"(\d{2}-\d{2}-\d{4})");
    if (!regex_match(fecha, formatoFecha)) {
        cout << "Error: El formato de la fecha debe ser DD-MM-YYYY.\n";
        return false;
    }

    int dia, mes, anio;
    sscanf(fecha.c_str(), "%d-%d-%d", &dia, &mes, &anio);

    if (anio <= 0 || mes < 1 || mes > 12 || dia < 1 || dia > diasEnMes(mes, anio)) {
        cout << "Error: Fecha no válida.\n";
        return false;
    }

    // Obtener la fecha actual
    time_t t = time(nullptr);
    tm* fechaActual = localtime(&t);

    int diaActual = fechaActual->tm_mday;
    int mesActual = fechaActual->tm_mon + 1;
    int anioActual = fechaActual->tm_year + 1900;

    // Verificar que la fecha ingresada no sea mayor a la actual
    if (anio > anioActual || (anio == anioActual && mes > mesActual) || (anio == anioActual && mes == mesActual && dia > diaActual)) {
        cout << "Error: La fecha no puede ser mayor a la fecha actual.\n";
        return false;
    }

    // Validar que la fecha de nacimiento sea al menos 5 años antes de la fecha actual
    if (anio > anioActual - 5 || (anio == anioActual - 5 && (mes > mesActual || (mes == mesActual && dia > diaActual)))) {
        cout << "Error: La fecha de nacimiento debe ser al menos 5 años antes de la fecha actual.\n";
        return false;
    }
    
    return true;
}


// Validación de título y nombre
bool Validaciones::validarTituloNombre(const string& texto, const string& campo) {
    regex formatoTituloNombre(R"(([A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)(\s[A-ZÁÉÍÓÚÑ][a-záéíóúñ]+)*)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTituloNombre)) {
        cout << "Error: El campo " << campo << " debe comenzar con una letra mayúscula y las demas minúsculas.\n";
        return false;
    }
    return true;
}

// Validación de título
bool Validaciones::validarTitulo(const string& texto, const string& campo) {
    regex formatoTitulo(R"(([A-ZÁÉÍÓÚÑa-záéíóúñ0-9#\+\-]+)(\s[A-ZÁÉÍÓÚÑa-záéíóúñ0-9#\+\-]+)*)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTitulo)) {
        cout << "Error: El campo " << campo << " debe comenzar con una letra mayúscula, número o carácter especial permitido y cada palabra debe tener al menos una letra.\n";
        return false;
    }

    // Verificar que cada palabra comience con mayúscula y las demás letras sean minúsculas o caracteres especiales permitidos
    stringstream ss(texto);
    string palabra;
    while (ss >> palabra) {
        if (!isupper(palabra[0]) && !isdigit(palabra[0])) {
            cout << "Error: Cada palabra debe comenzar con una letra mayúscula o un número.\n";
            return false;
        }
        for (size_t i = 1; i < palabra.size(); ++i) {
            if (!islower(palabra[i]) && !isdigit(palabra[i]) && palabra[i] != '#' && palabra[i] != '+' && palabra[i] != '-') {
                cout << "Error: Las letras después de la primera deben ser minúsculas o caracteres especiales permitidos.\n";
                return false;
            }
        }
    }

    return true;
}


bool Validaciones::validarFechaPublicacion(const string& fechaPub, const string& fechaNacAutor) {
    try {
        // Crear objetos Fecha a partir de las cadenas de texto
        Fecha fechaPublicacion = Fecha::crearDesdeCadena(fechaPub);
        Fecha fechaNacimiento = Fecha::crearDesdeCadena(fechaNacAutor);

        // Validar que ambas fechas sean válidas
        if (!Fecha::esFechaValida(fechaPublicacion.getDia(), fechaPublicacion.getMes(), fechaPublicacion.getAnio()) ||
            !Fecha::esFechaValida(fechaNacimiento.getDia(), fechaNacimiento.getMes(), fechaNacimiento.getAnio())) {
            cout << "Error: Una o ambas fechas no son válidas.\n";
            return false;
        }

        // Obtener la fecha actual
        time_t t = time(nullptr);
        tm* fechaActual = localtime(&t);

        int diaActual = fechaActual->tm_mday;
        int mesActual = fechaActual->tm_mon + 1;
        int anioActual = fechaActual->tm_year + 1900;

        // Verificar que la fecha ingresada no sea mayor a la actual
        if (fechaPublicacion.getAnio() > anioActual || (fechaPublicacion.getAnio() == anioActual && fechaPublicacion.getMes() > mesActual) || (fechaPublicacion.getAnio() == anioActual && fechaPublicacion.getMes() == mesActual && fechaPublicacion.getDia() > diaActual)) {
            cout << "Error: La fecha no puede ser mayor a la fecha actual.\n";
            return false;
        }

        // Comparar si la diferencia de años es menor a 4
        int diferenciaAnios = fechaPublicacion.getAnio() - fechaNacimiento.getAnio();
        if (diferenciaAnios < 4) {
            cout << "Error: La fecha de publicación debe ser al menos 4 años posterior al año de nacimiento del autor (" 
                << fechaNacimiento.getAnio() << ").\n";
            return false;
        }

        return true;
    } catch (const invalid_argument& e) {
        // En caso de que alguna fecha no sea válida
        cout << "Error: " << e.what() << endl;
        return false;
    }
}



bool Validaciones::validarIsbn(const string& isbn) {
    if (isbn.empty()) {
        cout << "Error: El ISBN no puede estar vacío.\n";
        return false;
    }

    // Validar formato de guiones
    if (isbn.front() == '-' || isbn.back() == '-') {
        cout << "Error: El ISBN no puede comenzar ni terminar con un guion.\n";
        return false;
    }

    if (isbn.find("--") != string::npos) {
        cout << "Error: El ISBN no puede contener guiones consecutivos.\n";
        return false;
    }
    string isbnSinGuiones = isbn;
    isbnSinGuiones.erase(remove(isbnSinGuiones.begin(), isbnSinGuiones.end(), '-'), isbnSinGuiones.end());

    // Verificar que todos los caracteres no sean iguales
    if (all_of(isbnSinGuiones.begin(), isbnSinGuiones.end(), [isbnSinGuiones](char c) { return c == isbnSinGuiones[0]; })) {
        cout << "Error: El ISBN no puede contener todos los caracteres iguales.\n";
        return false;
    }

    if (isbnSinGuiones.size() == 10) {
        return validarIsbn10(isbnSinGuiones);
    } else if (isbnSinGuiones.size() == 13) {
        return validarIsbn13(isbnSinGuiones);
    }
    cout << "Error: El ISBN debe tener 10 o 13 caracteres (sin contar los guiones).\n";
    return false;
}

bool Validaciones::validarIsbn10(const string& isbn) {
    if (isbn.size() != 10) {
        return false;
    }

    // Verificar que los primeros 9 caracteres sean dígitos y el último sea un dígito o 'X'
    for (int i = 0; i < 9; i++) {
        if (!isdigit(isbn[i])) {
            return false;
        }
    }

    char digitoControl = isbn[9];
    if (!(isdigit(digitoControl) || digitoControl == 'X')) {
        return false;
    }

    // Validar el dígito de control
    return calcularDigitoControlIsbn10(isbn) == 0;
}

bool Validaciones::validarIsbn13(const string& isbn) {
    if (isbn.size() != 13) {
        return false;
    }

    // Verificar que todos los caracteres sean dígitos
    for (int i = 0; i < 13; i++) {
        if (!isdigit(isbn[i])) {
            return false;
        }
    }

    // Validar el dígito de control
    return calcularDigitoControlIsbn13(isbn) == 0;
}

int Validaciones::calcularDigitoControlIsbn10(const string& isbn) {
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        suma += (isbn[i] - '0') * (10 - i);
    }
    char digitoControl = isbn[9];
    if (digitoControl == 'X') {
        suma += 10;
    } else {
        suma += (digitoControl - '0');
    }
    return suma % 11;
}

int Validaciones::calcularDigitoControlIsbn13(const string& isbn) {
    int suma = 0;
    for (int i = 0; i < 12; i++) {
        if (i % 2 == 0) {
            suma += (isbn[i] - '0');
        } else {
            suma += (isbn[i] - '0') * 3;
        }
    }
    int digitoControlCalculado = (10 - (suma % 10)) % 10;
    return digitoControlCalculado == (isbn[12] - '0') ? 0 : -1;
}

// Validación de ISNI
bool Validaciones::validarIsni(const string& isni) {
    // Remover espacios y guiones del ISNI
    std::string isniSinEspacios = isni;
    isniSinEspacios.erase(
        std::remove_if(isniSinEspacios.begin(), isniSinEspacios.end(),
                    [](char c) { return c == '-' || c == ' '; }),
        isniSinEspacios.end());

    // Verificar que el tamaño sea exactamente 16 caracteres
    if (isniSinEspacios.size() != 16) {
        std::cout << "Error: El ISNI debe contener exactamente 16 caracteres (sin incluir espacios ni guiones).\n";
        return false;
    }

    // Verificar que los primeros 15 caracteres sean numéricos
    if (!std::all_of(isniSinEspacios.begin(), isniSinEspacios.end() - 1, ::isdigit)) {
        std::cout << "Error: Los primeros 15 caracteres del ISNI deben ser numéricos.\n";
        return false;
    }

    // Verificar que el último carácter sea un dígito o una 'X'
    char lastChar = isniSinEspacios[15];
    if (!(std::isdigit(lastChar) || lastChar == 'X')) {
        std::cout << "Error: El último carácter del ISNI debe ser un dígito o 'X'.\n";
        return false;
    }

    // Verificar que todos los caracteres no sean iguales
    if (all_of(isniSinEspacios.begin(), isniSinEspacios.end(), [isniSinEspacios](char c) { return c == isniSinEspacios[0]; })) {
        std::cout << "Error: Ingrese un Isni Valido.\n";
        return false;
    }

    // Cálculo del dígito de control
    int sum = 0;
    int weight = 1; // Alternating weights: 1, 2
    for (int i = 0; i < 15; ++i) {
        int digit = isniSinEspacios[i] - '0';
        sum += digit * weight;
        weight = (weight == 1) ? 2 : 1;
    }

    return true;
}


// Validación de texto no vacío
bool Validaciones::validarTextoNoVacio(const string& texto, const string& campo) {
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    }
    return true;
}

// Validación de texto
bool Validaciones::validarTexto(const string& texto, const string& campo) {
    regex formatoTexto(R"([a-zA-ZñÑáéíóúÁÉÍÓÚ\s]+)");
    if (texto.empty() || texto.find_first_not_of(' ') == string::npos) {
        cout << "Error: El campo " << campo << " no puede estar vacío o contener solo espacios.\n";
        return false;
    } else if (!regex_match(texto, formatoTexto)) {
        cout << "Error: El campo " << campo << " solo debe contener letras, espacios y caracteres válidos en español.\n";
        return false;
    }
    return true;
}

// Función auxiliar: días en un mes
int Validaciones::diasEnMes(int mes, int anio) {
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return (esBisiesto(anio)) ? 29 : 28;
        default: return 0;
    }
}

// Función auxiliar: año bisiesto
bool Validaciones::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0);
}
