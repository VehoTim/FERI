USE baza1002470617;

#Brisanje tabel
DROP TABLE IF EXISTS Dogodek;
DROP TABLE IF EXISTS VrstaDogodka;
DROP TABLE IF EXISTS IgralecNaTekmi;
DROP TABLE IF EXISTS IgralecPolozaj;
DROP TABLE IF EXISTS PogodbaIgralca;
DROP TABLE IF EXISTS Polozaj;
DROP TABLE IF EXISTS Igralec;
DROP TABLE IF EXISTS Tekma;
DROP TABLE IF EXISTS KlubVSezoni;
DROP TABLE IF EXISTS Sezona;
DROP TABLE IF EXISTS PogodbaOsebja;
DROP TABLE IF EXISTS Klub;
DROP TABLE IF EXISTS Osebje;
DROP TABLE IF EXISTS ZaposlitevOsebe;
DROP TABLE IF EXISTS NogometnoIgrisce;
DROP TABLE IF EXISTS Naslov;
DROP TABLE IF EXISTS Kraj;

#UStvarjanje tabel in dodajanje tujih kljucev

CREATE TABLE Kraj(
	posta char(4) not null  primary key,
    kraj varchar(50) not null
);

CREATE TABLE Naslov(
	idNaslov int not null auto_increment primary key,
    ulica varchar(50) not null,
    stevilka int not null
);

CREATE TABLE NogometnoIgrisce(
	idNogometnoIgrisce int not null auto_increment primary key,
    imeIgrisca varchar(50) not null,
    fk_kraj char(4) not null,
    fk_naslov int not null
);

ALTER TABLE NogometnoIgrisce ADD CONSTRAINT fk_igrisce_kraj FOREIGN KEY (fk_kraj) REFERENCES Kraj (posta) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE NogometnoIgrisce ADD CONSTRAINT fk_igrisce_naslov FOREIGN KEY (fk_naslov) REFERENCES Naslov (idNaslov) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE ZaposlitevOsebe(
	idZaposlitevOsebe int not null auto_increment primary key,
    nazivZaposlitve varchar(45) not null
);

CREATE TABLE Osebje(
	idOsebe int not null auto_increment primary key,
    Ime varchar(30) not null,
    Priimek varchar(45) not null,
    datRojstva DATE not null,
    fk_posta char(4) not null
);

ALTER TABLE Osebje ADD CONSTRAINT fk_oseba_posta FOREIGN KEY (fk_posta) REFERENCES kraj (posta) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE Klub(
	idKlub int not null auto_increment primary key,
    kratica char(3) not null,
    naziv varchar(20)
);

CREATE TABLE PogodbaOsebja(
	idPogodbaOsebha int not null auto_increment primary key,
    fk_klub int not null,
    datPridruzitve datetime not null,
    datZapustitve datetime,
    placa decimal(10,2) not null,
    fk_oseba int not null
);

ALTER TABLE PogodbaOsebja ADD CONSTRAINT fk_pogodbaOsebja_klub FOREIGN KEY (fk_klub) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE PogodbaOsebja ADD CONSTRAINT fk_pogodbaOsebja_oseba FOREIGN KEY (fk_oseba) REFERENCES Osebje (idOsebe) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE Sezona(
	idSezona int not null auto_increment primary key,
    zacSezone date not null,
    konSezone date
);

CREATE TABLE KlubVSezoni(
	idKlubaVSezoni int not null auto_increment primary key,
    fk_klub int not null,
    fk_sezona int not null,
    stTock int
);

ALTER TABLE KlubVSezoni ADD CONSTRAINT fk_klubVSezoni_klub FOREIGN KEY (fk_klub) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE KlubVSezoni ADD CONSTRAINT fk_klubVSezoni_sezona FOREIGN KEY (fk_sezona) REFERENCES Sezona (idSezona) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE Tekma(
	idTekme int not null auto_increment primary key,
    fk_klub1 int not null,
    fk_klub2 int not null,
    fk_sezona int not null,
    datum datetime not null,
    fk_nogIgrisce int not null
);

ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_klub1 FOREIGN KEY (fk_klub1) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_klub2 FOREIGN KEY (fk_klub2) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_sezona FOREIGN KEY (fk_sezona) REFERENCES Sezona (idSezona) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_nogIgrisce FOREIGN KEY (fk_nogIgrisce) REFERENCES NogometnoIgrisce (idNogometnoIgrisce) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE Igralec(
	idIgralec int not null auto_increment primary key,
    Ime varchar(30) not null,
    Priimek varchar(45) not null,
    datRojstva DATE not null,
    fk_kraj char(4) not null
);

ALTER TABLE Igralec ADD CONSTRAINT fk_igralec_kraj FOREIGN KEY (fk_kraj) REFERENCES Kraj (posta) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE Polozaj(
	idPolozaj int not null auto_increment primary key,
    naziv varchar(45) not null
);

