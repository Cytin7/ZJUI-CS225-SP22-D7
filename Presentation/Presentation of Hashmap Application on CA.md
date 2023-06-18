# Presentation of Hashmap Application on CA

## Overall Flowchart for Hashmap Application

### Hashing Process: mainly via id to generate a hash map storing Record* pointer.

```flow
 st=>start: From file stream to class Record object
 e=>end: The Hashmap Hashing process ends.
 op1=>operation: template<class int, class Record*> void Hashmap<int,Record*>::add(int id, Record* ptr)
 st->op1->e
```

### Retrieve Process: basic traversal the map to generate a stream satisfying input constraints.

```flow
st=>start: Start to retrieve for certain class Record object.
e=>end: End retrieve and 
cout << info << endl;
loop=>condition: for (int id = Min(id);
id < Max(id);
id++)
cond1=>condition: Satisfy
retrieve condtion?
op1=>operation: info << hash_map->retrieve(key)->info.
op2=>operation: continue;
op3=>operation: fenzhi
st->loop
loop(no)->e
loop(yes)->cond1
cond1(yes)->op1(left)->loop
cond1(no)->op2->loop
```

