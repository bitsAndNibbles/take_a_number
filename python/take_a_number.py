import threading
from time import time

num_threads = 20
desired_total = 100000000

start = time()

global counter
counter = 0
threads = []

def number_taker():
    global counter
    for _ in range(int(desired_total/num_threads)):
        counter += 1

for _ in range(num_threads):
    thread = threading.Thread(target=number_taker)
    thread.start()
    threads.append(thread)

for thread in threads:
    thread.join()

print(f"Result: {counter}; expected: {desired_total}")

end = time()
print(f"Elapsed: {end-start:.2f} seconds")
