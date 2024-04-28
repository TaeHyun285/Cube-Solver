#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

//ť�� ȸ�� �Լ�
void func_L ();
void func_sym_L();
void func_F ();
void func_sym_F();
void func_R ();
void func_sym_R();
void func_B ();
void func_sym_B();
void func_U ();
void func_sym_U();
void func_D ();
void func_sym_D();
void func_E ();
void func_sym_E();
void func_M ();
void func_sym_M();
void func_S ();
void func_sym_S();
void func_r ();
void func_sym_r();

void rotate_left();
void rotate_right();

//ť�� ��� �Լ�
void print_current_cube();
void textcolor(int color_name);

//ť�� �Է� �Լ�
void func_init(char *file_name);

//�����(ť�꿡�� �������ʴ� �߾ӿ� ��ġ�� ��) �ʱ�ȭ �Լ�
void reset_constant();

//ť���� �Է��� �ǹٸ��� Ȯ���ϴ� �Լ�
int cube_valid_check();

//������ ������ ���� ���ߴ� �Լ�
void front_down();
void front_right_down();
void front_right();

//ť�긦 ���߱����� ����(ť�� ȸ���� ����)
void func_front_right();
void func_up_edge();
void func_middle_edge();
void func_up_side();
void func_middle_vertex();

//�迭 ���� �Լ�
void delete_array(int num);

//�����
char LEFT=' ';
char FRONT=' ';
char RIGHT=' ';
char BACK=' ';
char UP=' ';
char DOWN=' ';

//�Է°�
char l[3][3]={{'O','O','O'},{'O','O','O'},{'O','O','O'}};
char f[3][3]={{'G','G','G'},{'G','G','G'},{'G','G','G'}};
char r[3][3]={{'R','R','R'},{'R','R','R'},{'R','R','R'}};
char b[3][3]={{'B','B','B'},{'B','B','B'},{'B','B','B'}};
char u[3][3]={{'W','W','W'},{'W','W','W'},{'W','W','W'}};
char d[3][3]={{'Y','Y','Y'},{'Y','Y','Y'},{'Y','Y','Y'}};

//������
char (*pl)[3], (*pf)[3], (*pr)[3], (*pb)[3], (*pu)[3], (*pd)[3];

//ť�긦 ���� Ƚ��
int cnt=0;

int checker=0;

//ť�� ��� ���� (0�Ͻ� ť�� ����� / 1�Ͻ� ť�� ���)
int flag;
int temp_flag;

//�Է� ��� ����
int option;

//ť��迭
int cube_array[500] = {0,};

//ť�� �ݺ� Ȯ��
int repeat_cnt = 0;

