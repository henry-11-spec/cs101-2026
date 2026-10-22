#include <stdio.h>

int main() {
    FILE *fp;
    int a[] = {0, 1, 2};
    char b[] = "ABC";
    float c[] = {1.1, 1.2, 1.3};
    
    int ra;
    char rb;
    float rc;
    
    fp = fopen("a.bin", "wb");
    fwrite(a, sizeof(int), 3, fp);
    fwrite(b, sizeof(char), 3, fp);
    fwrite(c, sizeof(float), 3, fp);
    fclose(fp);
    
    fp = fopen("a.bin", "rb");
    
    for (int i = 0; i < 3; i++) {
        fread(&ra, sizeof(int), 1, fp);
        printf("%d ", ra);
    }
    printf("\n");
    
    for (int i = 0; i < 3; i++) {
        fread(&rb, sizeof(char), 1, fp);
        printf("%c ", rb);
    }
    printf("\n");
    
    for (int i = 0; i < 3; i++) {
        fread(&rc, sizeof(float), 1, fp);
        printf("%f ", rc);
    }
    printf("\n");
    
    fclose(fp);
    return 0;
}
