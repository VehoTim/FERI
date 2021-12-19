use std::io::{Read, Write};
use std::str::from_utf8;
use std::env::args;

use std::os::unix::net::{UnixStream};

fn main() {
    //preberemo argumente
    let stevilka: String = args().nth(1).unwrap();

    //povezemo na unix stream
    let mut stream = UnixStream::connect("../imenik/imenik.sock").unwrap();
    
    //posljemo ukaz #I da streznik ve, da se bo izvajal izbris
    let msg = "#I".to_owned();

    stream.write(msg.as_bytes()).unwrap();

    let mut data = [0 as u8; 30];

    //potrditev streznika
    match stream.read(&mut data) {
        Ok(_) => {
            println!("Uspesno poslan ukaz: {}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }

    //posljemo stevilko za izbris
    stream.write(stevilka.as_bytes()).unwrap();

    
    //potrditev streznika
    match stream.read(&mut data) {
        Ok(_) => {
            println!("Uspesno poslano stevilka: {}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }

    //streznik sporoci ali je bil izbris uspesen
    match stream.read(&mut data) {
        Ok(_) => {
            println!("{}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }
}