use std::io::{Read, Write};
use std::str::from_utf8;
use std::env::args;

use std::os::unix::net::{UnixStream};


fn main() {
    //preberemo argumente
    let ime: String = args().nth(1).unwrap();
    let priimek: String = args().nth(2).unwrap();
    let stevilka: String = args().nth(3).unwrap();

    //najprej preverimo dolzine, da nebi vpisali predolgih vnosov
    if ime.len() > 100 {
        println!("Ime je predolgo");
    }
    else if priimek.len() > 100 {
        println!("Priimek je predolg");
    }
    else if ime.len() > 30 {
        println!("Stevilka je predolga");
    }
    else{
        //povezemo se na unix stream
        let mut stream = UnixStream::connect("../imenik/imenik.sock").unwrap();
    
        //posljemo ukaz #V da streznik ve, da se bo izvajal vpis
        let msg = "#V".to_owned();
    
        stream.write(msg.as_bytes()).unwrap();
    
        let mut data = [0 as u8; 100]; 
    
        //dobimo potrditev povezave
        match stream.read(&mut data) {
            Ok(_) => {
                println!("Uspesno poslan ukaz: {}", from_utf8(&data).unwrap());
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }
    
        //posljemo ime
        stream.write(ime.as_bytes()).unwrap();
    
        //potrditev streznika
        match stream.read(&mut data) {
            Ok(_) => {
                println!("Uspesno poslano ime: {}", from_utf8(&data).unwrap());
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }
    
        //posljemo priimek
        stream.write(priimek.as_bytes()).unwrap();
    
        //potrditev streznika
        match stream.read(&mut data) {
            Ok(_) => {
                println!("Uspesno poslano priimek: {}", from_utf8(&data).unwrap());
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }
    
        //posljemo stevilko
        stream.write(stevilka.as_bytes()).unwrap();
        
        //potrditev streznika
        match stream.read(&mut data) {
            Ok(_) => {
                println!("Uspesno poslano stevilka: {}", from_utf8(&data).unwrap());
                //prejeto sporocilo od serverja
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }
    
        //prejmemo ali je bil vnos dodan
        match stream.read(&mut data) {
            Ok(_) => {
                println!("{}", from_utf8(&data).unwrap());
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }
    }
}