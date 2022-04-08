#pragma once
// Multiple head file only include once

// Include libraries
#include <fstream>
#include <sstream>

// Include our head files
#include "../ListNode/ListNode.h"
#include "../Print Functions/Print Functions.h"

string DatetimeToString(time_t time);
int name_sort(ListNode& treat_list, ListNode& risk_list, ListNode& waiting, ListNode& left_list);
int age_sort(ListNode& treat_list, ListNode& risk_list, ListNode& waiting, ListNode& left_list);
int profession_sort(ListNode& treat_list, ListNode& risk_list, ListNode& waiting, ListNode& left_list);
void List_report(ListNode& List, string file_name);
int month_report(ListNode& List, int month, int reginum, int waitnum, int waitnum_total, int appointnum, int withdrawnum, int averagetime);
int week_report(ListNode& treat_list, ListNode& risk_list, ListNode& waiting, ListNode& left_list, int week);