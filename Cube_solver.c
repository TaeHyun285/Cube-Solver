#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>

//큐브 회전 함수
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

void rotate_left();
void rotate_right();

//큐브 출력 함수
void print_current_cube();
void textcolor(int color_name);

//큐브 입력 함수
void func_init(char *file_name);

//상수값(큐브에서 변하지않는 중앙에 위치한 색) 초기화 함수
void reset_constant();

//큐브의 입력이 옳바른지 확인하는 함수
int cube_valid_check();

//각각의 지정된 블럭을 맞추는 함수
void front_down();
void front_right_down();
void front_right();

//큐브를 맞추기위한 공식(큐브 회전의 조합)
void func_front_right();
void func_up_edge();
void func_middle_edge();
void func_up_side();
void func_middle_vertex();

//상수값
char LEFT=' ';
char FRONT=' ';
char RIGHT=' ';
char BACK=' ';
char UP=' ';
char DOWN=' ';

//입력값
char l[3][3]={{'O','O','O'},{'O','O','O'},{'O','O','O'}};
char f[3][3]={{'G','G','G'},{'G','G','G'},{'G','G','G'}};
char r[3][3]={{'R','R','R'},{'R','R','R'},{'R','R','R'}};
char b[3][3]={{'B','B','B'},{'B','B','B'},{'B','B','B'}};
char u[3][3]={{'W','W','W'},{'W','W','W'},{'W','W','W'}};
char d[3][3]={{'Y','Y','Y'},{'Y','Y','Y'},{'Y','Y','Y'}};

//포인터
char (*pl)[3], (*pf)[3], (*pr)[3], (*pb)[3], (*pu)[3], (*pd)[3];

//큐브를 돌린 횟수
int cnt=0;

int checker=0;

//큐브 출력 여부 (0일시 큐브 미출력 / 1일시 큐브 출력)
int flag;
int temp_flag;

//입력 방식 선택
int option;

int main(int argc, char *argv[]){
    while(1){
        printf("1.랜덤한 입력값 설정\n");
        printf("2.파일로부터 입력값 받아오기\n");
        printf("3.끝내기\n\n");
        fflush(stdin);
        scanf("%d",&option);

        if(option==1 || option==2 || option==3) break;
        printf("\n잘못된 입력입니다.\n\n");
    }

    if(option==1){
        srand((int)time(NULL));

        //포인터에 함수 주소 지정
        pl = l; pf = f; pr = r; pb = b; pu = u; pd = d;

        //입력받은 함수로 부터 상수값 초기화
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
        // 파일로부터 배열 세팅
        char file_name[100] = "cube_init";

        if(argc==2) {
            printf("%s\n", argv[1]);
            strcat(file_name, "_");
            strcat(file_name, argv[1]);
        }
        strcat(file_name, ".txt");
        printf("\nfile name : %s\n", file_name);

        func_init(file_name);

        //포인터에 함수 주소 지정
        pl = l; pf = f; pr = r; pb = b; pu = u; pd = d;

        //입력받은 함수로 부터 상수값 초기화
        reset_constant();

        //입력이 옳바른지 확인
        int validity = cube_valid_check();
        if(validity == 0){
            printf("잘못된 입력입니다.");
            scanf("%c",&validity);
            exit(0);
        }
    }

    else if(option==3) exit(0);

    print_current_cube();

    flag=1;
    cnt=0;

    //1단계 - 아랫면 십자 맞추기
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

    //2단계 - 아랫면 꼭짓점 맞추기
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

    //3단계 - 둘째 줄 맞추기
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

    //4단계 - 윗면 모서리 맞추기
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

    //5단계 - 옆면 위쪽 모서리 맞추기
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

    //6단계 - 윗면 모두 맞추기
    while(pu[0][0]!=UP || pu[0][2]!=UP || pu[2][0]!=UP || pu[2][1]!=UP){

        if(pf[0][0]==UP && pf[0][2]==UP && pb[0][0]==UP && pb[0][2]==UP || pl[0][0]==UP && pl[0][2]==UP && pf[0][2]==UP && pb[0][0]==UP || pl[0][2]==UP && pr[0][2]==UP && pb[0][2]==UP && pu[2][2]==UP || pf[0][0]==UP && pr[0][0]==UP && pb[0][0]==UP && pu[0][0]==UP || pl[0][0]==UP && pl[0][2]==UP && pu[0][2]==UP && pu[2][2]==UP || pf[0][2]==UP && pb[0][0]==UP && pu[0][0]==UP && pu[2][0]==UP || pl[0][2]==UP && pb[0][0]==UP && pu[0][0]==UP && pu[2][2]==UP){
            func_up_side();
        }
        rotate_left();

    }

    //7단계 - 옆면 꼭짓점 맞추기
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
    }

    return 0;
}


