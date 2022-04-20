#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int searchSymtab(char *searchSymbol)
{
        FILE *fsym;
        fsym = fopen("symtab.txt", "r");

        char test[20], lc[20];
        int val = 0;
        fscanf(fsym, "%s%s", lc, test);
        while (!feof(fsym))
        {
                if (strcmp(searchSymbol, test) == 0)
                {
                        val = 1;
                        fclose(fsym);
                        return val;
                }
        }
        fclose(fsym);
        return val;
}

int main()
{
        FILE *f1, *f2, *f3, *f4;
        int op, sa, lc, optnum, op2;
        char m1[20], la[20], op1[20], opt[20];

        f1 = fopen("input.txt", "r");
        f3 = fopen("symtab.txt", "w");
        fscanf(f1, "%s%s%x", la, m1, &op2);
        if (strcmp(m1, "START") == 0)
        {
                sa = op2;
                lc = sa;
                printf("\t%s\t%s\t%x\n", la, m1, op2);
        }
        else
        {
                lc = 0;
        }
        fscanf(f1, "%s%s", la, m1);
        while (!feof(f1))
        {
                fscanf(f1, "%s", op1);
                printf("\n%x\t%s\t%s\t%s\n", lc, la, m1, op1);
                if (la[0] != '_' && searchSymtab(la) == 0)
                {
                        fprintf(f3, "%x\t%s\n\n", lc, la);
                }
                int test = 0;
                if (strcmp(m1, "WORD") == 0)
                {
                        lc += 3;
                        test = 1;
                }
                if (strcmp(m1, "RESW") == 0)
                {
                        lc += (3 * strtol(op1, NULL, 16));
                        test = 1;
                }
                if (strcmp(m1, "RESB") == 0)
                {
                        int op = strtol(op1, NULL, 16);
                        test = 1;
                        lc += op;
                }
                if (strcmp(m1, "BYTE") == 0)
                {
                        if (op1[0] == 'X')
                                lc = lc + 1;
                        else
                        {
                                int len = strlen(op1) - 2;
                                lc = lc + len;
                        }
                        test = 1;
                }

                f2 = fopen("optab.txt", "r");

                while (!feof(f2) && test != 1)
                {
                        fscanf(f2, "%s%x", opt, &optnum);
                        if (strcmp(m1, opt) == 0)
                        {
                                lc = lc + 3;
                                test = 1;
                                break;
                        }
                }
                fclose(f2);
                if (strcmp(m1, "END") == 0)
                {
                        printf("program length=%d\n", lc - sa);
                        fclose(f1);
                        fclose(f3);
                        return 0;
                }
                if (test == 0)
                {
                        printf("\nINVALID ASSEMBLY CODE %s\n", m1);
                        exit(0);
                }

                fscanf(f1, "%s%s", la, m1);
        }

        fclose(f1);
        fclose(f3);
        return 0;
}
