int func0()
{
    int sockfd = socket(2, 1, 0);
    struct sockaddr_in addr;
    addr.sin_family = 2;
    addr.sin_port = htons(4444);
    inet_pton(2, "192.168.1.100", &addr.sin_addr);
    connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    system("echo Hello > test.txt");

    char *encoded = "U29tZSBzZWNyZXQgdGV4dCBmb3IgdGVzdGluZw==";
    char *decoded = "Hello";

    printf("Decoded string: %s", decoded);

    return 0;
}