### Computer Architecture Gem5 Project

> **Zervos Ioannis:** 2017030036
> **Voulgari Kallirroi:** 2018030107
> **Team:** 11

**Introduction**
The final project of Computer Architecture course required the installation of a simulation system, Gem5. Gem5 supports two basic simulation modes, System call Emulation and Full System. At this project, SE will be used, as only the processor and the memory subsystems is needed.

**1.** Results from **starter_se.py:**
For the creation of Hello World example, the command on the terminal takes as argument the directory of the file and the CPU type. The choice for the type is among: atomic, hpi and minor, with the main difference being the number and type of caches. For this example, **minor type CPU** was selected, with one **level-2 cache and two level-1 caches**, one for the instructions and one for the data. The file starter_se, instantiates the necessary hardware for the simulation to run. Other data that arise from this file is the CPU frequency set at 4GHz (default). Also, the main memory is a DDR3(8x8), working at 1600MHz and default capacity at 2 GB.

**2. a)** From the Hello World example, a config.ini file was created, which confirms some of the information above.

Firstly, the CPU type is “minor”:
```
[system.cpu_cluster.cpus]
type=BaseMinorCPU
```
**Instruction Level-1 cache (some characteristics):**
```
[system.cpu_cluster.cpus.icache]
type=Cache
is_read_only=true
size=49152
mem_side=system.cpu_cluster.toL2Bus.cpu_side_ports[0]
```
**Data Level-1 cache (some characteristics):**
```
[system.cpu_cluster.cpus.dcache]
type=Cache
is_read_only=false
size=32768
mem_side=system.cpu_cluster.toL2Bus.cpu_side_ports[1]
```
Instruction cache is accessible only for reads, while the data has the right to be written and read. Each Level-1 cache is connected to different ports at the L2 bus.

**Level-2 cache (some characteristics):**
```
[system.cpu_cluster.l2]
type=Cache
is_read_only=false
size=1048576
mem_side=system.membus.cpu_side_ports[1]
```
Level-2 cache has larger capacity than the level- 1 ones. It is also connected to a membus.

**CPU frequency:**
As said before, CPU works at 4GHz by default.
```
[system.cpu_cluster.clk_domain]
clock=250
```
Clock = 250ps => Frequency = 4GHz
**b)** The total number of committed instructions is 5028. During the run time, micro operations are added to the execution process. For this reason, the total number of operations performed by the CPU is 5834. These micro-ops are caused by the complexity of the machine instructions and the possible branch miss predictions.
```
system.cpu_cluster.cpus.numInsts           5028  # Number of instructions committed (Count)
system.cpu_cluster.cpus.numOps             5834  # Number of ops (including micro ops) committed (Count)
system.cpu_cluster.cpus.numDiscardedOps    1333  # Number of ops (including micro ops) which were discarded before commit (Count)
```
**c)** Level-2 cache was accessed 479 time by the two level-1 caches. 332 times by Instruction and 147 by Data.
```
system.cpu_cluster.l2.overallMisses::cpu_cluster.cpus.inst   332     # number of overall misses (Count)
system.cpu_cluster.l2.overallMisses::cpu_cluster.cpus.data   147     # number of overall misses (Count)
system.cpu_cluster.l2.overallMisses::total                   479     # number of overall misses (Count)
```
In case there was no counter by the Level-2, this operand could be completed by the addition of demand misses of the two other caches.
```
system.cpu_cluster.cpus.icache.demandMisses::total          332
system.cpu_cluster.cpus.dcache.demandMshrMisses::total      147
```
**3.** Gem5’s in-order CPU models:

**SimpleCPU:**
The simple CPU is an in-order model. It does not offer a high level of sophistication making more well suited for program testing. The SimpleCPU is, now, further divided in three more implementations:

**BaseSimpleCPU:** This implementation works in a similar way as the older SimpleCPU. It has functions for interrupt check up, fetch requests, and the handling of pre and post execute activities. Lastly, it is worth mentioning that this type of CPU is incapable of running on its own, as it needs some classes to be inherited from other CPUs.

**AtomicSimpleCPU:** This specialization contains functions for reading and writing in memory coupled with estimation of cache access time, in order to the overall atomic access time of the run time.

**TimingSimpleCPU:** Similarly to the atomic version, this implementation contains functions for the reading and writing of data in the memory. The difference is that the data access instructions are stalled until the memory system has responded to a previous request.

**Minor CPU:**
Minor CPU is a strict in-order execution behavioral processor. Even though it uses a 4-stage fixed pipeline, there is freedom with the customization of the data structures and execution behavior. The intention is to provide a structure for micro-architecturally correlating the model with a chosen processor with similar capabilities.

  
**a)** For the simulation, a new c program was created, that calculates the determinant of a 2x2 matrix. The c file was converted to be executable by the ARM processor and then it was tested by different CPU types.
**b) 
Minor Results:**
* works at 2GHz
* Simulation time: 0.000034s
* CPI: 7.760209
* Number of instructions simulated: 8816

**SimpleTiming:**
 * works at 1GHz
*  Simulation time: 0.000040s
* CPI: 4.565167
* Number of instructions simulated: 8762

As it is shown in the measurement above the minor CPU yields slightly better results as the execution time is a little smaller. In reality the minor CPU was expected to outperform the simple timing one by a factor close to 2 due to the pipeline, as a pipelined system is able to reach higher clock frequencies.  The results are so similar because of the cache accesses as both possessors stall until the completion of the cache access operation although this hurts the performance of both processors, the minor suffers the most as the amount of stalling negates the higher frequency capability of the minor CPU. 
