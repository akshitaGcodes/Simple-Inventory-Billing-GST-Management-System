#include <stdio.h>


int main()
{
   // items

    int login = 0;
     printf("\n GST BILLING SYSTEM GENERATOR \n");
     printf("Choose your login credentials :- \n");
     printf("1. Shopkeeper\n");
     printf("2. Cashier(s)\n");
     printf("3. Loader(Stock Updating)\n");
     scanf("%d", &login);
    int choice;

    switch(login)
    {
    case 1:
    do {
        printf("\n SHOPKEEPER PORTAL \n");
        printf("1. View All Items\n");//show inventory
        printf("2. Search Item (by Name or Code or Quantity)\n");
        printf("3. Add New Item\n");
        printf("4. Delete Item\n");
        printf("5. Update Quantity\n");
        printf("6. Generate Bill\n");
        printf("7. Show Low Stock Items\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice) {
            case 1:
                //  display Items
                break;
            case 2:
                // search
                break;
            case 3:
                // ADD
                break;
            case 4:
                // delete
                break;
            case 5:
                // update
                break;
            case 6:
                // generate
                break;
            case 7:
                // low stock
                break;
            case 8:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 8);
    break;


    case 2:
    do {
        printf("\n CASHIER PORTAL \n");
        printf("1. View All Items\n");//show inventory
        printf("2. Search Item (by Name or Code or Quantity)\n");
        printf("3. Generate Bill\n");
        printf("4. Show Low Stock Items\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1:
                //  display Items
                break;
            case 2:
                // search
                break;
                break;
            case 3:
                // generate
                break;
            case 4:
                // low stock
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
    break;


    case 3:
    do {
        printf("\n STOCK UPDATING PORTAL \n");
        printf("1. View All Items\n");//show inventory
        printf("2. Search Item (by Name or Code or Quantity)\n");
        printf("3. Add New Item\n");
        printf("4. Update Quantity\n");
        printf("5. Show Low Stock Items\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice) {
            case 1:
                //  display Items
                break;
            case 2:
                // search
                break;
            case 3:
                // ADD
                Break;
            case 4:
                // update
                break;
            case 5:
                // low stock
                break;
            case 6:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);
    break;


    default:
    printf("Invalid Login...Please try again");
    break;
}
    return 0;
}

