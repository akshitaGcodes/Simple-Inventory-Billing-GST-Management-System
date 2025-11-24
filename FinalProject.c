#include <stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#define low_stock 5
#define max_items 50

int total_items = 40;
int billItems = 0; 

struct User 
{
    char username[50];
    char password[50];
    int login;
} ;

struct inventory
    {
        char name[100];
        int itemCode;
        int gstCode;
        int cost;
        int gstRate;
        int quantity;
    };

char* Date(void) 
{
    static char date_buffer[100];
    time_t now = time(NULL);
    struct tm *t = localtime(&now);

    strftime(date_buffer, sizeof(date_buffer), "%d-%m-%Y", t);
    
    return date_buffer; 
}

void inventoryView(struct inventory items[], int size)
{
    printf("Inventory List as on : %s\n",Date()); 
 
    printf("--------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-10s %-10s %-10s%-10s\n", "Item Code", "Item Name", "GST Code", "Cost", "GST Rate","Quantity");
    printf("--------------------------------------------------------------------------\n");

    for (int i = 0; i < size; i++) 
    {
        printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",items[i].itemCode,items[i].name,items[i].gstCode,items[i].cost,items[i].gstRate,items[i].quantity);
    }
     printf("--------------------------------------------------------------------------\n");
}


void search(struct inventory items[], int size)
{
    int searchChoice = 0;
    printf("Would you like to search by :\n1.Name\n2.Itemcode.\nPlease enter your choice :"); 
    scanf("%d",&searchChoice);

    char itemName[50];
    int temp = -1;
    int code = 0;
    switch(searchChoice)
    {
        case 1:
        {
        printf("Please enter item name : ");
        getchar(); 
        fgets(itemName, sizeof(itemName), stdin);
        itemName[strcspn(itemName, "\n")] = 0;
        for(int i = 0; i<total_items;i++)
        {
            int result = strcmp(itemName, items[i].name);
            if(result == 0)
            {
                temp = i;
                break;
            }
        }
        break;
        }

        case 2:
        {
            printf("Please enter item code : ");
            scanf("%d",&code);
            
            for(int i = 0; i<total_items;i++)
            {
                if(code == items[i].itemCode)
                temp = i;
            }

        break;
        }

        default:
        {
            printf("Error...Please try again.\n");
            break;
        }
        
    }

    if (temp == -1)
        {
            printf("Item not found.\n");
            return;
        }
            printf("\n Item Found. Details below.\n");
            printf("--------------------------------------------------------------------------\n");
            printf("%-10s %-20s %-10s %-10s %-10s%-10s\n", "Item Code", "Item Name", "GST Code", "Cost", "GST Rate","Quantity");
            printf("--------------------------------------------------------------------------\n");
            printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",items[temp].itemCode,items[temp].name,items[temp].gstCode,items[temp].cost,items[temp].gstRate,items[temp].quantity);
            printf("--------------------------------------------------------------------------\n");

}
void AddNewItem(struct inventory *items, int *total_items)
{
    if (*total_items >= 100)
    {
        printf("\nInventory FULL! Cannot add more items.\n");
        return;
    }

    int itemCode;
    printf("Enter Item Code: ");
    scanf("%d", &itemCode);
    for (int i = 0; i < *total_items; i++)
    {
        if ((items + i)->itemCode == itemCode)
        {
            printf("\nInvalid! Item Code already exists.\n");
            return;
        }
    }
    struct inventory *newItem = items + (*total_items);

    newItem->itemCode = itemCode;

    printf("Enter Item Name: ");
    //scanf("%s", newItem->name);
    scanf(" %[^\n]", newItem->name);

    printf("Enter GST Code: ");
    scanf("%d", &newItem->gstCode);

    printf("Enter Cost: ");
    scanf("%d", &newItem->cost);

    printf("Enter GST Rate: ");
    scanf("%d", &newItem->gstRate);

    printf("Enter Quantity: ");
    scanf("%d", &newItem->quantity);

    (*total_items)++; 
    printf("\nItem Added Successfully!\n");
    printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",
        newItem->itemCode,
        newItem->name,
        newItem->gstCode,
        newItem->cost,
        newItem->gstRate,
        newItem->quantity);
}
void DeleteItem(struct inventory items[],int size) 
{   
    char name[50];

    printf("Enter Item Name: ");
   scanf(" %[^\n]", name);

    int len = strlen(name);
    int itemCode = -1;
 
    for(int i = 0; i < total_items ;i++)
    {
        if(strcmp(name,items[i].name) == 0)
        {
            itemCode = i;
            break;
        }
    }

    if (itemCode == -1)
    {
        printf("Error... Item not in found in Inventory. PLease try again. \n");
    }
    else
   {

    for(int i = itemCode; i < total_items -1 ;i++)
    {
        items[i] = items[i+1];
        items[i].itemCode = i+1;
    }
    

    total_items --;
    printf("\nItem Deleted Successfully!\n");

    }
    return;
}

