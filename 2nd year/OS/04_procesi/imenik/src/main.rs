//cargo run -- compila in izvede program
//cargo check -- preveri ali se compila vendar ne izvede (hitrejse)

//imenik

//funkcija za branje in dodajanje vnosa
fn beri(stevilke: &mut Vec<String>, imena: &mut Vec<String>, priimki: &mut Vec<String>) -> bool {

    //dodajanje telefonske stevilke
    println!("Vpisi stevilko: ");
    let mut stevilka = String::new();
    std::io::stdin().read_line(&mut stevilka);

    //preverimo ali je stevilka ze v vektorju (ce da koncamo funkcijo)
    for st in stevilke.iter(){
        if st.to_string() == stevilka {
            return false;
        }
    }

    if stevilka.chars().count() <= 30 {
        stevilke.push(stevilka);
    } else {
        println!("Vnesenih je bilo prevec znakov");
        return false;
    }

    
    //dodajanje imena
    println!("Vpisi ime: ");
    let mut ime = String::new();
    std::io::stdin().read_line(&mut ime);

    if ime.chars().count() <= 100 {
        imena.push(ime);
    } else {
        println!("Vnesenih je bilo prevec znakov");
        return false;
    }

     //dodajanje priimka
     println!("Vpisi priimek: ");
     let mut priimek = String::new();
     std::io::stdin().read_line(&mut priimek);

     if priimek.chars().count() <= 100 {
        priimki.push(priimek);
    } else {
        println!("Vnesenih je bilo prevec znakov");
        return false;
    }

    return true
}

//funkcija za brisanje vnosov
fn izbris(stevilka: String, stevilke: &mut Vec<String>, imena: &mut Vec<String>, priimki: &mut Vec<String>) -> bool {
    //iskanje po vektorju za ujemanje
    let mut n = 0;
    while n < stevilke.len() {
        if stevilka == stevilke[n].to_string() {
            priimki.remove(n);
            imena.remove(n);
            stevilke.remove(n);
            return true;
        }
        n += 1;
    } 
    return false;
}

//funkcija za izpis vnosa
fn vnos(stevilka: String, stevilke: &mut Vec<String>, imena: &mut Vec<String>, priimki: &mut Vec<String>) -> bool {
     //iskanje po vektorju za ujemanje
     let mut n = 0;
     while n < stevilke.len() {
         if stevilka == stevilke[n].to_string() {
             //formating izpisa je malo wack :C
             println!("{} {} - {}", imena[n], priimki[n], stevilke[n]);
             return true;
         }
         n += 1;
     } 
     return false;
}

//funkcija za iskanje
fn iskanje(niz: &mut String, stevilke: &mut Vec<String>, imena: &mut Vec<String>, priimki: &mut Vec<String>) -> Vec<usize> {
    
    let mut _indeksi: Vec<usize> = Vec::new();
    //iskanje po vektorju za ujemanje
    let mut n = 0;
    while n < stevilke.len() {
        //if vsebuje(niz.to_string(), &mut imena[n]/*, priimki[n]*/) {
        //if imena[n].contains(&niz) {
        if imena[n].contains("Ti") {
            _indeksi.push(n);
        } 
        //else if priimki[n].contains(&niz) {
         else if priimki[n].contains("Ve") {
            _indeksi.push(n);
        }
        else {
            println!("Ne vsebuje :C");
        }
        n += 1;
    } 
    return _indeksi;
}

/*fn vsebuje (niz: String, ime: &mut String/*, priimek: String*/) -> bool {
    let is = niz.len();
    let mut n = 0;
    let mut m = 0;
    while n < ime.len() && m != is{
        if ime.chars().nth(n).unwrap() == niz.chars().nth(m).unwrap() {
            m += 1;
        }
        else {
            m = 0;
        }
        n += 1;
    }
    if m == is {
        return true;
    }
    else {
        return false;
    }
}*/

fn main() {
    let mut imena: Vec<String> = Vec::new();
    let mut priimki: Vec<String> = Vec::new();
    let mut stevilke: Vec<String> = Vec::new();

    //dodajanje
    if beri(&mut stevilke, &mut imena, &mut priimki){
        println!("Uspesno dodan");
    } else {
        println!("Vnos s to stevilko ze obstaja");
    }

    //brisanje
    println!("Vpisi stevilko: ");
    let mut st_izbris = String::new();
    std::io::stdin().read_line(&mut st_izbris);

    if izbris(st_izbris, &mut stevilke, &mut imena, &mut priimki) {
        println!("Uspesno izbrisan");
    } else {
        println!("Vnos s to stevilko ne obstaja");
    }

    //izpis
    println!("Vpisi stevilko: ");
    let mut st_vnos = String::new();
    std::io::stdin().read_line(&mut st_vnos);

    if !vnos(st_vnos, &mut stevilke, &mut imena, &mut priimki) {
        println!("Vnos s to stevilko ne obstaja");
    }

    //iskanje
    let mut niz_vnos = String::new();
    std::io::stdin().read_line(&mut niz_vnos);

    let ix: Vec<usize> = iskanje(&mut niz_vnos, &mut stevilke, &mut imena, &mut priimki);

    for i in ix {
        vnos(stevilke[i].to_string(), &mut stevilke, &mut imena, &mut priimki);
    }
}
