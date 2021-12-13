//cargo run -- compila in izvede program
//cargo check -- preveri ali se compila vendar ne izvede (hitrejse)

use std::thread;
use crate::thread::sleep;
use std::time::Duration;
use std::os::unix::net::{UnixStream,UnixListener};

use std::io::{Read, Write};
use std::fs;
use std::path::Path;

use std::ptr::null_mut;

use std::str::from_utf8;

//libc za shared memory

use libc::shm_open;
use libc::O_RDWR;
use libc::O_CREAT;
use libc::PROT_WRITE;
use libc::MAP_SHARED;
use libc::c_char; 
use libc::c_void;
use libc::ftruncate;
use libc::mmap;
use libc::memcpy;
use libc::off_t;
use libc::S_IRUSR;
use libc::S_IWUSR;
//use std::ffi::CStr;

use random_string::generate;


static mut IMENA: Vec<String> = Vec::new();
static mut PRIIMKI: Vec<String> = Vec::new();
static mut STEVILKE: Vec<String> = Vec::new();

static mut LIGHT: String = String::new();

//imenik

//funkcija za branje in dodajanje vnosa
fn beri(ime: String, priimek: String, stevilka: String) -> bool {
    unsafe{
        //preverimo ali je stevilka ze v vektorju (ce da koncamo funkcijo)
        for st in STEVILKE.iter(){
            if st == &stevilka {
                return false;
            }
        }

        println!("{}", &ime.chars().count());

        if &stevilka.chars().count() <= &30 {
            STEVILKE.push(stevilka);
        } else {
            println!("Vnesenih je bilo prevec znakov");
            return false;
        }

        if &ime.chars().count() <= &100 {
            IMENA.push(ime);
        } else {
            println!("Vnesenih je bilo prevec znakov");
            return false;
        }

        if &priimek.chars().count() <= &100 {
            PRIIMKI.push(priimek);
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
        while n < STEVILKE.len() {
            if stevilka == STEVILKE[n].to_string() {
                PRIIMKI.remove(n);
                IMENA.remove(n);
                STEVILKE.remove(n);
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
        while n < STEVILKE.len() {
            if stevilka == STEVILKE[n].to_string() {
                println!("{} {} - {}", IMENA[n], PRIIMKI[n], STEVILKE[n]);
                return true;
            }
            n += 1;
        } 
        return false;
    }
}

//funkcija za iskanje
fn iskanje(niz: String) -> Vec<usize> {
    unsafe{
        let mut _indeksi: Vec<usize> = Vec::new();
        //iskanje po vektorju za ujemanje
        let mut n = 0;
        while n < STEVILKE.len() {
            if IMENA[n].contains(&niz) {
                _indeksi.push(n);
            } 
            else if PRIIMKI[n].contains(&niz) {
                _indeksi.push(n);
            }
            n += 1;
        }
        return _indeksi;

    }
}

fn handle_client(mut stream: UnixStream) {
   
    let mut data = [0 as u8; 100];
    let mut ime = [0 as u8; 100];
    let mut priimek = [0 as u8; 100];
    let mut stevilka = [0 as u8; 30]; 
    match stream.read(&mut data) {
        Ok(size) => {
            if &data[0..2] == b"#V" {
                unsafe{
                    LIGHT = "red".to_string();
                }
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
                    stream.write(b"Uspesno dodali").unwrap();
                } else {
                    stream.write(b"Vnos ni uspel").unwrap();
                }
                
                unsafe{
                    LIGHT = "green".to_string();
                }
            }
            else if &data[0..2] == b"#I" {
                unsafe{
                    LIGHT = "red".to_string();
                }
                println!("Brisem podatke"); 
                stream.write(&data[0..size]).unwrap(); 

                stream.read(&mut stevilka);
                println!("Brisem vnos: {}", from_utf8(&stevilka).unwrap());
                stream.write(&stevilka[..]).unwrap();

                //brisanje
                if izbris(String::from_utf8_lossy(&stevilka[..]).to_string().replace('\0', "")) {
                    stream.write(b"Uspesno izbrisali").unwrap();
                } else {
                    stream.write(b"Izbris ni uspel").unwrap();
                }
                
                unsafe{
                    LIGHT = "green".to_string();
                }
            }
            else if &data[0..2] == b"#O" {
                println!("Iskanje vnosa"); 
                stream.write(&data[0..size]).unwrap(); 
                
                stream.read(&mut stevilka);
                println!("Iskanje vnosa: {}", from_utf8(&stevilka).unwrap());
                stream.write(&stevilka[..]).unwrap();

                //iskanje
                if vnos(String::from_utf8_lossy(&stevilka[..]).to_string().replace('\0', "")) {
                    unsafe{
                        //iskanje po vektorju za ujemanje
                        let mut n = 0;
                        while n < STEVILKE.len() {
                            if String::from_utf8_lossy(&stevilka[..]).to_string().replace('\0', "") == STEVILKE[n].to_string() {
                                stream.write((IMENA[n].to_string() + " " + &PRIIMKI[n] + " - " + &STEVILKE[n]).as_bytes()).unwrap();
                                //println!("{} {} - {}", IMENA[n], PRIIMKI[n], STEVILKE[n]);
                            }
                            n += 1;
                        } 
                    }
                } else {
                    stream.write(b"Vnos ne obstaja").unwrap();
                }
            }
            else if &data[0..2] == b"#S" {
                println!("Iskanje"); 
                stream.write(&data[0..size]).unwrap(); 
                
                loop {
                    let mut vsebina: String = String::new();
                    let mut srch = [0 as u8; 100];
                    stream.read(&mut srch);
                    println!("Iskanje vnosa: {}", from_utf8(&srch).unwrap());
                    
                    let charset = "1234567890abcdefghijklmnopqrstuvxyz";

                    //shared memory
                    let s: String = generate(6, charset);

                    println!("{}", s);

                    stream.write(&mut s.as_bytes());
                    
                    let (fd, addr) = unsafe {
                        let null = null_mut();
                        let fd   = shm_open(s.as_bytes().as_ptr() as *const c_char, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
                        let _res = ftruncate(fd, 4096 as off_t);
                        let addr = mmap(null, 4096, PROT_WRITE, MAP_SHARED, fd, 0);
                        
                        (fd, addr)
                    };
    
                    //iskanje
                    let ix: Vec<usize> = iskanje(String::from_utf8_lossy(&srch[..]).to_string().replace('\0', ""));
                    
                    stream.write(ix.len().to_string().as_bytes()).unwrap();

                    for i in ix {
                        unsafe{
                            println!("{}", IMENA[i].to_string() + " " + &PRIIMKI[i] + " - " + &STEVILKE[i]);

                            vsebina += &(IMENA[i].to_string() + " " + &PRIIMKI[i] + " - " + &STEVILKE[i] + "\n");
                        }
                    }
                    let data = vsebina.as_bytes();
                    
                    let pdata = data.as_ptr() as *const c_void;
    
                    unsafe {
                        memcpy(addr, pdata, data.len());
                        //munmap(addr, 4096);
                    }
                }
            }
            else if &data[0..2] == b"#Z" {
                stream.write(b"#Z");
                println!("Konec programa");
                std::process::exit(0);
            }
        },
        Err(_) => {
            println!("An error occurred, terminating connection");
        }
    } {}
}

fn main() -> std::io::Result<()> {
    if Path::new("imenik.sock").exists() {
        fs::remove_file("imenik.sock")?;
    }

    let listener = UnixListener::bind("imenik.sock").unwrap();

    for stream in listener.incoming() {
        match stream {
            Ok(stream) => {
                unsafe{
                    loop{
                        if LIGHT == "red" {
                            sleep(Duration::from_secs(5));
                        }
                        else {
                            break;
                        }
                    }
                }
                thread::spawn(move || {
                    handle_client(stream);
                });
                println!("--- Konec niti ---")
            }
            Err(e) => {
                println!("Error: {}", e);
            }
        }
    }
    Ok(())
}