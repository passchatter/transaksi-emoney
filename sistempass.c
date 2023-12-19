#include <stdio.h>
#include <string.h>

struct Account{
    int id_account;
    char name[50];
    int saldo;
};

struct History{
    int id_account;
    char action[50];
    int jumlah;
    int id_account_b;
};

//fungins untuk menu
void menu(){
    printf("\n=====menu=====\n");
    printf("1. Buat Account\n");
    printf("2. Info Accout\n");
    printf("3. Withdraw\n");
    printf("4. Deposit\n");
    printf("5. Tranfer\n");
    printf("6. History\n");
}


//funsing untuk membuat account
int buatAccount(struct Account account[], int *idx_account){
    printf("\n====buat account====\n");
    int newId;
    int matchingId = 0;
    
    do {
        matchingId = 0;
        printf("id : ");
        scanf("%d", &newId);

        for(int i = 0; i < *idx_account; i++){
            if(account[i].id_account == newId){
                printf("Maaf, ID sudah terdaftar\n");
                matchingId = 1;
                break;
            }
        }
    } while(matchingId);

    account[*idx_account].id_account = newId;

    getchar();
    printf("name : ");
    fgets(account[*idx_account].name, sizeof(account[*idx_account].name), stdin);
    
    printf("saldo awal min(200000) : ");
    scanf("%d", &account[*idx_account].saldo);
    getchar();
    
    if(account[*idx_account].saldo < 200000){
        printf("Maaf, saldo minimal adalah 200000\n");
    } else {
        printf("Akun berhasil dibuat\n\n");
        (*idx_account)++;
    }
    
    return *idx_account;
}


//fungsi info accout
void infoAccount(struct Account account[], int idx_account){
    int idAccount;
    int macId = 0;
    printf("id account : ");
    scanf("%d", &idAccount);
    printf("\n=====info saldo=====\n");
    for(int i=0; i < idx_account; i++){
        if(account[i].id_account == idAccount){
            printf("name : %s", account[i].name);
            printf("saldo : %d", account[i].saldo);
            macId = 1;
        }
    }
    if(!macId){
        printf("maaf akun tidak di temukan");
    }
    printf("\n");

}


//fungsig tarik saldo
int withdraw(struct Account account[], int idx_account, struct History history[], int *idx_history){
    int idAccount;
    int macId = 0;

    printf("\n=====withdraw saldo=====\n");
    printf("id account : ");
    scanf("%d", &idAccount);
    for(int i=0; i<idx_account; i++){
        if(account[i].id_account == idAccount){
            int jumlah;
            macId = 1;
            printf("jumlah : ");
            scanf("%d", &jumlah);
            if(account[i].saldo >= jumlah){
                account[i].saldo -= jumlah;
                history[*idx_history].id_account = idAccount;
                strcpy(history[*idx_history].action, "Withdraw");
                history[*idx_history].jumlah = jumlah;
                printf("penarikan berhasil");
            }
        }
    }
    if(!macId){
        printf("maaf akun tidak di temukan");
    }

    printf("\n");
    (*idx_history)++;
    return *idx_history;
   
}


int topUp(struct Account account[], int idx_account, struct History history[], int *idx_history){
    int idAccount;
    int macId = 0;
    printf("\n=====Top Up saldo=====\n");
    printf("id accout : ");
    scanf("%d", &idAccount);
    for(int i=0; i<idx_account; i++){
        if(account[i].id_account ==  idAccount){
            int jumlah;
            macId = 1;
            printf("jumlah : ");
            scanf("%d", &jumlah);
            history[*idx_history].id_account = idAccount;
            strcpy(history[*idx_history].action, "Deposit");
            history[*idx_history].jumlah = jumlah;
            account[i].saldo += jumlah;
        }
    }
    if(!macId){
        printf("maaf akun tidak di temukan");
    }
    printf("\n");
    (*idx_history)++;
    return *idx_history;
}

int tranfer(struct Account account[], int idx_account, struct History history[], int *idx_history){
    printf("\n====transfer====\n");
    int pengirim, penerima;
    printf("id pengirim : ");
    scanf("%d", &pengirim);
    int macPengirim = 0;
    int macPenerima = 0;

    for(int i=0; i<idx_account; i++){
        if(account[i].id_account == pengirim){
            macPengirim = 1;
            printf("id penerima : ");
            scanf("%d", &penerima);
            int jumlah;
            printf("jumlah transfer : ");
            scanf("%d", &jumlah);

            if(account[i].saldo >= jumlah){
                for(int j=0; j<idx_account; j++){
                    if(account[j].id_account == penerima){
                        printf("sumber : %s", account[i].name);
                        printf("penerima : %s", account[j].name);
                        printf("jumlah : %d\n", jumlah);
                        macPenerima = 1; 
                        char konfirmasi[3];
                        printf("konfirmasi (y/n) : ");
                        scanf("%s", konfirmasi);
                        if (strcmp(konfirmasi, "y")==0){
                            printf("tranfer berhasil");
                            account[j].saldo += jumlah;
                            account[i].saldo -= jumlah;

                            history[*idx_history].id_account = pengirim;
                            snprintf(history[*idx_history].action, sizeof(history[*idx_history].action), "transfer => %s", account[j].name);
                            history[*idx_history].jumlah = jumlah;
                            (*idx_history)++; 
                            history[*idx_history].id_account = penerima;
                            snprintf(history[*idx_history].action, sizeof(history[*idx_history].action), "penerima => %s", account[i].name);
                            history[*idx_history].jumlah = jumlah;
                            (*idx_history)++; 
                        }else{
                            printf("tranfer di batalkan");
                        }
                       
                    }
                }
                if(!macPenerima){
                    printf("maaf id tujuan tidak di temukan");
                }
            }else{
                printf("maaf saldo tidak cukup ");
            }  
            break;    
        }
    }

    if(!macPengirim){
        printf("maaf id tidak tersedia");
    }

     printf("\n");
   
    return *idx_history;
    
}

void lihatHistory(struct History history[], int idx_history){
    int idAccount;
    int macId = 0;
    printf("id account : ");
    scanf("%d", &idAccount);
    printf("\n=====history=====\n");
    for(int i=0; i < idx_history; i++){
        if(history[i].id_account == idAccount){
            macId = 1;
            printf("jumlah: %d | aksi: %s \n", history[i].jumlah, history[i].action);
        }
    }
}

int main(){

    struct Account account[10];
    struct History history[100];

    int pilihan;
    int idx_account = 0;
    int idx_history = 0;

    do{
        menu();
        printf("input pilihan : ");
        scanf("%d", &pilihan);
        getchar();
        switch(pilihan){
            case 1:
                idx_account = buatAccount(account, &idx_account);
                break;
            case 2:
                infoAccount(account, idx_account);
                break;
            case 3:
                idx_history = withdraw(account, idx_account, history, &idx_history);
                break;
            case 4:
                idx_history = topUp(account, idx_account, history, &idx_history);
                break;
            case 5:
                idx_account = tranfer(account, idx_account, history, &idx_history);
                break;
            case 6:
                lihatHistory(history, idx_history);
                break;
        }
        
    }while(pilihan != 0);

    return 0;
}