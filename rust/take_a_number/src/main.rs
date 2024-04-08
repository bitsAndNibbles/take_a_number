use std::sync::{Arc, Mutex};
use std::thread;
use std::time::Instant;

fn main() {

    let num_threads = 6;
    let desired_total = 10000000000u64;

    let start = Instant::now();

    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];

    for _ in 0..num_threads {
        let counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {

            let mut local_num = 0;
            for _ in 0..(desired_total/num_threads) {
                local_num += 1u64;
            }

            let mut num = counter.lock().unwrap();

            // for _ in 0..(desired_total/num_threads) {
            //     *num += 1u64;
            // }
            *num += local_num;
        });
        handles.push(handle);
    }

    for handle in handles {
        handle.join().unwrap();
    }

    println!("Result: {}", *counter.lock().unwrap());

    let elapsed = start.elapsed();

    println!("Elapsed: {:.2?}", elapsed);
}
