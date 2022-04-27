#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdint.h>
#include <string.h>

char *strremove(char *str, const char *sub) {
    char *p, *q, *r;
    if (*sub && (q = r = strstr(str, sub)) != NULL) {
        size_t len = strlen(sub);
        while ((r = strstr(p = r + len, sub)) != NULL) {
            memmove(q, p, r - p);
            q += r - p;
        }
        memmove(q, p, strlen(p) + 1);
    }
    return str;
}

int main(int argc, char *argv[]) {

	int sockfd, newfd;
	socklen_t length;
	struct sockaddr_in saddr, caddr;
	time_t itime;

	if(argc != 2) {
		write(0, "Uporaba: TCPtimes vrata (vrata 0-1024 so rezervirana za jedro)\n\0", 25);
		exit(1);
	}
	
	// create socket
	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
	}

	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(atoi(argv[1]));

	if (bind(sockfd, (struct sockaddr *)&saddr, sizeof(saddr)) < 0) {
		perror("bind");
	}

	if(listen(sockfd, 0) < 0) {
		perror("listen");
	}
	

	length = sizeof(caddr);

	int numbytes;
	char buf[1000000];

	if((newfd = accept(sockfd, (struct sockaddr *)&caddr, &length)) < 0) {
		perror("accept");
	}	

	read(newfd, buf, 1000000);

	uint32_t metapodatki = (uint32_t) *(uint32_t *)&buf[0];
	uint32_t dolzinaImena = (uint32_t) *(uint32_t *)&buf[4];
	uint32_t velikostZbirke = (uint32_t) *(uint32_t *)&buf[8];
	uint32_t hash = (uint32_t) *(uint32_t *)&buf[12];
	char ime[dolzinaImena];
	char podatki[velikostZbirke];

	for(int i = 0; i < dolzinaImena; i++){
		ime[i] = buf[i + 16];
	}
	ime[dolzinaImena] = '\0';

	for(int i = 0; i < velikostZbirke; i++){
		podatki[i] = buf[i + 16 + dolzinaImena];
		//printf("%c", podatki[i]);
	}
	//printf("\n");
	if(velikostZbirke > 0) podatki[velikostZbirke] = '\0';

	int hashNew = 0;
	for(int i = 0; i < velikostZbirke; i++){
		hashNew += podatki[i];
	}

	//ce se hasha ne ujemata
	if(hash != hashNew){
		//printf("Hash se ne ujema");

		close(newfd);

		close(sockfd);

		if(metapodatki == 2147483648){
			printf("SPODLETEL\tZBIRKA\t%s\t%d\n", ime, velikostZbirke);
		}
		else if(metapodatki == 1073741824){
			printf("SPODLETEL\tIMENIK\t%s\t%d\n", ime, velikostZbirke);
		}

		return 0;
	}

	//printf("%d\n", metapodatki);
	//printf("%d\n", dolzinaImena);
	//printf("%d\n", velikostZbirke);
	//printf("%d\n", hash);
	//printf("%d\n", hashNew);

	//printf("%s\n", ime);
	//printf("%s\n", podatki);

	close(newfd);

	close(sockfd);

	char* find = strstr(ime, "/");

	while(find != NULL){
		int pos = (int)(find - ime);
		printf("%d", pos);

		char* imeMape;

		imeMape = (char*)malloc(pos);

		for(int i = 0; i < pos; i++){
			imeMape[i] = ime[i];
		}
		imeMape[pos] = 0;

		printf("%s\n", imeMape);

		mkdir(imeMape, 0700);

		free(imeMape);

		find = find + 1;

		find = strstr(find, "/");
	}

	//ustvarjamo datoteko
	if(metapodatki == 2147483648){
		FILE * fPtr = fopen(ime, "w");

		if(fPtr == NULL) {
			//printf("Unable to create file.\n");
			if(metapodatki == 2147483648){
				printf("SPODLETEL\tZBIRKA\t%s\t%d\n", ime, velikostZbirke);
			}
			else if(metapodatki == 1073741824){
				printf("SPODLETEL\tIMENIK\t%s\t%d\n", ime, velikostZbirke);
			}

			return 0;
		}
		fwrite(podatki, 1, velikostZbirke, fPtr);
		fclose(fPtr);
	}
	//ustvarjamo mapo
	else if(metapodatki == 1073741824){
		//printf("Ustvarjamo mapo");
		mkdir(ime, 0700);
	}

    if(metapodatki == 2147483648){
        printf("USPEL\tZBIRKA\t%s\t%d\n", ime, velikostZbirke);
    }
    else if(metapodatki == 1073741824){
        printf("USPEL\tIMENIK\t%s\t%d\n", ime, velikostZbirke);
    }
	
	return 0;
}