void UpdateQuantity(struct inventory items[],int size) 
{   
    char name[100];

    printf("Enter Item Name: ");
   scanf(" %[^\n]", name);

    int itemCode = -1;
 
    for(int i = 0; i < total_items ;i++)
    {
        if(strcmp(name,items[i].name) == 0)
        {
            itemCode = i;
            break;
        }
    }
    if(itemCode == -1)
    {
        printf("Error.. Item not found in inventory.");
    }

    else
    {
    int quantity = 0;
    printf("Please enter the new quantity : ");
    scanf("%d",&quantity);
    items[itemCode].quantity = quantity;

    printf("Quantity Updated Successfully..\n");
    printf("%-10s %-20s %-10s %-10s %-10s%-10s\n", "Item Code", "Item Name", "GST Code", "Cost", "GST Rate","Quantity");
    printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",items[itemCode].itemCode,items[itemCode].name,items[itemCode].gstCode,items[itemCode].cost,items[itemCode].gstRate,items[itemCode].quantity);
    
    }

    return;
}

struct BillItems 
{
    char name[100];
    int quantity;
    int cost;
    int gstRate;
    int itemCode;
    double amount;
    double gstAmount;
    double total;
};

struct BillItems BillComponents[max_items];
struct BillItems AllBills[1000];
int totalAllBillItems=0;

void printBill(struct BillItems bill[], int count, double subTotal, double totalGST);

