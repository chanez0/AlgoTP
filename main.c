#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>


bool estPremier_A1(int N) {
    if (N < 2) return false;
    int i;
    for (i = 2; i < N-1; i++) {
        if (N % i == 0)
            return false;
    }
    return true;
}


bool estPremier_A2(int N) {
    if (N < 2) return false;
    int i;
    for (i = 2; i <= N / 2; i++) {
        if (N % i == 0)
            return false;
    }
    return true;
}


bool estPremier_A3(int N) {
    if (N < 2) return false;
    int i;
    for (i = 2; i * i <= N; i++) {
        if (N % i == 0)
            return false;
    }
    return true;
}


bool estPremier_A4(int N) {
    if (N < 2) return false;
    if (N % 2 == 0)
        return N == 2;
    int i;
    for (i = 3; i * i <= N; i += 2) {
        if (N % i == 0)
            return false;
    }
    return true;
}
void nettoyer(char *s) {
    // enlever BOM si pr�sent
    if ((unsigned char)s[0] == 0xEF &&
        (unsigned char)s[1] == 0xBB &&
        (unsigned char)s[2] == 0xBF) {
        memmove(s, s + 3, strlen(s) - 2);
    }

    // enlever \r et \n
    int len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r')) {
        s[len-1] = '\0';
        len--;
    }
}

int main() {
    int choix;
    long long N;
    bool resultat;
    clock_t debut, fin;
    double temps;

    char nomFichier[100];
    FILE *f;

    printf("=== Test de primalite (4 algorithmes + fichier) ===\n");
    printf("1. Approche naive (A1)\n");
    printf("2. Amelioree avec N/2 (A2)\n");
    printf("3. Optimisee avec sqrt(N) (A3)\n");
    printf("4. Optimisee avec sqrt(N) et impairs (A4)\n");
    printf("-----------------------------------------\n");
    printf("Votre choix : ");
    scanf("%d", &choix);

    printf("Nom du fichier contenant les nombres : ");
    scanf(" %[^\n]", nomFichier);


    f = fopen(nomFichier, "r");
    if (f == NULL) {
        printf("Erreur : impossible d'ouvrir le fichier.\n");
        return 1;
    }

    printf("\n=== R�sultats ===\n");



char ligne[200];

while (fgets(ligne, sizeof(ligne), f)) {

    nettoyer(ligne);

    if (sscanf(ligne, "%lld", &N) != 1) {
        continue;
    }

    debut = clock();

    switch (choix) {
        case 1: resultat = estPremier_A1((int)N); break;
        case 2: resultat = estPremier_A2((int)N); break;
        case 3: resultat = estPremier_A3((int)N); break;
        case 4: resultat = estPremier_A4((int)N); break;
    }

    fin = clock();
    temps = (double)(fin - debut) / CLOCKS_PER_SEC;

    printf("N = %lld --> %s (%f sec)\n",
           N,
           resultat ? "premier" : "non premier",
           temps);
}




    fclose(f);
    return 0;
}