int main(int argc, char *argv[]){
    while(1){
        printf("1.������ �Է°� ����\n");
        printf("2.���Ϸκ��� �Է°� �޾ƿ���\n");
        printf("3.������\n\n");
        fflush(stdin);
        scanf("%d",&option);

        if(option==1 || option==2 || option==3) break;
        printf("\n�߸��� �Է��Դϴ�.\n\n");
    }

    if(option==1){
        srand((int)time(NULL));

        //�����Ϳ� �Լ� �ּ� ����
        pl = l; pf = f; pr = r; pb = b; pu = u; pd = d;

        //�Է¹��� �Լ��� ���� ����� �ʱ�ȭ
        reset_constant();

        flag=0;

        for(int i=0; i<50; i++){

            int random = rand()%14+1;

            switch(random){
            case 1:
                func_L(); break;
            case 2:
                func_sym_L(); break;
            case 3:
                func_F(); break;
            case 4:
                func_sym_F(); break;
            case 5:
                func_R(); break;
            case 6:
                func_sym_R(); break;
            case 7:
                func_B(); break;
            case 8:
                func_sym_B(); break;
            case 9:
                func_U(); break;
            case 10:
                func_sym_U(); break;
            case 11:
                func_D(); break;
            case 12:
                func_sym_D(); break;
            case 13:
                rotate_left(); break;
            case 14:
                rotate_right();
            }
        }
    }

    else if(option==2){
        // ���Ϸκ��� �迭 ����
        char file_name[100] = "cube_init";

        if(argc==2) {
            printf("%s\n", argv[1]);
            strcat(file_name, "_");
            strcat(file_name, argv[1]);
        }
        strcat(file_name, ".txt");
        printf("\nfile name : %s\n", file_name);

        func_init(file_name);

        //�����Ϳ� �Լ� �ּ� ����
        pl = l; pf = f; pr = r; pb = b; pu = u; pd = d;

        //�Է¹��� �Լ��� ���� ����� �ʱ�ȭ
        reset_constant();

        //�Է��� �ǹٸ��� Ȯ��
        int validity = cube_valid_check();
        if(validity == 0){
            printf("�߸��� �Է��Դϴ�.");
            scanf("%c",&validity);
            exit(0);
        }
    }

    else if(option==3) exit(0);

    print_current_cube();

    flag=1;
    cnt=0;


    //1�ܰ� - �Ʒ��� ���� ���߱�
    while(pd[0][1]!=DOWN || pd[1][0]!=DOWN || pd[1][2]!=DOWN || pd[2][1]!=DOWN || pl[2][1]!=LEFT || pf[2][1]!=FRONT || pr[2][1]!=RIGHT || pb[2][1]!=BACK){
        front_down();
        rotate_left();

        front_down();
        rotate_left();

        front_down();
        rotate_left();

        front_down();
        rotate_left();
    }

    //2�ܰ� - �Ʒ��� ������ ���߱�
    while(pd[0][0]!=DOWN || pd[0][2]!=DOWN || pd[2][0]!=DOWN || pd[2][2]!=DOWN || pl[2][0]!=LEFT || pf[2][0]!=FRONT || pr[2][0]!=RIGHT || pb[2][0]!=BACK || pl[2][2]!=LEFT || pf[2][2]!=FRONT || pr[2][2]!=RIGHT || pb[2][2]!=BACK){
        front_right_down();
        rotate_left();

        front_right_down();
        rotate_left();

        front_right_down();
        rotate_left();

        front_right_down();
        rotate_left();
    }

    //3�ܰ� - ��° �� ���߱�
    while(pl[1][0]!=LEFT || pf[1][0]!=FRONT || pr[1][0]!=RIGHT || pb[1][0]!=BACK || pl[1][2]!=LEFT || pf[1][2]!=FRONT || pr[1][2]!=RIGHT || pb[1][2]!=BACK){
        front_right();
        rotate_left();

        front_right();
        rotate_left();

        front_right();
        rotate_left();

        front_right();
        rotate_left();
    }

    //4�ܰ� - ���� �𼭸� ���߱�
    while(pu[0][1]!=UP || pu[1][0]!=UP || pu[1][2]!=UP || pu[2][1]!=UP){

        if(pu[1][0]==UP && pu[1][2]==UP){
            func_U();
        }
        else if(pu[0][1]==UP && pu[1][2]==UP){
            func_U(); func_U();
        }
        else if(pu[0][1]==UP && pu[1][0]==UP){
            func_sym_U();
        }
        else if(pu[1][2]==UP && pu[2][1]==UP){
            func_U();
        }

        if(pu[0][1]!=UP && pu[1][0]!=UP && pu[1][2]!=UP && pu[2][1]!=UP || pu[0][1]==UP && pu[1][0]!=UP && pu[1][2]!=UP && pu[2][1]!=UP || pu[0][1]!=UP && pu[1][0]==UP && pu[1][2]!=UP && pu[2][1]!=UP || pu[0][1]!=UP && pu[1][0]!=UP && pu[1][2]==UP && pu[2][1]!=UP || pu[0][1]!=UP && pu[1][0]!=UP && pu[1][2]!=UP && pu[2][1]==UP){
            func_up_edge();
        }
        else if(pu[0][1]==UP && pu[2][1]==UP){
            func_up_edge();
        }
        else if(pu[1][0]==UP  && pu[2][1]==UP){
            func_up_edge();
        }

    }

    //5�ܰ� - ���� ���� �𼭸� ���߱�
    checker=0;

    while(pl[0][1]!=LEFT || pf[0][1]!=FRONT || pr[0][1]!=RIGHT || pb[0][1]!=BACK){

        if(checker>3){
            func_middle_edge(); checker=0;
        }

        if(pf[0][1]==FRONT && pb[0][1]==BACK){
            func_middle_edge(); rotate_left(); rotate_left(); checker=0;
        }

        if(pl[0][1]==FRONT && pf[0][1]==RIGHT && pr[0][1]==LEFT && pb[0][1]==BACK){
            func_middle_edge();
        }

        if(pl[0][1]==RIGHT && pf[0][1]==LEFT && pr[0][1]==FRONT && pb[0][1]==BACK){
            func_middle_edge(); checker=0; break;
        }

        func_U();

        checker++;

    }

    //6�ܰ� - ���� ��� ���߱�
    while(pu[0][0]!=UP || pu[0][2]!=UP || pu[2][0]!=UP || pu[2][1]!=UP){

        if(pf[0][0]==UP && pf[0][2]==UP && pb[0][0]==UP && pb[0][2]==UP || pl[0][0]==UP && pl[0][2]==UP && pf[0][2]==UP && pb[0][0]==UP || pl[0][2]==UP && pr[0][2]==UP && pb[0][2]==UP && pu[2][2]==UP || pf[0][0]==UP && pr[0][0]==UP && pb[0][0]==UP && pu[0][0]==UP || pl[0][0]==UP && pl[0][2]==UP && pu[0][2]==UP && pu[2][2]==UP || pf[0][2]==UP && pb[0][0]==UP && pu[0][0]==UP && pu[2][0]==UP || pl[0][2]==UP && pb[0][0]==UP && pu[0][0]==UP && pu[2][2]==UP){
            func_up_side();
        }
        rotate_left();

    }

    //7�ܰ� - ���� ������ ���߱�
    checker=0;

    while(pl[0][0]!=LEFT || pf[0][0]!=FRONT || pr[0][0]!=RIGHT || pb[0][0]!=BACK || pl[0][2]!=LEFT || pf[0][2]!=FRONT || pr[0][2]!=RIGHT || pb[0][2]!=BACK){

        if(checker>3){
            func_middle_vertex(); checker=0;
        }

        if(pl[0][0]==FRONT && pl[0][2]==RIGHT && pf[0][0]==BACK && pf[0][2]==FRONT && pr[0][0]==RIGHT && pr[0][2]==BACK && pb[0][0]==LEFT && pb[0][2]==LEFT){
            func_middle_vertex();
        }

        if(pl[0][0]==BACK && pl[0][2]==BACK && pf[0][0]==LEFT && pf[0][2]==FRONT && pr[0][0]==RIGHT && pr[0][2]==LEFT && pb[0][0]==FRONT && pb[0][2]==RIGHT){
            func_middle_vertex(); break;
        }

        rotate_left();

        checker++;
    }

    printf("Took %d moves to solve\n\n\n",cnt);




    while(1){
            for(int i=0; i<500 && cube_array[i] != 0; i++){

            //1+-1=0
            if(cube_array[i]+cube_array[i+1]==13 ){
                delete_array(i);
                delete_array(i);
                repeat_cnt++;
            }
            else if(cube_array[i]+cube_array[i+1] == 27){
                delete_array(i);
                delete_array(i);
                repeat_cnt++;
            }
            //1+1+1+1=0
            if(cube_array[i]==cube_array[i+1] && cube_array[i+2]==cube_array[i+3] && cube_array[i+1]==cube_array[i+2]){
                delete_array(i);
                delete_array(i);
                delete_array(i);
                delete_array(i);
                repeat_cnt++;
            }

            //1+1+1=-1
            if(cube_array[i]==cube_array[i+1] && cube_array[i+1]==cube_array[i+2] && cube_array[i]!=13 && cube_array[i]!=14){
                cube_array[i] = 13-cube_array[i];
                delete_array(i+1);
                delete_array(i+1);
                repeat_cnt++;
            }
            else if(cube_array[i]==cube_array[i+1] && cube_array[i+1]==cube_array[i+2] && cube_array[i]==13){
                cube_array[i] = 14;
                delete_array(i+1);
                delete_array(i+1);
                repeat_cnt++;
            }
            else if(cube_array[i]==cube_array[i+1] && cube_array[i+1]==cube_array[i+2] && cube_array[i]==14){
                cube_array[i] = 13;
                delete_array(i+1);
                delete_array(i+1);
                repeat_cnt++;
            }
        }
        //�ݺ�����
            
        if(repeat_cnt==0) break;

        repeat_cnt=0;
    }

    for(int i=0; i<500; i++){
        if(cube_array[i]==13){
            for(int j=i+1; j<500; j++){
                if(cube_array[j]==1) cube_array[j]=2;
                else if(cube_array[j]==2) cube_array[j]=3;
                else if(cube_array[j]==3) cube_array[j]=4;
                else if(cube_array[j]==4) cube_array[j]=1;
                else if(cube_array[j]==9) cube_array[j]=12;
                else if(cube_array[j]==10) cube_array[j]=9;
                else if(cube_array[j]==11) cube_array[j]=10;
                else if(cube_array[j]==12) cube_array[j]=11;
                else if(cube_array[j]==0) break;
            }
            delete_array(i);
            i--;            
        }
    }

    for(int i=0; i<500; i++){
        if(cube_array[i]==14){
            for(int j=i+1; j<500; j++){
                if(cube_array[j]==1) cube_array[j]=4;
                else if(cube_array[j]==2) cube_array[j]=1;
                else if(cube_array[j]==3) cube_array[j]=2;
                else if(cube_array[j]==4) cube_array[j]=3;
                else if(cube_array[j]==9) cube_array[j]=10;
                else if(cube_array[j]==10) cube_array[j]=11;
                else if(cube_array[j]==11) cube_array[j]=12;
                else if(cube_array[j]==12) cube_array[j]=9;
                else if(cube_array[j]==0) break;
            }
            delete_array(i);
            i--;        
        }
    }

    //1+1=100
    for(int i=0; i<500; i++){
        if(cube_array[i]==cube_array[i+1] && cube_array[i]!=13 && cube_array[i]!=14){
            cube_array[i] = cube_array[i]*100;
            delete_array(i+1);
        }
    }

    //���� ���
    FILE * fp=fopen("cube array.rtf","wt");
    if(fp==NULL){
        puts("���Ͽ��� ����!");
        return -1;
    }
    for(int i=0; i<500; i++){
        switch(cube_array[i]){
            case 0:
                fputs("0\n", fp);
                break;
            case 1:
                fputs("1\n", fp);
                break;
            case 2:
                fputs("2\n", fp);
                break;
            case 3:
                fputs("3\n", fp);
                break;
            case 4:
                fputs("4\n", fp);
                break;
            case 5:
                fputs("5\n", fp);
                break;
            case 6:
                fputs("6\n", fp);
                break;
            case 7:
                fputs("7\n", fp);
                break;
            case 8:
                fputs("8\n", fp);
                break;
            case 9:
                fputs("9\n", fp);
                break;
            case 10:
                fputs("10\n", fp);
                break;
            case 11:
                fputs("11\n", fp);
                break;
            case 12:
                fputs("12\n", fp);
                break;
            case 100:
                fputs("100\n", fp);
                break;
            case 200:
                fputs("200\n", fp);
                break;
            case 300:
                fputs("300\n", fp);
                break;
            case 400:
                fputs("400\n", fp);
                break;
            case 500:
                fputs("500\n", fp);
                break;
            case 600:
                fputs("600\n", fp);
                break;
            case 700:
                fputs("700\n", fp);
                break;
            case 800:
                fputs("800\n", fp);
                break;
            case 900:
                fputs("900\n", fp);
                break;
            case 1000:
                fputs("1000\n", fp);
                break;
            case 1100:
                fputs("1100\n", fp);
                break;
            case 1200:
                fputs("1200\n", fp);
                break;
            case 13:
                fputs("13\n", fp);
                break;
            case 14:
                fputs("14\n", fp);
                break;
        }
    }
    fclose(fp);
    
    while(1){
    }

    return 0;
}