void generateBill(struct inventory items[],int size,struct BillItems BillComponents[]) 
{ 
    int billItems = 0; 
    double subTotal = 0.0; 
    double totalGST = 0.0;
    int choice = 1;
    int itemCode;
    int Quantity;
    int itemIndex = -1; 

    printf("\n--- GENERATE BILL ---\n");
 
    while (1) 
    {
        printf("\n1. Add Item to Bill\n");
        printf("2. Finalize and Print Bill\n");
        printf("3. Cancel Bill\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1)
        {
            if (billItems >= max_items) 
            {
                printf("\nBill limit reached! Please finalize the current bill.\n");
                continue;
            }

            printf("Enter Item Code: ");
            scanf("%d", &itemCode);

            itemIndex = -1;
            for (int i = 0; i < size; i++) 
            {
                if (items[i].itemCode == itemCode) 
                {
                    itemIndex = i;
                    break;
                }
            }

            if (itemIndex != -1) 
            {
                printf("Enter Quantity for %s (Max: %d): ", items[itemIndex].name, items[itemIndex].quantity);
                scanf("%d", &Quantity);

                if (Quantity > 0 && Quantity <= items[itemIndex].quantity) 
                {
                    strcpy(BillComponents[billItems].name, items[itemIndex].name);
                    BillComponents[billItems].itemCode = items[itemIndex].itemCode;
                    BillComponents[billItems].quantity = Quantity;
                    BillComponents[billItems].cost = items[itemIndex].cost;
                    BillComponents[billItems].gstRate = items[itemIndex].gstRate;

                    BillComponents[billItems].amount = (double)BillComponents[billItems].cost * BillComponents[billItems].quantity;

                    double gst_rate_factor = (double)BillComponents[billItems].gstRate / 100.0;
                    BillComponents[billItems].gstAmount = BillComponents[billItems].amount * gst_rate_factor;

                    BillComponents[billItems].total = BillComponents[billItems].amount + BillComponents[billItems].gstAmount;
                    
                    items[itemIndex].quantity -= Quantity;

                    subTotal += BillComponents[billItems].amount;
                    totalGST += BillComponents[billItems].gstAmount;

                    printf("\nItem **%s** added (Qty: %d). Taxable Value: %.2f\n", BillComponents[billItems].name, Quantity, BillComponents[billItems].amount);

                    billItems++;
                } 
                else 
                {
                    printf("Invalid quantity or insufficient stock (Available: %d)\n", items[itemIndex].quantity);
                }
            } 
            else 
            {
                printf("Item with code %d not found in inventory.\n", itemCode);
            }
        }
        else if (choice == 2 || choice == 3) 
        {
            break; 
        }
        else
        {
            printf("Invalid choice! Please enter 1, 2, or 3.\n");
        }
    } 

    if (choice == 2 && billItems > 0) 
    {
        printf("\nFinalizing bill...\n");
        printBill(BillComponents, billItems, subTotal, totalGST);
        
        for (int i = 0; i < billItems; i++) 
        {
            AllBills[totalAllBillItems++] = BillComponents[i];
        } 
    }
    else if (choice == 2 && billItems == 0) 
    {
        printf("\nCannot finalize, the bill is empty.\n");
    }
}

void addToFile(char fileName[], int mode, struct BillItems bill[], int count, double subTotal, double totalGST)
{    
    const char *companyName = "ABC Stationery Store";
    const char *state = "Delhi";
    const char *stateCode = "07";
    
    double grandTotal = subTotal + totalGST;

    FILE *fp;
    if (mode == 0)
    {
        fp = fopen(fileName, "w");
    }
    else
    {
        fp = fopen(fileName, "a");
    }

    if (!fp) 
    { 
        perror("Error opening file for GST log"); 
        return; 
    }

    fprintf(fp, "\n=======================================================================\n");
    fprintf(fp, "                           **GST INVOICE**\n");
    fprintf(fp, "-----------------------------------------------------------------------\n");
    fprintf(fp, "Company Name: %s\n", companyName);
    fprintf(fp, "Invoice No: ABC Stationers/2025/11/0001\n"); 
    fprintf(fp, "Date: %s\n", Date()); 
    fprintf(fp, "State: %s\n", state);
    fprintf(fp, "State Code : %s\n",stateCode);
    fprintf(fp, "Name: Customer Name\n");
    fprintf(fp, "=======================================================================\n");
    
    fprintf(fp, "%-5s %-20s %-10s %-10s %-10s %-8s\n","S No.", "Item Name", "Quantity", "Price(pp)", "Amount", "GST Rate");
    fprintf(fp, "-----------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) 
    {
        fprintf(fp, "%-5d %-20s %-10d %-10d %-10.2f %-8d%%\n",i + 1,bill[i].name,bill[i].quantity,bill[i].cost,bill[i].amount,bill[i].gstRate); 
    }

    fprintf(fp, "-----------------------------------------------------------------------\n");
    
    fprintf(fp, "%50s %-15s %.2f\n", "Total Amount Before Tax:", "", subTotal);
    fprintf(fp, "%50s %-15s %.2d\n", "Add CGST:", "", 0); 
    fprintf(fp, "%50s %-15s %.2d\n", "Add SGST:", "", 0);
    fprintf(fp, "%50s %-15s %.2f\n", "Add IGST:", "", totalGST);
    fprintf(fp, "=======================================================================\n");
    fprintf(fp, "%50s %-15s %.2f\n", "TOTAL AMOUNT:", "", grandTotal);
    fprintf(fp, "=======================================================================\n");
    
    fflush(fp);
    fclose(fp);
}

void printBillInFile(struct BillItems bill[], int count, double subTotal, double totalGST)
{   
    char fileName[50] = "Bills\\Bill";     
    int sixDigitRandomNumber = rand() % 900000 + 100000;
    char random[6];
    int temp = sixDigitRandomNumber;
    for (int i = 0; i < 5; i++)
    {
        int digit = temp % 10;
        char charDigit = (char)(digit + '0'); 
        
        random[i] = charDigit;
        temp /= 10;
    }
   
    strcat(fileName, random);
    strcat(fileName, ".txt");
    addToFile(fileName, 0, bill, count, subTotal, totalGST);
        
    addToFile("Reports/GST_Log.txt", 1, bill, count, subTotal, totalGST);
    return;
}

void printBill(struct BillItems bill[], int count, double subTotal, double totalGST)
{   
    printBillInFile(bill, count, subTotal, totalGST);
    
    const char *companyName = "ABC Stationery Store";
    const char *state = "Delhi";
    const char *stateCode = "07";
    
    double grandTotal = subTotal + totalGST;

    printf("\n=======================================================================\n");
    printf("                           **GST INVOICE**\n");
    printf("-----------------------------------------------------------------------\n");
    printf("Company Name: %s\n", companyName);
    printf("Invoice No: ABC Stationers/2025/11/0001\n"); 
    printf("Date: %s\n", Date()); 
    printf("State: %s\n", state);
    printf("State Code : %s\n",stateCode);
    printf("Name: Customer Name\n");
    printf("=======================================================================\n");
    
    printf("%-5s %-20s %-10s %-10s %-10s %-8s\n","S No.", "Item Name", "Quantity", "Price(pp)", "Amount", "GST Rate");
    printf("-----------------------------------------------------------------------\n");

    for (int i = 0; i < count; i++) 
    {
        printf("%-5d %-20s %-10d %-10d %-10.2f %-8d%%\n",i + 1,bill[i].name,bill[i].quantity,bill[i].cost,bill[i].amount,bill[i].gstRate); 
    }

    printf("-----------------------------------------------------------------------\n");
    
    printf("%50s %-15s %.2f\n", "Total Amount Before Tax:", "", subTotal);
    printf("%50s %-15s %.2d\n", "Add CGST:", "", 0); 
    printf("%50s %-15s %.2d\n", "Add SGST:", "", 0);
    printf("%50s %-15s %.2f\n", "Add IGST:", "", totalGST);
    printf("=======================================================================\n");
    printf("%50s %-15s %.2f\n", "TOTAL AMOUNT:", "", grandTotal);
    printf("=======================================================================\n");

    return;
}

void LowStock(struct inventory items[],int size) 
{   
    int temp =0;
    int found = 0;

    for(int i = 0; i < total_items ;i++)
    {
        if (items[i].quantity <= low_stock)
        {
            temp =1;
            found++;
            if(found == 1)
            {
                printf("\nLow Stock Items are :-\n");
                printf("%-10s %-20s %-10s %-10s %-10s%-10s\n", "Item Code", "Item Name", "GST Code", "Cost", "GST Rate","Quantity");
            }
            printf("%-10d %-20s %-10d %-10d %-10d %-10d\n",items[i].itemCode,items[i].name,items[i].gstCode,items[i].cost,items[i].gstRate,items[i].quantity);
            found++;
        }
    }
    if(temp == 0)
    {
        printf(" \nNo low stock items currently. \n");
    }
    return ;
}

void TopSellingItems() 
{
    struct SalesData {
        char name[100];
        int itemCode;
        int quantitySold;
        double totalRevenue;
    } sales[100];

    int salesCount = 0;
    for (int i = 0; i < totalAllBillItems; i++)
     {
        int found = 0;
        for (int j = 0; j < salesCount; j++) {
            if (sales[j].itemCode == AllBills[i].itemCode) 
            {
                sales[j].quantitySold += AllBills[i].quantity;
                sales[j].totalRevenue += AllBills[i].total;
                found = 1;
                break;
            }
        }
        if (!found) 
        {
            sales[salesCount].itemCode = AllBills[i].itemCode;
            strcpy(sales[salesCount].name, AllBills[i].name);
            sales[salesCount].quantitySold = AllBills[i].quantity;
            sales[salesCount].totalRevenue = AllBills[i].total;
            salesCount++;
        }
    }
    for (int i = 0; i < salesCount - 1; i++) 
    {
        for (int j = i + 1; j < salesCount; j++)
         {
            if (sales[j].quantitySold > sales[i].quantitySold) 
            {
                struct SalesData temp = sales[i];
                sales[i] = sales[j];
                sales[j] = temp;
            }
        }
    }
    printf("\n=== Top Selling Items ===\n");
    printf("%-5s %-20s %-10s %-15s\n", "S.No", "Item Name", "Qty Sold", "Revenue");
    printf("-------------------------------------------------\n");
    for (int i = 0; i < salesCount && i < 10; i++) { 
        printf("%-5d %-20s %-10d %-15.2f\n", i + 1, sales[i].name, sales[i].quantitySold, sales[i].totalRevenue);
    }
}

void returnItem(struct inventory items[], int size, struct BillItems bill[], int *billCount)
 {
    int itemCode, quantity;
    printf("\nEnter Item Code to return: ");
    scanf("%d", &itemCode);
    int billIndex = -1;
    for (int i = 0; i < *billCount; i++) 
    {
        if (bill[i].itemCode == itemCode) 
        {
            billIndex = i;
            break;
        }
    }
     if (billIndex == -1) 
     {
        printf("Item not found in the current bill.\n");
        return;
    }
     printf("Enter quantity to return (Max %d): ", bill[billIndex].quantity);
    scanf("%d", &quantity);

    if (quantity <= 0 || quantity > bill[billIndex].quantity)
     {
        printf("Invalid quantity.\n");
        return;
    }
    for (int i = 0; i < size; i++) 
    {
        if (items[i].itemCode == itemCode) 
        {
            items[i].quantity += quantity;
            break;
        }
    }
    double amountPerItem = bill[billIndex].cost;
    double gstPerItem = (bill[billIndex].gstRate / 100.0) * amountPerItem;
    double totalPerItem = amountPerItem + gstPerItem;

    bill[billIndex].quantity -= quantity;
    bill[billIndex].amount -= amountPerItem * quantity;
    bill[billIndex].gstAmount -= gstPerItem * quantity;
    bill[billIndex].total -= totalPerItem * quantity;

    printf("Return processed successfully.\n");
    if (bill[billIndex].quantity == 0) {
        for (int i = billIndex; i < *billCount - 1; i++) {
            bill[i] = bill[i + 1];
        }
        (*billCount)--;
    }
}

int loginFun(struct User users[], int num_users)
 {
    char username[50];
    char password[50];
    printf("\nEnter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s",password );

    for (int i = 0; i < num_users; ++i) 
    {
        if (strcmp(username, users[i].username) == 0 && strcmp(password, users[i].password) == 0) 
        {
            printf("Login successful. Role: ");
            switch (users[i].login) 
            {
                case 1: 
                printf("Shopkeeper\n");
                 break;
                case 2: 
                printf("Cashier\n"); 
                    break;
                case 3: 
                printf("Loader\n"); 
                    break;
                case 4: 
                printf("Self-checkout\n");
                 break;
            }
            return users[i].login;
        }
    }

    printf("Invalid username or password.\n");
    return 0;
}

int main()
{
    struct inventory items[100];

    items[0] =  (struct inventory){"Pen Black",1,9608,5,18,150};
    items[1] =  (struct inventory){"Pen Blue",2,9608,5,18,150};
    items[2] =  (struct inventory){"Pen Coloured",3,9608,10,18,100};
    items[3] =  (struct inventory){"Pencil",4,9609,5,12,200};
    items[4] =  (struct inventory){"Eraser",5,4016,2,18,100};
    items[5] =  (struct inventory){"Crayons",6,9609,30,18,50};
    items[6] =  (struct inventory){"Staplers",7,8205,50,18,20};
    items[7] =  (struct inventory){"Stapler pins",8,8205,10,18,30};
    items[8] =  (struct inventory){"Adhesive Tape",9,3919,25,18,30};
    items[9] =  (struct inventory){"Diaries",10,4820,250,18,40};
    items[10] = (struct inventory){"Marker Pen",11,9608,20,18,100};
    items[11] = (struct inventory){"Highlighter",12,9608,15,18,80};
    items[12] = (struct inventory){"Glue Stick",13,3506,10,18,120};
    items[13] = (struct inventory){"Drawing Book",14,4820,50,12,60};
    items[14] = (struct inventory){"Sketch Pen Set",15,9609,200,18,40};
    items[15] = (struct inventory){"Notebook",16,4820,30,12,150};
    items[16] = (struct inventory){"Geometry Box",17,9017,45,18,70};
    items[17] = (struct inventory){"Sharpener",18,4016,5,18,200};
    items[18] = (struct inventory){"Whiteboard",19,9403,300,18,15};
    items[19] = (struct inventory){"Clipboard",20,3926,120,18,25};
    items[20] = (struct inventory){"Paper Punch",21,8472,120,18,30};
    items[21] = (struct inventory){"File Tray",22,3926,200,18,25};
    items[22] = (struct inventory){"Cutter Knife",23,8213,70,18,40};
    items[23] = (struct inventory){"Punching Machine",24,8472,350,18,10};
    items[24] = (struct inventory){"Sticky Tack",25,3506,15,18,80};
    items[25] = (struct inventory){"Correction Pen", 26, 3824, 40, 18, 50};
    items[26] = (struct inventory){"A4 Paper Pack", 27, 4802, 350, 12, 60};
    items[27] = (struct inventory){"Folder Clips", 28, 8305, 15, 18, 100};
    items[28] = (struct inventory){"Index Dividers", 29, 4820, 60, 18, 40};
    items[29] = (struct inventory){"Rubber Bands", 30, 4008, 10, 12, 200};
    items[30] = (struct inventory){"Thermal Rolls", 31, 4811, 80, 18, 30};
    items[31] = (struct inventory){"Desk Organizer", 32, 3926, 180, 18, 20};
    items[32] = (struct inventory){"File Covers", 33, 4820, 20, 12, 150};
    items[33] = (struct inventory){"Ink Cartridge", 34, 8443, 800, 18, 15};
    items[34] = (struct inventory){"Letter Pad", 35, 4817, 45, 12, 75};
    items[35] = (struct inventory){"White Out Tape", 36, 4823, 35, 18, 90};
    items[36] = (struct inventory){"Stamp Pad", 37, 9611, 60, 18, 40};
    items[37] = (struct inventory){"Binder Clips", 38, 8305, 25, 18, 120};
    items[38] = (struct inventory){"Labeling Machine", 39, 8472, 2500, 18, 5};
    items[39] = (struct inventory){"Project Files", 40, 4820, 150, 12, 50};

    struct User users[4];
    users[0] = (struct User){"Shopkeeper","SK@123",1};
    users[1] = (struct User){"Cashier","C@123",2};
    users[2] = (struct User){"Loader","L@123",3};
    users[3] = (struct User){"Customer","123",4};


    int login = 0;
    printf("\n GST BILLING SYSTEM GENERATOR \n");
    printf("Login with your credentials :- \n");
    printf("1. Shopkeeper\n");
    printf("2. Cashier(s)\n");
    printf("3. Loader(Stock Updating)\n");
    printf("4. Customer(Self Checkout)\n");
   
    login = loginFun(users,4);

    int choice;
    switch(login)
    {
    case 1:
    do {
        printf("\n SHOPKEEPER PORTAL \n");
        printf("1. View All Items\n");
        printf("2. Search Item (by Name or Code)\n");
        printf("3. Add New Item\n");
        printf("4. Return Item\n"); 
        printf("5. Delete Item\n"); 
        printf("6. Update Quantity\n");
        printf("7. Generate Bill\n");
        printf("8. Show Low Stock Items\n"); 
        printf("9. Show Top Selling Items \n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice) {
            case 1:
                inventoryView(items,total_items);
                break;
            case 2:
                search(items,total_items);
                break;
            case 3:
                AddNewItem(items,&total_items);
                break;
            case 4:
            returnItem(items, total_items, BillComponents, &billItems);
            break;
            case 5:
                DeleteItem(items,total_items);
                break;
            case 6:
                UpdateQuantity(items,total_items);
                break;
            case 7:
                generateBill(items,total_items,BillComponents);
                break;
            case 8:
                LowStock(items,total_items);
                break;
            case 9:
                TopSellingItems();
                break; 
            case 10:
            {
               printf("Exiting program...Thanks For Visiting.\n");
                break;
            }
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 11);
    break;


    case 2:
    do {
        printf("\n CASHIER PORTAL \n");
        printf("1. View All Items\n");
        printf("2. Search Item (by Name or Code)\n");
        printf("3. Generate Bill\n");
        printf("4. Show Low Stock Items\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice)
        {
            case 1:
                inventoryView(items,total_items);
                break;
            case 2:
                search(items,total_items);
                break;
            case 3:
                generateBill(items,total_items,BillComponents);
                break;
            case 4:
                LowStock(items,total_items);
                break;
            case 5:
                printf("Exiting program...Thanks For Visiting.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 5);
    break;


    case 3:
    do {
        printf("\n STOCK UPDATING PORTAL \n");
        printf("1. View All Items\n");
        printf("2. Search Item (by Name or Code)\n");
        printf("3. Add New Item\n");
        printf("4. Update Quantity\n");
        printf("5. Show Low Stock Items\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice) {
            case 1:
               inventoryView(items,total_items);
                break;
            case 2:
                search(items,total_items);
                break;
            case 3:
                AddNewItem(items,&total_items);
                break;
            case 4:
                UpdateQuantity(items,total_items);
                break;
            case 5:
                LowStock(items,total_items);
                break;
            case 6:
                printf("Exiting program... Thanks For Visiting.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 6);
    break;

    case 4:
    do {
        printf("\n CUSTOMER PORTALL \n");
        printf("1. Generate Bill\n");
        printf("2. Search Item (by Name or Code)\n");
        printf("3. Return / Exchange Item \n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);


        switch(choice)
         {
            case 1:
               generateBill(items,total_items,BillComponents);
                break;
            case 2:
                search(items,total_items);
                break;
            case 3:
            {
                returnItem(items, total_items, BillComponents, &billItems);
                if (billItems > 0) {
                    double subTotal = 0.0;
                    double totalGST = 0.0;
                    printf("\n--- Updated Bill Summary ---\n");
                    printf("%-5s %-20s %-8s %-10s %-10s\n", "S.No", "Item Name", "Qty", "Amount", "GST");
                    printf("----------------------------------------------------\n");
                    for (int i = 0; i < billItems; i++) {
                        double amount = BillComponents[i].amount;
                        double gst = BillComponents[i].gstAmount;
                        subTotal += amount;
                        totalGST += gst;
                        printf("%-5d %-20s %-8d %-10.2f %-10.2f\n", i+1, BillComponents[i].name, BillComponents[i].quantity, amount, gst);
                    }
                    printf("----------------------------------------------------\n");
                    printf("%-35s %-10.2f\n", "Total (before tax):", subTotal);
                    printf("%-35s %-10.2f\n", "Total GST:", totalGST);
                    printf("%-35s %-10.2f\n", "GRAND TOTAL:", subTotal + totalGST);
                } else {
                    printf("\nNo items left in the current bill.\n");
                }
                break;
            }
            case 4:
                printf("Exiting program... Thanks For Visiting.\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != 4);
    break;

    default:
    printf("Invalid Login...Please try again");
    break;
}
    return 0;
}
