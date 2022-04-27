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
#include <stdint.h>

//funkcija za preverjanje ali je file ali folder
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
    uint32_t dolzinaImena = strlen(datoteka) + 1;

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
        printf("SPODLETEL\tNI NAJDENO\t%s\t-\n", datoteka);
    }

    char podatki[velikostZbirke];

    if(velikostZbirke != 0){
        FILE *fp;
        char *buffer;

        fp = fopen ( datoteka , "rb" );
        if( !fp ) perror(datoteka),exit(1);

        buffer = calloc( 1, velikostZbirke+1 );
        if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

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


    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        exit(1);
    }

    their_addr.sin_family = AF_INET; 
	their_addr.sin_port = htons(atoi(argv[2])); 
 	their_addr.sin_addr = *((struct in_addr *)he->h_addr);
	memset(&(their_addr.sin_zero), '\0', 8);
	
	if (connect(sockfd, (struct sockaddr *)&their_addr, sizeof(struct sockaddr)) == -1) {
		//perror("connect");

        if(metapodatki == 2147483648){
            printf("SPODLETEL\tZBIRKA\t%s\t%d\n", datoteka, velikostZbirke);
        }
        else if(metapodatki == 1073741824){
            printf("SPODLETEL\tIMENIK\t%s\t%d\n", datoteka, velikostZbirke);
        }

        exit(1);
	}

    int velikost = 4 * sizeof(uint32_t) + velikostZbirke + dolzinaImena;
    char struktura[velikost];

    *(uint32_t *)&struktura[0] = metapodatki;
    *(uint32_t *)&struktura[4] = dolzinaImena;
    *(uint32_t *)&struktura[8] = velikostZbirke;
    *(uint32_t *)&struktura[12] = hash;
    
    for(int i = 0; i < dolzinaImena; i++){
        struktura[i + 16] = ime[i];
    }
    for(int i = 0; i < velikostZbirke; i++){
        struktura[i + 16 + dolzinaImena] = podatki[i];
    }

    int posiljanje = write(sockfd, struktura, velikost);

    if(posiljanje < 0){
        if(metapodatki == 2147483648){
            printf("SPODLETEL\tZBIRKA\t%s\t%d\n", datoteka, velikostZbirke);
        }
        else if(metapodatki == 1073741824){
            printf("SPODLETEL\tIMENIK\t%s\t%d\n", datoteka, velikostZbirke);
        }
    }
	
    close(sockfd);

    if(metapodatki == 2147483648){
        printf("USPEL\tZBIRKA\t%s\t%d\n", datoteka, velikostZbirke);
    }
    else if(metapodatki == 1073741824){
        printf("USPEL\tIMENIK\t%s\t%d\n", datoteka, velikostZbirke);
    }
}