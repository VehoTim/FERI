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

fn main() {
    let mut imena: Vec<String> = Vec::new();
    let mut priimki: Vec<String> = Vec::new();
    let mut stevilke: Vec<String> = Vec::new();

    if beri(&mut stevilke, &mut imena, &mut priimki){
        println!("Uspesno dodan");
    } else {
        println!("Vnos s to stevilko ze obstaja");
    }

    println!("Vpisi stevilko: ");
    let mut stevilka = String::new();
    std::io::stdin().read_line(&mut stevilka);

    if izbris(stevilka, &mut stevilke, &mut imena, &mut priimki) {
        println!("Uspesno izbrisan");
    } else {
        println!("Vnos s to stevilko ne obstaja");
    }

    //println!("{}", stevilke.len());
}
