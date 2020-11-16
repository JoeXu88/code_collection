## test env
Architecture:          x86_64
<br>CPU op-mode(s):        32-bit, 64-bit
<br>Byte Order:            Little Endian
<br>CPU(s):                4
<br>On-line CPU(s) list:   0-3
<br>Thread(s) per core:    1
<br>Core(s) per socket:    4
<br>Socket(s):             1
<br>Vendor ID:             GenuineIntel
<br>CPU family:            6
<br>Model:                 60
<br>Model name:            Intel(R) Core(TM) i5-4590 CPU @ 3.30GHz
<br>Stepping:              3
<br>CPU MHz:               3301.000
<br>CPU max MHz:           3301.0000
<br>BogoMIPS:              6602.00
<br>Hypervisor vendor:     Windows Subsystem for Linux
<br>Virtualization type:   container


## test result
sem_cond TimeCost 8267us
<br>spin TimeCost 28084us
<br>atomic TimeCost 64084us


## conclusion
atomic is not always perform best. it will add too much memory barrier if we want to modify data, and caused too much cpu cost.
<br>we can consider condition valriable in most scene
<br>***but if we only read atomic value, it will much faster than spin lock(almost closed speed with raw value), because we do not modify data***
