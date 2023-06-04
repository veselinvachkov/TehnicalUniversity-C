#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char specialCode[3];
char productName[21];
int weight;
float pricePerKillo;
}IceCream;

float sumOfIceCreams(IceCream iceCreamsList[], int size, char letter){
    float sum = 0;
    for (int i = 0; i < size; i++){
        if (strcmp(iceCreamsList[i].productName[0],letter == 0)){
            sum += iceCreamsList[i].pricePerKillo * iceCreamsList[i].weight;
        }
    }
    return sum;
}

int write_to_file(IceCream iceCreamList[], int size, float price, int weight){
    int count = 0;
    FILE* fp = fopen("info.txt", "w");
    if (fp != NULL){
        for (int i = 0; i < size; i++){
            if (iceCreamList[i].pricePerKillo < price && iceCreamList[i].weight > weight){
                fprintf(fp, "%s;%s;%d,%.2fleva\n", iceCreamList[i].specialCode, iceCreamList[i].productName, iceCreamList[i].weight, iceCreamList[i].pricePerKillo);
                count++;
            }
        }
    }else{
        printf("Error");
        return 1;
    }
    return count;
}

void read_from_bin(char specialCode[3], int size){
    FILE* fp = fopen("icecream.bin", "rb");
    IceCream* iceCream_bin_list;
        iceCream_bin_list = (IceCream*)malloc(size * sizeof(IceCream));
    if (fp != NULL){
        fread(&size, sizeof(int), 1, fp);
        fread(iceCream_bin_list, sizeof(IceCream), size, fp);
        fclose(fp);
    }else{
        printf("File Error");
        return 1;
    }
    for (int i = 0; i < size; i++){
        if (strcmp(iceCream_bin_list[i].specialCode, specialCode) == 0){
            printf("dsfdfs\n");
        }
    }
}

int main()
{
    int size;
    scanf("%d", size);
    if (size < 5 || size > 15){
        printf("Invalid input");
        return 1;
    }

    IceCream* iceCreams_list;
    iceCreams_list = (IceCream*)malloc(size * sizeof(IceCream));
    if (iceCreams_list == NULL){
        printf("Error");
        return 1;
    }

    for (int i = 0; i < size; i++){
        IceCream new_iceCreams_list;
        printf("Special code: ");
        scanf("%s", new_iceCreams_list.specialCode);
        printf("\nProduct name: ");
        scanf("%s", new_iceCreams_list.productName);
        printf("\nWeight: ");
        scanf("%d", &new_iceCreams_list.weight);
        printf("\nPrice per killo: ");
        scanf("%f", &new_iceCreams_list.pricePerKillo);
        iceCreams_list[i] = new_iceCreams_list;
    }

    char specialLetter;
    scanf("%s", specialLetter);
    float sum = sumOfIceCreams(iceCreams_list, size, specialLetter);


    float price;
    scanf("%f", price);
    int weight;
    scanf("%d", weight);
    int txt_write_count = write_to_file(iceCreams_list, size, price, weight);


    return 0;
}
