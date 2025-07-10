#include <stdio.h>
#include <string.h>

// โครงสร้างสินค้า
typedef struct {
    char name[20];
    int price;
    int quantity;
} Product;

// สินค้า
Product products[] = {
    {"Coke", 10, 10},
    {"Sunflower", 13, 5},
    {"GreenTea", 12, 5},
    {"PeanutBar", 20, 5},
    {"Americano", 30, 5},
    {"OrangeSnack", 15, 5},
    {"LatteSweet", 35, 5}
};
const int num_products = sizeof(products)/sizeof(products[0]);

// เหรียญที่รับ
int accepted[] = {1,5,10,20,50,100};
const int num_accepted = sizeof(accepted)/sizeof(accepted[0]);

// ยอดเงินคงเหลือ
int balance = 0;

// ฟังก์ชันตรวจสอบเหรียญ
int is_accepted(int amount) {
    for(int i=0; i<num_accepted; i++) {
        if (accepted[i] == amount) return 1;
    }
    return 0;
}

// ฟังก์ชันแสดงสินค้า
void show_products() {
    printf("สินค้าที่มีจำหน่าย:\n");
    for(int i=0; i<num_products; i++) {
        printf("- %s ราคา %d บาท (เหลือ %d)\n", 
               products[i].name, products[i].price, products[i].quantity);
    }
}

// คืนเงินทอน
void make_change(int money) {
    printf("เงินทอนคืน:\n");
    for(int i=num_accepted-1; i>=0; i--) {
        int coin = accepted[i];
        int count = money / coin;
        if (count > 0) {
            printf("%d บาท x %d\n", coin, count);
        }
        money %= coin;
    }
}

// เลือกสินค้า
void select_product() {
    show_products();
    printf("เลือกสินค้า (พิมพ์ชื่อสินค้าที่ตรง), หรือ 'cancel' เพื่อคืนเงิน\n> ");
    char choice[20];
    scanf("%s", choice);

    if(strcmp(choice, "cancel")==0) {
        make_change(balance);
        balance = 0;
        return;
    }

    int found = 0;
    for(int i=0; i<num_products; i++) {
        if(strcmp(choice, products[i].name)==0) {
            found = 1;
            if(products[i].quantity <= 0) {
                printf("สินค้าหมด\n");
                return;
            }
            if(balance < products[i].price) {
                printf("ยอดเงินไม่พอ! ยังขาดอีก %d บาท\n", products[i].price - balance);
                return;
            }
            // จ่ายสินค้า
            balance -= products[i].price;
            products[i].quantity--;
            printf("รับสินค้า: %s ราคา %d บาท\n", products[i].name, products[i].price);

            if(balance > 0) {
                make_change(balance);
            }
            balance = 0;
            printf("ขอบคุณที่ใช้บริการ!\n");
            return;
        }
    }

    if(!found) {
        printf("สินค้าไม่มีในระบบ\n");
    }
}

// main
int main() {
    printf("*** เครื่องขายน้ำอัตโนมัติ ตะพาบลอย (ภาษา C) ***\n");
    while(1) {
        printf("\nใส่เหรียญหรือธนบัตร (1,5,10,20,50,100) หรือ 0 เพื่อยกเลิก\n> ");
        int coin;
        scanf("%d", &coin);
        if(coin==0) {
            if(balance>0) {
                printf("คืนเงินเต็มจำนวน:\n");
                make_change(balance);
                balance = 0;
            }
            continue;
        }
        if(is_accepted(coin)) {
            balance += coin;
            printf("ยอดเงินปัจจุบัน: %d บาท\n", balance);
        } else {
            printf("เหรียญไม่รับ กรุณาใส่ใหม่!\n");
        }

        printf("ต้องการซื้อสินค้าหรือไม่? พิมพ์ 'y' เพื่อเลือก, อื่นๆ เพื่อใส่เงินต่อ\n> ");
        char cmd[10];
        scanf("%s", cmd);
        if(cmd[0]=='y' || cmd[0]=='Y') {
            select_product();
        }
    }
    return 0;
}