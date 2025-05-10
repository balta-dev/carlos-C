# Nombre del ejecutable
TARGET = Lenguaje_Carlos

# Archivos fuente
SRCS = Lenguaje_Carlos.c Analizador_Lexico.c Analizador_Sintactico.c Evaluador.c

# Archivos objeto (se generan a partir de los .c)
OBJS = $(SRCS:.c=.o)

# Compilador
CC = gcc

# Opciones de compilación
CFLAGS = -Wall -g

# Regla por defecto
all: $(TARGET)

# Cómo construir el ejecutable
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Regla para limpiar archivos intermedios
clean:
	rm -f $(OBJS) $(TARGET)
