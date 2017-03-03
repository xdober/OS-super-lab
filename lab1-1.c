/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main( ) {
  char src_name[255], tgt_name[255], swap[1024];
  FILE *fp_src, *fp_tgt;// fp source and dp target;
  int j = 1024;//read 1024 bytes one time;
  int flag_name_check = 1;
  do {
    printf("please input the source file name:\n");
    scanf("%s", src_name);
    getchar();
    printf("please input the target file name\n", tgt_name);
    scanf("%s", tgt_name);
    getchar();
    flag_name_check = !strcmp(src_name, tgt_name);
    if (flag_name_check) {
      printf("Error! your source flie and target file have the same name.\n");
    }
  } while(flag_name_check);
  printf("source file: %s\ntarget file: %s\n", src_name, tgt_name);
  printf("copy processing...\n");
  fp_src = fopen(src_name, "r");
  fp_tgt = fopen(tgt_name, "w");
  if (!fp_src) {
    printf("error open source file\n");
    return 0;
  }
  if (!fp_tgt) {
    printf("error open target file\n");
    return 0;
  }
  while ( j == 1024) {//read uncomplete
    j = fread(swap, 1, 1024, fp_src);
    fwrite(swap, 1, j, fp_tgt);
  }
  fclose(fp_src);
  fclose(fp_tgt);

  printf("copy finished!\n");

  return 0;
}*/
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <wait.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <string.h>
union semun {
  int              val;    /* Value for SETVAL */
  struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
  unsigned short  *array;  /* Array for GETALL, SETALL */
  struct seminfo  *__buf;  /* Buffer for IPC_INFO
                              (Linux specific) */
}arg;
void P(int semid, int index) {//P操作
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op = -1;
	sem.sem_flg = 0; //操作标记：0或IPC_NOWAIT等
	semop(semid,&sem,1);	//1:表示执行命令的个数
	return;
}
void V(int semid, int index) {//V操作
	struct sembuf sem;
	sem.sem_num = index;
	sem.sem_op =  1;
	sem.sem_flg = 0;
	semop(semid,&sem,1);
	return;
}
FILE* fp1, *fp2;
char *shmaddr1,*shmaddr2;
int *cout1,*cout2;
int shmid,global_var;//共享内存
int flag_name_check;
char src_name[255], tgt_name[255];//source file name and target file name
int S;//信号灯
int Sv;//全局变量的信号灯
pid_t readbuf, writebuf;
void par_task(int shmid,int global_var,int S,int Sv) {
    waitpid(readbuf, NULL, 0);
    waitpid(writebuf, NULL, 0);
    semctl(S, 0, IPC_RMID, arg);
    semctl(S, 1, IPC_RMID, arg);
    semctl(Sv,0,IPC_RMID,arg);
    shmctl(shmid, IPC_RMID, NULL);
    shmctl(global_var,IPC_RMID,NULL);
}
void read_task(){
    shmaddr1 = shmat(shmid, NULL, 0);//连接共享内存
    cout1 = shmat(global_var,NULL,0);
    P(Sv,0);
    *cout1 = 0;
    *(cout1+8)=64;//最后一次从文件读到的内存大小，初始值设为64
    V(Sv,0);
    fp1 = fopen (src_name,"r");
    if (fp1!=NULL)
    {
        int i = 0,j=64;
        while (j==64) {
            P(S,0);//空个数
            j = fread(shmaddr1+i,1,64,fp1);
            V(S,1);//满个数
            if (j!=64) {
                P(Sv,0);
                *(cout1+8)=j;//最后一次从文件读到的内存大小
                V(Sv,0);
                break;
            }
            i+=64;
            i=i%1024;
            P(Sv,0);
            (*cout1)++;
            V(Sv,0);
        }
        fclose (fp1);
    }
    shmdt(shmaddr1);//断开共享内存
    shmdt(cout1);
}
void write_task(){
    shmaddr2 = shmat(shmid, NULL, SHM_RDONLY);//连接共享内存
    cout2 = shmat(global_var,NULL,0);//全局变量地址
    P(Sv,0);
    *(cout2+8)=64;
    V(Sv,0);
    fp2 = fopen(tgt_name,"w");
    if (fp2!=NULL) {
        int i = 0,count2=0,j=64,count0;
        while (j==64||count2<count0) {//只有上一次写到缓冲区的内存个数不足64并且写到文件的次数不小于从文件读取的次数时才是最后一次写操作
            P(S,1);
            fwrite(shmaddr2+i,1,64,fp2);
            V(S,0);
            i=i+64;
            i=i%1024;
            count2++;
            P(Sv,0);
            j=*(cout2+8);//上一次从文件读到的内存个数
            count0=*cout2;//已经从文件读到缓冲区的次数
            V(Sv,0);
        }
        fwrite(shmaddr2+i,1,*(cout2+8),fp2);//最后一次写操作，读到缓冲区几个内存大小就写到文件几个内存大小
        fclose(fp2);
    }
    shmdt(shmaddr2);
    shmdt(cout2);
    printf("cpoy finished!\n");
}

int main() {
    do {
      printf("please input the source file name:\n");
      scanf("%s", src_name);
      getchar();
      printf("please input the target file name\n", tgt_name);
      scanf("%s", tgt_name);
      getchar();
      flag_name_check = !strcmp(src_name, tgt_name);
      if (flag_name_check) {
        printf("Error! your source flie and target file have the same name.\n");
      }
    } while(flag_name_check);
    shmid = shmget(IPC_PRIVATE,1024,IPC_CREAT|IPC_EXCL|0660);//创建共享内存
    global_var = shmget(IPC_PRIVATE,256,IPC_CREAT|IPC_EXCL|0660);//全局变量
    if (shmid == -1) {
        perror("shmget()");
    }
    S = semget(IPC_PRIVATE, 2, IPC_CREAT|0666);
    if (S<0) {
        perror("semget()");
        return -1;
    }
    arg.val = 16;//设置信号灯
    semctl(S, 0, SETVAL, arg);
    arg.val = 0;
    semctl(S, 1, SETVAL, arg);
    Sv = semget(IPC_PRIVATE, 1, IPC_CREAT|0666);//全局变量的信号灯
    if (Sv<0) {
        perror("semget()");
        return -1;
    }
    arg.val = 1;//设置信号灯
    semctl(Sv, 0, SETVAL, arg);
    while ((readbuf = fork()) == -1);
    if (readbuf) {//不在readbuf进程
        while ((writebuf = fork()) == -1);
        if(writebuf){//在父进程
            par_task(shmid,global_var,S,Sv);
        }
        if(!writebuf) {//在writebuf进程
            write_task();
        }
    }
    if(!readbuf) {
        read_task();
    }
}
