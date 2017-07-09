use std::env;
use std::fs::File;
use std::io::BufReader;
use std::io::prelude::*;
use std::path::Path;

extern crate regex;
use regex::Regex;
use regex::Captures;

#[derive(Debug)]
struct Ops {
    name: String,
    sub_type: String,
    op_type: String,
    op_group: String,
    optype: String,
    typ: String,
    cfg: u32,
    hgc: u64,
    fgc: u64,
    hec: u64,
    fec: u64,
    igc: u64,
    vhc: String,
    vpc: String,
    cpu_time: f64,
    real_time: f64,
    elapsed_time: u64,
    scale_factor: f64,
    lvheap_used: u64,
    lvheap_allocated: u64,
    lvheap_max: u64,
    shared_used: u64,
    shared_allocated: u64
}

impl Ops {
    fn new() -> Ops {
        Ops {
            name: String::new(),
            sub_type: String::from("FullOp"),
            op_type: String::new(),
            op_group: String::new(),
            optype: String::new(),
            typ: String::new(),
            cfg: 0,
            hgc: 0,
            fgc: 0,
            hec: 0,
            fec: 0,
            igc: 0,
            vhc: String::new(),
            vpc: String::new(),
            cpu_time: 0.0,
            real_time: 0.0,
            elapsed_time: 0,
            scale_factor: 0.0,
            lvheap_used: 0,
            lvheap_allocated: 0,
            lvheap_max: 0,
            shared_used: 0,
            shared_allocated: 0
        }
    }
    
    fn init_op1(&mut self, caps: &Captures) {
        self.name = caps[1].to_string();
        self.optype = caps[2].to_string();
        self.typ = caps[3].to_string();
        self.cfg = caps[4].parse::<u32>().unwrap();
        self.hgc = caps[5].parse::<u64>().unwrap();
        self.fgc = caps[6].parse::<u64>().unwrap();
        self.hec = caps[7].parse::<u64>().unwrap();
        self.fec = caps[8].parse::<u64>().unwrap();
        self.igc = caps[9].parse::<u64>().unwrap();
        self.vhc = caps[10].to_string();
        self.vpc = caps[11].to_string();
    }

    // CPU TIME = 0  REAL TIME = 0, LVHEAP = 7059/7061/7061  SHARED = 0/0 - INIT_OPT 
    fn init_sub_op1(&mut self, caps: &Captures) {
        println!("sub_op1:{:?}", caps);
        self.sub_type = caps[5].to_string();
        self.cpu_time = caps[1].parse::<f64>().unwrap();
        self.real_time = caps[2].parse::<f64>().unwrap();
        self.scale_factor = if self.real_time!=0.0 { self.cpu_time / self.real_time } else { 0.0 };

        // Heap number collecting
        let heap = caps[3].to_string();
        let heaps: Vec<&str> = heap.split('/').collect();
        self.lvheap_used = heaps[0].parse::<u64>().unwrap();
        self.lvheap_allocated = heaps[1].parse::<u64>().unwrap();
        self.lvheap_max = heaps[2].parse::<u64>().unwrap();
        
        // Shared number collecting
        let shared = caps[4].to_string();
        let shareds: Vec<&str> = shared.split('/').collect();
        self.shared_used = shareds[0].parse::<u64>().unwrap();
        self.shared_allocated = shareds[1].parse::<u64>().unwrap();
    }
    
    // CPU TIME = 14  REAL TIME = 8 - PUSH_OUT
    fn init_sub_op2(&mut self, caps: &Captures) {
        println!("sub_op2:{:?}", caps);
        self.sub_type = caps[3].to_string();
        self.cpu_time = caps[1].parse::<f64>().unwrap();
        self.real_time = caps[2].parse::<f64>().unwrap();
        self.scale_factor = if self.real_time!=0.0 { self.cpu_time / self.real_time } else { 0.0 };
    }

    // CPU TIME = 2  REAL TIME = 2  LVHEAP = 3/5/5  OPS COMPLETE = 8 OF 16  ELAPSED TIME = 7
    fn add_op2(&mut self, caps: &Captures) {
        self.cpu_time = caps[1].parse::<f64>().unwrap();
        self.real_time = caps[2].parse::<f64>().unwrap();
        self.elapsed_time = caps[4].parse::<u64>().unwrap();
        self.scale_factor = if self.real_time!=0.0 { self.cpu_time / self.real_time } else { 0.0 };

        // Heap number collecting
        let heap = caps[3].to_string();
        let heaps: Vec<&str> = heap.split('/').collect();
        self.lvheap_used = heaps[0].parse::<u64>().unwrap();
        self.lvheap_allocated = heaps[1].parse::<u64>().unwrap();
        self.lvheap_max = heaps[2].parse::<u64>().unwrap();
    }
    
    // CPU TIME = 370  REAL TIME = 292  LVHEAP = 5/21/21  SHARED = 1/32  OPS COMPLETE = 15 OF 16  ELAPSED TIME = 299
    fn add_op3(&mut self, caps: &Captures) {
        self.cpu_time = caps[1].parse::<f64>().unwrap();
        self.real_time = caps[2].parse::<f64>().unwrap();
        self.elapsed_time = caps[5].parse::<u64>().unwrap();
        self.scale_factor = if self.real_time!=0.0 { self.cpu_time / self.real_time } else { 0.0 };

        // Heap number collecting
        let heap = caps[3].to_string();
        let heaps: Vec<&str> = heap.split('/').collect();
        self.lvheap_used = heaps[0].parse::<u64>().unwrap();
        self.lvheap_allocated = heaps[1].parse::<u64>().unwrap();
        self.lvheap_max = heaps[2].parse::<u64>().unwrap();
        
        // Shared number collecting
        let shared = caps[4].to_string();
        let shareds: Vec<&str> = shared.split('/').collect();
        self.shared_used = shareds[0].parse::<u64>().unwrap();
        self.shared_allocated = shareds[1].parse::<u64>().unwrap();
    }
}

