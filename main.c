#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
//TK: Minh . MK: 23022006
struct Supplements {
    int id;
    char name[100];
};

struct Item {
    int id;
    char name[100];
    float price;
    int quan;
};

void deleItem(struct Item a[], int *b);
void repairItem(struct Item a[], int *b);
void clearScreen();
void sortItem(struct Item a[], int *b);
void searchItem(struct Item a[], int *b);
void categoryAndProduct(struct Supplements m[], int *n, struct Item a[], int *b);
void showMenuuu();
void showMenuu();
void sort(struct Supplements m[], int *n);
void dele(struct Supplements m[], int *n);
void repair(struct Supplements m[], int *n);
void search(struct Supplements m[], int *n);
void add(struct Supplements m[], int *n);
void print(struct Supplements m[], int *n);
int accountAdmin(int *userChoice, int *lock);
void showChoose();
void showMenu();
void choose2(struct Supplements m[], int *n);
void category(struct Supplements m[], int *n);
void save(struct Supplements m[], int *n);
void load(struct Supplements m[], int *n);
void saveItem(struct Item a[], int *b);
void loadItem(struct Item a[], int *b);
void addItem(struct Item a[], int *b);
void product(struct Item a[], int *b);
void printItem(struct Item a[], int *b);

int main(int argc, char *argv[]) {
    int n = 0;
    int b = 0;
    int choice;
    int choiceCategory;
    struct Supplements m[100];
    struct Item a[100];
    load(m, &n);
    loadItem(a, &b);
    do {
        showChoose();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();
        clearScreen();
        switch (choice) {
            case 1:
                if (accountAdmin(&choice, &choice)) {
                    printf("Login successful! Welcome to the Admin Menu.\n");
                    categoryAndProduct(m, &n, a, &b);
                } else {
                    printf("Login failed! Incorrect username or password.\n");
                }
                break;
            case 2:
                printf("Welcome to the Employee Menu.\n");
                choose2(m, &n);
                break;
            case 3:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice != 3);
    return 0;
}

void clearScreen() {
    const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J";
    write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

void showChoose() {
    printf(" * SUPPLEMENTS FOR THE RICH *\n");
    printf("=============================\n");
    printf("\t CHOOSE THE ROLE \n");
    printf("=============================\n");
    printf("| [1].Admin.                |\n");
    printf("| [2].Employee.             |\n");
    printf("| [3].Exit The Program.     |\n");
    printf("=============================\n");
}

int accountAdmin(int *userChoice, int *lock) {
    char inputAdmin[50];
    char inputPass[50];
    char addAccount[] = "Minh";
    char addPassword[] = "23022006";
    char ch;
    int i = 0;
    printf("=============================\n");
    printf(" Login to your account \n");
    printf("=============================\n");
    printf("Enter admin: ");
    scanf("%s", inputAdmin);
    getchar();
    printf("Enter password: ");
    while (1) {
        ch = getch();
        if (ch == '\r') {
            inputPass[i] = '\0';
            break;
        } else if (ch == '\b') {
            if (i > 0) {
                i--;
                printf("\b \b");
            }
        } else {
            inputPass[i++] = ch;
            printf("*");
        }
    }
    printf("\n");
    if (strcmp(inputAdmin, addAccount) == 0 && strcmp(inputPass, addPassword) == 0) {
        *lock = 1;
        return 1;
    } else {
        *lock = 0;
        return 0;
    }
}

void choose2(struct Supplements m[], int *n) {  
    int choice2;
    do {
        showMenuu();
        printf("Enter your choice: ");
        scanf("%d", &choice2);
        getchar();
        clearScreen();
        switch (choice2) {
            case 1:
                add(m, n);
                save(m, n);
                break;
            case 2:
                print(m, n);
                break;
            case 3:
                search(m, n);
                break;
            case 4:
                sort(m, n);
                break;
            case 5:
                printf("Exiting Employee menu. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice2 != 5);
}

void showMenu() {
    printf(" * SUPPLEMENTS FOR THE RICH *\n");
    printf("=============================\n");
    printf("\t GYM MENU \n");
    printf("=============================\n");
    printf("| [1].Add A New Supplements. |\n");
    printf("| [2].Show All Supplements.  |\n");
    printf("| [3].Repair Supplements.    |\n");
    printf("| [4].Delete Supplements.    |\n");
    printf("| [5].Search Supplements.    |\n");
    printf("| [6].Sort Supplements.      |\n");
    printf("| [7].Exit The Program.      |\n");
    printf("=============================\n");
}

void category(struct Supplements m[], int *n) {
    int choice1;
    do {
        showMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice1);
        getchar();
        clearScreen();
		switch (choice1) {
            case 1:
                add(m, n);
                save(m, n);
                break;
            case 2:
                print(m, n);
                break;
            case 3:
                repair(m, n);
                save(m, n);
                break;
            case 4:
                dele(m, n);
                save(m, n);
                break;
            case 5:
                search(m, n);
                break;
            case 6:
                sort(m, n);
                break;
            case 7:
                printf("Exiting Admin menu. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice1 != 7);
}

void add(struct Supplements *m, int *n) {
    int count;
    char temp[100];
    int isDuplicate;
    printf("Enter the number of supplements to add: ");
    scanf("%d", &count);
    getchar();
    for (int i = 0; i < count; i++) {
        printf("Supplement ID: %d\n", *n + 1);
        m[*n].id = *n + 1;
        do {
            isDuplicate = 0;
            printf("Enter the name of the supplement: ");
            fgets(temp, 100, stdin);
            temp[strcspn(temp, "\n")] = '\0';
            for (int j = 0; j < *n; j++) {
                if (strcmp(m[j].name, temp) == 0) {
                    printf("The name '%s' is already in use. Please try again.\n", temp);
                    isDuplicate = 1;
                    break;
                }
            }
        } while (isDuplicate);

        strcpy(m[*n].name, temp);
        (*n)++;
    }
    printf("%d supplements added successfully.\n", count);
}


void save(struct Supplements m[], int *n) {
    FILE *file = fopen("category.bin", "wb");
    if (file == NULL) {
        printf("Unable to save the file\n");
        return;
    }
    fwrite(n, sizeof(int), 1, file);
    fwrite(m, sizeof(struct Supplements), *n, file);
    fclose(file);
    printf("Information saved successfully to Shop.bin\n");
}

void load(struct Supplements m[], int *n) {
    FILE *file = fopen("category.bin", "rb");
    if (file == NULL) {
        printf("No data found in category.bin. Initializing empty list.\n");
        *n = 0; 
        return;
    }
    fread(n, sizeof(int), 1, file);
    fread(m, sizeof(struct Supplements), *n, file);
    fclose(file);
    printf("Information loaded successfully from category.bin\n");
}

void print(struct Supplements m[], int *n) {
    if (*n == 0) {
        printf("No supplements available to display.\n");
        return;
    } else {
        printf("*===========|===========================*\n");
        printf("|    ID     |       Name Supplements    |\n");
        printf("*===========|===========================*\n");
        for (int i = 0; i < *n; i++) {
            printf("|%6d     | %-25s |\n", i + 1, m[i].name);
        }
        printf("*===========|===========================*\n");
    }
}

void search(struct Supplements m[], int *n) {
    char a;
    int found = 0;
    if (*n == 0) {
        printf("No supplements available to search.\n");
        return;
    }
    printf("Enter a character to search: ");
    getchar();
    scanf("%c", &a);
    printf("\nSearch Results:\n");
    printf("*===========|===========================*\n");
    printf("|    ID     |       Name Supplements    |\n");
    printf("*===========|===========================*\n");
    for (int i = 0; i < *n; i++) {
        if (strchr(m[i].name, a) != NULL) {
            printf("|%6d     | %-25s |\n", m[i].id, m[i].name);
            found = 1;
        }
    }
    if (found == 0) {
        printf("No supplements found with the character '%c'.\n", a);
    }
    printf("*======================================*\n");
}

void repair(struct Supplements m[], int *n) {
    int a;
    int found = 0;
    if (*n == 0) {
        printf("No supplements available to repair.\n");
        return;
    }
    printf("Enter the ID of the supplement you want to repair: ");
    scanf("%d", &a);
    for (int i = 0; i < *n; i++) {
        if (m[i].id == a) {
            printf("Current Name: %s\n", m[i].name);
            printf("Enter new name for the supplement: ");
            getchar();
            fgets(m[i].name, 100, stdin);
            m[i].name[strcspn(m[i].name, "\n")] = '\0';
            printf("Supplement ID %d has been updated to '%s'.\n", m[i].id, m[i].name);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("No supplement found with ID %d.\n", a);
    }
}

void dele(struct Supplements m[], int *n) {
    int a;
    int b;
    int found = 0;
    if (*n == 0) {
        printf("No supplements available to delete.\n");
        return;
    }
    printf("Enter the ID of the supplement you want to delete: ");
    scanf("%d", &a);
    for (int i = 0; i < *n; i++) {
        if (m[i].id == a) {
            found = 1;
            printf("Found Supplement:\n");
            printf("*===========|===========================*\n");
            printf("|    ID     |       Name Supplements    |\n");
            printf("*===========|===========================*\n");
            printf("|%6d     | %-25s |\n", m[i].id, m[i].name);
            printf("*===========|===========================*\n");
            printf("Do you want to delete this supplement? (1 = Yes, 2 = No): ");
            scanf("%d", &b);
            if (b == 1) {
                for (int j = i; j < *n - 1; j++) {
                    m[j] = m[j + 1];
                    m[j].id = j + 1;
                }
                (*n)--;
                printf("Supplement with ID %d deleted successfully.\n", a);
            } else {
                printf("Delete operation cancelled.\n");
            }
            return;
        }
    }
    if (found == 0) {
        printf("No supplement found with ID %d.\n", a);
    }
}

void sort(struct Supplements m[], int *n) {
	struct Supplements temp;
    if (*n == 0) {
        printf("No products available to sort.\n");
        return;
    }
    for (int i = 0; i < *n - 1; i++) {
        for (int j = 0; j < *n - i - 1; j++) {
            if (strcmp(m[j].name, m[j + 1].name) > 0) {
                temp = m[j];
                m[j] = m[j + 1];
                m[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by name successfully.\n");
}

void showMenuu() {
    printf(" * SUPPLEMENTS FOR THE RICH *\n");
    printf("=============================\n");
    printf("\t GYM MENU \n");
    printf("=============================\n");
    printf("| [1].Add A New Supplements. |\n");
    printf("| [2].Show All Supplements.  |\n");
    printf("| [3].Search Supplements.    |\n");
    printf("| [4].Sort Supplements.      |\n");
    printf("| [5].Exit The Program.      |\n");
    printf("=============================\n");
}

void showMenuuu() {
    printf(" * SUPPLEMENTS FOR THE RICH *\n");
    printf("=============================\n");
    printf("\t GYM MENU \n");
    printf("=============================\n");
    printf("| [1].Add A New Product.   |\n");
    printf("| [2].Show All Products.   |\n");
    printf("| [3].Repair Products.     |\n");
    printf("| [4].Delete Products.     |\n");
    printf("| [5].Search Products.     |\n");
    printf("| [6].Sort Products.       |\n");
    printf("| [7].Exit The Program.    |\n");
    printf("=============================\n");
}

void categoryAndProduct(struct Supplements m[], int *n, struct Item a[], int *b) {
    int choice;
    int exit = 0;
    do {
        printf(" * SUPPLEMENTS FOR THE RICH *\n");
        printf("=============================\n");
        printf("\t CHOOSE THE ROLE \n");
        printf("=============================\n");
        printf("| [1].Category.             |\n");
        printf("| [2].Product.              |\n");
        printf("| [3].Exit The Program.     |\n");
        printf("=============================\n");
        printf("Please Input Your CHoice: ");
        scanf("%d", &choice);
        getchar();
        clearScreen();
        switch (choice) {
            case 1:
                category(m, n);
                break;
            case 2:
                product(a, b);
                break;
            case 3:
                printf("Exiting Admin menu. Goodbye!\n");
                exit = 1;
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice != 3 && !exit);
}

void product(struct Item a[], int *b) {
    int choice1;
    do {
        showMenuuu();
        printf("Enter your choice: ");
        scanf("%d", &choice1);
        getchar();
        switch (choice1) {
            case 1:
                addItem(a, b);
                saveItem(a, b);
                break;
            case 2:
                printItem(a, b);
                break;
            case 3:
            	repairItem(a,b);
            	saveItem(a,b);
            	break;
            case 4:
            	deleItem(a,b);
            	saveItem(a,b);
            	break;
            case 5:
            	searchItem(a,b);
            	break;
            case 6:
            	sortItem(a, b);
            	break;
            case 7:
                printf("Exiting Product menu. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
        printf("\n");
    } while (choice1 != 7);
}

void saveItem(struct Item a[], int *b) {
    FILE *file = fopen("product.bin", "wb");
    if (file == NULL) {
        printf("Unable to save the file\n");
        return;
    }
    fwrite(b, sizeof(int), 1, file);
    fwrite(a, sizeof(struct Item), *b, file);
    fclose(file);
    printf("Information saved successfully to Product.bin\n");
}

void loadItem(struct Item a[], int *b) {
    FILE *file = fopen("product.bin", "rb");
    if (file == NULL) {
        printf("No data found in Product.bin. Initializing empty list.\n");
        *b = 0; 
        return;
    }
    fread(b, sizeof(int), 1, file);
	fread(a, sizeof(struct Item), *b, file);
    fclose(file);
    printf("Information loaded successfully from Product.bin\n");
}

void addItem(struct Item *a, int *b) {
    int count;
    printf("Enter the number of items to add: ");
    scanf("%d", &count);
    getchar();
    for (int i = 0; i < count; i++) {
        a[*b].id = *b + 1;
        printf("Item ID: %d\n", a[*b].id);
        printf("Enter the name of the item: ");
        fgets(a[*b].name, 100, stdin);
        a[*b].name[strcspn(a[*b].name, "\n")] = '\0';
        printf("Enter price for %s: ", a[*b].name);
        scanf("%f", &a[*b].price);
        getchar();
        printf("Enter quantity for %s: ", a[*b].name);
        scanf("%d", &a[*b].quan);
        getchar();
        (*b)++;
    }
    printf("Added %d new items successfully.\n", count);
}

void printItem(struct Item a[], int *b) {
    if (*b == 0) {
        printf("No products available to display.\n");
        return;
    }
    printf("*===========|===========================|========|==========*\n");
    printf("|    ID     |       Name Product        | Price  | Quantity |\n");
    printf("*===========|===========================|========|==========*\n");
    for (int i = 0; i < *b; i++) {
        printf("|%6d     | %-25s | %5.2f | %6d |\n", a[i].id, a[i].name, a[i].price, a[i].quan);
    }
    printf("*===========|===========================|========|==========*\n");
}

void searchItem(struct Item a[], int *b) {
    char m;
    int found = 0;
    if (*b == 0) {
        printf("No products available to search.\n");
        return;
    }
    printf("Enter a character to search: ");
    getchar();
    scanf("%c", &m);
    printf("\nSearch Results:\n");
    printf("*===========|===========================|=========|==========*\n");
    printf("|    ID     |       Name Product        | Price   | Quantity |\n");
    printf("*===========|===========================|=========|==========*\n");
    for (int i = 0; i < *b; i++) {
        if (strchr(a[i].name, m) != NULL) {
            printf("|%6d     | %-25s | %5.2f | %6d |\n", a[i].id, a[i].name, a[i].price, a[i].quan);
            found = 1;
        }
    }
    if (!found) {
        printf("| No products found matching '%c'.                          |\n", m);
    }
    printf("*===========|===========================|=========|==========*\n");
}

void sortItem(struct Item a[], int *b) {
	struct Item temp;
    if (*b == 0) {
        printf("No products available to sort.\n");
        return;
    }
    for (int i = 0; i < *b - 1; i++) {
        for (int j = 0; j < *b - i - 1; j++) {
            if (strcmp(a[j].name, a[j + 1].name) > 0) {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
    printf("Products sorted by name successfully.\n");
}

void repairItem(struct Item a[], int *b) {
    int id;
    int found = 0;
    if (*b == 0) {
        printf("No items available to repair.\n");
        return;
    }
    printf("Enter the ID of the item you want to repair: ");
    scanf("%d", &id);
    for (int i = 0; i < *b; i++) {
        if (a[i].id == id) {
            found = 1;
            printf("Current Details:\n");
            printf("*===========|===========================|=========|==========*\n");
            printf("|    ID     |       Name Product        | Price   | Quantity |");
            printf("*===========|===========================|=========|==========*\n");
            printf("|%6d     | %-25s | %5.2f | %6d |\n", a[i].id, a[i].name, a[i].price, a[i].quan);
            printf("*===========|===========================|=========|==========*\n");
            printf("Enter new name for the item: ");
            getchar();
            fgets(a[i].name, 100, stdin);
            a[i].name[strcspn(a[i].name, "\n")] = '\0';
            printf("Enter new price for the item: ");
            scanf("%f", &a[i].price);
            printf("Enter new quantity for the item: ");
            scanf("%d", &a[i].quan);
            printf("Item ID %d has been updated successfully.\n", a[i].id);
            return;
        }
    }
    if (!found) {
        printf("No item found with ID %d.\n", id);
    }
}

void deleItem(struct Item a[], int *b) {
    int id;
    int confirm;
    int found = 0;
    if (*b == 0) {
        printf("No items available to delete.\n");
        return;
    }
    printf("Enter the ID of the item you want to delete: ");
    scanf("%d", &id);
    for (int i = 0; i < *b; i++) {
        if (a[i].id == id) {
            found = 1;
            printf("Found Item:\n");
            printf("*===========|===========================|=========|==========*\n");
            printf("|    ID     |       Name Product        | Price   | Quantity |");
            printf("*===========|===========================|=========|==========*\n");
            printf("|%6d     | %-25s | %5.2f | %6d |\n", a[i].id, a[i].name, a[i].price, a[i].quan);
            printf("*===========|===========================|=========|==========*\n");
            printf("Do you want to delete this item? (1 = Yes, 2 = No): ");
            scanf("%d", &confirm);
            if (confirm == 1) {
                for (int j = i; j < *b - 1; j++) {
                    a[j] = a[j + 1];
                    a[j].id = j + 1;
                }
                (*b)--;
                printf("Item with ID %d deleted successfully.\n", id);
            } else {
                printf("Delete operation cancelled.\n");
            }
            return;
        }
    }
    if (!found) {
        printf("No item found with ID %d.\n", id);
    }
}
