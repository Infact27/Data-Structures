#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node{
	char nama[30];
	char perusahaan[30];
	int invest;
	node*kiri;
	node*kanan;
};

node *pohon = NULL;

clr(){
	system("cls");
}

void addNew(node **root, int databaru){
       
    if ((*root)==NULL){      
        node *baru;
        
        baru = new node;
        
        baru->invest=databaru;
        baru->kiri=NULL;
        baru->kanan=NULL;
        (*root) = baru;
        (*root) -> kiri = NULL;
        (*root) -> kanan = NULL;
       }
    
    else if (databaru<(*root)->invest)
        addNew(&(*root)->kiri,databaru);
    
    else if (databaru>(*root)->invest)
        addNew(&(*root)->kanan,databaru);

    else if (databaru==(*root)->invest);
}


void fileread(){
	char nama[30];
	char perusahaan[30];
	int invest;
    FILE *in=fopen("test.txt","r");
    if(!in){
        printf("\n\t\t\t\tNo File\n");
    }else{
        while(!feof(in)){
            fscanf(in,"%[^#]#%[^#]#%d\n", &nama, &perusahaan, &invest);fflush(stdin);
            printf("|%-25s | %-25s | %-20d |\n", nama, perusahaan, invest);
            addNew(&pohon, invest);
        }
        fclose(in);
    }     
}

void fileadd(){
	
	struct node *temp = (struct node*)malloc(sizeof(struct node));
	
	char nama[30];
	char perusahaan[30];
	int invest;
	printf("Masukkan nama : "); gets(nama); fflush(stdin);
	printf("Masukkan perusahaan : "); gets(perusahaan); fflush(stdin);
	printf("Masukkan Invest : "); scanf("%d", &invest); fflush(stdin);
	addNew(&pohon, invest);
	strcpy(temp->nama, nama);
	strcpy(temp->perusahaan, perusahaan);

	FILE *out=fopen("test.txt","a+");
	fprintf(out,"%s#%s#%d\n",nama, perusahaan, invest);
	fclose(out);
	printf("\n\nSukses menambah data.");
	getchar();
}

void filedelete(){
	char nama[30];
	char perusahaan[30];
	int invest;
    FILE *in=fopen("test.txt","r");
    if(!in){
        printf("\t\t\t\tNo File\n\n");
    }else{
        while(!feof(in)){
            fscanf(in,"%[^#]#%[^#]#%d\n", &nama, &perusahaan, &invest);fflush(stdin);
            printf("%-25s | %-25s | %-20d |\n", nama, perusahaan, invest);
        }
        fclose(in);
    }
}

int counter(node *root){
       if(root==NULL)
              return 0;
       else
              return counter(root->kiri)+ counter(root->kanan)+1;
}


void hitung(){
	printf("\nJumlah Perusahaan yang Terdaftar");
    printf("\n-------------------------");
    printf("\nBanyak Perusahaan : %d\n\n", counter(pohon));
    system("pause");
}

void menu(){
	printf("Data Saham Perusahaan\n");
	printf("-------------------------------\n\n");
	printf("===============================================================================\n");
	fileread();
	printf("===============================================================================\n\n");
	printf("1. Buat data investor baru\n");
	printf("2. Cari data\n");
	printf("3. List\n");
	printf("4. Cek jumlah investor\n");
	printf("5. Exit\n");
}

int inOrder(node *root){
	char nama[30];
	char perusahaan[30];
       if(root!=NULL)
       {
           inOrder(root->kiri);
           if(root->invest!=NULL)
           {
               printf("%d ",root->invest);
           }
           inOrder(root->kanan);
        }
    return 0;
}

void postOrder(node *root){
	char nama[30];
	char perusahaan[30];
       if(root!=NULL){
         postOrder(root->kiri);
         postOrder(root->kanan);
         if(root->invest!=NULL)
         {
            printf("%d ",root->invest);
         }
       }
}

void search(node **root, int cari){
    if((*root) == NULL){
        printf("Data tidak ditemukan!");
    }
    else if(cari < (*root)->invest)
        search(&(*root)->kiri,cari);
    else if(cari > (*root)->invest)
        search(&(*root)->kanan,cari);
    else if(cari == (*root)->invest)
        printf("Data ditemukan!");
        
}

void searchmenu(){
	int cari;
	printf("\nMasukkan jumlah invest yang ingin dicari : ");
    scanf("%d", &cari);
    if(pohon!=NULL){
    search(&pohon, cari);
    }else{
    printf("\nMasih kosong!");
	}
	printf("\n\n");
	system("pause");
}

void listmenu(){
	int list_menu;
	clr();
	printf("Daftar Perusahaan\n\n");
	printf("1. Invest Tertinggi\n");
	printf("2. Invest Terendah\n");
	printf("Input Choice : ");
	scanf("%d", &list_menu);
	switch(list_menu){
		case 1 :
			postOrder(pohon);
			break;
		case 2 :
			inOrder(pohon);
			break;
	}
	printf("\n\n");
	system("pause");
}

main(){
	int input;
	do{
		do{
		clr();	
		menu();
		printf("\n>> Input Choice : ");
		scanf("%d", &input);
	}while(input > 5|| input < 1);
	
switch(input){
	case 1 :
		fileadd();
		break;
	case 2 :
		searchmenu();
		break;
	case 3 :
		listmenu();
		break;
	case 4:
		hitung();
		break;
	case 5:
		break;
		}
	}while(input<6);
}

