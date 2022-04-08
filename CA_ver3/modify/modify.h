#pragma once
// Multiple head file only include once

// Include our head files
#include "../FibHeap/FibHeap.h"

extern void modify_operation(int modified_id, int information_type, int new_information, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* medium_risk_heap, FibHeap* high_risk_heap, FibHeap* withdraw_heap);

extern bool modify_for_main_and_ddl(FibNode* node_ddl, FibNode* node_main, int information_type, int new_information, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* medium_risk_heap, FibHeap* high_risk_heap);

extern bool modify_for_medium_risk(FibNode* node_medium, int information_type, int new_information, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* high_risk_heap);

extern bool modify_for_high_risk(FibNode* node_high, int information_type, int new_information, FibHeap* ddl_heap, FibHeap* main_heap, FibHeap* medium_risk_heap);

extern bool modify_for_withdraw(FibNode* node_withdraw, int information_type, int new_information);