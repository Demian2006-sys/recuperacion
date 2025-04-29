//Demian Durand, recuperacion
#include <stdio.h>
#include <string.h>

    // Declaración de variables fuera del main
    char equipos[4][50] = {"", "", "", ""};
    int pts[4] = {0}, gf[4] = {0}, gc[4] = {0};
    int equiposListos = 0, resultadosListos = 0;
    int opcion;

    // Función para leer números enteros válidos (como se repetia está de esta manera)
    int leerNumero() {
        int n;
        char c;
        while (1) {
            if (scanf("%d", &n) == 1 && (c = getchar()) == '\n') {
                return n;
            } else {
                while (getchar() != '\n');
                printf("Entrada invalida. Intente de nuevo, solo numeros enteros: ");
            }
        }
    }
int main() {
    do {
        printf("\n--- Menu del Torneo ---\n");
        printf("1. Ingresar equipos\n");
        printf("2. Ingresar resultados\n");
        printf("3. Ver finalistas\n");
        printf("4. Salir\n");
        printf("Seleccione una opcion\n ");
        printf(">>");
        opcion = leerNumero();

        switch (opcion) {
            case 1:
                // Ingreso de equipos
                if (!equiposListos) {
                    printf("\nIngrese los nombres de los 4 equipos:\n");
                    for (int i = 0; i < 4; i++) {
                        printf("Equipo %d: ", i + 1);
                        fgets(equipos[i], 50, stdin);
                        equipos[i][strcspn(equipos[i], "\n")] = '\0'; // Eliminar salto de línea
                    }
                    equiposListos = 1;
                } else {
                    printf("Los equipos ya fueron ingresados.\n");
                }
                break;

            case 2:
                // Ingreso de resultados
                if (!equiposListos) {
                    printf("Debe ingresar los equipos primero.\n");
                } else {
                    for (int i = 0; i < 4; i++) {
                        for (int j = i + 1; j < 4; j++) {
                            int g1, g2;
                            printf("\nPartido: %s vs %s\n", equipos[i], equipos[j]);
                            printf("Goles de %s: ", equipos[i]);
                            g1 = leerNumero();
                            printf("Goles de %s: ", equipos[j]);
                            g2 = leerNumero();

                            gf[i] += g1; gc[i] += g2;
                            gf[j] += g2; gc[j] += g1;

                            if (g1 > g2) pts[i] += 3;
                            else if (g2 > g1) pts[j] += 3;
                            else { pts[i]++; pts[j]++; }
                        }
                    }
                    resultadosListos = 1;
                }
                break;
            case 3:
            // Mostrar finalistas
            if (!equiposListos || !resultadosListos) {
                printf("Debe ingresar los equipos y los resultados primero.\n");
            } else {
                // Ordenar equipos por puntos y diferencia de goles
                for (int i = 0; i < 3; i++) {
                    for (int j = i + 1; j < 4; j++) {
                        int dif_i = gf[i] - gc[i];
                        int dif_j = gf[j] - gc[j];
        
                        if (pts[j] > pts[i] || (pts[j] == pts[i] && dif_j > dif_i)) {
                            // Intercambiar equipos
                            char temp[50];
                            strcpy(temp, equipos[i]);
                            strcpy(equipos[i], equipos[j]);
                            strcpy(equipos[j], temp);
        
                            // Intercambiar puntos, goles a favor y goles en contra
                            int t;
                            t = pts[i]; pts[i] = pts[j]; pts[j] = t;
                            t = gf[i]; gf[i] = gf[j]; gf[j] = t;
                            t = gc[i]; gc[i] = gc[j]; gc[j] = t;
                        }
                    }
                }
        
                // Mostrar los dos finalistas en formato tabla
                printf("\n--- Finalistas ---\n");
                printf("| %s              | Puntos | Dif. de Goles |\n", "Equipo");
                printf("|------------------|--------|----------------|\n");
                for (int i = 0; i < 2; i++) {
                    int dif = gf[i] - gc[i];
                    printf("| %-16s | %-6d | %-14d |\n", equipos[i], pts[i], dif);
                }
            }
            break;

            case 4:
                printf("Fin del programa\n");
                break;

            default:
                printf("Opcion no valida. Intente de nuevo.\n");
        }

    } while (opcion != 4);

    return 0;
}