int cube_valid_check(){
    //��� ��� �ߺ� Ȯ��
    int cnt_o=0,cnt_g=0,cnt_r=0,cnt_b=0,cnt_w=0,cnt_y=0;
    char a;

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(pl[i][j]==pl[1][1]) cnt_o++;
            else if(pl[i][j]==pf[1][1]) cnt_g++;
            else if(pl[i][j]==pr[1][1]) cnt_r++;
            else if(pl[i][j]==pb[1][1]) cnt_b++;
            else if(pl[i][j]==pu[1][1]) cnt_w++;
            else if(pl[i][j]==pd[1][1]) cnt_y++;
            else return 0;
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(pf[i][j]==pl[1][1]) cnt_o++;
            else if(pf[i][j]==pf[1][1]) cnt_g++;
            else if(pf[i][j]==pr[1][1]) cnt_r++;
            else if(pf[i][j]==pb[1][1]) cnt_b++;
            else if(pf[i][j]==pu[1][1]) cnt_w++;
            else if(pf[i][j]==pd[1][1]) cnt_y++;
            else return 0;
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(pr[i][j]==pl[1][1]) cnt_o++;
            else if(pr[i][j]==pf[1][1]) cnt_g++;
            else if(pr[i][j]==pr[1][1]) cnt_r++;
            else if(pr[i][j]==pb[1][1]) cnt_b++;
            else if(pr[i][j]==pu[1][1]) cnt_w++;
            else if(pr[i][j]==pd[1][1]) cnt_y++;
            else return 0;
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(pb[i][j]==pl[1][1]) cnt_o++;
            else if(pb[i][j]==pf[1][1]) cnt_g++;
            else if(pb[i][j]==pr[1][1]) cnt_r++;
            else if(pb[i][j]==pb[1][1]) cnt_b++;
            else if(pb[i][j]==pu[1][1]) cnt_w++;
            else if(pb[i][j]==pd[1][1]) cnt_y++;
            else return 0;
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(pu[i][j]==pl[1][1]) cnt_o++;
            else if(pu[i][j]==pf[1][1]) cnt_g++;
            else if(pu[i][j]==pr[1][1]) cnt_r++;
            else if(pu[i][j]==pb[1][1]) cnt_b++;
            else if(pu[i][j]==pu[1][1]) cnt_w++;
            else if(pu[i][j]==pd[1][1]) cnt_y++;
            else return 0;
        }
    }
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            if(pd[i][j]==pl[1][1]) cnt_o++;
            else if(pd[i][j]==pf[1][1]) cnt_g++;
            else if(pd[i][j]==pr[1][1]) cnt_r++;
            else if(pd[i][j]==pb[1][1]) cnt_b++;
            else if(pd[i][j]==pu[1][1]) cnt_w++;
            else if(pd[i][j]==pd[1][1]) cnt_y++;
            else return 0;
        }
    }

    if(cnt_o>9 || cnt_g>9 || cnt_r>9 || cnt_b>9 || cnt_w>9 || cnt_y>9) return 0;
    else if(pl[1][1]==pf[1][1] || pl[1][1] == pr[1][1] || pl[1][1] == pb[1][1] || pl[1][1] == pu[1][1] || pl[1][1] == pd[1][1] || pf[1][1] == pr[1][1] || pf[1][1] == pb[1][1] || pf[1][1] == pu[1][1] || pf[1][1] == pd[1][1] || pr[1][1] == pb[1][1] || pr[1][1] == pu[1][1] || pr[1][1] == pd[1][1] || pb[1][1] == pu[1][1] || pb[1][1] == pd[1][1] || pu[1][1] == pd[1][1]) return 0;
    else return 1;

}

