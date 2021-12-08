use std::net::{TcpStream};
use std::io::{Read, Write};
use std::str::from_utf8;
use std::env::args;

fn main() {
    //preberemo argumente
    let ime: String = args().nth(1).unwrap();
    let priimek: String = args().nth(2).unwrap();
    let stevilka: String = args().nth(3).unwrap();

    match TcpStream::connect("localhost:1234") {
        Ok(mut stream) => {
            //dodati stevilo za lazje branje and its done
            let msg = "#V".to_owned();

            stream.write(msg.as_bytes()).unwrap();

            let mut data = [0 as u8; 100]; // using 6 byte buffer

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
            stream.write(ime.as_bytes()).unwrap();
            
            println!("Poslan drugi");

            match stream.read(&mut data) {
                Ok(_) => {
                    println!("Uspesno poslano ime: {}", from_utf8(&data).unwrap());
                    //prejeto sporocilo od serverja
                },
                Err(e) => {
                    println!("Failed to receive data: {}", e);
                }
            }

            //
            stream.write(priimek.as_bytes()).unwrap();
            
            println!("Poslan tretji");

            match stream.read(&mut data) {
                Ok(_) => {
                    println!("Uspesno poslano priimek: {}", from_utf8(&data).unwrap());
                    //prejeto sporocilo od serverja
                },
                Err(e) => {
                    println!("Failed to receive data: {}", e);
                }
            }

            //
            stream.write(stevilka.as_bytes()).unwrap();
            
            println!("Poslan cetrti");

            match stream.read(&mut data) {
                Ok(_) => {
                    println!("Uspesno poslano stevilka: {}", from_utf8(&data).unwrap());
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