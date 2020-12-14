## Part 2 - Configuration and study of a network

### Cabling
tux33-E0 ↔ switch/1  
tux34-E0 ↔ switch/2  
tux32-E0 ↔ switch/3  
tux34-E1 ↔ switch/4  
3.1 ↔ Router GE0/1  
Router GE0/0 ↔ switch/5  

#### To configure switch
tux32-S0 ↔ T3 (crossover RS232)  
T4 (crossover RS232) ↔ Switch Console

#### To configure router
tux32-S0 ↔ T3 (crossover RS232)  
T4 (crossover RS232) ↔ Router Console

### Configuring

```sh
part2/config/tuxy2_config.sh 3 eth0
part2/config/tuxy3_config.sh 3 eth0
part2/config/tuxy4_config.sh 3 eth0 eth2
```

Then configure switch and router.

```sh
part2/config/tuxy_test.sh 3
```
