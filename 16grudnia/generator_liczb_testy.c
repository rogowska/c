/*Oliwia Rogowska*/

#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int max(int number1, int number2);
int max(int number1, int number2)
{
    if (number1 > number2)
    {
        return number1;
    }
    else
    {
        return number2;
    }
}

int porownywanie(const void *x1, const void *x2);
int porownywanie(const void *x1, const void *x2)
{
    if ((*(double *)x1) == (*(double *)x2))
    {
        return 0;
    }
    if ((*(double *)x1) > (*(double *)x2))
    {
        return 1;
    }
    return -1;
}

int main()
{
    int ilosc_przypadkow, liczba_przedzialow, maximum, i, j;
    float gwiazdka_normalizacja;
    int przedzialy[100] = {0};
    clock_t tp, tk;

    printf("%s\n", "podaj ilosc liczb na ktorych chcesz przeprowadzic testy:");
    scanf("%i", &ilosc_przypadkow);
    printf("%s\n", "podaj liczbe przedzialow:");
    scanf("%i", &liczba_przedzialow);

    double *przypadki = calloc(ilosc_przypadkow, sizeof(double));
    if (przypadki == 0)
    {
        printf("%s\n", "Podaj mniejsza liczbe przypadkow, brak pamieci");
        return -1;
    }

    if (ilosc_przypadkow < liczba_przedzialow)
    {
        printf("%s\n", "Podaj ilosc liczb wieksza od liczby przedzialow");
        return -1;
    }
    if ((ilosc_przypadkow == 0) || (liczba_przedzialow == 0))
    {
        printf("%s\n", "ilosc liczb i liczba przedzialow musza byc wieksze od 0");
        return -1;
    }

    srand48(time(NULL));
    for (i = 0; i < ilosc_przypadkow; i++)
    {
        przypadki[i] = drand48();
        int numer_przedzialu = przypadki[i] * liczba_przedzialow;
        przedzialy[numer_przedzialu]++;
    }

    /*szukanie max wartosci przedzialu*/
    maximum = przedzialy[0];
    for (i = 1; i < liczba_przedzialow; i++)
    {
        maximum = max(maximum, przedzialy[i]);
    }

    gwiazdka_normalizacja = maximum / 150.0;

    /*histogram pierwszy*/
    for (i = 0; i < liczba_przedzialow; i++)
    {
        printf("%i\t", i);
        for (j = 0; j < (przedzialy[i] / gwiazdka_normalizacja); j++)
        {
            printf("%c", '*');
        }
        printf("\n");
    }

    /*sortowanie i wyznaczanie czasu sortowania*/
    tp = clock();

    qsort(&przypadki[0], ilosc_przypadkow, sizeof(double), porownywanie);

    tk = clock();

    double czas_sortowania = (tk - tp) / (double)CLOCKS_PER_SEC;
    printf("%s%lf\n", "Czas sortowania wynosi: (sec)", czas_sortowania);

    /*histogram drugi nie wiem czy dobrze wykonalam, chyba nie, powinno byc minimalnie zebate nwm jak*/
    double deltai = przedzialy[i + 1] - przedzialy[i];

    for (i = 0; i < ilosc_przypadkow; i++)
    {
        przedzialy[i] = 0;
    }

    for (i = 0; i < ilosc_przypadkow; i++)
    {
        int ktory_przedzial = deltai * liczba_przedzialow; /*tu nie jestem pewna*/
        przedzialy[ktory_przedzial]++;
    }

    for (i = 0; i < liczba_przedzialow; i++)
    {
        printf("%i\t", i);
        for (j = 0; j < (przedzialy[i] / gwiazdka_normalizacja); j++)
        {
            printf("%c", '*');
        }
        printf("\n");
    }

    return 0;
}
