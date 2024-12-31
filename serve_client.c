#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

pthread_rwlock_t lock = PTHREAD_RWLOCK_INITIALIZER; 

void *downtime() {
    for(int i = 0; i < 3; i++){
        pthread_rwlock_wrlock(&lock);
        sleep(2); 
        Node* oldRoot = root;
        root = balanceTree(root);
        if(oldRoot!= root){
            freeSubtree(oldRoot); 
        }
        pthread_rwlock_unlock(&lock);
    }
    return NULL; 
}



void *ServeClient(char *client) {

    int a = 0; //Will get the string "clientN"
    // char clientName[8];
    char* clientName = calloc(1, sizeof(char)*8);

    while (client[a] != '_'){
        clientName[a] = client[a];
        a++;
    }

    FILE* rP; 
    rP = fopen(client, "r");
    char* command = calloc(1, sizeof(char)*20);
    // char* command = NULL; 
    int value = 0; 
    int count = 0; 
    float avg = 0; 

    fscanf(rP, "%s %d", command, &value);
    
    
    while (!feof(rP)){

        if (strcmp(command, "addNode") == 0){

            pthread_rwlock_wrlock(&lock);
            root = addNode(root, value); 
            printf("%sinsertNode %d\n", clientName, value);
            pthread_rwlock_unlock(&lock);

        } else if (strcmp(command, "removeNode") == 0){

            pthread_rwlock_wrlock(&lock);
            root = removeNode(root, value); 
            printf("%sdeleteNode %d\n", clientName, value);
            pthread_rwlock_unlock(&lock);


        } else if (strcmp(command, "avgSubtree") == 0){

            pthread_rwlock_rdlock(&lock);
            avg = avgSubtree(root);
            printf("%savgSubtree = %f\n", clientName, avg);
            pthread_rwlock_unlock(&lock);

        } else if (strcmp(command, "countNodes") == 0){

            pthread_rwlock_rdlock(&lock);
            count = countNodes(root);
            countNodes(root);
            printf("%scountNodes = %d\n", clientName, count);
            pthread_rwlock_unlock(&lock);
            
        }

        fscanf(rP, "%s %d", command, &value);

    }

    free(command);
    free(clientName); 
    fclose(rP);
    return NULL; 

}
