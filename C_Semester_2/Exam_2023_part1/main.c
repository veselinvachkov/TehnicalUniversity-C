#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct {
    int id;
    char owner_name[30];
    char pictureName[30];
    float price;
}Picture;

float avgPrice(Picture picture_list[], int countPictures, float price) {
    float sum = 0;
    float avg = 0;
    float count = 0;

    for (int i = 0; i < countPictures; i++){
        if(picture_list[i].price > price) {
            sum += picture_list[i].price;
            count++;
        }
    }

    if (sum != 0) {
        avg = sum / count;
    }
    return avg;
}

countMatchedPictures(Picture picture_list[], int countPictures, char letter) {
    int count = 0;

    FILE *f = fopen("info.txt", "w");

    if(f == NULL) {
        printf("Can't open this file\n");
        exit(0);
    }

    for (int i = 0; i < countPictures; i++) {
        Picture p = picture_list[i];
        if(strcmp(p.owner_name[0], letter) == 0){
            fprintf("%d;%s;%s;%.2fleva\n", p.id, p.owner_name, p.pictureName, p.price);
            count++;
        }
    }

    fclose(f);
    return count;
}

void readFromFile(char name[]) {
    bool isFound = false;
    unsigned len;
    Picture p;
    FILE *f = fopen("picture.bin", "rb");

    if(f == NULL) {
        printf("Problem with file\n");
        exit(0);
    }

    while(true) {
        if(fread(&p.id, sizeof(int), 1, f) != 1){
            if(feof(f)){
                printf("That is all\n");
                break;
            }else{
                printf("Problem with reading on id\n");
                fclose(f);
                exit(0);
            }
        }

        if(fread(&len, sizeof(unsigned), 1, f) != 1) {
            printf("Problem with len\n");
            fclose(f);
            exit(0);
        }

        if(len > 30){
            len = 30;
        }

        if(fread(p.owner_name, sizeof(char), len, f) != len) {
            printf("problem with owner name\n");
            fclose(f);
            exit(0);
        }

        p.owner_name[len] = '\0';

            if(fread(&len, sizeof(unsigned), 1, f) != 1){
                printf("problem with len\n");
                fclose(f);
                exit(0);
            }

            if(len > 30){
                len = 30;
            }

            if(fread(p.pictureName, sizeof(char), len, f) != len) {
                printf("problem with picture name\n");
                fclose(f);
                exit(0);
            }

            p.pictureName[len] = '\0';

            if(fread(&p.price, sizeof(float), 1, f) != 1) {
                printf("problem with price\n");
                fclose(f);
                exit(0);
            }

            if(strcmp(p.owner_name, name) == 0) {
              printf("Picture title: %s\n", p.pictureName);
              printf("Price: %.2f BGN\n", p.price);
              printf("---------------------\n");

              isFound = true;
            }
    }

    if(!isFound){
        printf("No matches\n");
    }

    fclose(f);
}

int main()
{
    int countPictures;
    Picture *picture_list;

    printf("Input count pictures (3 < n < 30): ");
    scanf("%d", &countPictures);

    if(countPictures > 3 && countPictures < 30) {
        picture_list = (Picture*)calloc(countPictures, sizeof(Picture));
        if (picture_list == NULL) {
            printf("Memory not allocated\n");
            exit(0);
        }

        for(int i =0; i < countPictures; i++) {
            printf("Input id: ");
            scanf("%d", &picture_list[i].id);

            printf("Input owner name: ");
            scanf("%s",&picture_list[i].owner_name);

            printf("Input picture name: ");
             scanf("%s",&picture_list[i].pictureName);

            printf("Input price: ");
            scanf("%f", &picture_list[i].price);
        }

    } else {
        printf("wrong count\n");
        exit(0);
    }
    free(picture_list);
    return 0;
}
