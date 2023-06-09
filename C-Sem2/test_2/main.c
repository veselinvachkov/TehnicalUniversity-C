#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
char name[31];
int id;
char date[10];
float price;
}Product;

int products_count = 0;

void add_product(Product products[]){
    if (products_count >= 50){
        printf("No more space for products!");
        return;
    }
    Product new_product;
    printf("\nGive a name for the product: ");
    scanf("%s", &new_product.name);
    printf("Give ID for the product: ");
    scanf("%d", &new_product.id);
    printf("Date: ");
    scanf("%s", &new_product.date);
    printf("Price: ");
    scanf("%f", &new_product.price);
    products[products_count++] = new_product;
    printf("Product added successfully.\n");
}

void write_to_bin_file(Product products[]){
    FILE *fp = fopen("in.bin", "wb");
    if (fp != NULL) {
        fwrite(&products_count, sizeof(int), 1, fp);
        fwrite(products, sizeof(Product), products_count, fp);
        fclose(fp);
        printf("Data written to binary file successfully.\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

void read_from_bin_file(Product products[]]){
    FILE *fp = fopen("in.bin", "rb");
    if (fp != NULL) {
        fread(&products_count, sizeof(int), 1, fp);
        fread(products, sizeof(Product), products_count, fp);
        fclose(fp);
        printf("Data read from binary file successfully.\n");
    } else {
        printf("Error opening file for reading.\n");
    }
}

void print(Product products[]){
    printf("%-10s%-20s%-30s%s\n", "Name", "ID", "Date", "Price");
    for(int i = 0; i < products_count; i++){
        printf("%-10s%-20d%-30s%.2f\n", products[i].name, products[i].id, products[i].date, products[i].price);
    }

}

void price_comp(Product products[], float price){
    int count = 0;
    for(int i = 0; i < products_count; i++){
        if (products[i].price > price){
            if (count == 0){
                printf("%-10s%-20s%-30s%s\n", "Name", "ID", "Date", "Price");
            }
            printf("%-10s%-20d%-30s%.2f\n", products[i].name, products[i].id, products[i].date, products[i].price);
            count++;
        }
    }
}

void write_to_txt_file(Product products[]){
    FILE *fp = fopen("out.txt", "w");
    if (fp != NULL) {
        fprintf(fp, "%-10s%-20s%-30s%s\n", "Name", "ID", "Date", "Price");
        for(int i = 0; i < products_count; i++){
            fprintf(fp, "%-10s%-20d%-30s%.2f\n", products[i].name, products[i].id, products[i].date, products[i].price);
        }
        fclose(fp);
        printf("Data written to txt file successfully.\n");
    } else {
        printf("Error opening file for writing.\n");
    }
}

int main() {
    Product products[50];
    int choice;
    float price;

    while (choice != 10){
        printf("\n1. Add product\n");
        printf("2. Write to binary file\n");
        printf("3. Read from binary file\n");
        printf("4. Print data\n");
        printf("5. Compare price\n");
        printf("6. Write to txt file\n");
        printf("10. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice){
            case 1: {
                add_product(products);
                break;
            }
            case 2: {
                write_to_bin_file(products);
                break;
            }
            case 3: {
                read_from_bin_file(products);
                break;
            }
            case 4: {
                print(products);
                break;
            }
            case 5: {
                printf("Give a price to compare: ");
                scanf("%f", &price);
                price_comp(products, price);
                break;
            }
            case 6: {
                write_to_txt_file(products);
                break;
            }
            case 10: {
                printf("Exiting...\n");
                break;
            }
            default: {
                printf("Invalid choice.\n");
                return;
            }
        }
    }
    return 0;
}