void func_L(){
    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pl[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pl[i][j]=temp[2-j][i];
        }
    }

    temp[0][0]=pf[0][0];
    pf[0][0]=pu[0][0];
    pu[0][0]=pb[2][2];
    pb[2][2]=pd[0][0];
    pd[0][0]=temp[0][0];

    temp[1][0]=pf[1][0];
    pf[1][0]=pu[1][0];
    pu[1][0]=pb[1][2];
    pb[1][2]=pd[1][0];
    pd[1][0]=temp[1][0];

    temp[2][0]=pf[2][0];
    pf[2][0]=pu[2][0];
    pu[2][0]=pb[0][2];
    pb[0][2]=pd[2][0];
    pd[2][0]=temp[2][0];

    if(flag==0) return;

    printf("L\n");
    print_current_cube();

    cube_array[cnt-1] = 1;
}

void func_sym_L(){
    temp_flag=flag;

    flag=0;

    func_L(); func_L(); func_L();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_L\n");
    print_current_cube();

    cube_array[cnt-1] = 12;
}

void func_F(){
    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pf[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pf[i][j]=temp[2-j][i];
        }
    }

    temp[2][2]=pu[2][2];
    pu[2][2]=pl[0][2];
    pl[0][2]=pd[0][0];
    pd[0][0]=pr[2][0];
    pr[2][0]=temp[2][2];

    temp[2][1]=pu[2][1];
    pu[2][1]=pl[1][2];
    pl[1][2]=pd[0][1];
    pd[0][1]=pr[1][0];
    pr[1][0]=temp[2][1];

    temp[2][0]=pu[2][0];
    pu[2][0]=pl[2][2];
    pl[2][2]=pd[0][2];
    pd[0][2]=pr[0][0];
    pr[0][0]=temp[2][0];

    if(flag==0) return;

    printf("F\n");
    print_current_cube();

    cube_array[cnt-1] = 2;
}

