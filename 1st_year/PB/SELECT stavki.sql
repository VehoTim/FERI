use baza1002470617

/* 1.	Kateri nogometaš je dosegel prvi gol na tekmi ”Maribor-Olimpija”dne ”29.9.2019”?  */
SELECT ime, priimek
FROM Igralec join Dogodek on igralec.idIgralec = dogodek.fk_igralec
WHERE fk_tekma = (SELECT idTekme FROM tekma 
				  WHERE datum='2019-09-29'
				  AND fk_klub1 = (SELECT idKlub FROM Klub WHERE naziv='NK Maribor') 
				  AND fk_klub2 = (SELECT idKlub FROM Klub WHERE naziv='NK Olimpija'))
AND cas = (SELECT MIN(cas)
			FROM Dogodek
			WHERE fk_tekma = (SELECT idTekme FROM tekma 
							  WHERE datum='2019-09-29'
							  AND fk_klub1 = (SELECT idKlub FROM Klub WHERE naziv='NK Maribor')
							  AND fk_klub2 = (SELECT idKlub FROM Klub WHERE naziv='NK Olimpija'))
							  AND fk_vrstaDogodka = (SELECT idVrstaDogodka FROM vrstadogodka WHERE naziv='gol'))

/* 2.	Izpišite vse kartone in kdo je kartone prejel. Kartoni naj se izpiˇsejo, tudi če ga ni ˇse nihče prejel. */
SELECT ime, priimek, vrstaDogodka.naziv
FROM Igralec right join Dogodek on igralec.idIgralec = dogodek.fk_igralec right join vrstaDogodka on dogodek.fk_vrstaDogodka = vrstaDogodka.idVrstaDogodka
WHERE naziv = 'rumen karton' or naziv = 'rdec karton'

/* 3.	Izračunajte starost vsakega igralca na tekmi Maribor-Olimpija dne 29.9.2019 glede na datum rojstva. */
SELECT ime, priimek, (DATEDIFF(NOW(),datRojstva) / 365) as starost
FROM Igralec join Dogodek on igralec.idIgralec = dogodek.fk_igralec
WHERE fk_tekma = (SELECT idTekme FROM tekma 
				  WHERE datum='2019-09-29'
				  AND fk_klub1 = (SELECT idKlub FROM Klub WHERE naziv='NK Maribor') 
				  AND fk_klub2 = (SELECT idKlub FROM Klub WHERE naziv='NK Olimpija'))

/* 4.	Izpiši letošnje število zadetih golov posameznih igralcev kluba ”Maribor”. */
SELECT ime, priimek, COUNT(*) as gol
FROM PogodbaIgralca join Igralec on pogodbaIgralca.fk_igralec = igralec.idIgralec left join dogodek on igralec.idIgralec = dogodek.fk_igralec
join tekma on tekma.idTekme = dogodek.fk_tekma
WHERE fk_klub = (SELECT idKlub
				 FROM Klub
                 WHERE naziv = 'NK Maribor')
AND dogodek.fk_vrstaDogodka = (SELECT idVrstaDogodka FROM vrstaDogodka WHERE naziv='gol')
AND YEAR(datum) = YEAR(CURDATE())
GROUP BY idIgralec
    
/* 5.	Kateri nogometaš je zamenjal največ klubov? */ 
SELECT ime, priimek, count(DISTINCT fk_klub) as stKlubov
FROM PogodbaIgralca join Igralec on fk_igralec=idIgralec
GROUP BY fk_igralec
HAVING stKlubov = (SELECT MAX(stKlubov) 
				   FROM (SELECT count(DISTINCT fk_klub) as stKlubov
						 FROM PogodbaIgralca join Igralec on fk_igralec=idIgralec
						 GROUP BY fk_igralec) AS maxKlubov)


/* 6.	V katerih sezonah je klub ”Maribor zbral več točk kot jih povprečno zbere na koncu sezone? */ 
SELECT fk_sezona, stTock
FROM KlubVSezoni
WHERE fk_klub = (SELECT idKlub FROM Klub WHERE naziv = 'NK Maribor') 
AND stTock > (SELECT AVG(stTock) FROM KlubVSezoni WHERE fk_klub = (SELECT idKlub FROM Klub WHERE naziv = 'NK Maribor'))

/* 7.	Spremeni ime nogometnega kluba ”Rudar Velenje”v ”Velenje TES”. ˇ */
SELECT naziv FROM Klub 

INSERT INTO Klub VALUES(null, 'RUD', 'Rudar Velenje')

UPDATE Klub A join Klub B on A.idKlub = B.idKlub
SET A.naziv = 'Velenje TES'
WHERE B.naziv = 'Rudar Velenje'

/* 8.	Izbriši igralca ”Nejc Ostružnik”. */
SELECT * FROM Igralec 

insert into Igralec (Ime, Priimek, datRojstva, fk_kraj) values ('Nejc', 'Ostružnik', '1995-04-24', '3000');

DELETE FROM Igralec 
WHERE ime = 'Nejc' AND priimek = 'Ostružnik' AND idIgralec != 0;

/* Kateri igralec se je udelezil najvec tekem? */
SELECT ime, priimek, count(fk_igralec) as stTekem
FROM igralec join igralecNaTekmi ON igralec.idIgralec = igralecNaTekmi.fk_igralec
GROUP BY idIgralec
HAVING stTekem = (SELECT MAX(stTekem) FROM (SELECT count(fk_igralec) as stTekem
											FROM IgralecNaTekmi JOIN igralec ON igralec.idIgralec = igralecNaTekmi.fk_igralec
											GROUP BY idIgralec) as maxTekem)