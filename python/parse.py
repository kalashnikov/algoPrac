import re
import sys 
import pandas as pd

if len(sys.argv) == 1: 
    print("Please provide input file.")
    exit()

input_file = sys.argv[1];

class Ops:
    # match op1 to create object for each calibre operations  
    def __init__(self, name, optype, cfg, typ, hgc, fgc, hec, fec, igc, vhc, vpc):
        self.name = name
        self.optype = optype
        self.typ = typ
        self.cfg = cfg
        self.hgc = hgc
        self.fgc = fgc
        self.hec = hec
        self.fec = fec
        self.igc = igc
        self.vhc = vhc
        self.vpc = vpc
       
        # Reset 
        self.cpu_time  = 0.0 
        self.real_time = 0.0 
        self.lvheap = ""  
        self.shared = "" 
        self.elapsed_time = 0 

        # calculated number
        self.scale_factor = 0.0
    
    def add_op2(self, cpu_time, real_time, lvheap, elapsed_time):
        self.cpu_time = float(cpu_time)
        self.real_time = float(real_time)
        self.lvheap = lvheap
        self.elapsed_time = float(elapsed_time)
        self.scale_factor = self.cpu_time / self.real_time  if self.real_time and self.real_time is not None else 0

    def add_op3(self, cpu_time, real_time, lvheap, shared, elapsed_time):
        self.cpu_time = float(cpu_time)
        self.real_time = float(real_time)
        self.lvheap = lvheap
        self.shared = shared
        self.elapsed_time = float(elapsed_time)
        self.scale_factor = self.cpu_time / self.real_time if self.real_time and self.real_time is not None else 0

    def to_dict(self):
        return {
            'name': self.name,
            'optype': self.optype,
            'cfg': self.cfg,
            'typ': self.typ,
            'hgc': self.hgc,
            'fgc': self.fgc,
            'hec': self.hec,
            'fec': self.fec,
            'igc': self.igc,
            'vhc': self.vhc,
            'vpc': self.vpc,
            'cpu_time': self.cpu_time,
            'real_time': self.real_time,
            'scale_factor': self.scale_factor,
            'lvheap': self.lvheap,
            'shared': self.shared,
            'elapsed_time': self.elapsed_time
        }

    def __str__(self):
        return '### {} ### | Type({}, {}, {}), Geometry#({}, {}), Edge#({}, {}), igc:{}, VHC:{}, VPC:{}\n\
                | CPU TIME: {}, REAL TIME: {}, Scale: {:.2f}, LVHEAP: {}, SHARED: {}, ELAPSED TIME: {}'.format(
            self.name, self.optype, self.cfg, self.typ, 
            self.hgc, self.fgc, self.hec, self.fec, self.igc, self.vhc, self.vpc, 
            self.cpu_time, self.real_time, self.scale_factor, self.lvheap, self.shared, self.elapsed_time)


all_ops = []
last_ops = []

# fSwissCheese (HIER TYP=1 CFG=1 HGC=322629 FGC=322629 HEC=1290516 FEC=1290516 IGC=585 VHC=F VPC=F)
op1 = re.compile('(\S+) \((\S+) TYP=(\d+) CFG=(\d+) HGC=(\d+) FGC=(\d+) HEC=(\d+) FEC=(\d+) IGC=(\d+) VHC=(\w) VPC=(\w)\)')

# CPU TIME = 2  REAL TIME = 2  LVHEAP = 3/5/5  OPS COMPLETE = 8 OF 16  ELAPSED TIME = 7
op2 = re.compile('CPU TIME = (\d+)  REAL TIME = (\d+)  LVHEAP = (\S+)  OPS COMPLETE = \d+ OF \d+  ELAPSED TIME = (\d+)')

# CPU TIME = 370  REAL TIME = 292  LVHEAP = 5/21/21  SHARED = 1/32  OPS COMPLETE = 15 OF 16  ELAPSED TIME = 299
op3 = re.compile('CPU TIME = (\d+)  REAL TIME = (\d+)  LVHEAP = (\S+)  SHARED = (\S+)  OPS COMPLETE = \d+ OF \d+  ELAPSED TIME = (\d+)')

with open(input_file, "r") as f:
    for line in f:
        if "CPU TIME" not in line and "FEC" not in line: 
            continue;
        
        if "WARNING" in line: 
            continue;

        l = line.strip()
        result1 = op1.match(l)
        result2 = op2.match(l)
        result3 = op3.match(l)

        # Operation information 
        if result1:
            op = Ops(*result1.groups())
            last_ops.append(op)
        else: 
            if len(last_ops)==0:
                last_ops.clear()
                continue

            if result2:     # Operation statistic 
                if int(result2.group(2))!=0:
                    for ops in last_ops: 
                        ops.add_op2(*result2.groups())
                        all_ops.append(ops)

                last_ops.clear()

            elif result3:   # Operation statistic 
                if int(result3.group(2))!=0:
                    for ops in last_ops: 
                        ops.add_op3(*result3.groups())
                        all_ops.append(ops)

                last_ops.clear()


print("######### Print Operations #########")

all_ops.sort(key=lambda x: x.real_time)

for ops in all_ops:
    print(ops)

df = pd.DataFrame.from_records([op.to_dict() for op in all_ops])
