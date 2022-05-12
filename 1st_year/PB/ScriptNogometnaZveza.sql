USE baza1002470617;

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

CREATE TABLE ZaposlitevOsebe(
	idZaposlitevOsebe int not null auto_increment primary key,
    nazivZaposlitve varchar(45) not null
);

CREATE TABLE Osebje(
	idOsebe int not null auto_increment primary key,
    Ime varchar(45) not null,
    Priimek varchar(45) not null,
    datRojstva DATE not null,
    fk_posta char(4) not null
);

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

CREATE TABLE Tekma(
	idTekme int not null auto_increment primary key,
    fk_klub1 int not null,
    fk_klub2 int not null,
    fk_sezona int not null,
    datum datetime not null,
    fk_nogIgrisce int not null
);

CREATE TABLE Igralec(
	idIgralec int not null primary key,
    Ime varchar(45) not null,
    Priimek varchar(45) not null,
    datRojstva DATE not null,
    fk_kraj char(4) not null
);

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

CREATE TABLE IgralecPolozaj(
	idIgralecPolozaj int not null auto_increment primary key,
    fk_polozaj int not null,
    fk_pogodbaIgralec int not null,
    polozajOd datetime not null,
    polozajDo datetime
);

CREATE TABLE IgralecNaTekmi(
	idIgralecNaTekmi int not null auto_increment primary key,
    fk_igralec int not null,
    fk_tekma int not null
);

CREATE TABLE VrstaDogodka(
	idVrstaDogodka int not null auto_increment primary key,
    naziv varchar(45)
);

CREATE TABLE Dogodek(
	idDogodek int not null auto_increment primary key,
    cas decimal(3,2) not null,
    fk_tekma int not null,
    fk_igralec int not null,
    fk_vrstaDogodka int not null
);

ALTER TABLE Osebje ADD CONSTRAINT fk_oseba_posta FOREIGN KEY (fk_posta) REFERENCES kraj (posta) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE PogodbaOsebja ADD CONSTRAINT fk_pogodba_oseba FOREIGN KEY (fk_oseba) REFERENCES Osebje (idOsebe) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE KlubVSezoni ADD CONSTRAINT fk_klubVSezoni_klub FOREIGN KEY (fk_klub) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE KlubVSezoni ADD CONSTRAINT fk_klubVSezoni_sezona FOREIGN KEY (fk_sezona) REFERENCES Sezona (idSezona) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_klub1 FOREIGN KEY (fk_klub1) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_klub2 FOREIGN KEY (fk_klub2) REFERENCES Klub (idKlub) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_sezona FOREIGN KEY (fk_sezona) REFERENCES Sezona (idSezona) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Tekma ADD CONSTRAINT fk_tekma_nogIgrisce FOREIGN KEY (fk_nogIgrisce) REFERENCES NogometnoIgrisce (idNogometnoIgrisce) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE NogometnoIgrisce ADD CONSTRAINT fk_igrisce_kraj FOREIGN KEY (fk_kraj) REFERENCES Kraj (posta) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE NogometnoIgrisce ADD CONSTRAINT fk_igrisce_naslov FOREIGN KEY (fk_naslov) REFERENCES Naslov (idNaslov) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Igralec ADD CONSTRAINT fk_igralec_kraj FOREIGN KEY (fk_kraj) REFERENCES Kraj (posta) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE IgralecPolozaj ADD CONSTRAINT fk_igralecPolozaj_pogodba FOREIGN KEY (fk_pogodbaIgralec) REFERENCES PogodbaIgralca (idPogodbeIgralca) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE IgralecNaTekmi ADD CONSTRAINT fk_igralecNaTekmi_igralec FOREIGN KEY (fk_igralec) REFERENCES Igralec (idIgralec) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE IgralecNaTekmi ADD CONSTRAINT fk_igralecNaTekmi_tekma FOREIGN KEY (fk_tekma) REFERENCES Tekma (idTekme) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Dogodek ADD CONSTRAINT fk_dogodek_tekma FOREIGN KEY (fk_tekma) REFERENCES Tekma (idTekme) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Dogodek ADD CONSTRAINT fk_dogodek_igralec FOREIGN KEY (fk_igralec) REFERENCES Igralec (idIgralec) ON DELETE CASCADE ON UPDATE NO ACTION;
ALTER TABLE Dogodek ADD CONSTRAINT fk_dogodek_vrsta FOREIGN KEY (fk_vrstaDogodka) REFERENCES VrstaDogodka (idVrstaDogodka) ON DELETE CASCADE ON UPDATE NO ACTION;



