#include <stdio.h>
#include <string.h>
#include <elf.h>
#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

//Izpis zaglavja
void printZaglavje(Elf32_Ehdr elfHead)
{
    printf("ELF Magic:\n");

    printf("MAGIC:\t");

    for (int j = 0; j < 16; j++)
    {
        printf(" %.2x", elfHead.e_ident[j]);
    }

    printf("\n");  

	printf("Class:\t\t\t\t\t ");
	switch(elfHead.e_ident[EI_CLASS])
	{
		case ELFCLASS32:
			printf("ELF32\n");
			break;

		case ELFCLASS64:
			printf("ELF64\n");
			break;

		default:
			printf("NAPAKA\n");
			break;
	}

	printf("Data:\t\t\t\t\t ");
	switch(elfHead.e_ident[EI_DATA])
	{
		case ELFDATA2LSB:
			printf("2's complement, little-endian\n");
			break;

		case ELFDATA2MSB:
			printf("2's complement, big-endian\n");
			break;

		default:
			printf("Napacen Format\n");
			break;
	}

	printf("Version:\t\t\t\t ");
	switch(elfHead.e_ident[EI_VERSION])
	{
		case EV_CURRENT:
			printf("1 (current)\n");
			break;

		default:
			printf("0 (invalid)\n");
			break;
	}

	
	printf("OS/ABI:\t\t\t\t\t ");
	switch(elfHead.e_ident[EI_OSABI])
	{
		case ELFOSABI_SYSV:
			printf("UNIX System V\n");
			break;

		case ELFOSABI_HPUX:
			printf("HP-UX\n");
			break;

		case ELFOSABI_NETBSD:
			printf("NetBSD\n");
			break;

		case ELFOSABI_LINUX:
			printf("Linux\n");
			break;

		case ELFOSABI_SOLARIS:
			printf("Solaris\n");
			break;

		case ELFOSABI_IRIX:
			printf("SGI Irix\n");
			break;

		case ELFOSABI_FREEBSD:
			printf("FreeBSD\n");
			break;

		case ELFOSABI_TRU64:
			printf("TRU64 UNIX\n");
			break;

		case ELFOSABI_ARM:
			printf("ARM\n");
			break;

		case ELFOSABI_STANDALONE:
			printf("Stand-alone (embedded)\n");
			break;

		default:
			printf("Same as ELFOSABI_SYSV");
			break;
	}

	printf("ABI Version:\t\t\t\t %d\n", elfHead.e_ident[EI_ABIVERSION]);

	printf("\n");


	printf("ELF Header\n");
	
	printf("Type: \t\t\t\t\t ");
	printf("0x%.4x ", elfHead.e_type);
	switch(elfHead.e_type)
	{
		case ET_NONE:
			printf("(N/A)\n");
			break;

		case ET_REL:
			printf("(Relocatable)\n");
			break;

		case ET_EXEC:
			printf("(Executable)\n");
			break;

		case ET_DYN:
			printf("(shared object)\n");
			break;
	}

	printf("Machine: \t\t\t\t ");
	printf("0x%.4x ", elfHead.e_machine);
	switch(elfHead.e_machine)
	{
		case EM_NONE:
			printf("(An unknown machine)\n");
			break;

		case EM_M32:
			printf("(AT&T WE 32100)\n");
			break;
			
		case EM_SPARC:
			printf("(Sun Microsystems SPARC)\n");
			break;
			
		case EM_68K:
			printf("(Motorola 68000)\n");
			break;
			
		case EM_88K:
			printf("(Motorola 88000)\n");
			break;

		case EM_860:
			printf("(INTEL 80860)\n");
			break;

		case EM_MIPS:
			printf("(MIPS RS3000 (big-endian only))\n");
			break;

		case EM_386:
			printf("(INTEL 80386)\n");
			break;

		case EM_ARM:
			printf("(Advanced RISC Machines)\n");
			break;
	}

	printf("Version: \t\t\t\t ");
	printf("0x%.4x ", elfHead.e_version);
	switch(elfHead.e_version)
	{
		case EV_CURRENT:
			printf("(current)\n");
			break;

		default:
			printf("(Invalid version)\n");
			break;
	}

	printf("Entry point address:\t\t\t 0x%.4x\n", elfHead.e_entry);

	printf("Start of program headers:\t\t 0x%.4x\n", elfHead.e_phoff);

	printf("Start of section headers:\t\t 0x%.4x\n", elfHead.e_shoff);
	
	printf("Flags:\t\t\t\t\t 0x%.4x\n", elfHead.e_flags);

	printf("Size of this header:\t\t\t 0x%.04x\n", elfHead.e_ehsize);

	printf("Size of program headers:\t\t 0x%.04x\n", elfHead.e_phentsize);

	printf("Number of program headers:\t\t 0x%.04x\n", elfHead.e_phnum);
	
	printf("Size of section headers:\t\t 0x%.04x\n", elfHead.e_shentsize);
	
	printf("Number of section headers:\t\t 0x%.04x\n", elfHead.e_shnum);

	printf("Section header string table index:\t 0x%.04x\n", elfHead.e_shstrndx);
	
}

