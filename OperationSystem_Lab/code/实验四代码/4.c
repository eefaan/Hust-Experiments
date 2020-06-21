#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
// lstat here
#include <sys/stat.h>
// opendir here
#include <sys/types.h>
#include <dirent.h>
// time here
#include <time.h>
// get uid's name
#include <pwd.h>

int printDir(char *dir, int depth){
    DIR *dp;
    struct dirent *entry;
    struct stat statbuf;

    // open the dir
    dp=opendir(dir);
    if(dp==NULL){
        printf("opendir error\n");
        return -1;
    }

    // change currently working dir to *dir
    chdir(dir);
    while(1){
        entry=readdir(dp);
        if(entry==NULL)break;
        if(lstat(entry->d_name, &statbuf)==-1){
            printf("lstat error\n");
            return -1;
        }
        if (S_ISDIR(statbuf.st_mode)){// read a dir
            // do nothing if dir's name is '.' or ".."
            if(strcmp(entry->d_name,".")==0 || strcmp(entry->d_name,"..")==0);
            else{
                // type
                printf("d");
                // access
                if (S_IRUSR&statbuf.st_mode) printf("r");
                else printf("-");
                if (S_IWUSR&statbuf.st_mode) printf("w");
                else printf("-");
                if (S_IXUSR&statbuf.st_mode) printf("x");
                else printf("-");
                if (S_IRGRP&statbuf.st_mode) printf("r");
                else printf("-");
                if (S_IWGRP&statbuf.st_mode) printf("w");
                else printf("-");
                if (S_IXGRP&statbuf.st_mode) printf("x");
                else printf("-");
                if (S_IROTH&statbuf.st_mode) printf("r");
                else printf("-");
                if (S_IWOTH&statbuf.st_mode) printf("w");
                else printf("-");
                if (S_IXOTH&statbuf.st_mode) printf("x");
                else printf("-");

                struct passwd *pwd;
                // depth, name, size(bytes)
                printf("\t%-4d  %-25s    %-12ld", depth+1, entry->d_name, statbuf.st_size);
                // time
                printf("\t%s",strtok(ctime(&statbuf.st_mtime),"\n"));
                // uid, gid -> name
                pwd = getpwuid(statbuf.st_uid);
                printf("\t%s",pwd->pw_name);
                pwd = getpwuid(statbuf.st_gid);
                printf("\t%s",pwd->pw_name);

                printf("\n");

                // into next direct
                printDir(entry->d_name, depth+1);
            }
        }
        else{// normal file
            // type
            printf("-");
            // access
            if (S_IRUSR&statbuf.st_mode) printf("r");
            else printf("-");
            if (S_IWUSR&statbuf.st_mode) printf("w");
            else printf("-");
            if (S_IXUSR&statbuf.st_mode) printf("x");
            else printf("-");
            if (S_IRGRP&statbuf.st_mode) printf("r");
            else printf("-");
            if (S_IWGRP&statbuf.st_mode) printf("w");
            else printf("-");
            if (S_IXGRP&statbuf.st_mode) printf("x");
            else printf("-");
            if (S_IROTH&statbuf.st_mode) printf("r");
            else printf("-");
            if (S_IWOTH&statbuf.st_mode) printf("w");
            else printf("-");
            if (S_IXOTH&statbuf.st_mode) printf("x");
            else printf("-");

            struct passwd *pwd;
            // depth, name, size(bytes)
            printf("\t%-4d  %-25s    %-12ld", depth+1, entry->d_name, statbuf.st_size);
            // time
            printf("\t%s",strtok(ctime(&statbuf.st_mtime),"\n"));
            // uid, gid -> name
            pwd = getpwuid(statbuf.st_uid);
            printf("\t%s",pwd->pw_name);
            pwd = getpwuid(statbuf.st_gid);
            printf("\t%s",pwd->pw_name);

            printf("\n");
        }
    }
    // read dir done
    chdir("..");
    closedir(dp);
    return 0;
}

int main(void){
    char dir_name[100];
    int depth=0;
    printf("input directory name please:\n");
    scanf("%s", dir_name);
    // table name
    printf("\ntype\t\tlayer name\t\t\t   size(bytes)  last modification\t\tuserID \t\tgroupID\n");
    printDir(dir_name, depth);
    return 0;
}