void func_sym_F(){
    temp_flag=flag;

    flag=0;

    func_F(); func_F(); func_F();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_F\n");
    print_current_cube();

    cube_array[cnt-1] = 11;
}

void func_R(){
    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pr[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pr[i][j]=temp[2-j][i];
        }
    }

    temp[0][2]=pf[0][2];
    pf[0][2]=pd[0][2];
    pd[0][2]=pb[2][0];
    pb[2][0]=pu[0][2];
    pu[0][2]=temp[0][2];

    temp[1][2]=pf[1][2];
    pf[1][2]=pd[1][2];
    pd[1][2]=pb[1][0];
    pb[1][0]=pu[1][2];
    pu[1][2]=temp[1][2];

    temp[2][2]=pf[2][2];
    pf[2][2]=pd[2][2];
    pd[2][2]=pb[0][0];
    pb[0][0]=pu[2][2];
    pu[2][2]=temp[2][2];

    if(flag==0) return;

    printf("R\n");
    print_current_cube();

    cube_array[cnt-1] = 3;
}

void func_sym_R(){
    temp_flag=flag;

    flag=0;

    func_R(); func_R(); func_R();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_R\n");
    print_current_cube();

    cube_array[cnt-1] = 10;
}

void func_B(){
    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pb[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pb[i][j]=temp[2-j][i];
        }
    }

    temp[0][0]=pu[0][0];
    pu[0][0]=pr[0][2];
    pr[0][2]=pd[2][2];
    pd[2][2]=pl[2][0];
    pl[2][0]=temp[0][0];

    temp[0][1]=pu[0][1];
    pu[0][1]=pr[1][2];
    pr[1][2]=pd[2][1];
    pd[2][1]=pl[1][0];
    pl[1][0]=temp[0][1];

    temp[0][2]=pu[0][2];
    pu[0][2]=pr[2][2];
    pr[2][2]=pd[2][0];
    pd[2][0]=pl[0][0];
    pl[0][0]=temp[0][2];

    if(flag==0) return;

    printf("B\n");
    print_current_cube();

    cube_array[cnt-1] = 4;
}

void func_sym_B(){
    temp_flag=flag;

    flag=0;

    func_B(); func_B(); func_B();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_B\n");
    print_current_cube();

    cube_array[cnt-1] = 9;
}

void func_U(){
    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pu[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pu[i][j]=temp[2-j][i];
        }
    }

    temp[0][0]=pf[0][0];
    pf[0][0]=pr[0][0];
    pr[0][0]=pb[0][0];
    pb[0][0]=pl[0][0];
    pl[0][0]=temp[0][0];

    temp[0][1]=pf[0][1];
    pf[0][1]=pr[0][1];
    pr[0][1]=pb[0][1];
    pb[0][1]=pl[0][1];
    pl[0][1]=temp[0][1];

    temp[0][2]=pf[0][2];
    pf[0][2]=pr[0][2];
    pr[0][2]=pb[0][2];
    pb[0][2]=pl[0][2];
    pl[0][2]=temp[0][2];

    if(flag==0) return;

    printf("U\n");
    print_current_cube();

    cube_array[cnt-1] = 5;
}

void func_sym_U(){
    temp_flag=flag;

    flag=0;

    func_U(); func_U(); func_U();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_U\n");
    print_current_cube();

    cube_array[cnt-1] = 8;
}

void func_D(){
    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pd[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pd[i][j]=temp[2-j][i];
        }
    }

    temp[2][0]=pf[2][0];
    pf[2][0]=pl[2][0];
    pl[2][0]=pb[2][0];
    pb[2][0]=pr[2][0];
    pr[2][0]=temp[2][0];

    temp[2][1]=pf[2][1];
    pf[2][1]=pl[2][1];
    pl[2][1]=pb[2][1];
    pb[2][1]=pr[2][1];
    pr[2][1]=temp[2][1];

    temp[2][2]=pf[2][2];
    pf[2][2]=pl[2][2];
    pl[2][2]=pb[2][2];
    pb[2][2]=pr[2][2];
    pr[2][2]=temp[2][2];

    if(flag==0) return;

    printf("D\n");
    print_current_cube();

    cube_array[cnt-1] = 6;
}