//Ipiz sekcij
void printSekcije(int32_t fd, Elf32_Ehdr elfHead, Elf32_Shdr shTabela[]){
	char* shString = malloc(shTabela[elfHead.e_shstrndx].sh_size);

	assert(shString != NULL);
	assert(lseek(fd, (off_t)shTabela[elfHead.e_shstrndx].sh_offset, SEEK_SET) == (off_t)shTabela[elfHead.e_shstrndx].sh_offset);
	assert(read(fd, (void *)shString, shTabela[elfHead.e_shstrndx].sh_size) == shTabela[elfHead.e_shstrndx].sh_size);

	printf("Sekcije\n");
	printf("     Ime                Tip             Naslov          Odmik   Velikost\n");

	for(int i = 0; i < elfHead.e_shnum; i++) {
		printf(" %02d ", i);
		printf("%-20s", (shString + shTabela[i].sh_name));

		switch (shTabela[i].sh_type)
		{
		case SHT_PROGBITS:
			printf("PROGBITS        ");
			break;

		case SHT_SYMTAB:
			printf("SYMTAB          ");
			break;

		case SHT_STRTAB:
			printf("STRTAB          ");
			break;

		case SHT_RELA:
			printf("RELA            ");
			break;

		case SHT_HASH:
			printf("HASH            ");
			break;

		case SHT_DYNAMIC:
			printf("DYNAMIC         ");
			break;

		case SHT_NOTE:
			printf("NOTE            ");
			break;

		case SHT_NOBITS:
			printf("NOBITS          ");
			break;

		case SHT_REL:
			printf("REL             ");
			break;

		case SHT_SHLIB:
			printf("SHLIB           ");
			break;

		case SHT_DYNSYM:
			printf("DYNSYM          ");
			break;

		case SHT_LOPROC:
			printf("LOPROC          ");
			break;

		case SHT_HIPROC:
			printf("HIPROC          ");
			break;

		case SHT_LOUSER:
			printf("LOUSER          ");
			break;

		case SHT_HIUSER:
			printf("HIUSER          ");
			break;
		
		default:
			printf("NULL            ");
			break;
		}

		printf("%08x\t", shTabela[i].sh_addr);
		printf("%06x\t", shTabela[i].sh_offset);
		printf("%06x\n", shTabela[i].sh_size);
	}

	free(shString);
}

//Izpis tabele simbolov
void printTabelaSimbolov(int32_t fd, Elf32_Shdr shTabela[], uint32_t idSimbolneTabele)
{
	char* buffer = malloc(shTabela[idSimbolneTabele].sh_size);

	assert(buffer != NULL);
	assert(lseek(fd, (off_t)shTabela[idSimbolneTabele].sh_offset, SEEK_SET) == (off_t)shTabela[idSimbolneTabele].sh_offset);
	assert(read(fd, (void *)buffer, shTabela[idSimbolneTabele].sh_size) == shTabela[idSimbolneTabele].sh_size);

	Elf32_Sym* simbolnaTabela = (Elf32_Sym*)buffer;

	uint32_t stringTabeleNdx = shTabela[idSimbolneTabele].sh_link;

	char* stringTabela = malloc(shTabela[stringTabeleNdx].sh_size);

	assert(stringTabela != NULL);
	assert(lseek(fd, (off_t)shTabela[stringTabeleNdx].sh_offset, SEEK_SET) == (off_t)shTabela[stringTabeleNdx].sh_offset);
	assert(read(fd, (void *)stringTabela, shTabela[stringTabeleNdx].sh_size) == shTabela[stringTabeleNdx].sh_size);


	printf("     Vrednost   Velikost  Ime\n");
	for(int i = 0; i < (shTabela[idSimbolneTabele].sh_size / sizeof(Elf32_Sym)); i++) {
		printf("%.3d: ", i);
		printf("%.8x\t", simbolnaTabela[i].st_value);
		printf("%.4x\t", simbolnaTabela[i].st_size);
		printf("%s\n", (stringTabela + simbolnaTabela[i].st_name));
	}

	free(stringTabela);
	free(buffer);
}