CREATE TABLE PogodbaIgralca(
	idPogodbeIgralca int not null auto_increment primary key,
    fk_klub int not null,
    fk_igralec int not null,
    datPridruzitve date not null,
    datZapustitve date,
    placa decimal(10,2)
);

ALTER TABLE PogodbaIgralca ADD CONSTRAINT fk_pogodbaIgralca_klub FOREIGN KEY (fk_klub) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE PogodbaIgralca ADD CONSTRAINT fk_pogodbaIgralca_igralec FOREIGN KEY (fk_igralec) REFERENCES Igralec (idIgralec) ON DELETE CASCADE ON UPDATE NO ACTION;



CREATE TABLE IgralecPolozaj(
	idIgralecPolozaj int not null auto_increment primary key,
    fk_polozaj int not null,
    fk_pogodbaIgralec int not null,
    polozajOd datetime not null,
    polozajDo datetime
);

ALTER TABLE IgralecPolozaj ADD CONSTRAINT fk_igralecPolozaj_pogodba FOREIGN KEY (fk_pogodbaIgralec) REFERENCES PogodbaIgralca (idPogodbeIgralca) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE IgralecPolozaj ADD CONSTRAINT fk_igralecPolozaj_polozaj FOREIGN KEY (fk_polozaj) REFERENCES Polozaj (idPolozaj) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE IgralecNaTekmi(
	idIgralecNaTekmi int not null auto_increment primary key,
    fk_igralec int not null,
    fk_tekma int not null
);

ALTER TABLE IgralecNaTekmi ADD CONSTRAINT fk_igralecNaTekmi_igralec FOREIGN KEY (fk_igralec) REFERENCES Igralec (idIgralec) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE IgralecNaTekmi ADD CONSTRAINT fk_igralecNaTekmi_tekma FOREIGN KEY (fk_tekma) REFERENCES Tekma (idTekme) ON DELETE CASCADE ON UPDATE NO ACTION;

CREATE TABLE VrstaDogodka(
	idVrstaDogodka int not null auto_increment primary key,
    naziv varchar(45)
);

CREATE TABLE Dogodek(
	idDogodek int not null auto_increment primary key,
    cas decimal(4,2) not null,
    fk_tekma int not null,
    fk_igralec int not null,
    fk_vrstaDogodka int not null
);

ALTER TABLE Dogodek ADD CONSTRAINT fk_dogodek_tekma FOREIGN KEY (fk_tekma) REFERENCES Tekma (idTekme) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Dogodek ADD CONSTRAINT fk_dogodek_igralec FOREIGN KEY (fk_igralec) REFERENCES Igralec (idIgralec) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Dogodek ADD CONSTRAINT fk_dogodek_vrsta FOREIGN KEY (fk_vrstaDogodka) REFERENCES VrstaDogodka (idVrstaDogodka) ON DELETE CASCADE ON UPDATE NO ACTION;

#INSERTS
INSERT INTO Kraj VALUES('1000','Ljubljana');
INSERT INTO Kraj VALUES('2000','Maribor');
INSERT INTO Kraj VALUES('3000','Celje');
INSERT INTO Kraj VALUES('3252','Rogatec');
INSERT INTO Kraj VALUES('3250','Rogaska Slatina');

INSERT INTO Naslov(ulica, stevilka) VALUES('Mladinska ulica', 29);
INSERT INTO Naslov(ulica, stevilka) VALUES('Vojkova cesta', 100);
INSERT INTO Naslov(ulica, stevilka) VALUES('Log', FLOOR(RAND() * 100));
INSERT INTO Naslov(ulica, stevilka) VALUES('Ceste', 67);
INSERT INTO Naslov(ulica, stevilka) VALUES('Tu bo pa malce daljse ime ulice', FLOOR(RAND() * 100));
INSERT INTO Naslov(ulica, stevilka) VALUES('Mladinska ulica', 17);
INSERT INTO Naslov(ulica, stevilka) VALUES('Vojkova cesta', 80);
INSERT INTO Naslov(ulica, stevilka) VALUES('Logarska cesta', FLOOR(RAND() * 100));
INSERT INTO Naslov(ulica, stevilka) VALUES('Ceste', FLOOR(RAND() * 100));
INSERT INTO Naslov(ulica, stevilka) VALUES('Dolda pot', FLOOR(RAND() * 100));

INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Ljudski vrt', '2000', 1);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Stožice', '1000', 2);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Igrisce v Rogatcu', '3252', 3);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Igrisce pri Rogatci', '3250', 8);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Ljudski vrt - trening', '1000', 4);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Ljudski vrt mini', '2000', 5);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Kladivar', '3000', 6);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Camp football', '2000', 7);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Igrisce samorog', '3250', 9);
INSERT INTO NogometnoIgrisce(imeIgrisca, fk_kraj, fk_naslov) VALUES('Nogometno igrisce', '1000', 10);


