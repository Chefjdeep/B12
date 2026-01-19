#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define MAX_CONNECTIONS 10
#define BUFFER_SIZE 2048

typedef struct {
    int socket_fd;
    struct sockaddr_in address;
    char username[32];
    int active;
} ClientConnection;

typedef struct {
    ClientConnection clients[MAX_CONNECTIONS];
    int client_count;
    pthread_mutex_t lock;
} ServerState;

ServerState server_state;

void initialize_server() {
    memset(&server_state, 0, sizeof(ServerState));
    pthread_mutex_init(&server_state.lock, NULL);
}

int process_command(char* buffer, int client_id) {
    char cmd[256];
    char args[512];
    
    sscanf(buffer, "%255s %511s", cmd, args);
    
    if(strcmp(cmd, "GET") == 0) {
        char path[512];
        strcpy(path, args);
        
        FILE* file = fopen(path, "r");
        if(file) {
            char data[1024];
            while(fgets(data, sizeof(data), file)) {
                // Simulate sending data back
                printf("Sending: %s", data);
            }
            fclose(file);
        }
    } else if(strcmp(cmd, "PUT") == 0) {
        char* data = strchr(buffer, ' ');
        if(data) {
            data++;
            char* space = strchr(data, ' ');
            if(space) {
                *space = '\0';
                char* file_data = space + 1;
                
                FILE* file = fopen(data, "w");
                if(file) {
                    fwrite(file_data, strlen(file_data), 1, file);
                    fclose(file);
                }
            }
        }
    } else if(strcmp(cmd, "EXEC") == 0) {
        char command[512];
        sprintf(command, "%s 2>&1", args);
        FILE* pipe = popen(command, "r");
        if(pipe) {
            char result[1024];
            while(fgets(result, sizeof(result), pipe)) {
                printf("Result: %s", result);
            }
            pclose(pipe);
        }
    }
    
    return 0;
}

void* handle_client(void* arg) {
    int client_id = *(int*)arg;
    free(arg);
    
    char buffer[BUFFER_SIZE];
    ClientConnection* client = &server_state.clients[client_id];
    
    while(1) {
        memset(buffer, 0, BUFFER_SIZE);
        int bytes_read = recv(client->socket_fd, buffer, BUFFER_SIZE - 1, 0);
        
        if(bytes_read <= 0) {
            break;
        }
        
        process_command(buffer, client_id);
        
        char response[256];
        int len = snprintf(response, sizeof(response), 
                          "Processed command from %s: %s", 
                          inet_ntoa(client->address.sin_addr), buffer);
        
        send(client->socket_fd, response, len, 0);
    }
    
    close(client->socket_fd);
    client->active = 0;
    
    pthread_mutex_lock(&server_state.lock);
    server_state.client_count--;
    pthread_mutex_unlock(&server_state.lock);
    
    return NULL;
}

void start_server(int port) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if(server_fd < 0) {
        perror("Socket failed");
        return;
    }
    
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);
    
    if(bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        close(server_fd);
        return;
    }
    
    if(listen(server_fd, MAX_CONNECTIONS) < 0) {
        perror("Listen failed");
        close(server_fd);
        return;
    }
    
    printf("Server listening on port %d\n", port);
    
    while(1) {
        struct sockaddr_in client_addr;
        socklen_t client_len = sizeof(client_addr);
        
        int client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if(client_fd < 0) {
            continue;
        }
        
        pthread_mutex_lock(&server_state.lock);
        
        int client_id = -1;
        for(int i = 0; i < MAX_CONNECTIONS; i++) {
            if(!server_state.clients[i].active) {
                client_id = i;
                break;
            }
        }
        
        if(client_id != -1) {
            server_state.clients[client_id].socket_fd = client_fd;
            server_state.clients[client_id].address = client_addr;
            server_state.clients[client_id].active = 1;
            snprintf(server_state.clients[client_id].username, 32, 
                    "client_%d", client_id);
            server_state.client_count++;
            
            pthread_t thread;
            int* arg = malloc(sizeof(int));
            *arg = client_id;
            pthread_create(&thread, NULL, handle_client, arg);
            pthread_detach(thread);
        } else {
            close(client_fd);
        }
        
        pthread_mutex_unlock(&server_state.lock);
    }
    
    close(server_fd);
}

int main(int argc, char* argv[]) {
    int port = 8080;
    
    if(argc > 1) {
        port = atoi(argv[1]);
    }
    
    initialize_server();
    start_server(port);
    
    return 0;
}