#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
  while(1){
    printf("mush:>");
    char prompt[2048];
    fgets(prompt, sizeof prompt, stdin);
    prompt[strlen(prompt) - 1] = '\0'; //strip newline
    char *token = strtok(prompt, " ");
    char *tokens[128];
    int current_token = 0;
    while(token != NULL){
      //printf("%s\n", token);

      tokens[current_token] = malloc(128 * sizeof(char));
      strcpy(tokens[current_token], token);
      //tokens[current_token] = &token;
      current_token++;
      token = strtok(NULL, " ");

    }
    tokens[current_token] = NULL;

    if(strcmp(tokens[0], "cd") == 0){
      int res = chdir(tokens[1]);
      switch(res){
        case -1:
          perror("cd");
          break;
        default:
          break;
      }
    }else if(strcmp(tokens[0], "exit") == 0){
      exit(0);
    }else{
      pid_t pid = fork();
      switch(pid){
        case -1:
          perror("fork");
          exit(1);
          break;
        case 0:
          execvp(tokens[0], tokens);
          exit(1);
          break;
        default:
          wait(NULL);
          break;
      }
    }
  }
}