void func_sym_D(){
    temp_flag=flag;

    flag=0;

    func_D(); func_D(); func_D();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_D\n");
    print_current_cube();

    cube_array[cnt-1] = 7;
}

void func_E (){
    char temp[3][3];

    for(int i=0; i<3; i++){
        temp[1][i]=pf[1][i];
        pf[1][i]=pl[1][i];
        pl[1][i]=pb[1][i];
        pb[1][i]=pr[1][i];
        pr[1][i]=temp[1][i];
    }

    if(flag==0) return;

    printf("E\n");
    print_current_cube();
}

void func_sym_E(){
    temp_flag=flag;

    flag=0;

    func_E(); func_E(); func_E();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_E\n");
    print_current_cube();
}

void func_M (){
    char temp[3][3];

    for(int i=0; i<3; i++){
        temp[i][1]=pf[i][1];
        pf[i][1]=pu[i][1];
        pu[i][1]=pb[i][1];
        pb[i][1]=pd[i][1];
        pd[i][1]=temp[i][1];
    }

    if(flag==0) return;

    printf("M\n");
    print_current_cube();
}

void func_sym_M(){
    temp_flag=flag;

    flag=0;

    func_M(); func_M(); func_M();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_M\n");
    print_current_cube();
}

void func_S (){
    /*(1,0) (2,1) (1,2) (0,1)
      (1,1) (1,1) (1,1) (1,1)
      (1,2) (0,1) (1,0) (2,1)*/    
    char temp[3][3];

    for(int i=0; i<3; i++){
        temp[1][i]=pu[1][i];
        pu[1][i]=pl[1][i];
        pl[1][i]=pd[1][i];
        pd[1][i]=pr[1][i];
        pr[1][i]=temp[1][i];
    }

    if(flag==0) return;

    printf("S\n");
    print_current_cube();
}

void func_sym_S(){
    temp_flag=flag;

    flag=0;

    func_S(); func_S(); func_S();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_S\n");
    print_current_cube();
}

void func_r (){
    char temp[3][3];

    for(int i=0; i<3; i++){
        temp[i][1]=pf[i][1];
        pf[i][1]=pd[i][1];
        pd[i][1]=pb[i][1];
        pb[i][1]=pu[i][1];
        pu[i][1]=temp[i][1];
    }

    if(flag==0) return;

    printf("r\n");
    print_current_cube();
}

void func_sym_r(){
    temp_flag=flag;

    flag=0;

    func_r(); func_r(); func_r();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_r\n");
    print_current_cube();
}

void rotate_left() {
    char (*ptemp)[3] = pf;
    pf = pr;
    pr = pb;
    pb = pl;
    pl = ptemp;

    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pu[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pu[i][j]=temp[2-j][i];
        }
    }

    for(int p=0; p<3; p++){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i][j]=pd[i][j];
            }
        }

        for (int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                pd[i][j]=temp[2-j][i];
            }
        }
    }

    reset_constant();

    if(flag==0) return;

    printf("Rotate Left\n");
    print_current_cube();

    cube_array[cnt-1] = 13;
}

void rotate_right() {
    char (*ptemp)[3] = pf;
    pf = pl;
    pl = pb;
    pb = pr;
    pr = ptemp;

    char temp[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            temp[i][j]=pd[i][j];
        }
    }

    for (int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            pd[i][j]=temp[2-j][i];
        }
    }

    for(int p=0; p<3; p++){
        for(int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                temp[i][j]=pu[i][j];
            }
        }

        for (int i=0; i<3; i++){
            for(int j=0; j<3; j++){
                pu[i][j]=temp[2-j][i];
            }
        }
    }

    reset_constant();

    if(flag==0) return;

    printf("Rotate Right\n");
    print_current_cube();

    cube_array[cnt-1] = 14;
}

void print_current_cube(){
    printf("\n");

    printf("------------------------------------------------\n");

    printf("\n");

    for(int i=0; i<3; i++){
        printf("            ");
        for(int j=0; j<3; j++){
            textcolor(pu[i][j]);
            printf("%c   ",pu[i][j]);
        }
        printf("\n\n");
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            textcolor(pl[i][j]);
            printf("%c   ",pl[i][j]);
        }
        for(int j=0; j<3; j++){
            textcolor(pf[i][j]);
            printf("%c   ",pf[i][j]);
        }
        for(int j=0; j<3; j++){
            textcolor(pr[i][j]);
            printf("%c   ",pr[i][j]);
        }
        for(int j=0; j<3; j++){
            textcolor(pb[i][j]);
            printf("%c   ",pb[i][j]);
        }
        printf("\n\n");
    }

    for(int i=0; i<3; i++){
        printf("            ");
        for(int j=0; j<3; j++){
            textcolor(pd[i][j]);
            printf("%c   ",pd[i][j]);
        }
        printf("\n\n");
    }

    textcolor('W');
    printf("------------------------------------------------\n");

    cnt++;

    char a;
    fflush(stdin);
    scanf("%c",&a);

}

