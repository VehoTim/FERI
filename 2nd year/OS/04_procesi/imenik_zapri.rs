use std::io::{Read, Write};
use std::str::from_utf8;

use std::os::unix::net::{UnixStream};

fn main() {
    //povezemo se na unix stream
    let mut stream = UnixStream::connect("../imenik/imenik.sock").unwrap();

    //posljemo ukaz #Z da streznik ve, da se bo koncal program
    let msg = "#Z".to_owned();

    stream.write(msg.as_bytes()).unwrap();

    //potrditev zaprtja
    let mut data = [0 as u8; 30];

    match stream.read(&mut data) {
        Ok(_) => {
            println!("Imenik je zaprt: {}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Napaka: {}", e);
        }
    }
}