# Presentation of FibHeap Operations.

## The overall FibHeap Usage Flowchart.

```flow
 st=>start: From ListNode into FibHeap.
 e=>end: The FibHeap functional execution ends.
 op1=>operation: void FibHeap::insert(*FibNode node)
 op2=>operation: void FibHeap::Pop_Min()
 op3=>operation: void FibHeap::consolidate()
 st->op1->op2->op3->e
 
```

![FibHeapPre](./FibHeapPre.png)