void textcolor(int color_name) {
    int color=color_name;
    switch(color){
    case 'O':
        color=6;
        break;
    case 'G':
        color=2;
        break;
    case 'R':
        color=4;
        break;
    case 'B':
        color=1;
        break;
    case 'W':
        color=15;
        break;
    case 'Y':
        color=14;
        break;
    default :
        color=15;
    }
    SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), color);
}

void func_init(char *file_name) {

    FILE *fp;

    fp = fopen(file_name, "r");
    if(fp == NULL) {
        printf("������ ������ �ʾҽ��ϴ�.\n");
        return;
    }

    fscanf(fp, "%s %s %s", &u[0], &u[1], &u[2]);
    fscanf(fp, "%s %s %s %s", &l[0], &f[0], &r[0], &b[0]);
    fscanf(fp, "%s %s %s %s", &l[1], &f[1], &r[1], &b[1]);
    fscanf(fp, "%s %s %s %s", &l[2], &f[2], &r[2], &b[2]);
    fscanf(fp, "%s %s %s", &d[0], &d[1], &d[2]);

    fclose(fp);
}

void reset_constant(){
    LEFT=pl[1][1]; FRONT=pf[1][1]; RIGHT=pr[1][1]; BACK=pb[1][1]; UP=pu[1][1]; DOWN=pd[1][1];
}

void front_down(){
    while(pf[2][1]!=FRONT || pd[0][1]!=DOWN){
        if(pf[2][1]==DOWN && pd[0][1]==FRONT){        //���ʿ� �ִ°� ����
        func_F(); func_F();
        }
        else if(pd[1][2]==DOWN && pr[2][1]==FRONT || pd[1][2]==FRONT && pr[2][1]==DOWN){
            func_R(); func_R();
        }
        else if(pd[2][1]==DOWN && pb[2][1]==FRONT || pd[2][1]==FRONT && pb[2][1]==DOWN){
            func_B(); func_B();
        }
        else if(pd[1][0]==DOWN && pl[2][1]==FRONT || pd[1][0]==FRONT && pl[2][1]==DOWN){
            func_L(); func_L();
        }

        if(pf[1][2]==DOWN && pr[1][0]==FRONT){      //�߰��� �ִ°� ����
            func_R(); func_U(); func_sym_R();
        }
        else if(pf[1][0]==DOWN && pl[1][2]==FRONT){
            func_sym_L(); func_sym_U(); func_L();
        }
        else if(pr[1][2]==DOWN && pb[1][0]==FRONT){
            func_B(); func_U(); func_sym_B();
        }
        else if(pr[1][2]==FRONT && pb[1][0]==DOWN){
            func_sym_R(); func_U(); func_R();
        }
        else if(pb[1][2]==DOWN && pl[1][0]==FRONT){
            func_L(); func_sym_U(); func_sym_L();
        }
        else if(pb[1][2]==FRONT && pl[1][0]==DOWN){
            func_sym_B(); func_U(); func_B();
        }

        if(pu[0][1]==FRONT && pb[0][1]==DOWN || pu[0][1]==DOWN && pb[0][1]==FRONT){     //���� �ִ°Ÿ� �ٷ� �������� ������
            func_U(); func_U();
        }
        else if(pu[1][0]==FRONT && pl[0][1]==DOWN || pu[1][0]==DOWN && pl[0][1]==FRONT){
            func_sym_U();
        }
        else if(pu[1][2]==FRONT && pr[0][1]==DOWN || pu[1][2]==DOWN && pr[0][1]==FRONT){
            func_U();
        }

        if(pf[0][1]==FRONT && pu[2][1]==DOWN){      //������ �Ʒ��� ������
            func_F(); func_F();
        }
        else if(pf[1][0]==FRONT && pl[1][2]==DOWN){
            func_sym_F();
        }
        else if(pf[1][2]==FRONT && pr[1][0]==DOWN){
            func_F();
        }
        else if(pf[0][1]==DOWN && pu[2][1]==FRONT){
            func_U(); func_L(); func_sym_F(); func_sym_L();
        }
    }
}