void printIzbranoSekcijo(int32_t fd, Elf32_Ehdr elfHead, Elf32_Shdr shTabela[], char* imeSekcije){
	char* shString = malloc(shTabela[elfHead.e_shstrndx].sh_size);

	assert(shString != NULL);
	assert(lseek(fd, (off_t)shTabela[elfHead.e_shstrndx].sh_offset, SEEK_SET) == (off_t)shTabela[elfHead.e_shstrndx].sh_offset);
	assert(read(fd, (void *)shString, shTabela[elfHead.e_shstrndx].sh_size) == shTabela[elfHead.e_shstrndx].sh_size);

	for(int i = 0; i < elfHead.e_shnum; i++) {
		if(strcmp((shString + shTabela[i].sh_name), imeSekcije) == 0){
			printf("Vsebina %s\n", imeSekcije);
			
			char* vsebina = malloc(16);

			for (int j = 0; j < shTabela[i].sh_size; j += 16)
			{
				assert(vsebina != NULL);
				assert(lseek(fd, (off_t)shTabela[i].sh_offset + j, SEEK_SET) == (off_t)shTabela[i].sh_offset + j);
				assert(read(fd, (void *)vsebina, 16) == 16);

				printf("%04x\t", shTabela[i].sh_addr + j);

				printf("%s\n", vsebina);
			}

			free(vsebina);
		}
	}
	
	free(shString);
}

int main(int argc, char *argv[]){

    int fd;
    Elf32_Ehdr eh;

    char* ime;

    for (int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "-h") == 0){

            ime = argv[i + 1];
            
            fd = open(ime , O_RDONLY|O_SYNC);

			assert(&eh != NULL);
			assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
			assert(read(fd, (void *)&eh, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));

            printZaglavje(eh);

			i++;

			close(fd);
        }

		if(strcmp(argv[i], "-S") == 0){
			ime = argv[i + 1];
            
            fd = open(ime , O_RDONLY|O_SYNC);

			assert(&eh != NULL);
			assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
			assert(read(fd, (void *)&eh, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));

			Elf32_Shdr* shTabela;

			shTabela = malloc(eh.e_shentsize * eh.e_shnum);


			assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

			for(int j = 0; j < eh.e_shnum; j++) {
				assert(read(fd, (void *)&shTabela[j], eh.e_shentsize) == eh.e_shentsize);
			}

			printSekcije(fd, eh, shTabela);

			i++;

			free(shTabela);
			close(fd);
		}

		if(strcmp(argv[i], "-s") == 0){
			ime = argv[i + 1];
            
            fd = open(ime , O_RDONLY|O_SYNC);

			assert(&eh != NULL);
			assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
			assert(read(fd, (void *)&eh, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));

			Elf32_Shdr* shTabela = malloc(eh.e_shentsize * eh.e_shnum);

			assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

			for(int j = 0; j < eh.e_shnum; j++) {
				assert(read(fd, (void *)&shTabela[j], eh.e_shentsize) == eh.e_shentsize);
			}

			printf("Simboli\n");

			for(int j = 0; j < eh.e_shnum; j++) {
				if (shTabela[j].sh_type==SHT_SYMTAB) {
					printTabelaSimbolov(fd, shTabela, j);
				}
			}

			free(shTabela);
			
			i++;
		}
    
		if(strcmp(argv[i], "-d") == 0){
			char* izbranaSekcija = argv[i + 1];
			
			ime = argv[i + 2];

			fd = open(ime , O_RDONLY|O_SYNC);

			assert(&eh != NULL);
			assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
			assert(read(fd, (void *)&eh, sizeof(Elf32_Ehdr)) == sizeof(Elf32_Ehdr));
			

			
			Elf32_Shdr* shTabela;

			shTabela = malloc(eh.e_shentsize * eh.e_shnum);


			assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

			for(int j = 0; j < eh.e_shnum; j++) {
				assert(read(fd, (void *)&shTabela[j], eh.e_shentsize) == eh.e_shentsize);
			}

			printIzbranoSekcijo(fd, eh, shTabela, izbranaSekcija);

			i++;

			free(shTabela);
			close(fd);

		}
	}
    
    return 0;
}