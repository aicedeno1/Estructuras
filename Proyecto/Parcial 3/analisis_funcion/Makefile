# Makefile para compilar y ejecutar el proyecto

# Compilador y flags
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Programas
MAIN = main
LECTOR = lector_funciones

# Archivos fuente
MAIN_SRC = main.cpp operaciones.cpp
LECTOR_SRC = lector_funciones.cpp

# Regla principal
all: $(MAIN) $(LECTOR)

# Compilar el programa principal
$(MAIN): $(MAIN_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compilar el lector de funciones
$(LECTOR): $(LECTOR_SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Ejecutar todo el proceso
run: all
	./$(MAIN)
	./$(LECTOR) operaciones.h
	python3 graficar_complejidad.py
	python3 analisis_lambda.py

# Regla para limpiar archivos generados
clean:
	rm -f $(MAIN) $(LECTOR) *.o *.csv *.txt *.png

# Phony targets
.PHONY: all run clean