void front_right_down(){
    while(pf[2][2]!=FRONT || pr[2][0]!=RIGHT || pd[0][2]!=DOWN){
        if(pf[2][2]==DOWN && pr[2][0]==FRONT && pd[0][2]==RIGHT || pf[2][2]==RIGHT && pr[2][0]==DOWN && pd[0][2]==FRONT){       //�ؿ��ִ°� ���� �ø���
            func_R(); func_U(); func_sym_R();
        }
        else if(pl[2][2]==DOWN && pf[2][0]==FRONT && pd[0][0]==RIGHT || pl[2][2]==RIGHT && pf[2][0]==DOWN && pd[0][0]==FRONT || pl[2][2]==FRONT && pf[2][0]==RIGHT && pd[0][0]==DOWN){
            func_F(); func_U(); func_sym_F();
        }
        else if(pb[2][2]==DOWN && pl[2][0]==FRONT && pd[2][0]==RIGHT || pb[2][2]==RIGHT && pl[2][0]==DOWN && pd[2][0]==FRONT || pb[2][2]==FRONT && pl[2][0]==RIGHT && pd[2][0]==DOWN){
            func_L(); func_U(); func_sym_L();
        }
        else if(pr[2][2]==DOWN && pb[2][0]==FRONT && pd[2][2]==RIGHT || pr[2][2]==RIGHT && pb[2][0]==DOWN && pd[2][2]==FRONT || pr[2][2]==FRONT && pb[2][0]==RIGHT && pd[2][2]==DOWN){
            func_B(); func_U(); func_sym_B();
        }

        if(pu[0][0]==DOWN && pl[0][0]==FRONT && pb[0][2]==RIGHT || pu[0][0]==RIGHT && pl[0][0]==DOWN && pb[0][2]==FRONT || pu[0][0]==FRONT && pl[0][0]==RIGHT && pb[0][2]==DOWN){       //�ٷ� ���� ������
            func_U(); func_U();
        }
        else if(pu[2][0]==DOWN && pf[0][0]==FRONT && pl[0][2]==RIGHT || pu[2][0]==RIGHT && pf[0][0]==DOWN && pl[0][2]==FRONT || pu[2][0]==FRONT && pf[0][0]==RIGHT && pl[0][2]==DOWN){
            func_sym_U();
        }
        else if(pu[0][2]==DOWN && pb[0][0]==FRONT && pr[0][2]==RIGHT || pu[0][2]==RIGHT && pb[0][0]==DOWN && pr[0][2]==FRONT || pu[0][2]==FRONT && pb[0][0]==RIGHT && pr[0][2]==DOWN){
            func_U();
        }

        if(pf[0][2]==DOWN && pu[2][2]==FRONT && pr[0][0]==RIGHT){       //�Ʒ��� ���߱�
            func_sym_F(); func_sym_U(); func_F();
        }
        else if(pf[0][2]==RIGHT && pu[2][2]==DOWN && pr[0][0]==FRONT){
            func_R(); func_U(); func_U(); func_sym_R(); func_sym_U(); func_R(); func_U(); func_sym_R();
        }
        else if(pf[0][2]==FRONT && pu[2][2]==RIGHT && pr[0][0]==DOWN){
            func_R(); func_U(); func_sym_R();
        }
    }
}

void front_right(){
    if(pf[1][2]==RIGHT && pr[1][0]==FRONT){     //�߰����� ���� �ø���
        func_front_right();
    }
    else if(pl[1][2]==FRONT && pf[1][0]==RIGHT || pl[1][2]==RIGHT && pf[1][0]==FRONT){
        rotate_right(); func_front_right(); rotate_left();
    }
    else if(pl[1][0]==FRONT && pb[1][2]==RIGHT || pl[1][0]==RIGHT && pb[1][2]==FRONT){
        rotate_left(); rotate_left(); func_front_right(); rotate_left(); rotate_left();
    }
    else if(pr[1][2]==FRONT && pb[1][0]==RIGHT || pr[1][2]==RIGHT && pb[1][0]==FRONT){
        rotate_left(); func_front_right(); rotate_right();
    }

    if(pu[1][0]==FRONT && pl[0][1]==RIGHT){     //�߸��� ���·� ������ ���κ�����
        func_U(); func_U();
    }
    else if(pu[0][1]==FRONT && pb[0][1]==RIGHT){
        func_U();
    }
    else if(pu[2][1]==FRONT && pf[0][1]==RIGHT){
        func_sym_U();
    }

    if(pu[1][0]==RIGHT && pl[0][1]==FRONT){     //�ǹٸ� ���·� ���� ���� ������
        func_sym_U();
    }
    else if(pu[0][1]==RIGHT && pb[0][1]==FRONT){
        func_U(); func_U();
    }
    else if(pu[1][2]==RIGHT && pr[0][1]==FRONT){
        func_U();
    }

    if(pu[1][2]==FRONT && pr[0][1]==RIGHT){
        func_R(); func_sym_U();func_sym_R(); func_F(); func_sym_R(); func_sym_F(); func_R(); func_front_right();
    }
    else if(pu[2][1]==RIGHT && pf[0][1]==FRONT){
        func_front_right();
    }
}

void func_front_right(){
    func_U(); func_R(); func_sym_U();func_sym_R(); func_F(); func_sym_R(); func_sym_F(); func_R();
}

void func_up_edge(){
    func_R(); func_U(); func_B(); func_sym_U(); func_sym_B(); func_sym_R();
}

void func_middle_edge(){
    func_sym_R(); func_sym_U(); func_R(); func_sym_U(); func_sym_R(); func_U(); func_U(); func_R();
}

void func_up_side(){
    func_sym_R(); func_sym_F(); func_sym_L(); func_F(); func_R(); func_sym_F(); func_L(); func_F();
}

void func_middle_vertex(){
    func_R(); func_U(); func_B(); func_L(); func_sym_B(); func_sym_R(); func_B(); func_sym_L(); func_sym_B(); func_R(); func_sym_U(); func_sym_R();
}

void delete_array(int num){
    for(int i=num; i<500; i++){
        cube_array[i]=cube_array[i+1];
    }
}