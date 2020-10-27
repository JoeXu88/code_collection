## test env
Architecture:          x86_64
CPU op-mode(s):        32-bit, 64-bit
Byte Order:            Little Endian
CPU(s):                4
On-line CPU(s) list:   0-3
Thread(s) per core:    1
Core(s) per socket:    4
Socket(s):             1
Vendor ID:             GenuineIntel
CPU family:            6
Model:                 60
Model name:            Intel(R) Core(TM) i5-4590 CPU @ 3.30GHz
Stepping:              3
CPU MHz:               3301.000
CPU max MHz:           3301.0000
BogoMIPS:              6602.00
Hypervisor vendor:     Windows Subsystem for Linux
Virtualization type:   container


## test result
sem_cond TimeCost 8267us
spin TimeCost 28084us
atomic TimeCost 64084us


## conclusion
atomic is not always perform best. it will add too much memory barrier, and caused too much cpu cost.
we can consider condition valriable in most scene
