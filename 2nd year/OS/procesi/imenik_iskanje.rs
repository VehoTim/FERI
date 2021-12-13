use std::io::{Read, Write};
use std::str::from_utf8;

use std::os::unix::net::{UnixStream};

//libc za shared memory
use libc::shm_open;
use libc::O_RDWR;
use libc::PROT_READ;
use libc::MAP_SHARED;
use libc::c_char; 
use libc::close;
use libc::ftruncate;
use libc::mmap;
//use libc::munmap;
//use libc::memcpy;
//use libc::shm_unlink;
use libc::off_t;
use libc::S_IRUSR;
use libc::S_IWUSR;
use libc::strncpy;
use std::error::Error;
//use std::ffi::CStr;

use std::ptr::null_mut;

fn main() -> Result<(), Box<dyn Error>>{    
    //povezemo se na stream
    let mut stream = UnixStream::connect("../imenik/imenik.sock").unwrap();
    
    //posljemo ukaz #S da streznik ve, da se bo izvajalo iskanje
    let msg = "#S".to_owned();

    stream.write(msg.as_bytes()).unwrap();
        
    //potrditev streznika
    let mut data = [0 as u8; 30]; 

    match stream.read(&mut data) {
        Ok(_) => {
            println!("Uspesno poslan ukaz: {}", from_utf8(&data).unwrap());
        },
        Err(e) => {
            println!("Failed to receive data: {}", e);
        }
    }
    
    //zanka za izvajanje iskanja
    loop {
        let vnos = &mut String::new();
        //poziv za vnos
        println!("Vpisi niz: ");
        //uporabnikov vnos
        std::io::stdin().read_line(vnos);
        vnos.pop();

        stream.write(vnos.as_bytes()).unwrap();

        let mut shm_name = [0 as u8; 6]; 
        match stream.read(&mut shm_name) {
            Ok(_) => {
                println!("Ime: {}", from_utf8(&shm_name).unwrap());
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }
        
        let mut st = [0 as u8; 30]; 
        match stream.read(&mut st) {
            Ok(_) => {
                println!("Najdenih vnosov: {}", from_utf8(&st).unwrap());
            },
            Err(e) => {
                println!("Failed to receive data: {}", e);
            }
        }

        //shared memory
        let s: String = from_utf8(&shm_name).unwrap().to_string();
        let (fd, addr) = unsafe {
            let null = null_mut();
            let fd   = shm_open(s.as_bytes().as_ptr() as *const c_char, O_RDWR, S_IRUSR | S_IWUSR);
            //let _res = ftruncate(fd, 128 as off_t);
            let addr = mmap(null, 4096, PROT_READ, MAP_SHARED, fd, 0);
            
            (fd, addr)
        };
        
        /*let c_str: &CStr = unsafe { CStr::from_ptr(s.as_ptr() as *const c_char) };
            let str_slice: &str = c_str.to_str().unwrap();
                let str_buf: String = str_slice.to_owned();
                println!("STORAGE ID {:?}", str_buf);*/

        let mut data = [0_u8; 4096];
        let pdata = data.as_mut_ptr() as *mut c_char;

        unsafe {
            strncpy(pdata, addr as *const c_char, 4096);
            close(fd);
        }
        println!("{}", std::str::from_utf8(&data)?);
        unsafe{
            let _res = ftruncate(fd, 4096 as off_t);
        }
    }
    Ok(())
}