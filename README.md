![cover-philosophers](https://github.com/user-attachments/assets/1a63d0e4-43d0-4b64-9ee6-a4e4ddfb7107)

<div align="center">
  <strong>Score: 100/100</strong><br>
  <strong>Finished: 13.11.2024</strong>
</div>

# Philosophers

The dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

### Installation

```plaintext
git clone https://github.com/mhummel7/philo.git philo && cd philo
```

```plaintext
make
```

### Usage
```plaintext
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

Arguments:
number_of_philosophers: (The number of philosophers (1-200)
time_to_die:            (Time in milliseconds until a philosopher dies from starvation)
ime_to_eat:             (Time in milliseconds it takes for a philosopher to eat)
time_to_sleep:          (Time in milliseconds a philosopher spends sleeping)

(Optional)
number_of_times_each_philosopher_must_eat: (Simulation stops after all philosophers eat this many times)

Example:
./philo 5 800 200 200 7
```
    
### Example

<img width="860" alt="philo picture" src="https://github.com/user-attachments/assets/5fd32647-3111-444d-bba9-f4e0b64f6e6d">
