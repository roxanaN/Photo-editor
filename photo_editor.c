#include <stdio.h>
#include <math.h>
#include <string.h>

/*
 * Limita superioara a intervalului din care fac parte R, G, B
 */
#define NMAX 255
/*
 * Limita superioara a intervalului din care face parte H
 */
#define HMAX 360

/*
 * Functie care returneaza minimul dintre a si b
 */
float min2(float a, float b) {
    return a < b ? a : b;
}

/*
 * Functie care returneaza maximul dintre a si b
 */
float max2(float a, float b) {
    return a > b ? a : b;
}

/* 
 * Valoarea variabilei x este normata, astfel incat
 * sa apartina intervalului [0, 1]
 */
float change(float x) {
    return (float)x / NMAX;
}

void edit_photo() {
    int N, M, j, R, G, B;
    float Cmax, Cmin, D, x, R_prim, G_prim, B_prim,
            H, S, V, H_prim, S_prim, V_prim;
    char c;

    /*
     * Citim N, M, c, x
     */
    scanf("%d %d %c %f", &N, &M, &c, &x);

    j = 1;
    while (j <= N * M) {
        /*
         * Citim un pixel (un triplet (R, G, B))
         */
        scanf("%d %d %d", &R, &G, &B);

        /*
         * Modificam valorile R, G, B,
         * pentru ca acestea sa apartina intervalului [0, 1]
         */
        R_prim = change(R);
        G_prim = change(G);
        B_prim = change(B);

        /*
         * Maximul dintre R_prim, G_prim, B_prim
         */
        Cmax = max2(R_prim, max2(G_prim, B_prim));

        /*
         * Minimul dintre R_prim, G_prim, B_prim
         */
        Cmin = min2(R_prim, min2(G_prim, B_prim));

        /*
         * Calculam valoarea lui delta
         */
        D = Cmax - Cmin;

        /*
         * Determinarea valorii H (hue)
         */
        if (R_prim == G_prim && G_prim == B_prim) {
            H = 0;
        } else {
            if (Cmax == R_prim)
                H = 60 * fmod(((double)(G_prim - B_prim) / D), 6);

            if (Cmax == G_prim)
                H = 60 * (((B_prim - R_prim) / D) + 2);

            if (Cmax == B_prim)
                H = 60 * (((R_prim - G_prim) / D) + 4);             

            /*
             * Pastram valoarea lui H_prim in intervalul [0, 1]
             */
            if (H < 0) {
                H += HMAX;
                H = (float)H / HMAX;
            } else {
                H = (float)H / HMAX;
            }
        }

        /*
         * Determinarea valorii S (saturation)
         */
        S = (Cmax == 0) ? 0 : (D / Cmax);

        /*
         * Determinarea valorii V (value)
         */
        V = Cmax;

        /*
         * Selectarea caracteristicii care va fi modificata
         */
        switch (c) {
            case 'h': {
                H_prim = H + x;
                /*
                 * Pastram valoarea lui H_prim in intervalul [0, 1]
                 */
                if (H_prim < 0)
                    H_prim = 0;

                if (H_prim > 1)
                    H_prim = 1;

                S_prim = S;
                V_prim = V;
                break;
            } 

            case 's': {
                S_prim = S * x;
                
                /*
                 * Pastram valoarea lui S_prim in intervalul [0, 1]
                 */
                if (S_prim < 0)
                    S_prim = 0;

                if (S_prim > 1)
                    S_prim = 1;  

                H_prim = H;
                V_prim = V;
                break;
            }

            case 'v': {
                V_prim = V * x;
                
                /*
                 * Pastram valoarea lui v_prim in intervalul [0, 1]
                 */
                if (V_prim < 0)
                    V_prim = 0;

                if (V_prim > 1)
                    V_prim = 1;

                H_prim = H;
                S_prim = S;
                break;  
            }   
        }

        /*
         * Se va afisa tripletul (H', S', V') obținut in urma transformarii
         */
        printf("%.5f %.5f %.5f\r\n", H_prim, S_prim, V_prim);

        /*
         * Trecem la urmatorul pixel
         */
        j++;
    }
}

int main() {
    edit_photo();

    return 0;
}