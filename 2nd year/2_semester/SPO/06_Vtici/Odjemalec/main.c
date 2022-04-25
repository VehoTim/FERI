#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/stat.h> //primerjava ali je file
#include <netinet/in.h>
#include <sys/socket.h>
#include <errno.h>

int is_regular_file(const char *path)
{
    struct stat path_stat;
    stat(path, &path_stat);
    return S_ISREG(path_stat.st_mode);
}

int main(int argc, char *argv[]) {
    char* naslov = argv[1];
    char* port = argv[2];
    char* datoteka = argv[3];

    uint32_t metapodatki;
    uint32_t dolzinaImena = sizeof(datoteka) + 1;

    //printf("%d\n", dolzinaImena);

    uint32_t velikostZbirke;
    uint32_t hash = 0;

    if( access( datoteka, F_OK ) == 0 ) {
        if(is_regular_file(datoteka) == 1){
            metapodatki = 2147483648;

            struct stat st;
            stat(datoteka, &st);
            velikostZbirke = st.st_size;
        }
        else{
            metapodatki = 1073741824;

            velikostZbirke = 0;
        }
    } else {
        printf("File ni najden");
    }

    char podatki[velikostZbirke];

    if(velikostZbirke != 0){
        FILE *fp;
        char *buffer;

        fp = fopen ( datoteka , "rb" );
        if( !fp ) perror(datoteka),exit(1);

        /* allocate memory for entire content */
        buffer = calloc( 1, velikostZbirke+1 );
        if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

        /* copy the file into the buffer */
        if( 1!=fread( buffer , velikostZbirke, 1 , fp) )
        fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);

        
        for(int i = 0; i < velikostZbirke; i++){
            hash += buffer[i];
            podatki[i] = buffer[i];
        }

        fclose(fp);
        free(buffer);
    }

    




    char ime[dolzinaImena];
    for(int i = 0; i < dolzinaImena; i++){
        ime[i] = datoteka[i];
        if(i == dolzinaImena - 1){
            ime[i + 1] = '\0';
        }
    }

    

    //printf("%d", hash);

    int sockfd;
    struct hostent *he;
    struct sockaddr_in their_addr;

    if (argc != 4) {
		write(0,"Podaj parametre\n\0", 17);
		exit(1);
	}

    if ((he = gethostbyname(argv[1])) == NULL) {
		exit(1);		  
	}


    if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
        exit(1);
    }

    their_addr.sin_family = AF_INET; 
	their_addr.sin_port = htons(atoi(argv[2])); 
 	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), '\0', 8);
	
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		perror("connect");
        exit(1);
	}

    int velikost = 4 * sizeof(uint32_t) + velikostZbirke + dolzinaImena;
    char struktura[velikost];

    struktura[0] = metapodatki;
    struktura[4] = dolzinaImena;
    struktura[8] = velikostZbirke;
    struktura[12] = hash;
    
    for(int i = 0; i < dolzinaImena; i++){
        struktura[i + 16] = ime[i];
    }
    for(int i = 0; i < velikostZbirke; i++){
        struktura[i + 16 + dolzinaImena] = podatki[i];
    }

    int sent = 0;

    //posiljanje
    if(sent = send(sockfd, struktura, velikost, 0) < 0) {
        perror("send");
    }
    else printf("%d", sent);

	
    close(sockfd);
}