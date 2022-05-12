use baza1002470617;

ALTER TABLE tekma
DROP COLUMN zmagovalec;
 
ALTER TABLE tekma
ADD COLUMN zmagovalec int DEFAULT 0; 	#1 - prvi, 2 - drugi, 3 - izenaceno, 0 - tekma se ni koncana

#TRIGGER
DROP TRIGGER zmagovalec_tekme

DELIMITER &
CREATE TRIGGER zmagovalec_tekme 
AFTER UPDATE on tekma
FOR EACH ROW
BEGIN
UPDATE klubVSezoni, tekma
SET stTock = CASE WHEN zmagovalec = 3 THEN stTock + 1
				  WHEN (zmagovalec = 1 OR zmagovalec = 2) THEN stTock + 3
				  ELSE stTock
			  END
WHERE fk_klub = CASE WHEN zmagovalec = 1 THEN fk_klub1 AND klubVSezoni.fk_sezona = tekma.fk_sezona
					 WHEN zmagovalec = 2 THEN fk_klub2 AND klubVSezoni.fk_sezona = tekma.fk_sezona
					 WHEN zmagovalec = 3 THEN fk_klub1 AND fk_klub = fk_klub2 AND klubVSezoni.fk_sezona = tekma.fk_sezona
                     ELSE 0 AND klubVSezoni.fk_sezona = tekma.fk_sezona
				END
AND idKlubaVSezoni != 0 AND idTekme != 0;
END&
DELIMITER ;

SELECT stTock, fk_sezona, fk_klub
FROM klubVSezoni;

UPDATE tekma
SET zmagovalec = 1 
WHERE idTekme = 1;

SELECT stTock, fk_sezona, fk_klub
FROM klubVSezoni;

#TRANSAKCIJA
start transaction;

savepoint sp1;

INSERT INTO igralec VALUES(NULL, 'Tim', 'Vehovar', '2001-02-17', '3252');

SELECT @idIgralca:=MAX(idIgralec) FROM igralec;

insert INTO pogodbaIgralca VALUES(NULL, 1, @idIgralca, curdate(), NULL, 2000.00);

commit;

select * from igralec left join pogodbaIgralca on igralec.idIgralec = pogodbaIgralca.fk_igralec where ime = 'Tim'