int cube_valid_check(){
    //가운데 상수 중복 확인
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

}

void func_sym_L(){

    temp_flag=flag;

    flag=0;

    func_L(); func_L(); func_L();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_L\n");
    print_current_cube();

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

}

void func_sym_F(){

    temp_flag=flag;

    flag=0;

    func_F(); func_F(); func_F();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_F\n");
    print_current_cube();

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

}

void func_sym_R(){

    temp_flag=flag;

    flag=0;

    func_R(); func_R(); func_R();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_R\n");
    print_current_cube();

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

}

void func_sym_B(){

    temp_flag=flag;

    flag=0;

    func_B(); func_B(); func_B();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_B\n");
    print_current_cube();

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

}

void func_sym_U(){

    temp_flag=flag;

    flag=0;

    func_U(); func_U(); func_U();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_U\n");
    print_current_cube();

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

}

void func_sym_D(){

    temp_flag=flag;

    flag=0;

    func_D(); func_D(); func_D();

    flag=temp_flag;

    if(flag==0) return;

    printf("Sym_D\n");
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
        printf("파일이 열리지 않았습니다.\n");
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
        if(pf[2][1]==DOWN && pd[0][1]==FRONT){        //밑쪽에 있는거 위로
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

        if(pf[1][2]==DOWN && pr[1][0]==FRONT){      //중간에 있는거 위로
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

        if(pu[0][1]==FRONT && pb[0][1]==DOWN || pu[0][1]==DOWN && pb[0][1]==FRONT){     //위에 있는거를 바로 위쪽으로 돌리기
            func_U(); func_U();
        }
        else if(pu[1][0]==FRONT && pl[0][1]==DOWN || pu[1][0]==DOWN && pl[0][1]==FRONT){
            func_sym_U();
        }
        else if(pu[1][2]==FRONT && pr[0][1]==DOWN || pu[1][2]==DOWN && pr[0][1]==FRONT){
            func_U();
        }

        if(pf[0][1]==FRONT && pu[2][1]==DOWN){      //위에서 아래로 내리기
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
        if(pf[2][2]==DOWN && pr[2][0]==FRONT && pd[0][2]==RIGHT || pf[2][2]==RIGHT && pr[2][0]==DOWN && pd[0][2]==FRONT){       //밑에있는거 위로 올리기
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

        if(pu[0][0]==DOWN && pl[0][0]==FRONT && pb[0][2]==RIGHT || pu[0][0]==RIGHT && pl[0][0]==DOWN && pb[0][2]==FRONT || pu[0][0]==FRONT && pl[0][0]==RIGHT && pb[0][2]==DOWN){       //바로 위로 모으기
            func_U(); func_U();
        }
        else if(pu[2][0]==DOWN && pf[0][0]==FRONT && pl[0][2]==RIGHT || pu[2][0]==RIGHT && pf[0][0]==DOWN && pl[0][2]==FRONT || pu[2][0]==FRONT && pf[0][0]==RIGHT && pl[0][2]==DOWN){
            func_sym_U();
        }
        else if(pu[0][2]==DOWN && pb[0][0]==FRONT && pr[0][2]==RIGHT || pu[0][2]==RIGHT && pb[0][0]==DOWN && pr[0][2]==FRONT || pu[0][2]==FRONT && pb[0][0]==RIGHT && pr[0][2]==DOWN){
            func_U();
        }

        if(pf[0][2]==DOWN && pu[2][2]==FRONT && pr[0][0]==RIGHT){       //아래로 맞추기
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
    if(pf[1][2]==RIGHT && pr[1][0]==FRONT){     //중간에서 위로 올리기
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

    if(pu[1][0]==FRONT && pl[0][1]==RIGHT){     //잘못된 상태로 오른쪽 위로보내기
        func_U(); func_U();
    }
    else if(pu[0][1]==FRONT && pb[0][1]==RIGHT){
        func_U();
    }
    else if(pu[2][1]==FRONT && pf[0][1]==RIGHT){
        func_sym_U();
    }

    if(pu[1][0]==RIGHT && pl[0][1]==FRONT){     //옳바른 상태로 앞쪽 위로 보내기
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
