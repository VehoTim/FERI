//cargo run -- compila in izvede program
//cargo check -- preveri ali se compila vendar ne izvede (hitrejse)

//imenik

fn beri(stevilke: &mut Vec<String>, imena: &mut Vec<String>, priimki: &mut Vec<String>) -> bool {

    //dodajanje telefonske stevilke
    println!("Vpisi stevilko: ");
    let mut stevilka = String::new();
    std::io::stdin().read_line(&mut stevilka);

    //preverimo ali je stevilka ze v vektorju (ce da koncamo funkcijo)
    for st in stevilke.iter(){
        if st.to_string() == stevilka {
            return false
        }
    }

    stevilke.push(stevilka);
    
    //dodajanje imena
    println!("Vpisi ime: ");
    let mut ime = String::new();
    std::io::stdin().read_line(&mut ime);
    
    imena.push(ime);

     //dodajanje priimka
     println!("Vpisi priimek: ");
     let mut priimek = String::new();
     std::io::stdin().read_line(&mut priimek);
     
     priimki.push(priimek);

    return true
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

    for st in stevilke {
        println!("Stevilka: {}", st);
    }
}
