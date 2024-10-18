#  Bin packing with dual resources

Implementation of the first fit decreasing bin packing algorithm for dual resources.

Each bin has a capacity limit for two resources, each item occupies a specified amount of each resource when assigned to a bin.  The two independant sums of resources occupied by the items assigned to a bin must not exceed either of the bin resource limits.

# Example

This example focuses on Kubernetes, where efficient use of CPU and memory is critical for containerized applications.
```
All iems packed
node_3 contains: pod_1 pod_21 pod_19 pod_15
node_4 contains: pod_31 pod_7 pod_8 pod_28
node_2 contains: pod_24 pod_17 pod_32 pod_16 pod_36 pod_30 pod_29 pod_6 pod_34 pod_22 pod_9 pod_20 pod_38 pod_37 pod_12 pod_13 pod_25 pod_26 pod_4 pod_3 pod_33 pod_39
node_1 contains: pod_27 pod_35 pod_2 pod_5 pod_23 pod_18 pod_14 pod_11 pod_10 pod_40 

Total CPU and RAM % utilization for each node:
      Node Total_CPU_Used Total_RAM_Used  Node_CPU  Node_RAM CPU_Utilization RAM_Utilization
    node_1             28             22       256       512              10               4
    node_2            128            138       128       512             100              26
    node_3             32             64        32        64             100             100
    node_4             14             64        32        64              43             100
```
