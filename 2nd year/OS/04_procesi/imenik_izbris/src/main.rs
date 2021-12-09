use std::net::{TcpStream};
use std::io::{Read, Write};
use std::str::from_utf8;
use std::env::args;

fn main() {
    //preberemo argumente
    let stevilka: String = args().nth(1).unwrap();

    match TcpStream::connect("localhost:1234") {
        Ok(mut stream) => {
            //dodati stevilo za lazje branje and its done
            let msg = "#I".to_owned();

            stream.write(msg.as_bytes()).unwrap();

            let mut data = [0 as u8; 30]; // using 6 byte buffer

            match stream.read(&mut data) {
                Ok(_) => {
                    println!("Uspesno poslan ukaz: {}", from_utf8(&data).unwrap());
                    //prejeto sporocilo od serverja
                },
                Err(e) => {
                    println!("Failed to receive data: {}", e);
                }
            }

            //
            stream.write(stevilka.as_bytes()).unwrap();

            match stream.read(&mut data) {
                Ok(_) => {
                    println!("Uspesno poslano stevilka: {}", from_utf8(&data).unwrap());
                    //prejeto sporocilo od serverja
                },
                Err(e) => {
                    println!("Failed to receive data: {}", e);
                }
            }

            match stream.read(&mut data) {
                Ok(_) => {
                    println!("{}", from_utf8(&data).unwrap());
                    //prejeto sporocilo od serverja
                },
                Err(e) => {
                    println!("Failed to receive data: {}", e);
                }
            }
        },
        Err(e) => {
            println!("Failed to connect: {}", e);
        }
    }
    println!("Terminated.");
}