#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int search_symtab(char s[20], char *ad)
{

    char label[20];
    FILE *f = fopen("symtab.txt", "r");
    while (!feof(f))
    {
        fscanf(f, "%s %s", label, ad);
        if (strcmp(s, label) == 0)
            return 1;
    }
    fclose(f);
    return 0;
}

int search_optab(char s[10], char *ad)
{
    char op[10];
    FILE *f = fopen("optab.txt", "r");
    while (!feof(f))
    {
        fscanf(f, "%s %s", op, ad);
        if (strcmp(s, op) == 0)
            return 1;
    }
    fclose(f);
    return 0;
}

int main()
{
    int locctr, sa, txtcnt = 60, len;
    char label[10], opcode[10], operand[10], pgrmname[20], opcodead[10], optr[10], objcode[10], txtrec[60];
    strcpy(txtrec, "");
    FILE *fin = fopen("intermediate.txt", "r");
    FILE *flen = fopen("length.txt", "r");
    FILE *fout = fopen("output.txt", "w");

    fscanf(flen, "%d", &len);
    fscanf(fin, "%s %s %d", pgrmname, opcode, &sa);

    fprintf(fout, "H%-6s%d%06x\nT%d", pgrmname, sa, len, sa);
    while (strcmp(opcode, "END") != 0)
    {
        fscanf(fin, "%d %s %s %s", &locctr, label, opcode, operand);
        if (search_optab(opcode, opcodead))
        {
            strcpy(objcode, opcodead);
            if (search_symtab(operand, optr))
                strcat(objcode, optr);
            else
            {
                strcat(objcode, "0000");
                printf("!! INVALID SYMBOL !!\n");
            }
        }
        else if (strcmp(opcode, "BYTE") == 0)
        {
            for (int i = 2; i < strlen(operand); i++)
            {
                char hex[2];
                sprintf(hex, "%X", operand[i]);
                strcat(objcode, hex);
            }
        }
        else if (strcmp(opcode, "WORD") == 0)
        {
            char hex[7];
            sprintf(hex, "%06X", atoi(operand));
            strcat(objcode, hex);
        }

        if (strlen(objcode) > 0)
        {
            if (txtcnt - strlen(objcode) > 0)
            {
                strcat(txtrec, objcode);
                strcpy(objcode, "");
            }
            else
            {
                txtcnt = 60;
                fprintf(fout, "%2lx%s\nT%d", strlen(txtrec) / 2, txtrec, locctr);
                strcpy(txtrec, "");
                strcat(txtrec, objcode);
            }
            txtcnt -= strlen(objcode);
        }
    }
    
    fprintf(fout, "%lx%s", strlen(txtrec) / 2, txtrec);
    fprintf(fout, "\nE%d\n", sa);
    printf("Assembler output: output.txt\n");
    fclose(fin);
    fclose(fout);
    return 0;
}