#include <stdio.h>
#include<string.h>
#define low_stock = 5

int total_items =10;

struct inventory
    {
        char name[100];
        int itemCode;
        int gstCode;
        int cost;
        int gstRate;
        int quantity;
    };

void inventory(struct inventory items[], int size)
{
    printf("Inventory List as on : \n");//add date here
 
    printf("%-10s %-20s %-10s %-10s %-10s%-10s\n", "Item Code", "Item Name", "GST Code", "Cost", "GST Rate","Quantity");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < size; i++) 
    {
        printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",items[i].itemCode,items[i].name,items[i].gstCode,items[i].cost,items[i].gstRate,items[i].quantity);
    }
}

void AddNewItem(struct inventory items[],int size) 
{
    if (total_items >= 100) 
    {
        printf("\nInventory FULL! Cannot add more items.\n");
        return;
    }

    int itemCode;
    int temp = 1;

    printf("Enter Item Code: ");
    scanf("%d", &itemCode);
    for(int i = 0; i < total_items;i++)
    {
        if(itemCode == items[i].itemCode)
        {
            temp = 0;
        }
    }

    if(temp != 0)
    {
        items[total_items].itemCode = itemCode;

        printf("Enter Item Name: ");
        scanf("%s", items[total_items].name);

        printf("Enter GST Code: ");
        scanf("%d", &items[total_items].gstCode);

        printf("Enter Cost: ");
        scanf("%d", &items[total_items].cost);

        printf("Enter GST Rate: ");
        scanf("%d", &items[total_items].gstRate);

        printf("Enter Quantity: ");
        scanf("%d", &items[total_items].quantity);

    total_items++;
    printf("\nItem Added Successfully!\n");
    printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",items[total_items].itemCode,items[total_items].name,items[total_items].gstCode,items[total_items].cost,items[total_items].gstRate,items[total_items].quantity);
    }

    else
    {
         printf("\nInvalid! Item Code already exists.\n");
        return;
    }
}

void DeleteItem(struct inventory items[],int size) 
{   
    char name[50];

    printf("Enter Item Name: ");
    scanf("%s",name);

    int len = strlen(name);
    int itemCode = 0;
    for(int i = 0; i < total_items ;i++)
    {
        for(int j = 0; j<len;j++)
        {
            int temp = 1;
            while(temp != 0)
            {
                if(name[j] == items[i].name)
                {
                    itemCode = items[i].itemCode;
                     temp = 1;
                }
                else
                {
                    temp = 0;
                }
           }
      
        }
    }
    for(int i = itemCode; i <= total_items;i++)
    {
        items[i].itemCode = items[i+1].itemCode;
        items[i].gstCode = items[i+1].gstCode;
        items[i].cost = items[i+1].cost;
        items[i].gstRate = items[i+1].gstRate;
        
    }
    total_items --;
    printf("\nItem Deleted Successfully!\n");
}


int main()
{
    struct inventory items[100];
    
    items[0] = (struct inventory){"Pen Black",1,9608,5,18,150};
    items[1] = (struct inventory){"Pen Blue",2,9608,5,18,150};
    items[2] = (struct inventory){"Pen Coloured",3,9608,10,18,100};
    items[3] = (struct inventory){"Pencil",4,9609,5,12,200};
    items[4] = (struct inventory){"Eraser",5,4016,2,18,100};
    items[5] = (struct inventory){"Crayons",6,9609,30,18,50};
    items[6] = (struct inventory){"Staplers",7,8205,50,18,20};
    items[7] = (struct inventory){"Stapler pins",8,8205,10,18,30};
    items[8] = (struct inventory){"Adhesive Tape",9,3919,25,18,30};
    items[9] = (struct inventory){"Diaries",10,4820,250,18,40};

    
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
        printf("2. Search Item (by Name or Code)\n");
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
                inventory(items,total_items);
                break;
            case 2:
                // search
                break;
            case 3:
                AddNewItem(items,total_items);
                break;
            case 4:
                DeleteItem(items,total_items);
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
        printf("2. Search Item (by Name or Code)\n");
        printf("3. Generate Bill\n");
        printf("4. Show Low Stock Items\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1:
                inventory(items,total_items);
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
        printf("2. Search Item (by Name or Code)\n");
        printf("3. Add New Item\n");
        printf("4. Update Quantity\n");
        printf("5. Show Low Stock Items\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice) {
            case 1:
               inventory(items,total_items);
                break;
            case 2:
                // search
                break;
            case 3:
                AddNewItem(items,total_items);
                break;
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
