#include<bits/stdc++.h>
#define fo(x,z,y) for(int x = (z); x < (y); ++x)
#define rfo(x,z,y) for(int x = (y) - 1; x >= (z); --x)
using namespace std;

map<string,int> ma;//��ָ����й�ϣ
string s,op[50],func[50];
int inst[200];//ָ���
int flag[50];//0��1��2�ֱ��ʾ��Ӧָ��Ϊr�͡�i�ͺ�J��ָ��
void presolve(){
    ma["add"] = 0,flag[0] = 0,op[0] = "000000",func[0] = "100000";
    ma["sub"] = 1,flag[1] = 0,op[1] = "000000",func[1] = "100010";
    ma["addiu"] = 2,flag[2] = 1,op[2] = "001001";
    ma["addu"] = 3,flag[3] = 0,op[3] = "000000",func[3] = "100001";
    ma["subu"] = 4,flag[4] = 0,op[4] = "000000",func[4] = "100011";
    ma["addi"] = 5,flag[5] = 1,op[5] = "001000";
    ma["andi"] = 6,flag[6] = 1,op[6] = "001100";
    ma["and"] = 7,flag[7] = 0,op[7] = "000000",func[7] = "100100";
    ma["ori"] = 8,flag[8] = 1,op[8] = "001101";
    ma["or"] = 9,flag[9] = 0,op[9] = "000000",func[9] = "100101";
    ma["xori"] = 10,flag[10] = 1,op[10] = "001110";
    ma["xor"] = 11,flag[11] = 0,op[11] = "000000",func[11] = "100110";
    ma["nor"] = 12,flag[12] = 0,op[12] = "000000",func[12] = "100111";
    ma["lui"] = 13,flag[13] = 1,op[13] = "001111";
    ma["sll"] = 14,flag[14] = 0,op[14] = "000000",func[14] = "000000";
    ma["srl"] = 15,flag[15] = 0,op[15] = "000000",func[15] = "000010";
    ma["sra"] = 16,flag[16] = 0,op[16] = "000000",func[16] = "000011";
    ma["sllv"] = 17,flag[17] = 0,op[17] = "000000",func[17] = "000100";
    ma["srlv"] = 18,flag[18] = 0,op[18] = "000000",func[18] = "000110";
    ma["srav"] = 19,flag[19] = 0,op[19] = "000000",func[19] = "000111";
    ma["slti"] = 20,flag[20] = 1,op[20] = "001010";
    ma["slt"] = 21,flag[21] = 0,op[21] = "000000",func[21] = "101010";
    ma["sltu"] = 22,flag[22] = 0,op[22] = "000000",func[22] = "101011";
    ma["sltiu"] = 23,flag[23] = 1,op[23] = "001011";
    ma["sw"] = 24,flag[24] = 1,op[24] = "101011";
    ma["lw"] = 25,flag[25] = 1,op[25] = "100011";
    ma["beq"] = 26,flag[26] = 1,op[26] = "000100";
    ma["bne"] = 27,flag[27] = 1,op[27] = "000101";
    ma["bltz"] = 28,flag[28] = 1,op[28] = "000001";
    ma["j"] = 29,flag[29] = 2,op[29] = "000010";
    ma["jr"] = 30,flag[30] = 0,op[30] = "000000",func[30] = "001000";
    ma["jal"] = 31,flag[31] = 2,op[31] = "000011";
    ma["halt"] = 32,flag[32] = 2,op[32] = "111111";
}
void print(int t){
    static int flag = 2;//Ϊ0ֻ��������ƻ������룬Ϊ1ֻ���16���ƻ������룬Ϊ2ȫ�����
    int now = 0;
    reverse(inst,inst+t);
    if(flag) fo(i,0,t) if(inst[i] == 0)now<<=1;else if(inst[i] == 1)now= now*2+1;
    if(!(flag&1)) fo(i,0,t) if(inst[i] == -1) putchar(' ');  else putchar('0' + inst[i]);//��������ƴ���
    if(flag) {
        if(flag == 2) putchar('\t');
        printf("%08X",now);//���16���ƴ���
    }
    puts("");
}
int main(){
    presolve();//Ԥ����,��������ϲ���ָ��Ļ��
    while(cin>>s){//�������ļ��е�ÿһ��mipsָ����ɶ����ƻ������뼰16���ƻ�������.
        int len = 0;//ָ���,Ϊ�˷�����⣬�����ƻ����������ָ�����Ͳ����˲��ֿո�.
        int id = ma[s];
        if(flag[id] == 2){//����ָ�����ͽ��зֱ���
            int addr = 0;
            if(id != 32)scanf("%x",&addr);
            addr>>=2;//��ַ����λ������ʾ
            fo(i,0,16) inst[len++] = addr&1,addr>>=1;
            inst[len++] = -1;//-1��ʾ�ո�,�ָ��ֶ�
            fo(i,0,5) inst[len++] = addr&1,addr>>=1;
            inst[len++] = -1;//-1��ʾ�ո�
            fo(i,0,5) inst[len++] = addr&1,addr>>=1;
            inst[len++] = -1;//-1��ʾ�ո�
            rfo(i,0,6) inst[len++] = op[id][i] - '0';
        }else if(flag[id] == 1){
            int rs = 0,rt = 0,imm;
            switch(id){
                case 13:scanf(" $%d %*c%d",&rt,&imm);break;
                case 24:
                case 25:scanf(" $%d %*c%d($%d)",&rt,&imm,&rs);break;
                case 26:
                case 27:scanf(" $%d %*c $%d %*c%d",&rs,&rt,&imm);break;
                case 28:scanf(" $%d %*c%d",&rs,&imm);break;
                default:scanf(" $%d %*c $%d %*c%d",&rt,&rs,&imm);break;
            }
            rfo(i,0,16) inst[len++] = imm&1,imm>>=1;
            inst[len++] = -1;
            rfo(i,0,5) inst[len++] = rt&1,rt>>=1;
            inst[len++] = -1;
            rfo(i,0,5) inst[len++] = rs&1,rs>>=1;
            inst[len++] = -1;
            rfo(i,0,6) inst[len++] = op[id][i] - '0';
        }else {
            int rs = 0,rt = 0,rd = 0,sa = 0;
            switch(id){
                case 14:
                case 15:
                case 16:scanf(" $%d %*c $%d %*c%d",&rd,&rt,&sa);break;
                case 30:scanf(" $%d",&rs);break;
                default:scanf(" $%d %*c $%d %*c $%d",&rd,&rs,&rt);break;
            }
            rfo(i,0,6) inst[len++] = func[id][i] - '0';
            inst[len++] = -1;
            rfo(i,0,5) inst[len++] = sa&1,sa>>=1;
            inst[len++] = -1;
            rfo(i,0,5) inst[len++] = rd&1,rd>>=1;
            inst[len++] = -1;
            rfo(i,0,5) inst[len++] = rt&1,rt>>=1;
            inst[len++] = -1;
            rfo(i,0,5) inst[len++] = rs&1,rs>>=1;
            inst[len++] = -1;
            rfo(i,0,6) inst[len++] = op[id][i] - '0';
        }
        while(getchar()!='\n');//�˵������ַ�
        print(len);//���ָ��
    }
    return 0;
}