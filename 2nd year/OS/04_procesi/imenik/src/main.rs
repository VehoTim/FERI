//cargo run -- compila in izvede program
//cargo check -- preveri ali se compila vendar ne izvede (hitrejse)

use std::thread;
use std::net::{TcpListener, TcpStream, Shutdown};
use std::io::{Read, Write};

use std::str::from_utf8;


static mut imena: Vec<String> = Vec::new();
static mut priimki: Vec<String> = Vec::new();
static mut stevilke: Vec<String> = Vec::new();

//imenik

//funkcija za branje in dodajanje vnosa
fn beri(ime: String, priimek: String, stevilka: String) -> bool {
    unsafe{

        //preverimo ali je stevilka ze v vektorju (ce da koncamo funkcijo)
        for st in stevilke.iter(){
            if st == &stevilka {
                return false;
            }
        }

        println!("{}", &ime.chars().count());

        if &stevilka.chars().count() <= &30 {
            stevilke.push(stevilka);
        } else {
            println!("Vnesenih je bilo prevec znakov");
            return false;
        }

        if &ime.chars().count() <= &100 {
            imena.push(ime);
        } else {
            println!("Vnesenih je bilo prevec znakov");
            return false;
        }

        if &priimek.chars().count() <= &100 {
            priimki.push(priimek);
        } else {
            println!("Vnesenih je bilo prevec znakov");
            return false;
        }
    }

    return true
}


//funkcija za brisanje vnosov
fn izbris(stevilka: String) -> bool {
    unsafe{
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
}

//funkcija za izpis vnosa
fn vnos(stevilka: String) -> bool {
    unsafe{
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
}

//funkcija za iskanje
fn iskanje(niz: &mut String) -> Vec<usize> {
    unsafe{
        let mut _indeksi: Vec<usize> = Vec::new();
        //iskanje po vektorju za ujemanje
        let mut n = 0;
        while n < stevilke.len() {
            if vsebuje(niz.to_string(), &imena[n]) {
            //if imena[n].contains(&niz) {
            //if imena[n].contains("Ti") {
                _indeksi.push(n);
            } 
            //else if priimki[n].contains(&niz) {
            //else if priimki[n].contains("Ve") {
            if vsebuje(niz.to_string(), &priimki[n]) {
                _indeksi.push(n);
            }
            else {
                println!("Ne vsebuje :C");
            }
            n += 1;
        }
        return _indeksi;

    }
}

fn vsebuje (niz: String, beseda: &String) -> bool {
    let niz_chars: Vec<_> = niz.chars().collect();
    let beseda_chars: Vec<_> = beseda.chars().collect();

    let is = niz.len();
    let mut n = 0;
    let mut m = 0;
    while n < (beseda.len() - 1) && m != (is - 1) {
        if beseda_chars[n] == niz_chars[m] {
            m += 1;
        }
        else {
            m = 0;
        }
        n += 1;
    }
    if m == (is - 1) {
        return true;
    }
    else {
        return false;
    }
}

fn handle_client(mut stream: TcpStream) {
    let mut data = [0 as u8; 50];
    let mut ime = [0 as u8; 100];
    let mut priimek = [0 as u8; 100];
    let mut stevilka = [0 as u8; 30]; 
    match stream.read(&mut data) {
        Ok(size) => {
            if &data[0..2] == b"#V" {
                println!("Vpisujem podatke");   
                stream.write(&data[0..size]).unwrap();

                stream.read(&mut ime);
                println!("{}", from_utf8(&ime).unwrap());
                stream.write(&ime[..]).unwrap();
                
                stream.read(&mut priimek);
                println!("{}", from_utf8(&priimek).unwrap());
                stream.write(&priimek[..]).unwrap();

                stream.read(&mut stevilka);
                println!("{}", from_utf8(&stevilka).unwrap());
                stream.write(&stevilka[..]).unwrap();

                println!("{}", String::from_utf8_lossy(&ime[..]).to_string());

                //dodajanje
                if beri(String::from_utf8_lossy(&ime[..]).to_string().replace('\0', ""), String::from_utf8_lossy(&priimek[..]).to_string().replace('\0', ""), String::from_utf8_lossy(&stevilka[..]).to_string().replace('\0', "")){
                    println!("Uspesno dodan");
                } else {
                    println!("Napaka pri vnosu");
                }
            }
        },
        Err(_) => {
            println!("An error occurred, terminating connection with {}", stream.peer_addr().unwrap());
            stream.shutdown(Shutdown::Both).unwrap();
        }
    } {}
}

fn main() {
    let listener = TcpListener::bind("0.0.0.0:1234").unwrap();
    println!("Server posluša na vratih 1234");

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                println!("Nova povezava: {}", stream.peer_addr().unwrap());
                thread::spawn(move || {
                    handle_client(stream);
                });
            }
            Err(e) => {
                println!("Error: {}", e);
                /* connection failed */
            }
        }
    }
    drop(listener);

    /*

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
    st_izbris.pop();

    if izbris(st_izbris, &mut stevilke, &mut imena, &mut priimki) {
        println!("Uspesno izbrisan");
    } else {
        println!("Vnos s to stevilko ne obstaja");
    }

    //izpis
    println!("Vpisi stevilko: ");
    let mut st_vnos = String::new();
    std::io::stdin().read_line(&mut st_vnos);
    st_vnos.pop();

    if !vnos(st_vnos, &mut stevilke, &mut imena, &mut priimki) {
        println!("Vnos s to stevilko ne obstaja");
    }

    //iskanje
    let mut niz_vnos = String::new();
    std::io::stdin().read_line(&mut niz_vnos);
    niz_vnos.pop();

    let ix: Vec<usize> = iskanje(&mut niz_vnos, &mut stevilke, &mut imena, &mut priimki);

    println!("Najdenih je bilo: {} vnosov", ix.len());

    for i in ix {
        vnos(stevilke[i].to_string(), &mut stevilke, &mut imena, &mut priimki);
    }*/
}
