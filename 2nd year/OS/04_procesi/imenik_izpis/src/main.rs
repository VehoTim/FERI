use std::io::{Read, Write};
use std::str::from_utf8;
use std::env::args;

use std::os::unix::net::{UnixStream};

fn main() {
    //preberemo argumente
    let stevilka: String = args().nth(1).unwrap();
    
    let mut stream = UnixStream::connect("../imenik/imenik.sock").unwrap();
    
    //posljemo ukaz #O da streznik ve, da se bo izvajal izpis
    let msg = "#O".to_owned();

    stream.write(msg.as_bytes()).unwrap();

    let mut data = [0 as u8; 30];

    //dobimo potrditev povezave
    match stream.read(&mut data) {
        Ok(_) => {
            println!("Uspesno poslan ukaz: {}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }

    //posljemo stevilko
    stream.write(stevilka.as_bytes()).unwrap();

    //dobimo potrditev povezave
    match stream.read(&mut data) {
        Ok(_) => {
            println!("Uspesno poslano stevilka: {}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }

    //izpis najdenega vnosa ali izpis da ni bilo najdeno
    match stream.read(&mut data) {
        Ok(_) => {
            println!("{}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }
}