fn main() {
    let args: Vec<String> = env::args().collect();
    if args.len()==1 {
        println!("Please provide input file.");
        return;
    }

    // ==============================================================================================
    // File existence checking
    let ref filename = args[1]; 
    if !Path::new(filename).exists() {
        println!("The provided file is not exist. Please check.");
        return;
    }

    // ==============================================================================================
    // Regular expression definition
    //
    // fSwissCheese (HIER TYP=1 CFG=1 HGC=322629 FGC=322629 HEC=1290516 FEC=1290516 IGC=585 VHC=F VPC=F)
    let op1 = Regex::new(r"(\S+) \((\S+) TYP=(\d+) CFG=(\d+) HGC=(\d+) FGC=(\d+) HEC=(\d+) FEC=(\d+) IGC=(\d+) VHC=(\w) VPC=(\w)\)").unwrap();

    // CPU TIME = 2  REAL TIME = 2  LVHEAP = 3/5/5  OPS COMPLETE = 8 OF 16  ELAPSED TIME = 7
    let op2 = Regex::new(r"CPU TIME = (\d+)  REAL TIME = (\d+)  LVHEAP = (\S+)  OPS COMPLETE = \d+ OF \d+  ELAPSED TIME = (\d+)").unwrap();

    // CPU TIME = 370  REAL TIME = 292  LVHEAP = 5/21/21  SHARED = 1/32  OPS COMPLETE = 15 OF 16  ELAPSED TIME = 299
    let op3 = Regex::new(r"CPU TIME = (\d+)  REAL TIME = (\d+)  LVHEAP = (\S+)  SHARED = (\S+)  OPS COMPLETE = \d+ OF \d+  ELAPSED TIME = (\d+)").unwrap();

    // CPU TIME = 0  REAL TIME = 0, LVHEAP = 7059/7061/7061  SHARED = 0/0 - INIT_OPT 
    let sub_op1 = Regex::new(r"WARNING:\s+CPU TIME = (\d+)  REAL TIME = (\d+), LVHEAP = (\S+)  SHARED = (\S+) - (\S+)").unwrap();

    // CPU TIME = 14  REAL TIME = 8 - PUSH_OUT
    let sub_op2 = Regex::new(r"CPU TIME = (\d+)  REAL TIME = (\d+).?\s? - (\S+)").unwrap();
    // ==============================================================================================

    // ==============================================================================================
    let mut sub_ops: Vec<Ops> = Vec::new();
    let mut last_ops: Vec<Ops> = Vec::new();
    let mut all_ops: Vec<Ops> = Vec::new();
    
    // Parsing
    let file = BufReader::new(File::open(filename).expect("Unable to open file"));
    for line in file.lines().filter_map(|result| result.ok()) {

        if !line.contains("CPU TIME") && !line.contains("FEC") {
            continue;
        }

        // Try sub operation parsing first
        if line.contains("WARNING") && !line.contains("REAL TIME = 0") {
            if sub_op1.is_match(&line) {
                let mut op = Ops::new();
                op.init_sub_op1(&sub_op1.captures(&line).unwrap());
                sub_ops.push(op);
                continue;
            } else if sub_op2.is_match(&line) {
                let mut op = Ops::new();
                op.init_sub_op2(&sub_op2.captures(&line).unwrap());
                sub_ops.push(op);
                continue;
            }
        }

        if op1.is_match(&line) {
            let mut op = Ops::new();
            let caps: Captures = op1.captures(&line).unwrap();
            op.init_op1(&caps);
            op.op_group = if last_ops.len()!=0 { last_ops[0].name.clone() } else { op.name.clone() };

            if sub_ops.len()!=0 { 
                for so in &mut sub_ops { 
                    so.init_op1(&caps);
                    
                    // Concat sub-op type
                    so.name.push_str(" - ");
                    so.name.push_str(&so.sub_type); 
                    
                    so.op_group = op.name.clone();
                }
                all_ops.append(&mut sub_ops);
                sub_ops.clear();
            }
            
            last_ops.push(op);
        } else { 
            if last_ops.len()==0{
                last_ops.clear();
                continue;
            }
            
            if op2.is_match(&line) {
                let caps: Captures = op2.captures(&line).unwrap();
                if caps[1].parse::<u64>().unwrap()!=0{
                    for ops in &mut last_ops{
                        ops.add_op2(&caps);
                    }
                    all_ops.append(&mut last_ops);
                }
                last_ops.clear();
            } else if op3.is_match(&line) {
                let caps: Captures = op3.captures(&line).unwrap();
                if caps[1].parse::<u64>().unwrap()!=0{
                    for ops in &mut last_ops{
                        ops.add_op3(&caps);
                    }
                    all_ops.append(&mut last_ops);
                }
                last_ops.clear();
            }
        }
    }

    for op in all_ops{
        println!("{:?}", op);
    }
}