INSERT INTO ZaposlitevOsebe VALUES(NULL, 'Trener');
INSERT INTO ZaposlitevOsebe VALUES(NULL, 'Zdravnik');
INSERT INTO ZaposlitevOsebe VALUES(NULL, 'Pomocnik trenerju');
INSERT INTO ZaposlitevOsebe VALUES(NULL, 'Trener vratarjev');
INSERT INTO ZaposlitevOsebe VALUES(NULL, 'Fizioterapevt');

insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Benedicta', 'Lethbrig', '1976-03-09', '1000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Florry', 'Baroc', '1940-11-28', '2000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Corene', 'Bennison', '1973-01-07', '3000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Stevana', 'Ballingal', '1956-12-15', '3250');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Ebony', 'Senogles', '1935-10-14', '3000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Fayette', 'Curnokk', '1973-05-29', '3252');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Meggi', 'Sowten', '1939-11-25', '2000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Sarajane', 'Culley', '1950-03-01', '3000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Simone', 'Berthod', '1965-03-16', '1000');
insert into Osebje (Ime, Priimek, datRojstva, fk_posta) values ('Tess', 'Rosewall', '1982-04-14', '1000');

insert into Klub(kratica, naziv) values ("MAR", "NK Maribor");
insert into Klub(kratica, naziv) values ("OLI", "NK Olimpija");
insert into Klub(kratica, naziv) values ("MON", "Mons Claudius");
insert into Klub(kratica, naziv) values ("NKR", "NK Rogaška");
insert into Klub(kratica, naziv) values ("NKD", "NK Domžale");

insert into PogodbaOsebja (fk_klub, datPridruzitve, datZapustitve, placa, fk_oseba) values (4, '2010-07-10', '2015-01-11', 2085.52, 9);
insert into PogodbaOsebja (fk_klub, datPridruzitve, placa, fk_oseba) values (3, '2018-05-03', 2378.39, 3);
insert into PogodbaOsebja (fk_klub, datPridruzitve, datZapustitve, placa, fk_oseba) values (4, '2008-01-30', '2013-07-15', 2103.96, 10);
insert into PogodbaOsebja (fk_klub, datPridruzitve, placa, fk_oseba) values (1, '2019-03-29', 4854.73, 1);
insert into PogodbaOsebja (fk_klub, datPridruzitve, placa, fk_oseba) values (5, '2018-04-08', 3530.32, 2);
insert into PogodbaOsebja (fk_klub, datPridruzitve, placa, fk_oseba) values (2, '2018-05-28', 2678.28, 7);
insert into PogodbaOsebja (fk_klub, datPridruzitve, placa, fk_oseba) values (5, '2019-05-13', 2053.84, 4);
insert into PogodbaOsebja (fk_klub, datPridruzitve, datZapustitve, placa, fk_oseba) values (2, '2011-06-09', '2011-06-19', 3877.9, 8);
insert into PogodbaOsebja (fk_klub, datPridruzitve, placa, fk_oseba) values (4, '2014-09-26', 2036.86, 5);
insert into PogodbaOsebja (fk_klub, datPridruzitve, datZapustitve, placa, fk_oseba) values (4, '2010-11-24', '2019-11-24', 1999.27, 6);

insert into Sezona values(NULL, '2015-08-22', '2016-05-30');
insert into Sezona values(NULL, '2016-08-16', '2017-04-27');
insert into Sezona values(NULL, '2017-08-29', '2018-06-07');
insert into Sezona values(NULL, '2018-09-02', NULL);
insert into Sezona values(NULL, '2019-09-12', NULL);

insert into klubVSezoni values(NULL, 1,1, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 2,1, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 3,1, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 4,1, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 5,1, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 1,2, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 2,2, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 3,2, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 4,2, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 5,2, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 1,3, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 2,3, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 3,3, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 4,3, FLOOR(RAND() * 50));
insert into klubVSezoni values(NULL, 5,3, FLOOR(RAND() * 50));

insert into Tekma values(NULL, 1, 2, 1, '2015-10-20', 1);
insert into Tekma values(NULL, 2, 3, 1, '2015-10-21', 2);
insert into Tekma values(NULL, 3, 4, 1, '2015-11-10', 5);
insert into Tekma values(NULL, 4, 5, 1, '2015-12-07', 7);
insert into Tekma values(NULL, 5, 2, 1, '2016-03-21', 6);
insert into Tekma values(NULL, 5, 3, 1, '2016-04-15', 9);
insert into Tekma values(NULL, 5, 1, 1, '2016-04-17', 8);
insert into Tekma values(NULL, 1, 3, 1, '2016-04-27', 3);
insert into Tekma values(NULL, 1, 4, 1, '2016-05-03', 5);
insert into Tekma values(NULL, 1, 5, 1, '2016-05-29', 4);
insert into Tekma values(NULL, 1, 2, 5, '2019-09-29', 1);
insert into Tekma values(NULL, 1, 4, 5, '2021-09-29', 1);

insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Jordan', 'Haill', '1995-04-24', '3000');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Jenica', 'Durnford', '1986-08-04', '1000');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Sissy', 'Lincoln', '1981-11-16', '3252');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Ric', 'Kollatsch', '1987-02-13', '3000');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Peter', 'Jewar', '1997-06-24', '2000');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Gennie', 'Davidowich', '1983-08-24', '2000');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Derek', 'Meake', '1988-12-24', '3250');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Zitella', 'Chopy', '1980-01-26', '2000');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Colver', 'Oventon', '1991-03-10', '3250');
insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Terrye', 'Arondel', '1994-02-28', '3250');

insert into Polozaj values(NULL, 'vratar');
insert into Polozaj values(NULL, 'obrambni');
insert into Polozaj values(NULL, 'vezist');
insert into Polozaj values(NULL, 'napadalec');
insert into Polozaj values(NULL, 'napadalni vezist');

insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (4, 7, '2017-04-28', 4273.18);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (2, 2, '2016-12-16', 13625.38);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (2, 9, '2017-04-03', 11601.82);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, datZapustitve, placa) values (4, 1, '2010-04-19', '2016-08-19', 10858.2);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (1, 3, '2015-10-31', 4945.82);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (3, 4, '2018-03-07', 11489.02);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (5, 6, '2016-12-24', 3210.6);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, datZapustitve, placa) values (1, 5, '2012-01-25', '2018-08-15', 4208.76);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, datZapustitve, placa) values (4, 4, '2010-04-19', '2013-010-19', 10858.2);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, placa) values (3, 10, '2020-02-01', 13275.18);
insert into PogodbaIgralca (fk_klub, fk_igralec, datPridruzitve, datZapustitve, placa) values (4, 4, '2013-010-22', '2018-03-05', 10858.2);

insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (2, 1, '2017-04-28');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (1, 2, '2016-12-16');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (5, 3, '2017-04-03');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd, polozajDo) values (5, 4, '2010-04-19', '2016-08-19');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (5, 5, '2015-10-31');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (4, 6, '2018-03-07');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (1, 7, '2016-12-24');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd, polozajDo) values (2, 8, '2012-01-25', '2018-08-15');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd, polozajDo) values (3, 9, '2010-04-19', '2013-010-19');
insert into IgralecPolozaj (fk_polozaj, fk_pogodbaIgralec, polozajOd) values (2, 10, '2020-02-01');

insert into IgralecNaTekmi values (NULL, 7, 3);
insert into IgralecNaTekmi values (NULL, 2, 1);
insert into IgralecNaTekmi values (NULL, 9, 2);
insert into IgralecNaTekmi values (NULL, 1, 4);
insert into IgralecNaTekmi values (NULL, 3, 1);
insert into IgralecNaTekmi values (NULL, 4, 8);
insert into IgralecNaTekmi values (NULL, 6, 7);
insert into IgralecNaTekmi values (NULL, 5, 1);
insert into IgralecNaTekmi values (NULL, 4, 9);
insert into IgralecNaTekmi values (NULL, 10, 3);

insert into VrstaDogodka values(NULL, 'gol');
insert into VrstaDogodka values(NULL, 'rumen karton');
insert into VrstaDogodka values(NULL, 'rdec karton');
insert into VrstaDogodka values(NULL, 'prekrsek');
insert into VrstaDogodka values(NULL, 'podaja');

insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (8.77, 1, 3, 3);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (5.28, 2, 9, 5);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (43.47, 3, 1, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (85.17, 4, 7, 2);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (77.06, 5, 9, 4);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (14.49, 6, 2, 2);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (21.62, 7, 8, 2);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (58.43, 8, 1, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (54.25, 9, 1, 4);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (69.33, 10, 1, 4);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (20.23, 11, 2, 2);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (40.34, 11, 3, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (56.33, 11, 4, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (70.13, 8, 3, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (32.15, 8, 5, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (20.13, 10, 3, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (62.15, 9, 5, 1);

insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (12.07, 12, 3, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (22.36, 12, 3, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (32.12, 12, 3, 2);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (42.15, 12, 5, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (62.30, 12, 3, 1);
insert into Dogodek (cas, fk_tekma, fk_igralec, fk_vrstaDogodka) values (68.50, 12, 5, 1);
